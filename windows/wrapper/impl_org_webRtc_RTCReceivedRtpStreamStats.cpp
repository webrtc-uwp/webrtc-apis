
#include "impl_org_webRtc_RTCReceivedRtpStreamStats.h"
#include "impl_org_webRtc_RTCRtpStreamStats.h"
#include "impl_org_webRtc_RTCStats.h"

#include "impl_org_webRtc_enums.h"
#include "Org.WebRtc.Glue.events.h"

#include <zsLib/SafeInt.h>
#include <zsLib/helpers.h>

using ::zsLib::String;
using ::zsLib::Optional;
using ::zsLib::Any;
using ::zsLib::AnyPtr;
using ::zsLib::AnyHolder;
using ::zsLib::Promise;
using ::zsLib::PromisePtr;
using ::zsLib::PromiseWithHolder;
using ::zsLib::PromiseWithHolderPtr;
using ::zsLib::eventing::SecureByteBlock;
using ::zsLib::eventing::SecureByteBlockPtr;
using ::std::shared_ptr;
using ::std::weak_ptr;
using ::std::make_shared;
using ::std::list;
using ::std::set;
using ::std::map;

// borrow definitions from class
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCRtpStreamStats, ImplRTCRtpStreamStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::RTCReceivedRtpStreamStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCReceivedRtpStreamStatsPtr wrapper::org::webRtc::RTCReceivedRtpStreamStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::~RTCReceivedRtpStreamStats() noexcept
{
  thisWeak_.reset();
}


//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_26(
    x, i, Detail, RTCReceivedRtpStreamStats, stats, Stats, Info,
    string, type, type.has_value() ? UseEnum::toString(type.value()) : "",
    string, otherType, get_statsTypeOther(),
    string, id, get_id(),
    bool, hasSsrcValue, get_ssrc().has_value(),
    uint32, ssrc, get_ssrc().has_value() ? get_ssrc().value() : 0,
    string, kind, get_kind(),
    string, transportId, get_transportId(),
    string, codecId, get_codecId(),
    ulong, firCount, get_firCount(),
    ulong, pliCount, get_pliCount(),
    ulong, nackCount, get_nackCount(),
    ulong, sliCount, get_sliCount(),
    ulonglong, qpSum, get_qpSum(),
    ulong, packetsReceived, get_packetsReceived(),
    ulong, get_packetsLost, get_packetsLost(),
    double, jitter, get_jitter(),
    ulong, packetsDiscarded, get_packetsDiscarded(),
    ulong, packetsRepaired, get_packetsRepaired(),
    ulong, burstPacketsLost, get_burstPacketsLost(),
    ulong, burstPacketsDiscarded, get_burstPacketsDiscarded(),
    ulong, burstLossCount, get_burstLossCount(),
    ulong, burstDiscardCount, get_burstDiscardCount(),
    double, burstLossRate, get_burstLossRate(),
    double, burstDiscardRate, get_burstDiscardRate(),
    double, gapLossRate, get_gapLossRate(),
    double, gapDiscardRate, get_gapDiscardRate()
  );

}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
Optional< uint32_t > wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_ssrc() noexcept
{
  return ImplRTCRtpStreamStats::get_ssrc(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_kind() noexcept
{
  return ImplRTCRtpStreamStats::get_kind(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_transportId() noexcept
{
  return ImplRTCRtpStreamStats::get_transportId(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_codecId() noexcept
{
  return ImplRTCRtpStreamStats::get_codecId(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_firCount() noexcept
{
  return ImplRTCRtpStreamStats::get_firCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_pliCount() noexcept
{
  return ImplRTCRtpStreamStats::get_pliCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_nackCount() noexcept
{
  return ImplRTCRtpStreamStats::get_nackCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_sliCount() noexcept
{
  return ImplRTCRtpStreamStats::get_sliCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_qpSum() noexcept
{
  return ImplRTCRtpStreamStats::get_qpSum(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_packetsReceived() noexcept
{
  return get_packetsReceived(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_packetsLost() noexcept
{
  return get_packetsLost(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_jitter() noexcept
{
  return get_jitter(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_packetsDiscarded() noexcept
{
  return get_packetsDiscarded(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_packetsRepaired() noexcept
{
  return get_packetsRepaired(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_burstPacketsLost() noexcept
{
  return get_burstPacketsLost(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_burstPacketsDiscarded() noexcept
{
  return get_burstPacketsDiscarded(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_burstLossCount() noexcept
{
  return get_burstLossCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_burstDiscardCount() noexcept
{
  return get_burstDiscardCount(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_burstLossRate() noexcept
{
  return get_burstLossRate(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_burstDiscardRate() noexcept
{
  return get_burstDiscardRate(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_gapLossRate() noexcept
{
  return get_gapLossRate(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats::get_gapDiscardRate() noexcept
{
  return get_gapDiscardRate(&cast());
}

//------------------------------------------------------------------------------
WrapperTypePtr WrapperImplType::toWrapper(NativeTypeUniPtr value) noexcept
{
  if (!value) return WrapperTypePtr();
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = std::move(value);
  return result;
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_packetsReceived(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->packets_received.is_defined()) return {};
  return SafeInt<unsigned long>(*(native->packets_received));
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_packetsLost(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->packets_lost.is_defined()) return {};
  return SafeInt<unsigned long>(*(native->packets_lost));
}

//------------------------------------------------------------------------------
double WrapperImplType::get_jitter(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->jitter.is_defined()) return {};
  return *(native->jitter);
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_packetsDiscarded(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->packets_discarded.is_defined()) return {};
  return SafeInt<unsigned long>(*(native->packets_discarded));
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_packetsRepaired(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->packets_repaired.is_defined()) return {};
  return SafeInt<unsigned long>(*(native->packets_repaired));
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_burstPacketsLost(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->burst_packets_lost.is_defined()) return {};
  return SafeInt<unsigned long>(*(native->burst_packets_lost));
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_burstPacketsDiscarded(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};


  if (!native->packets_discarded.is_defined()) return {};
  return SafeInt<unsigned long>(*(native->packets_discarded));
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_burstLossCount(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->burst_loss_count.is_defined()) return {};
  return SafeInt<unsigned long>(*(native->burst_loss_count));
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_burstDiscardCount(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->burst_discard_count.is_defined()) return {};
  return SafeInt<unsigned long>(*(native->burst_discard_count));
}

//------------------------------------------------------------------------------
double WrapperImplType::get_burstLossRate(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->burst_loss_rate.is_defined()) return {};
  return *(native->burst_loss_rate);
}

//------------------------------------------------------------------------------
double WrapperImplType::get_burstDiscardRate(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->burst_discard_rate.is_defined()) return {};
  return *(native->burst_discard_rate);
}

//------------------------------------------------------------------------------
double WrapperImplType::get_gapLossRate(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->gap_loss_rate.is_defined()) return {};
  return *(native->gap_loss_rate);
}

//------------------------------------------------------------------------------
double WrapperImplType::get_gapDiscardRate(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->gap_discard_rate.is_defined()) return {};
  return *(native->gap_discard_rate);
}

//------------------------------------------------------------------------------
const NativeStats &WrapperImplType::cast() noexcept
{
  ZS_ASSERT(native_);
  return native_->cast_to<NativeStats>();
}
