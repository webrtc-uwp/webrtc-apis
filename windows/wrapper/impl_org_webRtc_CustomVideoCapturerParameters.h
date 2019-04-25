
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomVideoCapturerParameters.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomVideoCapturerParameters : public wrapper::org::webRtc::CustomVideoCapturerParameters
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomVideoCapturerParameters, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturerParameters, WrapperImplType);
          CustomVideoCapturerParametersWeakPtr thisWeak_;

          CustomVideoCapturerParameters() noexcept;
          virtual ~CustomVideoCapturerParameters() noexcept;

          void wrapper_init_org_webRtc_CustomVideoCapturerParameters() noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

