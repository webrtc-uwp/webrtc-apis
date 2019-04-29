
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioRecordingDeviceInfo.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioRecordingDeviceInfo : public wrapper::org::webRtc::CustomAudioRecordingDeviceInfo
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioRecordingDeviceInfo, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioRecordingDeviceInfo, WrapperImplType);
          CustomAudioRecordingDeviceInfoWeakPtr thisWeak_;

          CustomAudioRecordingDeviceInfo() noexcept;
          virtual ~CustomAudioRecordingDeviceInfo() noexcept;

          void wrapper_init_org_webRtc_CustomAudioRecordingDeviceInfo() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr clone(WrapperTypePtr wrapper) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

