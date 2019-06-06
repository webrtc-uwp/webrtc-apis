
#ifndef WRAPPER_USE_GENERATED_ORG_WEBRTC_VIDEODATA

#pragma once

#include "types.h"

namespace wrapper {
  namespace org {
    namespace webRtc {

      struct VideoData
      {
        static VideoDataPtr wrapper_create() noexcept;
        virtual ~VideoData() noexcept {}

        virtual void wrapper_dispose() noexcept = 0;

        virtual void wrapper_init_org_webRtc_VideoData(size_t size) noexcept = 0;

        virtual bool get_is8BitColorSpace() noexcept = 0;
        virtual bool get_is16BitColorSpace() noexcept = 0;
        virtual const uint8_t *get_data8bit() noexcept = 0;
        virtual const uint16_t *get_data16bit() noexcept = 0;

        virtual uint8_t *get_mutableData8bit() noexcept = 0;
        virtual uint16_t *get_mutableData16bit() noexcept = 0;

        virtual size_t get_size() noexcept = 0;
      };

    } // webRtc
  } // org
} // namespace wrapper

#endif //ifndef WRAPPER_USE_GENERATED_ORG_WEBRTC_VIDEODATA
