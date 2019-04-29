
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioDeviceRequestStereoEvent.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioDeviceRequestStereoEvent : public wrapper::org::webRtc::CustomAudioDeviceRequestStereoEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioDeviceRequestStereoEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioDeviceRequestStereoEvent, WrapperImplType);

          CustomAudioDeviceRequestStereoEventWeakPtr thisWeak_;
          bool isRecordingDevice_ {};
          bool isPlayoutDevice_ {};
          bool stereo_ {};

          CustomAudioDeviceRequestStereoEvent() noexcept;
          virtual ~CustomAudioDeviceRequestStereoEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomAudioDeviceRequestStereoEvent
          bool get_isRecordingDevice() noexcept override;
          bool get_isPlayoutDevice() noexcept override;
          bool get_stereo() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(
            bool isRecordingDevice,
            bool isPlayoutDevice,
            bool stereo) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

