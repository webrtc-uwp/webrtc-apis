
#pragma once

#include "types.h"
#include "generated/org_webRtc_AudioProcessingInitializeEvent.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct AudioProcessingInitializeEvent : public wrapper::org::webRtc::AudioProcessingInitializeEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::AudioProcessingInitializeEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioProcessingInitializeEvent, WrapperImplType);
          
          AudioProcessingInitializeEventWeakPtr thisWeak_;
          zsLib::Lock lock_;
          std::function<void(void)> complete_;
          size_t sampleHzRate_{};
          size_t channels_ {};

          AudioProcessingInitializeEvent() noexcept;
          virtual ~AudioProcessingInitializeEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties AudioProcessingInitializeEvent
          uint64_t get_samplRateHz() noexcept override;
          uint64_t get_channels() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            std::function<void(void)> completeFunction,
            size_t sampleHzRate,
            size_t channels) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

