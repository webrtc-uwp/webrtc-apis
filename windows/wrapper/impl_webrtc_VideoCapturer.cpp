
#ifdef _WIN32
#include <WinSock2.h>
#include <unknwn.h>
#endif //_WIN32

#include "impl_webrtc_VideoCapturer.h"
#include "impl_org_webRtc_VideoFrameBufferEvent.h"
#include "impl_org_webRtc_VideoFrameNativeBuffer.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/video/video_frame_buffer.h"
#include "rtc_base/refcountedobject.h"
#include "third_party/winuwp_h264/native_handle_buffer.h"
#include "impl_org_webRtc_post_include.h"

#ifdef CPPWINRT_VERSION

#include <ppltasks.h>

#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <Mferror.h>

#include <zsLib/String.h>
#include <zsLib/IMessageQueueThread.h>

#include "impl_org_webRtc_MediaSample.h"
#include "impl_org_webRtc_WebrtcLib.h"
#include "impl_webrtc_MRCAudioEffectDefinition.h"
#include "impl_webrtc_MRCVideoEffectDefinition.h"

#include <wrapper/impl_org_webRtc_pre_include.h>
#include "media/base/videocommon.h"
#include "rtc_base/logging.h"
#include "rtc_base/Win32.h"
#include "libyuv/planar_functions.h"
#include "common_video/libyuv/include/webrtc_libyuv.h"
#include "api/video/i420_buffer.h"
#include <wrapper/impl_org_webRtc_post_include.h>

#include <winrt/windows.media.capture.h>
#include <winrt/windows.media.capture.frames.h>
#include <winrt/windows.devices.enumeration.h>
#include <winrt/windows.system.profile.h>

#include <mfapi.h>

using zsLib::String;
using zsLib::Time;
using zsLib::Seconds;
using zsLib::Milliseconds;
using zsLib::AutoRecursiveLock;

using winrt::Windows::Devices::Enumeration::DeviceClass;
using winrt::Windows::Devices::Enumeration::DeviceInformation;
using winrt::Windows::Devices::Enumeration::DeviceInformationCollection;
using winrt::Windows::Devices::Enumeration::Panel;
using winrt::Windows::Graphics::Display::DisplayOrientations;
using winrt::Windows::Graphics::Display::DisplayInformation;
using winrt::Windows::Media::Capture::MediaCapture;
using winrt::Windows::Media::Capture::MediaCaptureFailedEventArgs;
using winrt::Windows::Media::Capture::MediaCaptureFailedEventHandler;
using winrt::Windows::Media::Capture::MediaCaptureInitializationSettings;
using winrt::Windows::Media::Capture::MediaStreamType;
using winrt::Windows::Media::IMediaExtension;
using winrt::Windows::Media::MediaProperties::IVideoEncodingProperties;
using winrt::Windows::Media::MediaProperties::MediaEncodingProfile;
using winrt::Windows::Media::MediaProperties::MediaEncodingSubtypes;
using winrt::Windows::Media::MediaProperties::VideoEncodingProperties;
using winrt::Windows::UI::Core::DispatchedHandler;
using winrt::Windows::UI::Core::CoreDispatcherPriority;
using winrt::Windows::Foundation::IAsyncAction;
using winrt::Windows::Foundation::TypedEventHandler;
using winrt::Windows::System::Threading::ThreadPoolTimer;
using winrt::Windows::System::Threading::TimerElapsedHandler;
using winrt::Windows::Foundation::Collections::IVectorView;

using namespace cricket;

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::WebRtcLib, UseWebrtcLib);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFrameNativeBuffer, UseVideoFrameNativeBuffer);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFrameBufferEvent, UseVideoFrameBufferEvent);

namespace webrtc
{
  // Used to store a IMFSample native handle buffer for a VideoFrame
  class MFNativeHandleBuffer : public NativeHandleBuffer {
  public:
    MFNativeHandleBuffer(
      cricket::FourCC fourCC,
      const winrt::com_ptr<IMFSample> &sample,
      rtc::scoped_refptr<I420BufferInterface> &i420Buffer,
      int width,
      int height) :
      NativeHandleBuffer(sample.get(), width, height),
      fourCC_(fourCC),
      sample_(sample),
      i420Buffer_(i420Buffer)
    {
    }

    virtual ~MFNativeHandleBuffer() {
    }

    rtc::scoped_refptr<I420BufferInterface> ToI420() override {
      return i420Buffer_;
    }

    virtual cricket::FourCC fourCC() const { return fourCC_; }

  private:
    cricket::FourCC fourCC_{};
    winrt::com_ptr<IMFSample> sample_;
    rtc::scoped_refptr<I420BufferInterface> i420Buffer_;
  };

  //-----------------------------------------------------------------------------
  class DisplayOrientation {
  public:
    virtual ~DisplayOrientation();

  public:
    DisplayOrientation(DisplayOrientationListener* listener);
    void OnOrientationChanged(
      winrt::Windows::Graphics::Display::DisplayInformation const& sender,
      winrt::Windows::Foundation::IInspectable const& args);

    winrt::Windows::Graphics::Display::DisplayOrientations Orientation() { return orientation_; }
  private:
    DisplayOrientationListener * listener_;
    winrt::Windows::Graphics::Display::DisplayInformation display_info_{ nullptr };
    winrt::Windows::Graphics::Display::DisplayOrientations orientation_
      { winrt::Windows::Graphics::Display::DisplayOrientations::None };
    winrt::event_token orientation_changed_registration_token_;
  };

  //-----------------------------------------------------------------------------
  DisplayOrientation::~DisplayOrientation() {
    auto tmpDisplayInfo = display_info_;
    auto tmpToken = orientation_changed_registration_token_;
    if (tmpDisplayInfo != nullptr) {
      auto queue = UseWebrtcLib::delegateQueue();
      ZS_ASSERT(queue);
      queue->postClosure([tmpDisplayInfo, tmpToken]() {
        tmpDisplayInfo.OrientationChanged(tmpToken);
      });  // Run async because it can deadlock with core thread.
    }
  }

  //-----------------------------------------------------------------------------
  DisplayOrientation::DisplayOrientation(DisplayOrientationListener* listener)
    : listener_(listener) {
    auto queue = UseWebrtcLib::delegateQueue();
    ZS_ASSERT(queue);
    // GetForCurrentView() only works on a thread associated with
    // a CoreWindow.  If this doesn't work because we're running in
    // a background task then the orientation needs to come from the
    // foreground as a notification.
    if (queue->isCurrentThread()) {
      try {
        display_info_ = DisplayInformation::GetForCurrentView();
        orientation_ = display_info_.CurrentOrientation();
        orientation_changed_registration_token_ =
          display_info_.OrientationChanged(
            TypedEventHandler<DisplayInformation,
            winrt::Windows::Foundation::IInspectable>(this, &DisplayOrientation::OnOrientationChanged));
      } catch (...) {
        display_info_ = nullptr;
        orientation_ = winrt::Windows::Graphics::Display::DisplayOrientations::Portrait;
        RTC_LOG(LS_ERROR) << "DisplayOrientation could not be initialized.";
      }
    } else {
      std::mutex mutex;
      std::condition_variable condition_variable;
      queue->postClosure([this, &condition_variable]() {
        try {
          display_info_ = DisplayInformation::GetForCurrentView();
          orientation_ = display_info_.CurrentOrientation();
          orientation_changed_registration_token_ =
            display_info_.OrientationChanged(
              TypedEventHandler<DisplayInformation,
              winrt::Windows::Foundation::IInspectable>(this, &DisplayOrientation::OnOrientationChanged));
        } catch (...) {
          display_info_ = nullptr;
          orientation_ = winrt::Windows::Graphics::Display::DisplayOrientations::Portrait;
          RTC_LOG(LS_ERROR) << "DisplayOrientation could not be initialized.";
        }
        condition_variable.notify_one();
      });
      {
        std::unique_lock<std::mutex> lock(mutex);
        condition_variable.wait(lock);
      }
    }
  }

