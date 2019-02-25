
#pragma once

#include "types.h"
#include "generated/org_webRtc_VideoFrameBuffer.h"


#include "impl_org_webRtc_pre_include.h"
#include "rtc_base/scoped_ref_ptr.h"
#include "impl_org_webRtc_post_include.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct VideoFrameBuffer : public wrapper::org::webRtc::VideoFrameBuffer
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::VideoFrameBuffer, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFrameBuffer, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::VideoFrameBuffer, NativeType);

          typedef rtc::scoped_refptr<NativeType> NativeTypeScopedRefPtr;

          VideoFrameBufferWeakPtr thisWeak_;
          NativeTypeScopedRefPtr native_;


          VideoFrameBuffer() noexcept;
          virtual ~VideoFrameBuffer() noexcept;
          void wrapper_dispose() noexcept override;


          // methods VideoFrameBuffer
          wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr toI420() noexcept override;

          // properties VideoFrameBuffer
          wrapper::org::webRtc::VideoFrameBufferType get_type() noexcept override;
          int get_width() noexcept override;
          int get_height() noexcept override;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeType *native) noexcept;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeTypeScopedRefPtr native) noexcept;
          wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr get_yuvFrame() noexcept override;
          wrapper::org::webRtc::VideoFramePlanarYuvaBufferPtr get_yuvaFrame() noexcept override;
          wrapper::org::webRtc::VideoFrameNativeBufferPtr get_nativeFrame() noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

