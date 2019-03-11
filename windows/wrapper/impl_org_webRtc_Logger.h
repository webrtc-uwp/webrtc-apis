
#pragma once

#include "types.h"
#include "generated/org_webRtc_Logger.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct Logger : public wrapper::org::webRtc::Logger
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::Logger, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::Logger, WrapperImplType);
          Logger() noexcept = delete;
          Logger(const Logger &) noexcept = delete;
          virtual ~Logger() noexcept;

        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

