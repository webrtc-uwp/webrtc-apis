
#pragma once

#include "types.h"
#include "generated/org_webRtc_VideoFrameNativeBuffer.h"


#include "impl_org_webRtc_pre_include.h"
//#include "rtc_base/scoped_ref_ptr.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct VideoFrameNativeBuffer : public wrapper::org::webRtc::VideoFrameNativeBuffer
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::VideoFrameNativeBuffer, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFrameNativeBuffer, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::NativeHandleBuffer, NativeNativeHandleBufferType);

          typedef rtc::scoped_refptr<NativeNativeHandleBufferType> NativeNativeHandleBufferTypeScopedRefPtr;

          VideoFrameNativeBufferWeakPtr thisWeak_;
          NativeNativeHandleBufferTypeScopedRefPtr native_;

          VideoFrameNativeBuffer() noexcept;
          virtual ~VideoFrameNativeBuffer() noexcept;

          void wrapper_dispose() noexcept override;

          // methods VideoFrameBuffer
          wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr toI420() noexcept override;

          // properties VideoFrameBuffer
          wrapper::org::webRtc::VideoFrameBufferType get_type() noexcept override;
          int get_width() noexcept override;
          int get_height() noexcept override;
          wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr get_yuvFrame() noexcept override;
          wrapper::org::webRtc::VideoFramePlanarYuvaBufferPtr get_yuvaFrame() noexcept override;
          wrapper::org::webRtc::VideoFrameNativeBufferPtr get_nativeFrame() noexcept override;

          // properties VideoFrameNativeBuffer
          wrapper::org::webRtc::MediaSamplePtr get_sample() noexcept override;

          ZS_NO_DISCARD() static NativeNativeHandleBufferTypeScopedRefPtr toNative(WrapperTypePtr wrapper) noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeNativeHandleBufferType *native) noexcept;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeNativeHandleBufferTypeScopedRefPtr native) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

