
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioMixerRequestMute.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioMixerRequestMute : public wrapper::org::webRtc::CustomAudioMixerRequestMute
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioMixerRequestMute, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioMixerRequestMute, WrapperImplType);
          CustomAudioMixerRequestMuteWeakPtr thisWeak_;

          CustomAudioMixerRequestMute() noexcept;
          virtual ~CustomAudioMixerRequestMute() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomAudioMixerRequestMute
          bool get_isSpeaker() noexcept override;
          bool get_isMicrophone() noexcept override;
          bool get_mute() noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

