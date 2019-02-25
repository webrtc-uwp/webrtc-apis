
#pragma once

#include "types.h"
#include "generated/org_webRtc_AudioBuffer.h"

#include "impl_org_webRtc_pre_include.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct AudioBuffer : public wrapper::org::webRtc::AudioBuffer
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::AudioBuffer, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioBuffer, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::AudioBuffer, NativeType);

          AudioBufferWeakPtr thisWeak_;

          zsLib::Lock lock_;
          NativeType *native_ {};
          NativeTypeUniPtr nativeStorage_;

          AudioBuffer() noexcept;
          virtual ~AudioBuffer() noexcept;
          void wrapper_dispose() noexcept override;


          // methods AudioBuffer
          void wrapper_init_org_webRtc_AudioBuffer(wrapper::org::webRtc::AudioBufferConfigurationPtr config) noexcept override;
          wrapper::org::webRtc::AudioDataPtr channel(uint64_t channel) noexcept override;
          wrapper::org::webRtc::AudioDataPtr splitBand(
            uint64_t channel,
            wrapper::org::webRtc::Band band
            ) noexcept override;
          wrapper::org::webRtc::AudioDataPtr splitChannel(
            wrapper::org::webRtc::Band band,
            uint64_t channel
            ) noexcept override;
          wrapper::org::webRtc::AudioDataPtr lowPassReference(uint64_t channel) noexcept override;
          void deinterleaveFrom(wrapper::org::webRtc::AudioFramePtr frame) noexcept override;
          void interleaveTo(wrapper::org::webRtc::AudioFramePtr frame) noexcept override;
          void copyLowPassToReference() noexcept override;
          void splitIntoFrequencyBands() noexcept override;
          void mergeFrequencyBands() noexcept override;

          // properties AudioBuffer
          uint64_t get_channels() noexcept override;
          uint64_t get_samplesPerChannel() noexcept override;
          uint64_t get_bands() noexcept override;
          uint64_t get_framesPerBand() noexcept override;
          wrapper::org::webRtc::AudioDataPtr get_mixedLowPassData() noexcept override;
          wrapper::org::webRtc::VadActivity get_activity() noexcept override;
          void set_activity(wrapper::org::webRtc::VadActivity value) noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeType *native) noexcept;
          ZS_NO_DISCARD() static NativeType *toNative(WrapperTypePtr wrapper) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

