
#pragma once

#include "types.h"
#include "generated/org_webRtc_WebRtcLibConfiguration.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct WebRtcLibConfiguration : public wrapper::org::webRtc::WebRtcLibConfiguration
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::WebRtcLibConfiguration, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::WebRtcLibConfiguration, WrapperImplType);
          WebRtcLibConfigurationWeakPtr thisWeak_;

          WebRtcLibConfiguration() noexcept;
          virtual ~WebRtcLibConfiguration() noexcept;

          void wrapper_init_org_webRtc_WebRtcLibConfiguration() noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