  //-----------------------------------------------------------------------------
  void DisplayOrientation::OnOrientationChanged(DisplayInformation const& sender,
    winrt::Windows::Foundation::IInspectable const& /*args*/) {
    orientation_ = sender.CurrentOrientation();
    if (listener_)
      listener_->OnDisplayOrientationChanged(sender.CurrentOrientation());
  }

  //-----------------------------------------------------------------------------
  class CaptureDevice : public ISinkCallback {
  public:

    static winrt::hstring GetVideoSubtype(uint32_t fourcc);

    static uint32_t GetFourCC(winrt::hstring const& subtype);

    CaptureDevice(CaptureDeviceListener* capture_device_listener);

    virtual ~CaptureDevice();

    void Initialize(winrt::hstring const& device_id, winrt::hstring const& video_profile_id,
      int width, int height, double framerate);

    void CleanupSink();

    void CleanupMediaCapture();

    void Cleanup();

    void StartCapture(winrt::Windows::Media::MediaProperties::MediaEncodingProfile const& media_encoding_profile,
      winrt::Windows::Media::MediaProperties::IVideoEncodingProperties const& video_encoding_properties,
      bool mrc_enabled);

    void StopCapture();

    bool CaptureStarted() { return capture_started_; }

    VideoFormat GetFrameInfo() { return frame_info_; }

    void OnCaptureFailed(winrt::Windows::Media::Capture::MediaCapture const&  sender,
      winrt::Windows::Media::Capture::MediaCaptureFailedEventArgs const& error_event_args);

    void OnSample(winrt::com_ptr<IMFSample> &sample) override;

    void OnShutdown() override;

    winrt::agile_ref<winrt::Windows::Media::Capture::MediaCapture> GetMediaCapture();

    void CleanupMixedRealityCapture();

    bool HasVideoCaptureHolographicCapabilities() {
      if (audio_effect_added_) {
        return true;
      }
      if (video_effect_added_) {
        return true;
      }
      return false;
    }

  private:
    bool FindAndAddVideoProfile(MediaCaptureInitializationSettings& settings);
    void RemovePaddingPixels(uint8_t* video_frame, size_t& video_frame_length);

  private:
    winrt::agile_ref<winrt::Windows::Media::Capture::MediaCapture> media_capture_;
    winrt::hstring device_id_;
    winrt::hstring video_profile_id_;
    winrt::com_ptr<IMFMediaSink> media_sink_;
    winrt::event_token
      media_capture_failed_event_registration_token_;
    winrt::event_token
      media_sink_video_sample_event_registration_token_;

    CaptureDeviceListener* capture_device_listener_;

    /// Constraints for video profile selection
    int width_;
    int height_;
    double framerate_;

    bool audio_effect_added_;
    bool video_effect_added_;
    bool capture_started_;
    VideoFormat frame_info_;
    std::unique_ptr<webrtc::EventWrapper> _stopped;
  };

  //-----------------------------------------------------------------------------
  winrt::hstring CaptureDevice::GetVideoSubtype(uint32_t fourcc)
  {
    winrt::hstring subtype;
    switch (fourcc) {
    case FOURCC_YV12:
      subtype = MediaEncodingSubtypes::Yv12();
      break;
    case FOURCC_YUY2:
      subtype = MediaEncodingSubtypes::Yuy2();
      break;
    case FOURCC_I420:
    case FOURCC_IYUV:
      subtype = MediaEncodingSubtypes::Iyuv();
      break;
    case FOURCC_24BG:
      subtype = MediaEncodingSubtypes::Rgb24();
      break;
    case FOURCC_ARGB:
      subtype = MediaEncodingSubtypes::Argb32();
      break;
    case FOURCC_MJPG:
      subtype = MediaEncodingSubtypes::Mjpg();
      break;
    case FOURCC_NV12:
      subtype = MediaEncodingSubtypes::Nv12();
      break;
    default:
      break;
    }
    return subtype;
  }

  //-----------------------------------------------------------------------------
  uint32_t CaptureDevice::GetFourCC(winrt::hstring const& subtype)
  {
    uint32_t fourcc;
    if (_wcsicmp(subtype.c_str(),
      MediaEncodingSubtypes::Yv12().c_str()) == 0) {
      fourcc = FOURCC_YV12;
    } else if (_wcsicmp(subtype.c_str(),
      MediaEncodingSubtypes::Yuy2().c_str()) == 0) {
      fourcc = FOURCC_YUY2;
    } else if (_wcsicmp(subtype.c_str(),
      MediaEncodingSubtypes::Iyuv().c_str()) == 0) {
      fourcc = FOURCC_IYUV;
    } else if (_wcsicmp(subtype.c_str(),
      MediaEncodingSubtypes::Rgb24().c_str()) == 0) {
      fourcc = FOURCC_24BG;
    } else if (_wcsicmp(subtype.c_str(),
      MediaEncodingSubtypes::Rgb32().c_str()) == 0) {
      fourcc = FOURCC_ARGB;
    } else if (_wcsicmp(subtype.c_str(),
      MediaEncodingSubtypes::Mjpg().c_str()) == 0) {
      fourcc = FOURCC_MJPG;
    } else if (_wcsicmp(subtype.c_str(),
      MediaEncodingSubtypes::Nv12().c_str()) == 0) {
      fourcc = FOURCC_NV12;
    } else {
      fourcc = FOURCC_ANY;
    }
    return fourcc;
  }

  //-----------------------------------------------------------------------------
  CaptureDevice::CaptureDevice(
    CaptureDeviceListener* capture_device_listener)
    : media_capture_(nullptr),
    capture_device_listener_(capture_device_listener),
    capture_started_(false),
    audio_effect_added_(false),
    video_effect_added_(false) {
    _stopped.reset(webrtc::EventWrapper::Create());
    _stopped->Set();
  }

  //-----------------------------------------------------------------------------
  CaptureDevice::~CaptureDevice() {
  }

  //-----------------------------------------------------------------------------
  void CaptureDevice::Initialize(winrt::hstring const& device_id,
                                 winrt::hstring const& video_profile_id,
                                 int width,
                                 int height,
                                 double framerate) {
    RTC_LOG(LS_INFO) << "CaptureDevice::Initialize";
    device_id_ = device_id;
    video_profile_id_ = video_profile_id;
    width_ = width;
    height_ = height;
    framerate_ = framerate;
  }

