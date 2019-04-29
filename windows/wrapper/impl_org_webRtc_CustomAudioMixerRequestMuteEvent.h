
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioMixerRequestMuteEvent.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioMixerRequestMuteEvent : public wrapper::org::webRtc::CustomAudioMixerRequestMuteEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioMixerRequestMuteEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioMixerRequestMuteEvent, WrapperImplType);

          CustomAudioMixerRequestMuteEventWeakPtr thisWeak_;
          bool isSpeaker_ {};
          bool isMicrophone_ {};
          bool mute_ {};

          CustomAudioMixerRequestMuteEvent() noexcept;
          virtual ~CustomAudioMixerRequestMuteEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomAudioMixerRequestMuteEvent
          bool get_isSpeaker() noexcept override;
          bool get_isMicrophone() noexcept override;
          bool get_mute() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            bool isSpeaker,
            bool isMicrophone,
            bool mute) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

