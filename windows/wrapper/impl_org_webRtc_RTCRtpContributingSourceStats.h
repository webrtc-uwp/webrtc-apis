
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCRtpContributingSourceStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"



namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCRtpContributingSourceStats : public wrapper::org::webRtc::RTCRtpContributingSourceStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCRtpContributingSourceStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCRtpContributingSourceStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCPeerConnectionStats, NativeStats);

          RTCRtpContributingSourceStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCRtpContributingSourceStats() noexcept;
          virtual ~RTCRtpContributingSourceStats() noexcept;

          void trace() noexcept;

          // properties RTCStats
          ::zsLib::Time get_timestamp() noexcept override;
          Optional< wrapper::org::webRtc::RTCStatsType > get_statsType() noexcept override;
          String get_statsTypeOther() noexcept override;
          String get_id() noexcept override;

          // properties RTCRtpContributingSourceStats
          unsigned long get_contributorSsrc() noexcept override;
          String get_inboundRtpStreamId() noexcept override;
          unsigned long get_packetsContributedTo() noexcept override;
          Optional< double > get_audioLevel() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;

          ZS_NO_DISCARD() static unsigned long get_contributorSsrc(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static String get_inboundRtpStreamId(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long get_packetsContributedTo(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static Optional< double > get_audioLevel(const NativeStats *native) noexcept;

          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

