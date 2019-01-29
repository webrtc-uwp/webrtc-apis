
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCDataChannelStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCDataChannelStats : public wrapper::org::webRtc::RTCDataChannelStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCDataChannelStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCDataChannelStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCDataChannelStats, NativeStats);

          RTCDataChannelStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCDataChannelStats() noexcept;
          virtual ~RTCDataChannelStats() noexcept;

          void trace() noexcept;

          // properties RTCStats
          ::zsLib::Time get_timestamp() noexcept override;
          Optional< wrapper::org::webRtc::RTCStatsType > get_statsType() noexcept override;
          String get_statsTypeOther() noexcept override;
          String get_id() noexcept override;

          // properties RTCDataChannelStats
          String get_label() noexcept override;
          String get_protocol() noexcept override;
          long get_dataChannelIdentifier() noexcept override;
          String get_transportId() noexcept override;
          wrapper::org::webRtc::RTCDataChannelState get_state() noexcept override;
          unsigned long get_messagesSent() noexcept override;
          unsigned long long get_bytesSent() noexcept override;
          unsigned long get_messagesReceived() noexcept override;
          unsigned long long get_bytesReceived() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;
          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

