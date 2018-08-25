
#pragma once

#ifdef WINUWP

#ifdef __has_include
#if __has_include(<winrt/windows.media.core.h>)
#include <winrt/windows.media.core.h>
#endif //__has_include(<winrt/windows.media.core.h>)
#if __has_include(<winrt/windows.system.threading.h>)
#include <winrt/windows.system.threading.h>
#endif //__has_include(<winrt/windows.system.threading.h>)
#if __has_include(<winrt/windows.media.mediaproperties.h>)
#include <winrt/windows.media.mediaproperties.h>
#endif //__has_include(<winrt/windows.media.mediaproperties.h>)
#if __has_include(<winrt/windows.ui.core.h>)
#include <winrt/windows.ui.core.h>
#endif //__has_include(<winrt/windows.ui.core.h>)
#if __has_include(<winrt/windows.graphics.display.h>)
#include <winrt/windows.graphics.display.h>
#endif //__has_include(<winrt/windows.graphics.display.h>)
#endif //__has_include

#ifdef CPPWINRT_VERSION

#include <wrapper/impl_org_webRtc_pre_include.h>
#include "modules/video_capture/video_capture_defines.h"
#include <wrapper/impl_org_webRtc_post_include.h>

#include <zsLib/types.h>
#include <zsLib/Proxy.h>
#include <zsLib/ProxySubscriptions.h>

#include <atomic>
#include <mfidl.h>


namespace webrtc
{
  ZS_DECLARE_INTERACTION_PTR(IVideoCapture);
  ZS_DECLARE_INTERACTION_PROXY(IVideoCaptureDelegate);
  ZS_DECLARE_CLASS_PTR(VideoCapture);
  ZS_DECLARE_INTERACTION_PROXY_SUBSCRIPTION(IVideoCaptureSubscription, IVideoCaptureDelegate);


  interaction IVideoCapture
  {
    struct CreationProperties
    {
      IVideoCaptureDelegatePtr delegate_;

      const char *id_ {};
      VideoCaptureExternal *externalCapture_ {};
    };

    static IVideoCapturePtr create(const CreationProperties &info) noexcept;

    virtual IVideoCaptureSubscriptionPtr subscribe(IVideoCaptureDelegatePtr delegate) = 0;

    virtual std::string id() const noexcept = 0;

    virtual int32_t startCapture(const VideoCaptureCapability& capability) = 0;
    virtual int32_t stopCapture() = 0;
    virtual bool captureStarted() = 0;
    virtual int32_t captureSettings(VideoCaptureCapability& settings) = 0;

    virtual bool suspendCapture() = 0;
    virtual bool resumeCapture() = 0;
    virtual bool isSuspended() = 0;
  };
  
  interaction IVideoCaptureDelegate
  {
  };

  interaction IVideoCaptureSubscription
  {
    virtual zsLib::PUID getID() const noexcept = 0;
    virtual void cancel() noexcept = 0;
    virtual void background() noexcept = 0;
  };
} // namespace webrtc


ZS_DECLARE_PROXY_BEGIN(webrtc::IVideoCaptureDelegate)
ZS_DECLARE_PROXY_TYPEDEF(webrtc::IVideoCapturePtr, IVideoCapturePtr)
ZS_DECLARE_PROXY_END()

ZS_DECLARE_PROXY_SUBSCRIPTIONS_BEGIN(webrtc::IVideoCaptureDelegate, webrtc::IVideoCaptureSubscription)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_TYPEDEF(webrtc::IVideoCapturePtr, IVideoCapturePtr)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_END()

#endif //CPPWINRT_VERSION
#endif //WINUWP
