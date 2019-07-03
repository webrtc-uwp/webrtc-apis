
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioMixerRequestSettingsEvent.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioMixerRequestSettingsEvent : public wrapper::org::webRtc::CustomAudioMixerRequestSettingsEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioMixerRequestSettingsEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioMixerRequestSettingsEvent, WrapperImplType);

          CustomAudioMixerRequestSettingsEventWeakPtr thisWeak_;
          bool isSpeaker_ {};
          bool isMicrophone_ {};
          Optional< bool > enableBuiltInAec_ {};
          Optional< bool > enableBuiltInAgc_ {};
          Optional< bool > enableBuiltInNs_ {};

          CustomAudioMixerRequestSettingsEvent() noexcept;
          virtual ~CustomAudioMixerRequestSettingsEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomAudioMixerRequestSettingsEvent
          bool get_isSpeaker() noexcept override;
          bool get_isMicrophone() noexcept override;
          Optional< bool > get_enableBuiltInAec() noexcept override;
          Optional< bool > get_enableBuiltInAgc() noexcept override;
          Optional< bool > get_enableBuiltInNs() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            bool isSpeaker,
            bool isMicrophone,
            const Optional< bool > &enableBuiltInAec,
            const Optional< bool > &enableBuiltInAgc,
            const Optional< bool > &enableBuiltInNs) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

