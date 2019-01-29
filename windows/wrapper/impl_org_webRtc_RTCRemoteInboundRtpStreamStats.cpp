
#include "impl_org_webRtc_RTCRemoteInboundRtpStreamStats.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCRtpStreamStats, ImplRTCRtpStreamStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats, ImplRTCReceivedRtpStreamStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::RTCRemoteInboundRtpStreamStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCRemoteInboundRtpStreamStatsPtr wrapper::org::webRtc::RTCRemoteInboundRtpStreamStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::~RTCRemoteInboundRtpStreamStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_29(
    x, i, Detail, RTCRemoteInboundRtpStreamStats, stats, Stats, Info,
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
    double, gapDiscardRate, get_gapDiscardRate(),
    string, localId, get_localId(),
    double, roundTripTime, get_roundTripTime(),
    double, fractionLost, get_fractionLost()
  );
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
Optional< uint32_t > wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_ssrc() noexcept
{
  return ImplRTCRtpStreamStats::get_ssrc(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_kind() noexcept
{
  return ImplRTCRtpStreamStats::get_kind(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_transportId() noexcept
{
  return ImplRTCRtpStreamStats::get_transportId(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_codecId() noexcept
{
  return ImplRTCRtpStreamStats::get_codecId(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_firCount() noexcept
{
  return ImplRTCRtpStreamStats::get_firCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_pliCount() noexcept
{
  return ImplRTCRtpStreamStats::get_pliCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_nackCount() noexcept
{
  return ImplRTCRtpStreamStats::get_nackCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_sliCount() noexcept
{
  return ImplRTCRtpStreamStats::get_sliCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_qpSum() noexcept
{
  return ImplRTCRtpStreamStats::get_qpSum(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_packetsReceived() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_packetsReceived(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_packetsLost() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_packetsLost(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_jitter() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_jitter(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_packetsDiscarded() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_packetsDiscarded(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_packetsRepaired() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_packetsRepaired(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_burstPacketsLost() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_burstPacketsLost(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_burstPacketsDiscarded() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_burstPacketsDiscarded(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_burstLossCount() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_burstLossCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_burstDiscardCount() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_burstDiscardCount(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_burstLossRate() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_burstLossRate(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_burstDiscardRate() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_burstDiscardRate(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_gapLossRate() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_gapLossRate(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_gapDiscardRate() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_gapDiscardRate(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_localId() noexcept
{
  String result {};
  return result;
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_roundTripTime() noexcept
{
  double result {};
  return result;
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCRemoteInboundRtpStreamStats::get_fractionLost() noexcept
{
  double result {};
  return result;
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
const NativeStats &WrapperImplType::cast() noexcept
{
  ZS_ASSERT(native_);
  return native_->cast_to<NativeStats>();
}
