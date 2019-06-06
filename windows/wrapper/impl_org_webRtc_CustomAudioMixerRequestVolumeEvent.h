
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioMixerRequestVolumeEvent.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioMixerRequestVolumeEvent : public wrapper::org::webRtc::CustomAudioMixerRequestVolumeEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioMixerRequestVolumeEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioMixerRequestVolumeEvent, WrapperImplType);

          CustomAudioMixerRequestVolumeEventWeakPtr thisWeak_;
          bool isSpeaker_ {};
          bool isMicrophone_ {};
          int32_t volume_ {};

          CustomAudioMixerRequestVolumeEvent() noexcept;
          virtual ~CustomAudioMixerRequestVolumeEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomAudioMixerRequestVolumeEvent
          bool get_isSpeaker() noexcept override;
          bool get_isMicrophone() noexcept override;
          int32_t get_requestedVolume() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            bool isSpeaker,
            bool isMicrophone,
            int32_t volume) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

