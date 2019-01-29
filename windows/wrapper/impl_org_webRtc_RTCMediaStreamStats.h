
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCMediaStreamStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCMediaStreamStats : public wrapper::org::webRtc::RTCMediaStreamStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCMediaStreamStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCMediaStreamStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCMediaStreamStats, NativeStats);

          RTCMediaStreamStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCMediaStreamStats() noexcept;
          virtual ~RTCMediaStreamStats() noexcept;

          void trace() noexcept;

          // properties RTCStats
          ::zsLib::Time get_timestamp() noexcept override;
          Optional< wrapper::org::webRtc::RTCStatsType > get_statsType() noexcept override;
          String get_statsTypeOther() noexcept override;
          String get_id() noexcept override;

          // properties RTCMediaStreamStats
          String get_streamIdentifier() noexcept override;
          shared_ptr< list< String > > get_trackIds() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;
          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

