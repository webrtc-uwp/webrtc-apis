
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioMixerRequestStateEvent.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioMixerRequestStateEvent : public wrapper::org::webRtc::CustomAudioMixerRequestStateEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioMixerRequestStateEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioMixerRequestStateEvent, WrapperImplType);
          CustomAudioMixerRequestStateEventWeakPtr thisWeak_;

          CustomAudioMixerRequestStateEvent() noexcept;
          virtual ~CustomAudioMixerRequestStateEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomAudioMixerRequestStateEvent
          bool get_isSpeaker() noexcept override;
          bool get_isMicrophone() noexcept override;
          wrapper::org::webRtc::CustomAudioMixerRequestStateEventPtr get_requestedState() noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

