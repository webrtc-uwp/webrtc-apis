
#pragma once

#include "impl_webrtc_IVideoCapture.h"

#ifdef WINUWP
#ifdef CPPWINRT_VERSION

#include <wrapper/impl_org_webRtc_pre_include.h>
#include "rtc_base/criticalsection.h"
#include "modules/video_capture/video_capture_defines.h"
#include <wrapper/impl_org_webRtc_post_include.h>

#include <zsLib/types.h>
#include <zsLib/Proxy.h>
#include <zsLib/ProxySubscriptions.h>

#include <atomic>
#include <wrl.h>
#include <agile.h>
#include <mfidl.h>

#include <functional>
#include <vector>
#include <queue>

namespace webrtc
{
  ref class CaptureDevice;
  ref class BlackFramesGenerator;
  ref class DisplayOrientation;

  class CaptureDeviceListener {
  public:
    virtual void OnIncomingFrame(uint8_t* video_frame,
      size_t video_frame_length,
      const VideoCaptureCapability& frame_info) = 0;
    virtual void OnCaptureDeviceFailed(HRESULT code,
      Platform::String^ message) = 0;
  };

  class DisplayOrientationListener {
  public:
    virtual void OnDisplayOrientationChanged(
      Windows::Graphics::Display::DisplayOrientations orientation) = 0;
  };

  class AppStateObserver {
  public:
    virtual void DisplayOrientationChanged(
      Windows::Graphics::Display::DisplayOrientations display_orientation) = 0;
  };

  class AppStateDispatcher : public AppStateObserver {
  public:
    static AppStateDispatcher* Instance();

    void DisplayOrientationChanged(
      Windows::Graphics::Display::DisplayOrientations display_orientation);
    Windows::Graphics::Display::DisplayOrientations GetOrientation() const;
    void AddObserver(AppStateObserver* observer);
    void RemoveObserver(AppStateObserver* observer);

  private:
    AppStateDispatcher();

    std::vector<AppStateObserver*> observers;
    static AppStateDispatcher* instance_;
    Windows::Graphics::Display::DisplayOrientations display_orientation_;
  };

  class VideoCapture : public IVideoCapture,
    public CaptureDeviceListener,
    public AppStateObserver,
    public DisplayOrientationListener
  {
  private:
    typedef Microsoft::WRL::ComPtr<IMFSample> IMFSampleComPtr;
    struct make_private {};

    typedef uint32_t DimensionType;
    typedef int RotationType;
    typedef LONGLONG RenderTime;  // The presentation time, in 100-nanosecond units.

  private:
    void init(const CreationProperties &props) noexcept;

  public:
    VideoCapture(const make_private &);
    ~VideoCapture();

    static VideoCapturePtr create(const CreationProperties &info) noexcept;

    IVideoCaptureSubscriptionPtr subscribe(IVideoCaptureDelegatePtr delegate) override;

    std::string id() const noexcept override { return id_; }

    int32_t startCapture(const VideoCaptureCapability& capability) override;
    int32_t stopCapture() override;
    bool captureStarted() override;
    int32_t captureSettings(VideoCaptureCapability& settings) override;

    bool suspendCapture() override;
    bool resumeCapture() override;
    bool isSuspended() override;

    // Overrides from AppStateObserver
    void DisplayOrientationChanged(
      Windows::Graphics::Display::DisplayOrientations display_orientation) override;

    // Overrides from DisplayOrientationListener
    void OnDisplayOrientationChanged(
      Windows::Graphics::Display::DisplayOrientations orientation) override;

  private:
    virtual void OnIncomingFrame(uint8_t* video_frame,
      size_t video_frame_length,
      const VideoCaptureCapability& frame_info);

    virtual void OnCaptureDeviceFailed(HRESULT code,
      Platform::String^ message);

    virtual void ApplyDisplayOrientation(
      Windows::Graphics::Display::DisplayOrientations orientation);

  private:
    VideoCaptureWeakPtr thisWeak_;
    mutable zsLib::RecursiveLock lock_;

    IVideoCaptureDelegateSubscriptions subscriptions_;
    IVideoCaptureSubscriptionPtr defaultSubscription_;

    std::string id_;
    VideoCaptureExternal *externalCapture_ {nullptr};

    char* deviceUniqueId_ { nullptr };
    rtc::CriticalSection apiCs_;

    VideoRotation rotateFrame_ { kVideoRotation_0 };
    bool apply_rotation_ { false };

    Platform::String^ device_id_;
    CaptureDevice^ device_;
    Windows::Devices::Enumeration::Panel camera_location_;
    DisplayOrientation^ display_orientation_;
    BlackFramesGenerator^ fake_device_;
    VideoCaptureCapability last_frame_info_;
    Windows::Media::MediaProperties::IVideoEncodingProperties^
      video_encoding_properties_;
    Windows::Media::MediaProperties::MediaEncodingProfile^
      media_encoding_profile_;
  };

  // Helper function to run code on the WinUWP CoreDispatcher
  // and only return once the call completed.
  void RunOnCoreDispatcher(std::function<void()> fn, bool async = false);
}

#endif //CPPWINRT_VERSION
#endif //WINUWP
