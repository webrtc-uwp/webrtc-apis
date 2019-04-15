
#ifndef WRAPPER_USE_GENERATED_ORG_WEBRTC_VIDEODEVICEINFO
#pragma once

#include "types.h"

namespace wrapper {
  namespace org {
    namespace webRtc {

      struct VideoDeviceInfo
      {
        static VideoDeviceInfoPtr wrapper_create() noexcept;
        virtual ~VideoDeviceInfo() noexcept {}

        virtual String get_id() noexcept = 0;
        virtual String get_name() noexcept = 0;
        virtual bool get_isDefault() noexcept = 0;
        virtual bool get_isEnabled() noexcept = 0;

      };

    } // webRtc
  } // org
} // namespace wrapper

#endif //ifndef WRAPPER_USE_GENERATED_ORG_WEBRTC_VIDEODEVICEINFO
