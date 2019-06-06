
#pragma once

#include "types.h"
#include "generated/org_webRtc_VideoFrameBuffer.h"


#include "impl_org_webRtc_pre_include.h"
#include "api/scoped_refptr.h"
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
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoData, UseVideoData);

          typedef rtc::scoped_refptr<NativeType> NativeTypeScopedRefPtr;

          VideoFrameBufferWeakPtr thisWeak_;
          NativeTypeScopedRefPtr native_;


          VideoFrameBuffer() noexcept;
          virtual ~VideoFrameBuffer() noexcept;
          void wrapper_dispose() noexcept override;


          // methods VideoFrameBuffer
          wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr toI420() noexcept override;
          wrapper::org::webRtc::VideoDataPtr toARGB() noexcept override;
          wrapper::org::webRtc::VideoDataPtr toBGRA() noexcept override;
          wrapper::org::webRtc::VideoDataPtr toABGR() noexcept override;
          wrapper::org::webRtc::VideoDataPtr toRGBA() noexcept override;
          wrapper::org::webRtc::VideoDataPtr toRGB24() noexcept override;

          // properties VideoFrameBuffer
          wrapper::org::webRtc::VideoFrameBufferType get_type() noexcept override;
          int get_width() noexcept override;
          int get_height() noexcept override;

          wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr get_yuvFrame() noexcept override;
          wrapper::org::webRtc::VideoFramePlanarYuvaBufferPtr get_yuvaFrame() noexcept override;
          wrapper::org::webRtc::VideoFrameNativeBufferPtr get_nativeFrame() noexcept override;

          ZS_NO_DISCARD() static NativeTypeScopedRefPtr toNative(WrapperType *type) noexcept;
          ZS_NO_DISCARD() static NativeTypeScopedRefPtr toNative(WrapperTypePtr type) noexcept;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeType *native) noexcept;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeTypeScopedRefPtr native) noexcept;

          ZS_NO_DISCARD() static wrapper::org::webRtc::VideoDataPtr toARGB(NativeType *native) noexcept;
          ZS_NO_DISCARD() static wrapper::org::webRtc::VideoDataPtr toBGRA(NativeType *native) noexcept;
          ZS_NO_DISCARD() static wrapper::org::webRtc::VideoDataPtr toABGR(NativeType *native) noexcept;
          ZS_NO_DISCARD() static wrapper::org::webRtc::VideoDataPtr toRGBA(NativeType *native) noexcept;
          ZS_NO_DISCARD() static wrapper::org::webRtc::VideoDataPtr toRGB24(NativeType *native) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

