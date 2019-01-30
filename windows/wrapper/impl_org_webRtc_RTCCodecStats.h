
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCCodecStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCCodecStats : public wrapper::org::webRtc::RTCCodecStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCCodecStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCCodecStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCCodecStats, NativeStats);

          RTCCodecStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCCodecStats() noexcept;
          virtual ~RTCCodecStats() noexcept;

          void trace() noexcept;

          // properties RTCStats
          ::zsLib::Time get_timestamp() noexcept override;
          Optional< wrapper::org::webRtc::RTCStatsType > get_statsType() noexcept override;
          String get_statsTypeOther() noexcept override;
          String get_id() noexcept override;

          // properties RTCCodecStats
          Optional< uint8_t > get_payloadType() noexcept override;
          Optional< wrapper::org::webRtc::RTCCodecType > get_codecType() noexcept override;
          String get_transportId() noexcept override;
          String get_mimeType() noexcept override;
          unsigned long get_clockRate() noexcept override;
          Optional< unsigned long > get_channels() noexcept override;
          String get_sdpFmtpLine() noexcept override;
          String get_implementation() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;
          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

