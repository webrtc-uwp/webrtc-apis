
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioMixerRequestStereo.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioMixerRequestStereo : public wrapper::org::webRtc::CustomAudioMixerRequestStereo
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioMixerRequestStereo, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioMixerRequestStereo, WrapperImplType);
          CustomAudioMixerRequestStereoWeakPtr thisWeak_;

          CustomAudioMixerRequestStereo() noexcept;
          virtual ~CustomAudioMixerRequestStereo() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomAudioMixerRequestStereo
          bool get_isSpeaker() noexcept override;
          bool get_isMicrophone() noexcept override;
          bool get_stereo() noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

