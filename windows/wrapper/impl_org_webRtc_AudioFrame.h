
#pragma once

#include "types.h"
#include "generated/org_webRtc_AudioFrame.h"

#include "impl_org_webRtc_pre_include.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct AudioFrame : public wrapper::org::webRtc::AudioFrame
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::AudioFrame, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioFrame, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::AudioFrame, NativeType);

          AudioFrameWeakPtr thisWeak_;

          AudioFrame() noexcept;
          virtual ~AudioFrame() noexcept;


          // methods AudioFrame
          void wrapper_init_org_webRtc_AudioFrame() noexcept override;

          ZS_NO_DISCARD() static NativeTypeUniPtr toNative(WrapperTypePtr wrapper) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

