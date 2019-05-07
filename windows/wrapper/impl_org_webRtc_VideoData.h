
#pragma once

#include "types.h"
#include "generated/org_webRtc_VideoData.h"

#include "impl_org_webRtc_pre_include.h"
#include "rtc_base/scoped_ref_ptr.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct VideoData : public wrapper::org::webRtc::VideoData
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::VideoData, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoData, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::VideoFrameBuffer, NativeType);

          typedef rtc::scoped_refptr<NativeType> NativeTypeScopedRefPtr;

          VideoDataWeakPtr thisWeak_;
          NativeTypeScopedRefPtr native_;

          std::unique_ptr<uint8_t> allocatedRawBuffer_;
          const uint8_t *buffer8bit_ {};
          const uint16_t *buffer16bit_ {};
          size_t size_ {};

          VideoData() noexcept;
          virtual ~VideoData() noexcept;
          void wrapper_dispose() noexcept override;


          // properties VideoData
          bool get_is8BitColorSpace() noexcept override;
          bool get_is16BitColorSpace() noexcept override;
          const uint8_t *get_data8bit() noexcept override;
          const uint16_t *get_data16bit() noexcept override;

          size_t get_size() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            NativeType *native,
            const uint8_t *buffer,
            size_t size) noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            NativeTypeScopedRefPtr native,
            const uint8_t *buffer,
            size_t size) noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            NativeType *native,
            const uint16_t *buffer,
            size_t size) noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            NativeTypeScopedRefPtr native,
            const uint16_t *buffer,
            size_t size) noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            std::unique_ptr<uint8_t> allocatedRawBuffer,
            size_t size) noexcept;

        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

