
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioMixerRequestSettings.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioMixerRequestSettings : public wrapper::org::webRtc::CustomAudioMixerRequestSettings
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioMixerRequestSettings, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioMixerRequestSettings, WrapperImplType);
          CustomAudioMixerRequestSettingsWeakPtr thisWeak_;

          CustomAudioMixerRequestSettings() noexcept;
          virtual ~CustomAudioMixerRequestSettings() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomAudioMixerRequestSettings
          bool get_isSpeaker() noexcept override;
          bool get_isMicrophone() noexcept override;
          Optional< bool > get_enableBuiltInAec() noexcept override;
          Optional< bool > get_enableBuiltInAgc() noexcept override;
          Optional< bool > get_enableBuiltInNs() noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

