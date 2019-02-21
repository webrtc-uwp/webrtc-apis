
#pragma once

#include "types.h"
#include "generated/org_webRtc_AudioBufferEvent.h"

#include "impl_org_webRtc_pre_include.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct AudioBufferEvent : public wrapper::org::webRtc::AudioBufferEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::AudioBufferEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioBufferEvent, WrapperImplType);

          ZS_DECLARE_TYPEDEF_PTR(::webrtc::AudioBuffer, AudioBufferNativeType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioBuffer, UseAudioBuffer);

          AudioBufferEventWeakPtr thisWeak_;
          zsLib::Lock lock_;
          std::function<void(void)> complete_;
          UseAudioBufferPtr buffer_;

          AudioBufferEvent() noexcept;
          virtual ~AudioBufferEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties AudioBufferEvent
          wrapper::org::webRtc::AudioBufferPtr get_buffer() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            std::function<void(void)> completeFunction,
            AudioBufferNativeType *buffer
            ) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

