
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomVideoCapturerStartEvent.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomVideoCapturerStartEvent : public wrapper::org::webRtc::CustomVideoCapturerStartEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomVideoCapturerStartEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturerStartEvent, WrapperImplType);
          CustomVideoCapturerStartEventWeakPtr thisWeak_;

          CustomVideoCapturerStartEvent() noexcept;
          virtual ~CustomVideoCapturerStartEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomVideoCapturerStartEvent
          wrapper::org::webRtc::VideoFormatPtr get_format() noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

