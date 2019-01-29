
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCRtpStreamStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCRtpStreamStats : public wrapper::org::webRtc::RTCRtpStreamStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCRtpStreamStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCRtpStreamStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCRTPStreamStats, NativeStats);

          RTCRtpStreamStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCRtpStreamStats() noexcept;
          virtual ~RTCRtpStreamStats() noexcept;

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

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;

          ZS_NO_DISCARD() static Optional< uint32_t > get_ssrc(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static String get_kind(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static String get_transportId(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static String get_codecId(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long get_firCount(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long get_pliCount(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long get_nackCount(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long get_sliCount(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long long get_qpSum(const NativeStats *native) noexcept;

          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

