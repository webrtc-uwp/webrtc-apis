
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCCertificateStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCCertificateStats : public wrapper::org::webRtc::RTCCertificateStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCCertificateStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCCertificateStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCCertificateStats, NativeStats);

          RTCCertificateStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCCertificateStats() noexcept;
          virtual ~RTCCertificateStats() noexcept;

          void trace() noexcept;

          // properties RTCStats
          ::zsLib::Time get_timestamp() noexcept override;
          Optional< wrapper::org::webRtc::RTCStatsType > get_statsType() noexcept override;
          String get_statsTypeOther() noexcept override;
          String get_id() noexcept override;

          // properties RTCCertificateStats
          String get_fingerprint() noexcept override;
          String get_fingerprintAlgorithm() noexcept override;
          String get_base64Certificate() noexcept override;
          String get_issuerCertificateId() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;
          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

