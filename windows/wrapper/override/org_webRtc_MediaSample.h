
#ifndef WRAPPER_USE_GENERATED_ORG_WEBRTC_MEDIASAMPLE

#pragma once

#include <wrapper/generated/types.h>

namespace wrapper {
  namespace org {
    namespace webRtc {

      struct MediaSample
      {
        static MediaSamplePtr wrapper_create() noexcept;
        virtual ~MediaSample() noexcept {}
        virtual void wrapper_dispose() noexcept = 0;
      };

    } // webRtc
  } // org
} // namespace wrapper

#endif //ifndef WRAPPER_USE_GENERATED_ORG_WEBRTC_MEDIASAMPLE
