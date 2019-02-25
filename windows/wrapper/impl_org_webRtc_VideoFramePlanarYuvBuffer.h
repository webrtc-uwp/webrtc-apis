
#pragma once

#include "types.h"
#include "generated/org_webRtc_VideoFramePlanarYuvBuffer.h"

#include "impl_org_webRtc_pre_include.h"
#include "rtc_base/scoped_ref_ptr.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct VideoFramePlanarYuvBuffer : public wrapper::org::webRtc::VideoFramePlanarYuvBuffer
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::VideoFramePlanarYuvBuffer, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::VideoFrameBuffer, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::I420BufferInterface, NativeI420Type);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::I420ABufferInterface, NativeI420AType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::I444BufferInterface, NativeI444Type);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::I010BufferInterface, NativeI010Type);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::PlanarYuvBuffer, NativePlanarYuvBufferType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::PlanarYuv8Buffer, NativePlanarYuv8BufferType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::PlanarYuv16BBuffer, NativePlanarYuv16BufferType);
          
          typedef rtc::scoped_refptr<NativeType> NativeTypeScopedRefPtr;
          typedef rtc::scoped_refptr<NativeI420Type> NativeI420TypeScopedRefPtr;
          typedef rtc::scoped_refptr<NativeI420AType> NativeI420ATypeScopedRefPtr;
          typedef rtc::scoped_refptr<NativeI444Type> NativeI444TypeScopedRefPtr;
          typedef rtc::scoped_refptr<NativeI010Type> NativeI010TypeScopedRefPtr;

          VideoFramePlanarYuvBufferWeakPtr thisWeak_;
          NativeType *native_{};
          NativePlanarYuvBufferType *nativeYuv_{};
          NativePlanarYuv8BufferType *nativeYuv8_{};
          NativePlanarYuv16BufferType *nativeYuv16_{};

          NativeI420TypeScopedRefPtr nativeI420_;
          NativeI420ATypeScopedRefPtr nativeI420A_;
          NativeI444TypeScopedRefPtr nativeI444_;
          NativeI010TypeScopedRefPtr nativeI010_;

          VideoFramePlanarYuvBuffer() noexcept;
          virtual ~VideoFramePlanarYuvBuffer() noexcept;

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

          // properties VideoFramePlanarYuvBuffer
          int get_chromaWidth() noexcept override;
          int get_chromaHeight() noexcept override;
          int get_strideY() noexcept override;
          int get_strideU() noexcept override;
          int get_strideV() noexcept override;
          wrapper::org::webRtc::VideoDataPtr get_y() noexcept override;
          wrapper::org::webRtc::VideoDataPtr get_u() noexcept override;
          wrapper::org::webRtc::VideoDataPtr get_v() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeI420Type *native) noexcept;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeI420TypeScopedRefPtr native) noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeI420AType *native) noexcept;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeI420ATypeScopedRefPtr native) noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeI444Type *native) noexcept;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeI444TypeScopedRefPtr native) noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeI010Type *native) noexcept;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeI010TypeScopedRefPtr native) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

