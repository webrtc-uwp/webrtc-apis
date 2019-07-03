
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomVideoCapturerStartEvent.h"

#include "impl_org_webRtc_pre_include.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomVideoCapturerStartEvent : public wrapper::org::webRtc::CustomVideoCapturerStartEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomVideoCapturerStartEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturerStartEvent, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFormat, UseFormat);

          ZS_DECLARE_TYPEDEF_PTR(::cricket::VideoFormat, NativeType);

          CustomVideoCapturerStartEventWeakPtr thisWeak_;
          UseFormatPtr format_;

          CustomVideoCapturerStartEvent() noexcept;
          virtual ~CustomVideoCapturerStartEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomVideoCapturerStartEvent
          wrapper::org::webRtc::VideoFormatPtr get_format() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(const ::cricket::VideoFormat &format) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

