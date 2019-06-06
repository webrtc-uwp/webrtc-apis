
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioDeviceSelectEvent.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioDeviceSelectEvent : public wrapper::org::webRtc::CustomAudioDeviceSelectEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioDeviceSelectEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioDeviceSelectEvent, WrapperImplType);

          CustomAudioDeviceSelectEventWeakPtr thisWeak_;
          uint16_t id_ {};
          bool isRecordingDevice_ {};
          bool isPlayoutDevice_ {};


          CustomAudioDeviceSelectEvent() noexcept;
          virtual ~CustomAudioDeviceSelectEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomAudioDeviceSelectEvent
          uint16_t get_deviceId() noexcept override;
          bool get_isRecordingDevice() noexcept override;
          bool get_isPlayoutDevice() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            uint16_t id,
            bool isRecording,
            bool isPlayout) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

