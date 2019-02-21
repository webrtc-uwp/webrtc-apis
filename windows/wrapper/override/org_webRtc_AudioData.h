
#ifndef WRAPPER_USE_GENERATED_ORG_WEBRTC_AUDIODATA

#pragma once

#include "types.h"

namespace wrapper {
  namespace org {
    namespace webRtc {

      struct AudioData
      {
        static AudioDataPtr wrapper_create() noexcept;
        virtual ~AudioData() noexcept {}


        virtual void wrapper_init_org_webRtc_AudioData() noexcept = 0;
        virtual void wrapper_init_org_webRtc_AudioData(size_t size) noexcept = 0;

        virtual bool readOnly() noexcept = 0;
        virtual const int16_t *data() noexcept = 0;
        virtual int16_t *mutableData() noexcept = 0;
        virtual size_t size() noexcept = 0;
      };

    } // webRtc
  } // org
} // namespace wrapper

#endif //ifndef WRAPPER_USE_GENERATED_ORG_WEBRTC_AUDIODATA
