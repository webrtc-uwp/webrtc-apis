
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


        virtual void wrapper_init_org_webRtc_AudioData() noexcept { }

        virtual bool get_readOnly() noexcept = 0;
        virtual shared_ptr< list< int16_t > > get_data() noexcept = 0;
        virtual void set_data(shared_ptr< list< int16_t > > value) noexcept = 0;
      };

    } // webRtc
  } // org
} // namespace wrapper

#endif //ifndef WRAPPER_USE_GENERATED_ORG_WEBRTC_AUDIODATA
