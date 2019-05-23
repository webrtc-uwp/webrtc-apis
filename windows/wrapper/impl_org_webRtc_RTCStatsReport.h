
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCStatsReport.h"

#include "impl_org_webRtc_pre_include.h"
//#include "rtc_base/scoped_ref_ptr.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCStatsReport : public wrapper::org::webRtc::RTCStatsReport
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCStatsReport, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStatsReport, WrapperImplType);
          RTCStatsReportWeakPtr thisWeak_;

          typedef ::webrtc::RTCStatsReport NativeType;
          typedef rtc::scoped_refptr<const NativeType> ScopedConstNativeTypePtr;

          ScopedConstNativeTypePtr native_;

          RTCStatsReport() noexcept;
          virtual ~RTCStatsReport() noexcept;


          // methods RTCStatsReport
          wrapper::org::webRtc::RTCStatsPtr getStats(String id) noexcept override;

          // properties RTCStatsReport
          uint64_t get_objectId() noexcept override;
          shared_ptr< list< String > > get_statsIds() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(const ScopedConstNativeTypePtr &value) noexcept;

          ZS_NO_DISCARD() static ScopedConstNativeTypePtr toNative(WrapperTypePtr value) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

