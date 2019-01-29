
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCAudioHandlerStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCAudioHandlerStats : public wrapper::org::webRtc::RTCAudioHandlerStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCAudioHandlerStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCAudioHandlerStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCMediaStreamTrackStats, NativeStats);

          RTCAudioHandlerStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCAudioHandlerStats() noexcept;
          virtual ~RTCAudioHandlerStats() noexcept;

          void trace() noexcept;

          // properties RTCStats
          ::zsLib::Time get_timestamp() noexcept override;
          Optional< wrapper::org::webRtc::RTCStatsType > get_statsType() noexcept override;
          String get_statsTypeOther() noexcept override;
          String get_id() noexcept override;

          // properties RTCMediaHandlerStats
          String get_trackIdentifier() noexcept override;
          Optional< bool > get_remoteSource() noexcept override;
          bool get_ended() noexcept override;
          String get_kind() noexcept override;
          wrapper::org::webRtc::RTCPriorityType get_priority() noexcept override;

          // properties RTCAudioHandlerStats
          double get_audioLevel() noexcept override;
          double get_totalAudioEnergy() noexcept override;
          bool get_voiceActivityFlag() noexcept override;
          double get_totalSamplesDuration() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;

          ZS_NO_DISCARD() static double get_audioLevel(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static double get_totalAudioEnergy(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static bool get_voiceActivityFlag(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static double get_totalSamplesDuration(const NativeStats *native) noexcept;

          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

