
#pragma once

#include "types.h"
#include "generated/org_webRtc_AudioData.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct AudioData : public wrapper::org::webRtc::AudioData
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::AudioData, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioData, WrapperImplType);

          AudioDataWeakPtr thisWeak_;
          zsLib::Lock lock_;
          int16_t *mutableData_ {};
          const int16_t *data_ {};
          size_t size_ {};
          std::vector<int16_t> buffer_;

          AudioData() noexcept;
          virtual ~AudioData() noexcept;
          void wrapper_dispose() noexcept override;


          // methods AudioData
          void wrapper_init_org_webRtc_AudioData() noexcept override;
          void wrapper_init_org_webRtc_AudioData(size_t size) noexcept override;

          // properties AudioData
          bool readOnly() noexcept override;
          const int16_t *data() noexcept override;
          int16_t *mutableData() noexcept override;
          size_t size() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            int16_t *value,
            size_t size) noexcept;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            const int16_t *value,
            size_t size) noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(WrapperTypePtr wrapper) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