  //-----------------------------------------------------------------------------
  void CaptureDevice::CleanupSink() {
    if (media_sink_ != nullptr) {
      media_sink_->Shutdown();
      media_sink_ = nullptr;
      capture_started_ = false;
    }
  }

  //-----------------------------------------------------------------------------
  void CaptureDevice::CleanupMediaCapture() {
    if (media_capture_) {
      CleanupMixedRealityCapture();
      winrt::Windows::Media::Capture::MediaCapture media_capture = media_capture_.get();
      media_capture.Failed(media_capture_failed_event_registration_token_);
      media_capture_ = nullptr;
    }
  }

  //-----------------------------------------------------------------------------
  void CaptureDevice::Cleanup() {
    if (!media_capture_) {
      return;
    }
    winrt::Windows::Media::Capture::MediaCapture media_capture = media_capture_.get();
    if (capture_started_) {
      if (_stopped->Wait(5000) == kEventTimeout) {
        Concurrency::create_task([this, media_capture]() {
          media_capture.StopRecordAsync().get();
        }).then([this](Concurrency::task<void> async_info) {
          try {
            async_info.get();
            CleanupSink();
            CleanupMediaCapture();
            device_id_.clear();
            _stopped->Set();
          } catch (winrt::hresult_error const& /*e*/) {
            CleanupSink();
            CleanupMediaCapture();
            device_id_.clear();
            _stopped->Set();
            throw;
          }
        }).wait();
      }
    } else {
      CleanupSink();
      CleanupMediaCapture();
      device_id_.clear();
    }
  }

  //-----------------------------------------------------------------------------
  void CaptureDevice::CleanupMixedRealityCapture() {
    Concurrency::task<void> cleanEffectTask;
    if (video_effect_added_) {
      // Clear effects in videoRecord stream
      cleanEffectTask = Concurrency::create_task([this]() {
        return media_capture_.get().ClearEffectsAsync(winrt::Windows::Media::Capture::MediaStreamType::VideoRecord).get();
      }).then([this]() {
        OutputDebugString(L"VideoEffect removed\n");
        video_effect_added_ = false;
      });
      cleanEffectTask.wait();
    }
    return;
  }

  //-----------------------------------------------------------------------------
  void CaptureDevice::StartCapture(
    MediaEncodingProfile const& media_encoding_profile,
    IVideoEncodingProperties const& video_encoding_properties,
    bool mrc_enabled) {
    // Ensure StartCapture() is not called twice
    if (capture_started_) {
      winrt::throw_hresult(ERROR_INVALID_STATE);
    }

    // Ensure StopCapture() terminated, and capture device is ready to start again
    if (_stopped->Wait(5000) == kEventTimeout) {
      winrt::throw_hresult(ERROR_INVALID_STATE);
    }

    if (device_id_.empty()) {
      RTC_LOG(LS_WARNING) << "Capture device is not initialized.";
      return;
    }

    // Construct the WebRTC frame info from the media encoding profile of the
    // video stream coming out of the encoder, which is the same as the encoding
    // coming out of the MF pipeline since the custom sink doesn't change the
    // encoding of the video stream (it is just an adapter).
    int width = media_encoding_profile.Video().Width();
    int height = media_encoding_profile.Video().Height();
    int fps =
      static_cast<int>(
        static_cast<float>(
          media_encoding_profile.Video().FrameRate().Numerator()) /
        static_cast<float>(
          media_encoding_profile.Video().FrameRate().Denominator()));
    int64_t interval = VideoFormat::FpsToInterval(fps);
    uint32_t fourcc = GetFourCC(media_encoding_profile.Video().Subtype());
    frame_info_.Construct(width, height, interval, fourcc);

    RTC_LOG(LS_INFO) << "Starting device capture with sink video format "
                     << rtc::ToUtf8(media_encoding_profile.Video().Subtype().c_str())
                     << " (" << width << " x " << height << " @ " << fps
                     << " FPS)";

    // MediaCapture must have been initialized, which must be the case since it's
    // needed to select the media encoding profile passed to this method. So ensure
    // the existing one is reused, and do not create a new one.
    if (!media_capture_.get()) {
      RTC_LOG(LS_ERROR)
          << "StartCapture called with uninitialized MediaCapture object.";
      winrt::throw_hresult(ERROR_INVALID_STATE);
    }
    media_capture_failed_event_registration_token_ =
      media_capture_.get().Failed(
        MediaCaptureFailedEventHandler(this,
        &CaptureDevice::OnCaptureFailed));

#ifdef WIN10
    // Tell the video device controller to optimize for Low Latency then Power consumption
    media_capture_.get().VideoDeviceController().DesiredOptimization(
      winrt::Windows::Media::Devices::MediaCaptureOptimization::LatencyThenPower);
#endif

    auto initTask = Concurrency::create_task([this, media_encoding_profile]() {
      // Create the custom sink reading frames for the MF pipeline
      IVideoCaptureMediaSink::CreationProperties info;
      info.encodingProperties_ = media_encoding_profile.Video();
      info.callback_ = this;
      IMediaExtension mediaExtension = IVideoCaptureMediaSink::create(info);
      if (!mediaExtension) {
        winrt::throw_hresult(E_NOINTERFACE);
      }
      mediaExtension.as(media_sink_);
      return mediaExtension;
    }).then([this, media_encoding_profile,
        video_encoding_properties, mrc_enabled](IMediaExtension const& media_extension) {
      // Add MRC if the device supports it and caller requested it
      winrt::hstring deviceFamily = winrt::Windows::System::Profile::AnalyticsInfo::VersionInfo().DeviceFamily();
      if (std::wstring(deviceFamily.c_str()).compare((L"Windows.Holographic")) == 0 && mrc_enabled) {
        MrcVideoEffectDefinition mrcVideoEffectDefinition;
        mrcVideoEffectDefinition.StreamType(MediaStreamType::VideoRecord);
        auto addEffectTask = Concurrency::create_task([this, &mrcVideoEffectDefinition]() {
          return media_capture_.get().AddVideoEffectAsync(mrcVideoEffectDefinition, MediaStreamType::VideoRecord).get();
        }).then([this](IMediaExtension const& /* videoExtension */)
        {
          OutputDebugString(L"VideoEffect Added\n");
          video_effect_added_ = true;
        });
        Concurrency::create_task(addEffectTask).wait();
      }
      return Concurrency::create_task([this, video_encoding_properties]() {
        // Configure the capture device to output raw frames
        // with the media type previously selected
        return media_capture_.get().VideoDeviceController().SetMediaStreamPropertiesAsync(
          MediaStreamType::VideoRecord, video_encoding_properties).get();
        }).then([this, media_encoding_profile, media_extension]() {
        return Concurrency::create_task([this, media_encoding_profile, media_extension]() {
          // Start capturing, and encode device frames into the
          // specified format that the custom sink expects so it
          // can deliver them as is to the rest of WebRTC
          return media_capture_.get().StartRecordToCustomSinkAsync(
            media_encoding_profile, media_extension).get();
          });
      });
    });

    initTask.then([this](Concurrency::task<void> async_info) {
      try {
        async_info.get();
        capture_started_ = true;
      } catch (winrt::hresult_error const& e) {
        RTC_LOG(LS_ERROR) << "StartRecordToCustomSinkAsync exception: "
          << rtc::ToUtf8(e.message().c_str());
        CleanupSink();
        CleanupMediaCapture();
      }
    }).wait();

    RTC_LOG(LS_INFO) << "CaptureDevice::StartCapture: returning";
  }

