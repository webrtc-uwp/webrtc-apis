
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCRemoteOutboundRtpStreamStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCRemoteOutboundRtpStreamStats : public wrapper::org::webRtc::RTCRemoteOutboundRtpStreamStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCRemoteOutboundRtpStreamStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCRTPStreamStats, NativeStats);

          RTCRemoteOutboundRtpStreamStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCRemoteOutboundRtpStreamStats() noexcept;
          virtual ~RTCRemoteOutboundRtpStreamStats() noexcept;

          void trace() noexcept;

          // properties RTCStats
          ::zsLib::Time get_timestamp() noexcept override;
          Optional< wrapper::org::webRtc::RTCStatsType > get_statsType() noexcept override;
          String get_statsTypeOther() noexcept override;
          String get_id() noexcept override;

          // properties RTCRtpStreamStats
          Optional< uint32_t > get_ssrc() noexcept override;
          String get_kind() noexcept override;
          String get_transportId() noexcept override;
          String get_codecId() noexcept override;
          unsigned long get_firCount() noexcept override;
          unsigned long get_pliCount() noexcept override;
          unsigned long get_nackCount() noexcept override;
          unsigned long get_sliCount() noexcept override;
          unsigned long long get_qpSum() noexcept override;

          // properties RTCSentRtpStreamStats
          unsigned long get_packetsSent() noexcept override;
          unsigned long get_packetsDiscardedOnSend() noexcept override;
          unsigned long get_fecPacketsSent() noexcept override;
          unsigned long long get_bytesSent() noexcept override;
          unsigned long long get_bytesDiscardedOnSend() noexcept override;

          // properties RTCRemoteOutboundRtpStreamStats
          String get_localId() noexcept override;
          ::zsLib::Time get_remoteTimestamp() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;
          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

