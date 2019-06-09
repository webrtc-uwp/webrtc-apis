
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomVideoCapturerCreateEvent.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomVideoCapturerCreateEvent : public wrapper::org::webRtc::CustomVideoCapturerCreateEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomVideoCapturerCreateEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturerCreateEvent, WrapperImplType);

          CustomVideoCapturerCreateEventWeakPtr thisWeak_;
          String deviceId_;
          String deviceName_;
          wrapper::org::webRtc::VideoFormatPtr format_;
          wrapper::org::webRtc::CustomVideoCapturerPtr capturer_;

          CustomVideoCapturerCreateEvent() noexcept;
          virtual ~CustomVideoCapturerCreateEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomVideoCapturerCreateEvent
          String get_deviceId() noexcept override;
          String get_deviceName() noexcept override;
          wrapper::org::webRtc::VideoFormatPtr get_format() noexcept override;
          wrapper::org::webRtc::CustomVideoCapturerPtr get_createdCapturer() noexcept override;
          void set_createdCapturer(wrapper::org::webRtc::CustomVideoCapturerPtr value) noexcept override;

          ZS_NO_DISCARD() static wrapper::org::webRtc::CustomVideoCapturerPtr extractCapturer(WrapperType &wrapperType) noexcept;
          ZS_NO_DISCARD() static wrapper::org::webRtc::CustomVideoCapturerPtr extractCapturer(WrapperType *wrapperType) noexcept;
          ZS_NO_DISCARD() static wrapper::org::webRtc::CustomVideoCapturerPtr extractCapturer(WrapperTypePtr wrapperType) noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            const std::string &deviceId,
            const std::string &deviceName,
            wrapper::org::webRtc::VideoFormatPtr format) noexcept;

        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

