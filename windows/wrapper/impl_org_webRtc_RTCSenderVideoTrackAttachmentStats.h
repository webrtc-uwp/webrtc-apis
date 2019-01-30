
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCSenderVideoTrackAttachmentStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCSenderVideoTrackAttachmentStats : public wrapper::org::webRtc::RTCSenderVideoTrackAttachmentStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCSenderVideoTrackAttachmentStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCMediaStreamTrackStats, NativeStats);

          RTCSenderVideoTrackAttachmentStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCSenderVideoTrackAttachmentStats() noexcept;
          virtual ~RTCSenderVideoTrackAttachmentStats() noexcept;

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

          // properties RTCVideoSenderStats
          unsigned long get_framesCaptured() noexcept override;
          unsigned long get_framesSent() noexcept override;
          unsigned long get_hugeFramesSent() noexcept override;
          unsigned long get_keyFramesSent() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;
          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