  //-----------------------------------------------------------------------------
  void CaptureDevice::StopCapture() {
    if (!capture_started_) {
      RTC_LOG(LS_INFO) << "CaptureDevice::StopCapture: called when never started";
      return;
    }

    Concurrency::create_task([this]() {
      return media_capture_.get().StopRecordAsync().get();
      }).then([this](Concurrency::task<void> async_info) {
      try {
        async_info.get();
        CleanupSink();
        CleanupMediaCapture();
        _stopped->Set();
      } catch (winrt::hresult_error const& e) {
        CleanupSink();
        CleanupMediaCapture();
        _stopped->Set();
        RTC_LOG(LS_ERROR) <<
          "CaptureDevice::StopCapture: Stop failed, reason: '" <<
          rtc::ToUtf8(e.message().c_str()) << "'";
      }
    });
  }

  //-----------------------------------------------------------------------------
  void CaptureDevice::OnCaptureFailed(
    winrt::Windows::Media::Capture::MediaCapture const& /*sender*/,
    MediaCaptureFailedEventArgs const& error_event_args)
  {
    if (!capture_device_listener_)
      return;

    capture_device_listener_->OnCaptureDeviceFailed(
      error_event_args.Code(),
      error_event_args.Message());
  }

  //-----------------------------------------------------------------------------
  void CaptureDevice::OnSample(winrt::com_ptr<IMFSample> &sample)
  {
    ZS_ASSERT((bool)sample);
    if (!capture_device_listener_)
      return;

    winrt::com_ptr<IMFMediaBuffer> spMediaBuffer;
    HRESULT hr = sample->GetBufferByIndex(0, spMediaBuffer.put());
    LONGLONG hnsSampleTime = 0;
    BYTE* pbBuffer = NULL;
    DWORD cbMaxLength = 0;
    DWORD cbCurrentLength = 0;

    if (SUCCEEDED(hr)) {
      hr = sample->GetSampleTime(&hnsSampleTime);
    }
    if (SUCCEEDED(hr)) {
      hr = spMediaBuffer->Lock(&pbBuffer, &cbMaxLength, &cbCurrentLength);
    }
    if (SUCCEEDED(hr)) {
      uint8_t* video_frame;
      size_t video_frame_length;
      int64_t capture_time;
      video_frame = pbBuffer;
      video_frame_length = cbCurrentLength;
      // conversion from 100-nanosecond to millisecond units
      capture_time = hnsSampleTime / 10000;

      RemovePaddingPixels(video_frame, video_frame_length);

      RTC_LOG(LS_VERBOSE) <<
        "Video Capture - Media sample received - video frame length: " <<
        video_frame_length << ", capture time : " << capture_time;

      capture_device_listener_->OnIncomingFrame(
        video_frame,
        video_frame_length,
        frame_info_,
        sample);

      hr = spMediaBuffer->Unlock();
    }
    if (FAILED(hr)) {
      RTC_LOG(LS_ERROR) << "Failed to send media sample. " << hr;
    }
  }

  //-----------------------------------------------------------------------------
  void CaptureDevice::OnShutdown()
  {
  }

  //-----------------------------------------------------------------------------
  winrt::agile_ref<MediaCapture> CaptureDevice::GetMediaCapture() {

    if (!media_capture_) {
#if (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP || \
                                defined(WINDOWS_PHONE_APP)))
      // WINDOWS_PHONE_APP is defined at gyp level to overcome the missing
      // WINAPI_FAMILY when building with VS2015

      // On some Windows Phone 8 devices, two calls of InitializeAsync on two
      // different coexisting instances causes exception to be thrown from the
      // second call.
      // Since after calling the second InitializeAsync all further calls fail
      // with exception, we maintain a maximum of one MediaCapture instance
      // in cache.
      // The behavior is present on Lumia620, OS version 8.10.14219.341 and
      // 10.0.10586.36
      media_capture_ = nullptr;
#endif
      winrt::agile_ref<winrt::Windows::Media::Capture::MediaCapture>
        media_capture_agile = winrt::Windows::Media::Capture::MediaCapture();

      Concurrency::task<void> initialize_async_task;
      auto initialize_task = [this, &media_capture_agile,
                              &initialize_async_task]() {
        auto settings = MediaCaptureInitializationSettings();
        settings.VideoDeviceId(device_id_);
        if (!video_profile_id_.empty()) {
          FindAndAddVideoProfile(settings);
        }
        initialize_async_task =
            Concurrency::create_task([this, media_capture_agile, settings]() {
              return media_capture_agile.get().InitializeAsync(settings).get();
            })
                .then([this,
                       media_capture_agile](Concurrency::task<void> initTask) {
                  try {
                    initTask.get();
                  } catch (winrt::hresult_error const& e) {
                    RTC_LOG(LS_ERROR)
                        << "Failed to initialize media capture device. "
                        << rtc::ToUtf8(e.message().c_str());
                  }
                });
      };

      auto queue = UseWebrtcLib::delegateQueue();
      ZS_ASSERT(queue);
      if (queue->isCurrentThread()) {
        // Run synchronously
        initialize_task();
      } else {
        // Run asynchronously
        std::condition_variable condition_variable;
        queue->postClosure([&initialize_task, &condition_variable]() {
          initialize_task();
          condition_variable.notify_one();
        });

        {
          std::mutex mutex;
          std::unique_lock<std::mutex> lock(mutex);
          condition_variable.wait(lock);
        }

        initialize_async_task.wait();
      }

