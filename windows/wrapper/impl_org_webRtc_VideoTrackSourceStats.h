
#pragma once

#include "types.h"
#include "generated/org_webRtc_VideoTrackSourceStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api\media_stream_interface.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct VideoTrackSourceStats : public wrapper::org::webRtc::VideoTrackSourceStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::VideoTrackSourceStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoTrackSourceStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::VideoTrackSourceInterface::Stats, NativeType);

          VideoTrackSourceStatsWeakPtr thisWeak_;

          VideoTrackSourceStats() noexcept;
          virtual ~VideoTrackSourceStats() noexcept;

          void wrapper_init_org_webRtc_VideoTrackSourceStats() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(const NativeType &native) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

