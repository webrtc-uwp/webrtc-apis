
#pragma once

#include "types.h"
#include "generated/org_webRtc_VideoFramePlanarYuvaBuffer.h"

#include "impl_org_webRtc_pre_include.h"
//#include "rtc_base/scoped_ref_ptr.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct VideoFramePlanarYuvaBuffer : public wrapper::org::webRtc::VideoFramePlanarYuvaBuffer
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::VideoFramePlanarYuvaBuffer, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::I420ABufferInterface, NativeI420AType);

          typedef rtc::scoped_refptr<NativeI420AType> NativeI420ATypeScopedRefPtr;

          VideoFramePlanarYuvaBufferWeakPtr thisWeak_;
          NativeI420ATypeScopedRefPtr native_;

          VideoFramePlanarYuvaBuffer() noexcept;
          virtual ~VideoFramePlanarYuvaBuffer() noexcept;

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

          // properties VideoFramePlanarYuvaBuffer
          int get_strideA() noexcept override;
          wrapper::org::webRtc::VideoDataPtr get_a() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeI420AType *native) noexcept;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeI420ATypeScopedRefPtr native) noexcept;

        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

