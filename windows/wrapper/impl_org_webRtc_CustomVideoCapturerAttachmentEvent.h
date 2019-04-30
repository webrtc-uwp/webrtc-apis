
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomVideoCapturerAttachmentEvent.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomVideoCapturerAttachmentEvent : public wrapper::org::webRtc::CustomVideoCapturerAttachmentEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomVideoCapturerAttachmentEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturerAttachmentEvent, WrapperImplType);

          CustomVideoCapturerAttachmentEventWeakPtr thisWeak_;
          uint64_t id_ {};

          CustomVideoCapturerAttachmentEvent() noexcept;
          virtual ~CustomVideoCapturerAttachmentEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomVideoCapturerAttachmentEvent
          uint64_t get_id() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(uint64_t id) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

