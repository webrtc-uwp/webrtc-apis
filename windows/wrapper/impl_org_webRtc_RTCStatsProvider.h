
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCStatsProvider.h"

#include "impl_org_webRtc_pre_include.h"
//#include "rtc_base/scoped_ref_ptr.h"
#include "api/stats/rtc_stats_collector_callback.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCStatsProvider : public wrapper::org::webRtc::RTCStatsProvider
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCStatsProvider, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStatsProvider, WrapperImplType);
          RTCStatsProvider() noexcept;
          RTCStatsProvider(const RTCStatsProvider &) noexcept = delete;
          virtual ~RTCStatsProvider() noexcept;

          struct StatsWebrtcObserver;
          typedef rtc::scoped_refptr<StatsWebrtcObserver> StatsWebrtcObserverScopedPtr;

          struct StatsWebrtcObserver : public ::webrtc::RTCStatsCollectorCallback {
            StatsWebrtcObserver(
                                WrapperImplTypePtr wrapper,
                                IMessageQueuePtr queue,
                                shared_ptr< PromiseWithHolderPtr< wrapper::org::webRtc::RTCStatsReportPtr > > promise
                                ) noexcept
                : outer_(wrapper), queue_(queue), promise_(promise) {}

            void OnStatsDelivered(const rtc::scoped_refptr<const ::webrtc::RTCStatsReport>& inReport) final {
              auto outer = outer_.lock();
              if (!outer)
                return;
              const rtc::scoped_refptr<const ::webrtc::RTCStatsReport> report = inReport;
              queue_->postClosure([outer, promise = promise_, report]() {
                outer->onWebrtcObserverStatsDelivered(promise.lock(), report);
              });
            };

          private:
            WrapperImplTypeWeakPtr outer_;
            IMessageQueuePtr queue_;
            std::weak_ptr< PromiseWithHolderPtr< wrapper::org::webRtc::RTCStatsReportPtr > > promise_;
          };

          StatsWebrtcObserverScopedPtr observer_;
          WrapperImplTypeWeakPtr thisWeak_;

          // methods RTCStatsProvider
          shared_ptr< PromiseWithHolderPtr< wrapper::org::webRtc::RTCStatsReportPtr > > getStats(wrapper::org::webRtc::RTCStatsTypeSetPtr statTypes) noexcept(false) override; // throws wrapper::org::webRtc::RTCErrorPtr

          void onWebrtcObserverStatsDelivered(
                                              shared_ptr< PromiseWithHolderPtr< wrapper::org::webRtc::RTCStatsReportPtr > > promise,
                                              rtc::scoped_refptr<const ::webrtc::RTCStatsReport> report
                                              ) noexcept;

          static WrapperImplTypePtr toWrapper(const shared_ptr< PromiseWithHolderPtr< wrapper::org::webRtc::RTCStatsReportPtr > > &value);

          static StatsWebrtcObserverScopedPtr getObserver(WrapperTypePtr value);
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

