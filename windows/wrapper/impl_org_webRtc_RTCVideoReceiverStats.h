
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCVideoReceiverStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCVideoReceiverStats : public wrapper::org::webRtc::RTCVideoReceiverStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCVideoReceiverStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCVideoReceiverStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCMediaStreamTrackStats, NativeStats);

          RTCVideoReceiverStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCVideoReceiverStats() noexcept;
          virtual ~RTCVideoReceiverStats() noexcept;

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

          // properties RTCVideoHandlerStats
          unsigned long get_frameWidth() noexcept override;
          unsigned long get_frameHeight() noexcept override;
          double get_framesPerSecond() noexcept override;

          // properties RTCVideoReceiverStats
          ::zsLib::Time get_estimatedPlayoutTimestamp() noexcept override;
          ::zsLib::Milliseconds get_jitterBufferDelay() noexcept override;
          unsigned long long get_jitterBufferEmittedCount() noexcept override;
          unsigned long get_framesReceived() noexcept override;
          unsigned long get_keyFramesReceived() noexcept override;
          unsigned long get_framesDecoded() noexcept override;
          unsigned long get_framesDropped() noexcept override;
          unsigned long get_partialFramesLost() noexcept override;
          unsigned long get_fullFramesLost() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;

          ZS_NO_DISCARD() static ::zsLib::Time get_estimatedPlayoutTimestamp(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static ::zsLib::Milliseconds get_jitterBufferDelay(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long long get_jitterBufferEmittedCount(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long get_framesReceived(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long get_keyFramesReceived(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long get_framesDecoded(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long get_framesDropped(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long get_partialFramesLost(const NativeStats *native) noexcept;
          ZS_NO_DISCARD() static unsigned long get_fullFramesLost(const NativeStats *native) noexcept;

          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

