
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
          bool isSpeaker_ {};
          bool isMicrophone_ {};
          wrapper::org::webRtc::CustomAudioRequestState state_ {};

          CustomAudioMixerRequestStateEvent() noexcept;
          virtual ~CustomAudioMixerRequestStateEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomAudioMixerRequestStateEvent
          bool get_isSpeaker() noexcept override;
          bool get_isMicrophone() noexcept override;
          wrapper::org::webRtc::CustomAudioRequestState get_requestedState() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            bool isSpeaker,
            bool isMicrophone,
            wrapper::org::webRtc::CustomAudioRequestState state) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

