
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioPlayoutDeviceInfo.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioPlayoutDeviceInfo : public wrapper::org::webRtc::CustomAudioPlayoutDeviceInfo
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioPlayoutDeviceInfo, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioPlayoutDeviceInfo, WrapperImplType);
          CustomAudioPlayoutDeviceInfoWeakPtr thisWeak_;

          CustomAudioPlayoutDeviceInfo() noexcept;
          virtual ~CustomAudioPlayoutDeviceInfo() noexcept;

          void wrapper_init_org_webRtc_CustomAudioPlayoutDeviceInfo() noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

