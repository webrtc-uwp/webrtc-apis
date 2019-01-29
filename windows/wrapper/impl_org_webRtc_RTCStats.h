
#pragma once

#include "types.h"
#include "generated/org_webRtc_RTCStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct RTCStats : public wrapper::org::webRtc::RTCStats
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::RTCStats, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::RTCStats, NativeType);

          RTCStatsWeakPtr thisWeak_;
          NativeTypeUniPtr native_;

          RTCStats() noexcept;
          virtual ~RTCStats() noexcept;


          // properties RTCStats
          ::zsLib::Time get_timestamp() noexcept override;
          Optional< wrapper::org::webRtc::RTCStatsType > get_statsType() noexcept override;
          String get_statsTypeOther() noexcept override;
          String get_id() noexcept override;

          void trace() noexcept override;

          ZS_NO_DISCARD() static WrapperTypePtr toWrapper(NativeTypeUniPtr value) noexcept;

          ZS_NO_DISCARD() static ::zsLib::Time get_timestamp(const NativeType *native) noexcept;
          ZS_NO_DISCARD() static Optional< wrapper::org::webRtc::RTCStatsType > get_statsType(const NativeType *native) noexcept;
          ZS_NO_DISCARD() static String get_statsTypeOther(const NativeType *native) noexcept;
          ZS_NO_DISCARD() static String get_id(const NativeType *native) noexcept;

          ZS_NO_DISCARD() static NativeTypeUniPtr toNative(WrapperImplTypePtr value) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