      // Cache the MediaCapture object so we don't recreate it later.
      media_capture_ = media_capture_agile;
    }
    return media_capture_;
  }

  //-----------------------------------------------------------------------------
  bool CaptureDevice::FindAndAddVideoProfile(
      MediaCaptureInitializationSettings& settings) {
    const bool hasConstraints =
        (width_ > 0) || (height_ > 0) || (framerate_ > 0.0);
    if (!MediaCapture::IsVideoProfileSupported(device_id_)) {
      if (!video_profile_id_.empty()) {
        RTC_LOG(LS_WARNING)
            << "Media capture device '" << rtc::ToUtf8(device_id_.c_str())
            << "' does not support video profiles. Ignoring requested "
               "profile ID value '"
            << rtc::ToUtf8(video_profile_id_.c_str()) << "'.";
      } else if (hasConstraints) {
        RTC_LOG(LS_WARNING) << "Ignoring width/height/framerate "
                               "constraints for media capture device '"
                            << rtc::ToUtf8(device_id_.c_str())
                            << "'; frame constraints on devices without "
                               "video profile support is not implemented.";
      }
      return false;
    }
    auto profiles = MediaCapture::FindAllVideoProfiles(device_id_);
    for (auto&& profile : profiles) {
      // Filter out profiles by unique ID if specified by caller
      if (!video_profile_id_.empty() && (profile.Id() != video_profile_id_)) {
        continue;
      }
      auto descriptions = profile.SupportedRecordMediaDescription();
      for (auto&& desc : descriptions) {
        // Apply filters
        if ((width_ > 0) && (desc.Width() != (uint32_t)width_))
          continue;
        if ((height_ > 0) && (desc.Height() != (uint32_t)height_))
          continue;
        if ((framerate_ > 0.0) && (desc.FrameRate() != framerate_))
          continue;

        settings.VideoProfile(profile);
        settings.RecordMediaDescription(desc);
        return true;
      }
    }
    if (!video_profile_id_.empty()) {
      RTC_LOG(LS_ERROR) << "Failed to find video profile '"
                        << rtc::ToUtf8(video_profile_id_.c_str())
                        << "' for media capture device '"
                        << rtc::ToUtf8(device_id_.c_str()) << "'.";
    }
    else if (hasConstraints) {
      RTC_LOG(LS_ERROR) << "Failed to find constrained video profile "
                           "for media capture device '"
                        << rtc::ToUtf8(device_id_.c_str()) << "'.";
    }
    return false;
  }

  //-----------------------------------------------------------------------------
  void CaptureDevice::RemovePaddingPixels(uint8_t* video_frame,
    size_t& video_frame_length) {

    int padded_row_num = 16 - frame_info_.height % 16;
    int padded_col_num = 16 - frame_info_.width % 16;
    if (padded_row_num == 16)
      padded_row_num = 0;
    if (padded_col_num == 16)
      padded_col_num = 0;

    if (frame_info_.fourcc == FOURCC_YV12 &&
      (int32_t)video_frame_length >
      frame_info_.width * frame_info_.height * 3 / 2) {
      uint8_t* src_video_y = video_frame;
      uint8_t* src_video_v = src_video_y +
        (frame_info_.width + padded_col_num) *
        (frame_info_.height + padded_row_num);
      uint8_t* src_video_u = src_video_v +
        (frame_info_.width + padded_col_num) *
        (frame_info_.height + padded_row_num) / 4;
      uint8_t* dst_video_y = src_video_y;
      uint8_t* dst_video_v = dst_video_y +
        frame_info_.width * frame_info_.height;
      uint8_t* dst_video_u = dst_video_v +
        frame_info_.width * frame_info_.height / 4;
      video_frame_length = frame_info_.width * frame_info_.height * 3 / 2;
      libyuv::CopyPlane(src_video_y, frame_info_.width + padded_col_num,
        dst_video_y, frame_info_.width,
        frame_info_.width, frame_info_.height);
      libyuv::CopyPlane(src_video_v, (frame_info_.width + padded_col_num) / 2,
        dst_video_v, frame_info_.width / 2,
        frame_info_.width / 2, frame_info_.height / 2);
      libyuv::CopyPlane(src_video_u, (frame_info_.width + padded_col_num) / 2,
        dst_video_u, frame_info_.width / 2,
        frame_info_.width / 2, frame_info_.height / 2);
    } else if (frame_info_.fourcc == FOURCC_YUY2 &&
      (int32_t)video_frame_length >
      frame_info_.width * frame_info_.height * 2) {
      uint8_t* src_video = video_frame;
      uint8_t* dst_video = src_video;
      video_frame_length = frame_info_.width * frame_info_.height * 2;
      libyuv::CopyPlane(src_video, 2 * (frame_info_.width + padded_col_num),
        dst_video, 2 * frame_info_.width,
        2 * frame_info_.width, frame_info_.height);
    } else if (frame_info_.fourcc == FOURCC_IYUV &&
      (int32_t)video_frame_length >
      frame_info_.width * frame_info_.height * 3 / 2) {
      uint8_t* src_video_y = video_frame;
      uint8_t* src_video_u = src_video_y +
        (frame_info_.width + padded_col_num) *
        (frame_info_.height + padded_row_num);
      uint8_t* src_video_v = src_video_u +
        (frame_info_.width + padded_col_num) *
        (frame_info_.height + padded_row_num) / 4;
      uint8_t* dst_video_y = src_video_y;
      uint8_t* dst_video_u = dst_video_y +
        frame_info_.width * frame_info_.height;
      uint8_t* dst_video_v = dst_video_u +
        frame_info_.width * frame_info_.height / 4;
      video_frame_length = frame_info_.width * frame_info_.height * 3 / 2;
      libyuv::CopyPlane(src_video_y, frame_info_.width + padded_col_num,
        dst_video_y, frame_info_.width,
        frame_info_.width, frame_info_.height);
      libyuv::CopyPlane(src_video_u, (frame_info_.width + padded_col_num) / 2,
        dst_video_u, frame_info_.width / 2,
        frame_info_.width / 2, frame_info_.height / 2);
      libyuv::CopyPlane(src_video_v, (frame_info_.width + padded_col_num) / 2,
        dst_video_v, frame_info_.width / 2,
        frame_info_.width / 2, frame_info_.height / 2);
    } else if (frame_info_.fourcc == FOURCC_24BG &&
      (int32_t)video_frame_length >
      frame_info_.width * frame_info_.height * 3) {
      uint8_t* src_video = video_frame;
      uint8_t* dst_video = src_video;
      video_frame_length = frame_info_.width * frame_info_.height * 3;
      libyuv::CopyPlane(src_video, 3 * (frame_info_.width + padded_col_num),
        dst_video, 3 * frame_info_.width,
        3 * frame_info_.width, frame_info_.height);
    } else if (frame_info_.fourcc == FOURCC_ARGB &&
      (int32_t)video_frame_length >
      frame_info_.width * frame_info_.height * 4) {
      uint8_t* src_video = video_frame;
      uint8_t* dst_video = src_video;
      video_frame_length = frame_info_.width * frame_info_.height * 4;
      libyuv::CopyPlane(src_video, 4 * (frame_info_.width + padded_col_num),
        dst_video, 4 * frame_info_.width,
        4 * frame_info_.width, frame_info_.height);
    } else if (frame_info_.fourcc == FOURCC_NV12 &&
      (int32_t)video_frame_length >
      frame_info_.width * frame_info_.height * 3 / 2) {
      uint8_t* src_video_y = video_frame;
      uint8_t* src_video_uv = src_video_y +
        (frame_info_.width + padded_col_num) *
        (frame_info_.height + padded_row_num);
      uint8_t* dst_video_y = src_video_y;
      uint8_t* dst_video_uv = dst_video_y +
        frame_info_.width * frame_info_.height;
      video_frame_length = frame_info_.width * frame_info_.height * 3 / 2;
      libyuv::CopyPlane(src_video_y, frame_info_.width + padded_col_num,
        dst_video_y, frame_info_.width,
        frame_info_.width, frame_info_.height);
      libyuv::CopyPlane(src_video_uv, frame_info_.width + padded_col_num,
        dst_video_uv, frame_info_.width,
        frame_info_.width, frame_info_.height / 2);
    }
  }

  //-----------------------------------------------------------------------------
  VideoCapturer::VideoCapturer(const make_private &) :
    device_(nullptr),
    camera_location_(Panel::Unknown),
    display_orientation_(nullptr),
    video_encoding_properties_(nullptr),
    media_encoding_profile_(nullptr),
    subscriptions_(decltype(subscriptions_)::create())
  {
    RTC_LOG(LS_INFO) << "Using local detection for orientation source";
    display_orientation_ = std::make_shared<DisplayOrientation>(this);
  }

  //-----------------------------------------------------------------------------
  VideoCapturer::~VideoCapturer()
  {
    if (deviceUniqueId_ != nullptr)
      delete[] deviceUniqueId_;
    if (device_ != nullptr)
      device_->Cleanup();
  }

  //-----------------------------------------------------------------------------
  VideoCapturerUniPtr VideoCapturer::create(const CreationProperties &info) noexcept
  {
    auto result = std::make_unique<VideoCapturer>(make_private{});
    result->init(info);
    return result;
  }

  //-----------------------------------------------------------------------------
  void VideoCapturer::init(const CreationProperties &props) noexcept
  {
    SetId(String(props.id_));

    if (props.delegate_) {
      defaultSubscription_ = subscriptions_.subscribe(props.delegate_, UseWebrtcLib::videoFrameProcessingQueue());
    }

    // Mandatory device ID
    if (!props.id_) {
      RTC_LOG_F(LS_ERROR) << "Invalid NULL video capture device ID.";
      return;
    }
    const std::string_view device_unique_id_utf8(props.id_);

    // Optional video profile ID
    const std::string_view video_profile_id_utf8 =
        (props.videoProfileId_ ? std::string_view{props.videoProfileId_}
                               : std::string_view{});

    winrt::Windows::Media::MediaProperties::VideoEncodingProperties
        properties{};

    rtc::CritScope cs(&apiCs_);
    mrc_enabled_ = props.mrcEnabled_;

    RTC_LOG(LS_INFO) << "Init called for device " << props.id_;
    if (!video_profile_id_utf8.empty()) {
      RTC_LOG(LS_INFO) << "Requested video profile " << props.videoProfileId_;
    }

    device_id_.clear();
    video_profile_id_.clear();

    deviceUniqueId_ = new (std::nothrow) char[device_unique_id_utf8.size() + 1];
    memcpy(deviceUniqueId_, props.id_, device_unique_id_utf8.size() + 1);

    Concurrency::create_task([this]() {
      return DeviceInformation::FindAllAsync(DeviceClass::VideoCapture).get().as<IVectorView<DeviceInformation> >();
      }).then([this, device_unique_id_utf8](
        IVectorView<DeviceInformation> const& collection) {
        try {
        DeviceInformationCollection dev_info_collection = collection.as<DeviceInformationCollection>();
        if (dev_info_collection == nullptr || dev_info_collection.Size() == 0) {
          RTC_LOG_F(LS_ERROR) << "No video capture device found";
          return;
        }
        // Look for the device in the collection.
        DeviceInformation chosen_dev_info = nullptr;
        const std::wstring device_unique_id_utf16 = rtc::ToUtf16(
            device_unique_id_utf8.data(), device_unique_id_utf8.size());
        for (unsigned int i = 0; i < dev_info_collection.Size(); i++) {
          auto dev_info = dev_info_collection.GetAt(i);
          if (dev_info.Id() == device_unique_id_utf16) {
            device_id_ = dev_info.Id();
            if (dev_info.EnclosureLocation() != nullptr) {
              camera_location_ = dev_info.EnclosureLocation().Panel();
            } else {
              camera_location_ = Panel::Unknown;
            }
            break;
          }
        }
      } catch (winrt::hresult_error const& e) {
        RTC_LOG(LS_ERROR)
          << "Failed to retrieve device info collection. "
          << rtc::ToUtf8(e.message().c_str());
      }
    }).wait();

    if (device_id_.empty()) {
      RTC_LOG(LS_ERROR) << "No video capture device found";
      return;
    }

    int width = 0;
    int height = 0;
    double framerate = 0.0;
    if (props.width_ > 0) {
      width = props.width_;
    }
    if (props.height_ > 0) {
      height = props.height_;
    }
    if (props.framerate_ > 0) {
      framerate = props.framerate_;
    }

    // Select the video profile, if requested
    std::vector<VideoFormat> formats;
    if (!video_profile_id_utf8.empty()) {
      if (!MediaCapture::IsVideoProfileSupported(device_id_)) {
        RTC_LOG_F(LS_ERROR) << "Video capture device " << device_unique_id_utf8
                            << " does not support video profiles.";
        return;
      }
      const std::wstring video_profile_id_utf16 = rtc::ToUtf16(
          video_profile_id_utf8.data(), video_profile_id_utf8.size());
      auto profiles = MediaCapture::FindAllVideoProfiles(device_id_);
      for (auto&& profile : profiles) {
        if (profile.Id() != video_profile_id_utf16) {
          continue;
        }

        // Extract the list of media types to populate the list of supported
        // WebRTC video formats associated with the selected profile only.
        auto fsiList = profile.FrameSourceInfos();
        for (auto&& fsi : fsiList) {
          // RTC_LOG(LS_INFO) << "FrameSourceInfo: id="
          //                 << rtc::ToUtf8(fsi.Id().c_str())
          //                 << " type=" << (int)fsi.MediaStreamType()
          //                 << " profileId="
          //                 << rtc::ToUtf8(fsi.ProfileId().c_str())
          //                 << " kind=" << (int)fsi.SourceKind();
          RTC_CHECK(fsi.ProfileId() == video_profile_id_utf16);
          if (fsi.MediaStreamType() != MediaStreamType::VideoRecord) {
            continue;
          }
          auto descs = fsi.VideoProfileMediaDescription();
          for (auto&& desc : descs) {
            // RTC_LOG(LS_INFO)
            //    << "- desc: (" << desc.Width() << " x " << desc.Height()
            //    << ") @ " << desc.FrameRate() << " ["
            //    << rtc::ToUtf8(desc.Subtype().c_str()) << "]";

            // Filter out formats by constraints
            if ((width > 0) && (desc.Width() != (uint32_t)width))
              continue;
            if ((height > 0) && (desc.Height() != (uint32_t)height))
              continue;
            if ((framerate > 0) && (desc.FrameRate() != framerate))
              continue;

            VideoFormat format;
            format.fourcc = CaptureDevice::GetFourCC(desc.Subtype());
            format.width = desc.Width();
            format.height = desc.Height();
            format.interval = VideoFormat::FpsToInterval((int)desc.FrameRate());
            formats.push_back(format);
          }
        }
		if (formats.empty()) {
          RTC_LOG(LS_ERROR) << "Failed to find any supported video format.";
		  return;
		}
		
        // Profile found
        video_profile_id_ = video_profile_id_utf16;
        break;
      }
      if (video_profile_id_.empty()) {
        RTC_LOG_F(LS_ERROR)
            << "Failed to find video profile " << video_profile_id_utf8
            << " for video capture device " << device_unique_id_utf8;
        return;
      }
    }

    device_ = std::make_shared<CaptureDevice>(this);
    device_->Initialize(device_id_, video_profile_id_, width, height,
                        framerate);

    // If not already collected from the video profile, gather all supported
    // media types to populate the list of supported WebRTC video formats.
    if (formats.empty()) {
      auto mediaCapture = device_->GetMediaCapture();
      auto streamProperties =
          mediaCapture.get()
              .VideoDeviceController()
              .GetAvailableMediaStreamProperties(MediaStreamType::VideoRecord);
      for (unsigned int i = 0; i < streamProperties.Size(); i++) {
        IVideoEncodingProperties prop;
        streamProperties.GetAt(i).as(prop);

        const double propFramerate =
            prop.FrameRate().Numerator() / prop.FrameRate().Denominator();

        // Filter out formats by constraints
        if ((width > 0) && (prop.Width() != (uint32_t)width))
          continue;
        if ((height > 0) && (prop.Height() != (uint32_t)height))
          continue;
        if ((framerate > 0) && (propFramerate != framerate))
          continue;

        VideoFormat format;
        format.fourcc = CaptureDevice::GetFourCC(prop.Subtype());
        format.width = prop.Width();
        format.height = prop.Height();
        format.interval = VideoFormat::FpsToInterval((int)propFramerate);
        formats.push_back(format);
      }
    }

    RTC_CHECK(!formats.empty());
    SetSupportedFormats(formats);
  }

  //-----------------------------------------------------------------------------
  IVideoCapturerSubscriptionPtr VideoCapturer::subscribe(IVideoCapturerDelegatePtr originalDelegate)
  {
    AutoRecursiveLock lock(lock_);
    if (!originalDelegate) return defaultSubscription_;

    return subscriptions_.subscribe(originalDelegate, UseWebrtcLib::videoFrameProcessingQueue());
  }

  //-----------------------------------------------------------------------------
  CaptureState VideoCapturer::Start(const VideoFormat& capture_format) {

    rtc::CritScope cs(&apiCs_);

    winrt::hstring subtype = CaptureDevice::GetVideoSubtype(capture_format.fourcc);
    if (subtype.empty()) {
      RTC_LOG(LS_ERROR) <<
        "The specified raw video format is not supported on this platform.";
      return CS_FAILED;
    }
    if (_wcsicmp(subtype.c_str(),
      MediaEncodingSubtypes::Mjpg().c_str()) == 0) {
      // MJPEG format is decoded internally by MF engine to NV12
      subtype = MediaEncodingSubtypes::Nv12();
    }

    RTC_LOG(LS_INFO) << "Trying to start video capture with video format "
                     << rtc::ToUtf8(subtype.c_str()) << " ("
                     << capture_format.width << " x " << capture_format.height
                     << " @ "
                     << VideoFormat::IntervalToFps(capture_format.interval)
                     << " FPS)";

    media_encoding_profile_ = MediaEncodingProfile();
    media_encoding_profile_.Audio(nullptr);
    media_encoding_profile_.Container(nullptr);
    media_encoding_profile_.Video(VideoEncodingProperties::CreateUncompressed(
      subtype, capture_format.width, capture_format.height));
    media_encoding_profile_.Video().FrameRate().Numerator(VideoFormat::IntervalToFps(capture_format.interval));
    media_encoding_profile_.Video().FrameRate().Denominator(1);

    video_encoding_properties_ = nullptr;
    int min_width_diff = INT_MAX;
    int min_height_diff = INT_MAX;
    int min_fps_diff = INT_MAX;
    auto mediaCapture = device_->GetMediaCapture();
    auto streamProperties =
      mediaCapture.get().VideoDeviceController().GetAvailableMediaStreamProperties(
        MediaStreamType::VideoRecord);
    for (unsigned int i = 0; i < streamProperties.Size(); i++) {
      IVideoEncodingProperties prop;
      streamProperties.GetAt(i).as(prop);

      if (capture_format.fourcc != FOURCC_MJPG &&
        _wcsicmp(prop.Subtype().c_str(), subtype.c_str()) != 0 ||
        capture_format.fourcc == FOURCC_MJPG &&
        _wcsicmp(prop.Subtype().c_str(),
          MediaEncodingSubtypes::Mjpg().c_str()) != 0) {
        continue;
      }

      int width_diff = abs(static_cast<int>(prop.Width() - capture_format.width));
      int height_diff = abs(static_cast<int>(prop.Height() - capture_format.height));
      int prop_fps = static_cast<int>(
        (static_cast<float>(prop.FrameRate().Numerator()) /
          static_cast<float>(prop.FrameRate().Denominator())));
      int fps_diff = abs(static_cast<int>(prop_fps - VideoFormat::IntervalToFps(capture_format.interval)));

      if (width_diff < min_width_diff) {
        video_encoding_properties_ = prop;
        min_width_diff = width_diff;
        min_height_diff = height_diff;
        min_fps_diff = fps_diff;
      } else if (width_diff == min_width_diff) {
        if (height_diff < min_height_diff) {
          video_encoding_properties_ = prop;
          min_height_diff = height_diff;
          min_fps_diff = fps_diff;
        } else if (height_diff == min_height_diff) {
          if (fps_diff < min_fps_diff) {
            video_encoding_properties_ = prop;
            min_fps_diff = fps_diff;
          }
        }
      }
    }

    float actualFps =
        (static_cast<float>(
             video_encoding_properties_.FrameRate().Numerator()) /
         static_cast<float>(
             video_encoding_properties_.FrameRate().Denominator()));
    RTC_LOG(LS_INFO) << "Found closest video encoding format ("
                     << video_encoding_properties_.Width() << " x "
                     << video_encoding_properties_.Height() << " @ "
                     << actualFps << " FPS)";

    try {
      ApplyDisplayOrientation(display_orientation_->Orientation());
      device_->StartCapture(media_encoding_profile_,
        video_encoding_properties_, mrc_enabled_);
    } catch (winrt::hresult_error const& e) {
      RTC_LOG(LS_ERROR) << "Failed to start capture. "
        << rtc::ToUtf8(e.message().c_str());
      return CS_FAILED;
    }

    SetCaptureFormat(&capture_format);

    SetCaptureState(CS_RUNNING);

    return CS_RUNNING;
  }

  //-----------------------------------------------------------------------------
  void VideoCapturer::Stop() {
    rtc::CritScope cs(&apiCs_);
    try {
      if (device_->CaptureStarted()) {
        device_->StopCapture();
      }
    } catch (winrt::hresult_error const& e) {
      RTC_LOG(LS_ERROR) << "Failed to stop capture. "
        << rtc::ToUtf8(e.message().c_str());
      return;
    }
    SetCaptureFormat(nullptr);
    SetCaptureState(CS_STOPPED);
  }

  //-----------------------------------------------------------------------------
  bool VideoCapturer::IsRunning() {
    rtc::CritScope cs(&apiCs_);
    return device_->CaptureStarted();
  }

  //-----------------------------------------------------------------------------
  bool VideoCapturer::IsScreencast() const {
    return false;
  }

  //-----------------------------------------------------------------------------
  bool VideoCapturer::GetPreferredFourccs(std::vector<uint32_t>* fourccs) {
    if (!fourccs) {
      return false;
    }

    fourccs->clear();
    fourccs->push_back(FOURCC_I420);
    fourccs->push_back(FOURCC_YV12);
    fourccs->push_back(FOURCC_YUY2);
    fourccs->push_back(FOURCC_UYVY);
    fourccs->push_back(FOURCC_NV12);
    fourccs->push_back(FOURCC_NV21);
    fourccs->push_back(FOURCC_MJPG);
    fourccs->push_back(FOURCC_ARGB);
    fourccs->push_back(FOURCC_24BG);

    return true;
  }

  //-----------------------------------------------------------------------------
  void VideoCapturer::OnDisplayOrientationChanged(
    DisplayOrientations orientation) {
    ApplyDisplayOrientation(orientation);
  }

  //-----------------------------------------------------------------------------
  void VideoCapturer::OnIncomingFrame(
    uint8_t* videoFrame,
    size_t videoFrameLength,
    const VideoFormat& frameInfo,
    winrt::com_ptr<IMFSample> spMediaSample)
  {
    rtc::CritScope cs(&apiCs_);

    const int32_t width = frameInfo.width;
    const int32_t height = frameInfo.height;

    int stride_y = width;
    int stride_uv = (width + 1) / 2;
    int target_width = width;
    int target_height = height;

    // SetApplyRotation doesn't take any lock. Make a local copy here.
    bool apply_rotation = apply_rotation_;

    if (apply_rotation) {
      // Rotating resolution when for 90/270 degree rotations.
      if (rotateFrame_ == kVideoRotation_90 ||
        rotateFrame_ == kVideoRotation_270) {
        target_width = abs(height);
        target_height = width;
      }
    }

    rtc::scoped_refptr<I420Buffer> buffer = I420Buffer::Create(
      target_width, abs(target_height), stride_y, stride_uv, stride_uv);

    libyuv::RotationMode rotation_mode = libyuv::kRotate0;
    if (apply_rotation) {
      switch (rotateFrame_) {
      case kVideoRotation_0:
        rotation_mode = libyuv::kRotate0;
        break;
      case kVideoRotation_90:
        rotation_mode = libyuv::kRotate90;
        break;
      case kVideoRotation_180:
        rotation_mode = libyuv::kRotate180;
        break;
      case kVideoRotation_270:
        rotation_mode = libyuv::kRotate270;
        break;
      }
    }

    const int conversionResult = libyuv::ConvertToI420(
      videoFrame, videoFrameLength, buffer.get()->MutableDataY(),
      buffer.get()->StrideY(), buffer.get()->MutableDataU(),
      buffer.get()->StrideU(), buffer.get()->MutableDataV(),
      buffer.get()->StrideV(), 0, 0,  // No Cropping
      width, height, target_width, target_height, rotation_mode,
      frameInfo.fourcc);
    if (conversionResult < 0) {
      RTC_LOG(LS_ERROR) << "Failed to convert capture frame from type "
        << static_cast<int>(frameInfo.fourcc) << " to I420.";
      return;
    }

    int64_t captureTime = 0;
    VideoFrame captureFrame(buffer, 0, rtc::TimeMillis(),
      !apply_rotation ? rotateFrame_ : kVideoRotation_0);
    captureFrame.set_ntp_time_ms(captureTime);

    forwardToDelegates(frameInfo, spMediaSample, buffer);
    OnFrame(captureFrame, captureFrame.width(), captureFrame.height());
  }

  //-----------------------------------------------------------------------------
  void VideoCapturer::forwardToDelegates(
    const cricket::VideoFormat &frameInfo,
    const winrt::com_ptr<IMFSample> &spMediaSample,
    rtc::scoped_refptr<I420BufferInterface> i420Frame)
  {
    if (subscriptions_.size() < 1)
      return;

    rtc::scoped_refptr<MFNativeHandleBuffer> nativeHandleBuffer(new rtc::RefCountedObject<MFNativeHandleBuffer>(
      static_cast<cricket::FourCC>(frameInfo.fourcc),
      spMediaSample,
      i420Frame,
      frameInfo.width,
      frameInfo.height));

    auto wrapperBuffer = UseVideoFrameNativeBuffer::toWrapper(nativeHandleBuffer.get());
    auto event = UseVideoFrameBufferEvent::toWrapper(wrapperBuffer);

    subscriptions_.delegate()->onVideoFrameReceived(event);
  }

  //-----------------------------------------------------------------------------
  bool VideoCapturer::SetVideoProfile(std::string_view video_profile_id) {
    RTC_CHECK(MediaCapture::IsVideoProfileSupported(device_id_));
    const std::wstring video_profile_id_utf16 =
        rtc::ToUtf16(video_profile_id.data(), video_profile_id.size());
    auto profiles = MediaCapture::FindAllVideoProfiles(device_id_);
    for (auto&& profile : profiles) {
      if (profile.Id() != video_profile_id_utf16) {
        continue;
      }
      video_profile_id_ = video_profile_id_utf16;
      return true;
    }
    return false;
  }

  //-----------------------------------------------------------------------------
  void VideoCapturer::OnCaptureDeviceFailed(HRESULT code,
    winrt::hstring const& message) {
    RTC_LOG(LS_ERROR) << "Capture device failed. HRESULT: " <<
      code << " Message: " << rtc::ToUtf8(message.c_str());
    rtc::CritScope cs(&apiCs_);
    if (device_ != nullptr && device_->CaptureStarted()) {
      try {
        device_->StopCapture();
      } catch (winrt::hresult_error const& ex) {
        RTC_LOG(LS_WARNING) <<
          "Capture device failed: failed to stop ex='"
          << rtc::ToUtf8(ex.message().c_str()) << "'";
      }
    }
  }

  //-----------------------------------------------------------------------------
  void VideoCapturer::ApplyDisplayOrientation(
    DisplayOrientations orientation) {
    if (camera_location_ == winrt::Windows::Devices::Enumeration::Panel::Unknown)
      return;
    rtc::CritScope cs(&apiCs_);
    switch (orientation) {
    case winrt::Windows::Graphics::Display::DisplayOrientations::Portrait:
      if (camera_location_ == winrt::Windows::Devices::Enumeration::Panel::Front)
        rotateFrame_ = VideoRotation::kVideoRotation_270;
      else
        rotateFrame_ = VideoRotation::kVideoRotation_90;
      break;
    case winrt::Windows::Graphics::Display::DisplayOrientations::PortraitFlipped:
      if (camera_location_ == winrt::Windows::Devices::Enumeration::Panel::Front)
        rotateFrame_ = VideoRotation::kVideoRotation_90;
      else
        rotateFrame_ = VideoRotation::kVideoRotation_270;
      break;
    case winrt::Windows::Graphics::Display::DisplayOrientations::Landscape:
      rotateFrame_ = VideoRotation::kVideoRotation_0;
      break;
    case winrt::Windows::Graphics::Display::DisplayOrientations::LandscapeFlipped:
      rotateFrame_ = VideoRotation::kVideoRotation_180;
      break;
    default:
      rotateFrame_ = VideoRotation::kVideoRotation_0;
      break;
    }
  }

  //-----------------------------------------------------------------------------
  IVideoCapturerUniPtr IVideoCapturer::create(const CreationProperties &info) noexcept
  {
    return VideoCapturer::create(info);
  }
} // namespace webrtc

#endif //CPPWINRT_VERSION
