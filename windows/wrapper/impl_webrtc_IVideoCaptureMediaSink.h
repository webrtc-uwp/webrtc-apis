
#pragma once

#ifdef WINUWP

#ifdef __has_include
#if __has_include(<winrt/windows.media.core.h>)
#include <winrt/windows.media.core.h>
#endif //__has_include(<winrt/windows.media.core.h>)
#if __has_include(<winrt/windows.media.h>)
#include <winrt/windows.media.h>
#endif //__has_include(<winrt/windows.media.h>)
#if __has_include(<winrt/windows.media.mediaproperties.h>)
#include <winrt/windows.media.mediaproperties.h>
#endif //__has_include(<winrt/windows.media.mediaproperties.h>)
#endif //__has_include

#ifdef CPPWINRT_VERSION

#include <wrapper/impl_org_webRtc_pre_include.h>
#include <wrapper/impl_org_webRtc_post_include.h>

#include <zsLib/types.h>
#include <zsLib/Proxy.h>
#include <zsLib/ProxySubscriptions.h>

#include <atomic>
#include <mfidl.h>


namespace webrtc
{
  ZS_DECLARE_INTERACTION_PTR(IVideoCaptureMediaSink);
  ZS_DECLARE_INTERACTION_PROXY(IVideoCaptureMediaSinkDelegate);
  ZS_DECLARE_CLASS_PTR(VideoCaptureMediaSink);
  ZS_DECLARE_INTERACTION_PROXY_SUBSCRIPTION(IVideoCaptureMediaSinkSubscription, IVideoCaptureMediaSinkDelegate);

  class ISinkCallback;

  interaction IVideoCaptureMediaSink
  {
    struct CreationProperties
    {
      IVideoCaptureMediaSinkDelegatePtr delegate_;
      ISinkCallback *callback_;
      winrt::Windows::Media::MediaProperties::IMediaEncodingProperties encodingProperties_;

      const char *id_{};
    };

    static winrt::Windows::Media::IMediaExtension create(const CreationProperties &info) noexcept;

    virtual IVideoCaptureMediaSinkSubscriptionPtr subscribe(IVideoCaptureMediaSinkDelegatePtr delegate) = 0;

    virtual std::string id() const noexcept = 0;
  };
  
  interaction IVideoCaptureMediaSinkDelegate
  {
    virtual void onDummyEvent(IVideoCaptureMediaSinkPtr source) = 0;
  };

  interaction IVideoCaptureMediaSinkSubscription
  {
    virtual zsLib::PUID getID() const noexcept = 0;
    virtual void cancel() noexcept = 0;
    virtual void background() noexcept = 0;
  };
} // namespace webrtc


ZS_DECLARE_PROXY_BEGIN(webrtc::IVideoCaptureMediaSinkDelegate)
ZS_DECLARE_PROXY_TYPEDEF(webrtc::IVideoCaptureMediaSinkPtr, IVideoCaptureMediaSinkPtr)
ZS_DECLARE_PROXY_METHOD(onDummyEvent, IVideoCaptureMediaSinkPtr)
ZS_DECLARE_PROXY_END()

ZS_DECLARE_PROXY_SUBSCRIPTIONS_BEGIN(webrtc::IVideoCaptureMediaSinkDelegate, webrtc::IVideoCaptureMediaSinkSubscription)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_TYPEDEF(webrtc::IVideoCaptureMediaSinkPtr, IVideoCaptureMediaSinkPtr)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_METHOD(onDummyEvent, IVideoCaptureMediaSinkPtr)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_END()

#endif //CPPWINRT_VERSION
#endif //WINUWP
