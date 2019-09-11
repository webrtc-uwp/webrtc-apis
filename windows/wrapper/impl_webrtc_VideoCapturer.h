
#pragma once

#include "impl_webrtc_IVideoCapturer.h"

#ifdef CPPWINRT_VERSION

#include <wrapper/impl_org_webRtc_pre_include.h>
#include "rtc_base/criticalsection.h"
#include "media/base/videocapturer.h"
#include "system_wrappers/include/event_wrapper.h"
#include <wrapper/impl_org_webRtc_post_include.h>

#include <zsLib/types.h>
#include <zsLib/Proxy.h>
#include <zsLib/ProxySubscriptions.h>

#include <atomic>
#include <mfidl.h>

#include <functional>
#include <vector>
#include <queue>

#include "impl_webrtc_VideoCaptureMediaSink.h"

namespace webrtc
{
  class DisplayOrientation;
  class CaptureDevice;

  class DisplayOrientationListener {
  public:
    virtual void OnDisplayOrientationChanged(
      winrt::Windows::Graphics::Display::DisplayOrientations orientation) = 0;
  };

  class CaptureDeviceListener {
  public:
    virtual void OnIncomingFrame(uint8_t* video_frame,
      size_t video_frame_length,
      const cricket::VideoFormat& frame_info,
      winrt::com_ptr<IMFSample> spMediaSample) = 0;
    virtual void OnCaptureDeviceFailed(HRESULT code,
      winrt::hstring const& message) = 0;
    virtual void BeginShutdown() = 0;
    virtual void EndShutdown() = 0;
  };

  class VideoCapturer : public IVideoCapturer,
    public cricket::VideoCapturer,
    public CaptureDeviceListener,
    public DisplayOrientationListener
  {
  private:
    struct make_private {};

  private:
    bool init(const CreationProperties &props) noexcept;

  public:
    VideoCapturer(const make_private &);
    virtual ~VideoCapturer();

    static VideoCapturerUniPtr create(const CreationProperties &info) noexcept;

    IVideoCapturerSubscriptionPtr subscribe(IVideoCapturerDelegatePtr delegate) override;

    std::string id() const noexcept override { return id_; }

    // Overrides from cricket::VideoCapturer
    virtual cricket::CaptureState Start(const cricket::VideoFormat& capture_format) override;
    virtual void Stop() override;
    virtual bool IsRunning() override;
    virtual bool IsScreencast() const override;
    virtual bool GetPreferredFourccs(std::vector<uint32_t>* fourccs) override;

    // Overrides from DisplayOrientationListener
    void OnDisplayOrientationChanged(
      winrt::Windows::Graphics::Display::DisplayOrientations orientation) override;

  private:
    // Overrides from CaptureDeviceListener
    virtual void OnIncomingFrame(
      uint8_t* video_frame,
      size_t video_frame_length,
      const cricket::VideoFormat& frame_info,
      winrt::com_ptr<IMFSample> spMediaSample) override;

    virtual void OnCaptureDeviceFailed(HRESULT code,
      winrt::hstring const& message) override;

    void BeginShutdown() override {
      rtc::CritScope lock(&frame_cs_);
      is_shutting_down_ = true;
    }

    void EndShutdown() override {
      rtc::CritScope lock(&frame_cs_);
      is_shutting_down_ = false;
    }

    virtual void ApplyDisplayOrientation(
      winrt::Windows::Graphics::Display::DisplayOrientations orientation);

    void forwardToDelegates(
      const cricket::VideoFormat& frameInfo,
      const winrt::com_ptr<IMFSample> &spMediaSample,
      rtc::scoped_refptr<I420BufferInterface> i420Frame);

    bool SetVideoProfile(std::string_view video_profile_id);

  private:
    mutable zsLib::RecursiveLock lock_;

    IVideoCapturerDelegateSubscriptions subscriptions_;
    IVideoCapturerSubscriptionPtr defaultSubscription_;

    std::string id_;

    char* deviceUniqueId_ { nullptr };
    rtc::CriticalSection apiCs_;

    /// Lock used by the OnIncomingFrame() callback to synchronize with
    /// StopCapture() without inducing any deadlock in MediaCapture. This is
    /// completely uncontended, except possibly during capture shutdown.
    rtc::CriticalSection frame_cs_;

    /// Indicate that the capture is shutting down, and the apiCs_ lock will be
    /// held so should not be acquired by OnIncomingFrame().
    bool is_shutting_down_{false};

    VideoRotation rotateFrame_ { kVideoRotation_0 };
    bool apply_rotation_ { false };

    winrt::hstring device_id_;
    winrt::hstring video_profile_id_;
    int video_profile_kind_ {};
    std::shared_ptr<CaptureDevice> device_;
    winrt::Windows::Devices::Enumeration::Panel camera_location_;
    std::shared_ptr<DisplayOrientation> display_orientation_;
    winrt::Windows::Media::MediaProperties::IVideoEncodingProperties
      video_encoding_properties_;
    winrt::Windows::Media::MediaProperties::MediaEncodingProfile
      media_encoding_profile_;

    bool mrc_enabled_{ false };
  };
}

#endif //CPPWINRT_VERSION
