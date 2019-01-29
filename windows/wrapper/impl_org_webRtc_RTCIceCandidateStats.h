
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCIceCandidateStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCIceCandidateStats : public wrapper::org::webRtc::RTCIceCandidateStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCIceCandidateStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCIceCandidateStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCIceCandidateStats, NativeStats);

          RTCIceCandidateStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCIceCandidateStats() noexcept;
          virtual ~RTCIceCandidateStats() noexcept;

          void trace() noexcept;

          // properties RTCStats
          ::zsLib::Time get_timestamp() noexcept override;
          Optional< wrapper::org::webRtc::RTCStatsType > get_statsType() noexcept override;
          String get_statsTypeOther() noexcept override;
          String get_id() noexcept override;

          // properties RTCIceCandidateStats
          String get_transportId() noexcept override;
          wrapper::org::webRtc::RTCNetworkType get_networkType() noexcept override;
          String get_ip() noexcept override;
          long get_port() noexcept override;
          String get_protocol() noexcept override;
          wrapper::org::webRtc::RTCIceCandidateType get_candidateType() noexcept override;
          long get_priority() noexcept override;
          String get_url() noexcept override;
          String get_relayProtocol() noexcept override;
          Optional< bool > get_deleted() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;
          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

