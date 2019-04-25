
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioMixerRequestVolume.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioMixerRequestVolume : public wrapper::org::webRtc::CustomAudioMixerRequestVolume
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioMixerRequestVolume, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioMixerRequestVolume, WrapperImplType);
          CustomAudioMixerRequestVolumeWeakPtr thisWeak_;

          CustomAudioMixerRequestVolume() noexcept;
          virtual ~CustomAudioMixerRequestVolume() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomAudioMixerRequestVolume
          bool get_isSpeaker() noexcept override;
          bool get_isMicrophone() noexcept override;
          int32_t get_requestedVolume() noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

