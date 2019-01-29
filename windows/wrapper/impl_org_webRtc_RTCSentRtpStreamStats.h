
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCSentRtpStreamStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCSentRtpStreamStats : public wrapper::org::webRtc::RTCSentRtpStreamStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCSentRtpStreamStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCSentRtpStreamStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCOutboundRTPStreamStats, NativeStats);

          RTCSentRtpStreamStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCSentRtpStreamStats() noexcept;
          virtual ~RTCSentRtpStreamStats() noexcept;

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

          // methods RTCSentRtpStreamStats

          // properties RTCSentRtpStreamStats
          unsigned long get_packetsSent() noexcept override;
          unsigned long get_packetsDiscardedOnSend() noexcept override;
          unsigned long get_fecPacketsSent() noexcept override;
          unsigned long long get_bytesSent() noexcept override;
          unsigned long long get_bytesDiscardedOnSend() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;

          ZS_NO_DISCARD() static unsigned long get_packetsSent(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long get_packetsDiscardedOnSend(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long get_fecPacketsSent(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long long get_bytesSent(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long long get_bytesDiscardedOnSend(const NativeStats *native) noexcept;

          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

