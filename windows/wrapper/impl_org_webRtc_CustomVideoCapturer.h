
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomVideoCapturer.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomVideoCapturer : public wrapper::org::webRtc::CustomVideoCapturer
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomVideoCapturer, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturer, WrapperImplType);
          CustomVideoCapturerWeakPtr thisWeak_;

          CustomVideoCapturer() noexcept;
          virtual ~CustomVideoCapturer() noexcept;
          void wrapper_dispose() noexcept override;


          // methods CustomVideoCapturer
          void notifyFrame(
            wrapper::org::webRtc::VideoFrameBufferPtr frame,
            int origWidth,
            int origHeight
            ) noexcept override;

          // properties CustomVideoCapturer
          wrapper::org::webRtc::VideoCaptureState get_currentState() noexcept override;
          void set_currentState(wrapper::org::webRtc::VideoCaptureState value) noexcept override;

          void wrapper_onObserverCountChanged(size_t count) noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

