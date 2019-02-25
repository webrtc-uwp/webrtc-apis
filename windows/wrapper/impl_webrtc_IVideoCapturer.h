
#pragma once

#ifdef WINUWP

#ifdef __has_include
#if __has_include(<winrt/windows.media.core.h>)
#include <winrt/windows.media.core.h>
#endif //__has_include(<winrt/windows.media.core.h>)
#if __has_include(<winrt/windows.media.devices.h>)
#include <winrt/windows.media.devices.h>
#endif //__has_include(<winrt/windows.media.devices.h>)
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

#include <wrapper/generated/types.h>

#include <wrapper/impl_org_webRtc_pre_include.h>
#include <wrapper/impl_org_webRtc_post_include.h>

#include <zsLib/types.h>
#include <zsLib/Proxy.h>
#include <zsLib/ProxySubscriptions.h>

#include <atomic>
#include <mfidl.h>

namespace wrapper {
  namespace org {
    namespace webRtc {
      struct MediaSample;
      ZS_DECLARE_STRUCT_PTR(MediaSample);
    }
  }
}

namespace webrtc
{
  ZS_DECLARE_INTERACTION_PTR(IVideoCapturer);
  ZS_DECLARE_INTERACTION_PROXY(IVideoCapturerDelegate);
  ZS_DECLARE_CLASS_PTR(VideoCapturer);
  ZS_DECLARE_INTERACTION_PROXY_SUBSCRIPTION(IVideoCapturerSubscription, IVideoCapturerDelegate);


  interaction IVideoCapturer
  {
    struct CreationProperties
    {
      IVideoCapturerDelegatePtr delegate_;

      const char *name_ {};
      const char *id_ {};
      bool mrcEnabled_ {};
    };

    static IVideoCapturerUniPtr create(const CreationProperties &info) noexcept;

    virtual IVideoCapturerSubscriptionPtr subscribe(IVideoCapturerDelegatePtr delegate) = 0;

    virtual std::string id() const noexcept = 0;
  };
  
  interaction IVideoCapturerDelegate
  {
    virtual void onVideoFrameReceived(wrapper::org::webRtc::VideoFrameBufferEventPtr event) = 0;
  };

  interaction IVideoCapturerSubscription
  {
    virtual zsLib::PUID getID() const noexcept = 0;
    virtual void cancel() noexcept = 0;
    virtual void background() noexcept = 0;
  };
} // namespace webrtc


ZS_DECLARE_PROXY_BEGIN(webrtc::IVideoCapturerDelegate)
ZS_DECLARE_PROXY_TYPEDEF(webrtc::IVideoCapturerPtr, IVideoCapturerPtr)
ZS_DECLARE_PROXY_METHOD(onVideoFrameReceived, wrapper::org::webRtc::VideoFrameBufferEventPtr)
ZS_DECLARE_PROXY_END()

ZS_DECLARE_PROXY_SUBSCRIPTIONS_BEGIN(webrtc::IVideoCapturerDelegate, webrtc::IVideoCapturerSubscription)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_TYPEDEF(webrtc::IVideoCapturerPtr, IVideoCapturerPtr)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_METHOD(onVideoFrameReceived, wrapper::org::webRtc::VideoFrameBufferEventPtr)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_END()

#endif //CPPWINRT_VERSION
#endif //WINUWP
