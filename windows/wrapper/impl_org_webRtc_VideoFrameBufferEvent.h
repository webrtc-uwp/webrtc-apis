
#pragma once

#include "types.h"
#include "generated/org_webRtc_VideoFrameBufferEvent.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct VideoFrameBufferEvent : public wrapper::org::webRtc::VideoFrameBufferEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::VideoFrameBufferEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFrameBufferEvent, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::VideoFrameBuffer, UseVideoFrameBuffer);

          VideoFrameBufferEventWeakPtr thisWeak_;
          UseVideoFrameBufferPtr buffer_;

          VideoFrameBufferEvent() noexcept;
          virtual ~VideoFrameBufferEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties VideoFrameBufferEvent
          wrapper::org::webRtc::VideoFrameBufferPtr get_buffer() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(UseVideoFrameBufferPtr buffer) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

