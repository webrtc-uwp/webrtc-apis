
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioDeviceParameters.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioDeviceParameters : public wrapper::org::webRtc::CustomAudioDeviceParameters
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioDeviceParameters, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioDeviceParameters, WrapperImplType);
          CustomAudioDeviceParametersWeakPtr thisWeak_;

          CustomAudioDeviceParameters() noexcept;
          virtual ~CustomAudioDeviceParameters() noexcept;

          void wrapper_init_org_webRtc_CustomAudioDeviceParameters() noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

