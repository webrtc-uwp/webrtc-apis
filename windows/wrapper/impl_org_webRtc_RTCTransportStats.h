
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCTransportStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCTransportStats : public wrapper::org::webRtc::RTCTransportStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCTransportStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCTransportStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCTransportStats, NativeStats);

          RTCTransportStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCTransportStats() noexcept;
          virtual ~RTCTransportStats() noexcept;

          void trace() noexcept;

          // properties RTCStats
          ::zsLib::Time get_timestamp() noexcept override;
          Optional< wrapper::org::webRtc::RTCStatsType > get_statsType() noexcept override;
          String get_statsTypeOther() noexcept override;
          String get_id() noexcept override;

          // properties RTCTransportStats
          unsigned long get_packetsSent() noexcept override;
          unsigned long get_packetsReceived() noexcept override;
          unsigned long long get_bytesSent() noexcept override;
          unsigned long long get_bytesReceived() noexcept override;
          String get_rtcpTransportStatsId() noexcept override;
          Optional< wrapper::org::webRtc::RTCIceRole > get_iceRole() noexcept override;
          wrapper::org::webRtc::RTCDtlsTransportState get_dtlsState() noexcept override;
          String get_selectedCandidatePairId() noexcept override;
          String get_localCertificateId() noexcept override;
          String get_remoteCertificateId() noexcept override;
          String get_dtlsCipher() noexcept override;
          String get_srtpCipher() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;
          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

