
#pragma once

#include "types.h"
#include "generated/org_webRtc_VideoCapturerCreationParameters.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct VideoCapturerCreationParameters : public wrapper::org::webRtc::VideoCapturerCreationParameters
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::VideoCapturerCreationParameters, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoCapturerCreationParameters, WrapperImplType);
          VideoCapturerCreationParametersWeakPtr thisWeak_;

          VideoCapturerCreationParameters() noexcept;
          virtual ~VideoCapturerCreationParameters() noexcept;

          void wrapper_init_org_webRtc_VideoCapturerCreationParameters() noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

