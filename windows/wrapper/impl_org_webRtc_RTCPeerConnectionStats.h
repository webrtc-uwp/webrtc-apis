
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCPeerConnectionStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCPeerConnectionStats : public wrapper::org::webRtc::RTCPeerConnectionStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCPeerConnectionStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCPeerConnectionStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCPeerConnectionStats, NativeStats);

          RTCPeerConnectionStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCPeerConnectionStats() noexcept;
          virtual ~RTCPeerConnectionStats() noexcept;


          // properties RTCStats
          ::zsLib::Time get_timestamp() noexcept override;
          Optional< wrapper::org::webRtc::RTCStatsType > get_statsType() noexcept override;
          String get_statsTypeOther() noexcept override;
          String get_id() noexcept override;

          // properties RTCPeerConnectionStats
          unsigned long get_dataChannelsOpened() noexcept override;
          unsigned long get_dataChannelsClosed() noexcept override;
          unsigned long get_dataChannelsRequested() noexcept override;
          unsigned long get_dataChannelsAccepted() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;
          ZS_NO_DISCARD() const NativeStats &cast() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

