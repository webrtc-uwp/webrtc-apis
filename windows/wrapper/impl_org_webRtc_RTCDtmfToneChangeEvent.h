
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCDtmfToneChangeEvent.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCDtmfToneChangeEvent : public wrapper::org::webRtc::RTCDtmfToneChangeEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCDtmfToneChangeEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCDtmfToneChangeEvent, WrapperImplType);

          String tone_;
          String toneBuffer_;
          RTCDtmfToneChangeEventWeakPtr thisWeak_;

          RTCDtmfToneChangeEvent() noexcept;
          virtual ~RTCDtmfToneChangeEvent() noexcept;


          // properties RTCDtmfToneChangeEvent
          String get_tone() noexcept override;
          String get_toneBuffer() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            const String &tone,
            const String &toneBuffer) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

