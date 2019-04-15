
#ifndef WRAPPER_USE_GENERATED_ORG_WEBRTC_MEDIASOURCE

#pragma once

#include <wrapper/generated/types.h>

namespace wrapper {
  namespace org {
    namespace webRtc {

      struct MediaSource
      {
        static MediaSourcePtr wrapper_create() noexcept;
        virtual ~MediaSource() noexcept {}

      };

    } // webRtc
  } // org
} // namespace wrapper

#endif //ifndef WRAPPER_USE_GENERATED_ORG_WEBRTC_MEDIASOURCE
