
#pragma once

#ifdef WINUWP

#ifdef __has_include
#if __has_include(<winrt/windows.media.core.h>)
#include <winrt/windows.media.core.h>
#endif //__has_include(<winrt/windows.media.core.h>)
#if __has_include(<winrt/windows.media.devices.h>)
#include <winrt/windows.media.devices.h>
#endif //__has_include(<winrt/windows.media.devices.h>)
#if __has_include(<winrt/windows.devices.enumeration.h>)
#include <winrt/windows.devices.enumeration.h>
#endif //__has_include(<winrt/windows.devices.enumeration.h>)
#if __has_include(<winrt/windows.media.effects.h>)
#include <winrt/windows.media.effects.h>
#endif //__has_include(<winrt/windows.media.effects.h>)
#endif //__has_include

#ifdef CPPWINRT_VERSION

#include <wrapper/impl_org_webRtc_pre_include.h>
#include "modules/audio_device/include/audio_device.h"
#include <wrapper/impl_org_webRtc_post_include.h>

#include <zsLib/types.h>
#include <zsLib/Proxy.h>
#include <zsLib/ProxySubscriptions.h>

#include <atomic>
#include <wrl.h>
#include <mfidl.h>


namespace webrtc
{
  ZS_DECLARE_INTERACTION_PTR(IAudioDeviceWasapi);
  ZS_DECLARE_INTERACTION_PROXY(IAudioDeviceWasapiDelegate);
  ZS_DECLARE_CLASS_PTR(AudioDeviceWasapi);
  ZS_DECLARE_INTERACTION_PROXY_SUBSCRIPTION(IAudioDeviceWasapiSubscription, IAudioDeviceWasapiDelegate);


  interaction IAudioDeviceWasapi
  {
    struct CreationProperties
    {
      IAudioDeviceWasapiDelegatePtr delegate_;

      const char *id_{};

			bool recordingEnabled_;
			bool playoutEnabled_;
    };

    static rtc::scoped_refptr<AudioDeviceModule> create(const CreationProperties &info) noexcept;

    virtual IAudioDeviceWasapiSubscriptionPtr subscribe(IAudioDeviceWasapiDelegatePtr delegate) = 0;

    virtual std::string id() const noexcept = 0;
  };
  
  interaction IAudioDeviceWasapiDelegate
  {
    virtual void onDefaultAudioCaptureDeviceChanged() = 0;
    virtual void onDefaultAudioRendereDeviceChanged() = 0;
  };

  interaction IAudioDeviceWasapiSubscription
  {
    virtual zsLib::PUID getID() const noexcept = 0;
    virtual void cancel() noexcept = 0;
    virtual void background() noexcept = 0;
  };
} // namespace webrtc


ZS_DECLARE_PROXY_BEGIN(webrtc::IAudioDeviceWasapiDelegate)
ZS_DECLARE_PROXY_TYPEDEF(webrtc::IAudioDeviceWasapiPtr, IAudioDeviceWasapiPtr)
ZS_DECLARE_PROXY_METHOD(onDefaultAudioCaptureDeviceChanged)
ZS_DECLARE_PROXY_METHOD(onDefaultAudioRendereDeviceChanged)
ZS_DECLARE_PROXY_END()

ZS_DECLARE_PROXY_SUBSCRIPTIONS_BEGIN(webrtc::IAudioDeviceWasapiDelegate, webrtc::IAudioDeviceWasapiSubscription)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_TYPEDEF(webrtc::IAudioDeviceWasapiPtr, IAudioDeviceWasapiPtr)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_METHOD(onDefaultAudioCaptureDeviceChanged)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_METHOD(onDefaultAudioRendereDeviceChanged)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_END()

#endif //CPPWINRT_VERSION
#endif //WINUWP
