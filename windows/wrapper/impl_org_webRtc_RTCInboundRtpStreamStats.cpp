
#include "impl_org_webRtc_RTCInboundRtpStreamStats.h"
#include "impl_org_webRtc_RTCReceivedRtpStreamStats.h"
#include "impl_org_webRtc_RTCRtpStreamStats.h"
#include "impl_org_webRtc_RTCStats.h"

#include "impl_org_webRtc_enums.h"
#include "Org.WebRtc.Glue.events.h"

#include <zsLib/SafeInt.h>
#include <zsLib/helpers.h>

using ::zsLib::Milliseconds;
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCRtpStreamStats, ImplRTCRtpStreamStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats, ImplRTCReceivedRtpStreamStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::RTCInboundRtpStreamStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCInboundRtpStreamStatsPtr wrapper::org::webRtc::RTCInboundRtpStreamStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCInboundRtpStreamStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::~RTCInboundRtpStreamStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  auto dscpPackets = get_perDscpPacketsReceived();

  ZS_EVENTING_37(
    x, i, Detail, RTCInboundRtpStreamStats, stats, Stats, Info,
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
    string, trackId, get_trackId(),
    string, receiverId, get_receiverId(),
    string, remoteId, get_remoteId(),
    bool, hasFramesDecodedValue, get_framesDecoded().has_value(),
    ulong, framesDecoded, get_framesDecoded().has_value() ? get_framesDecoded().value() : 0,
    duration, timestamp, zsLib::timeSinceEpoch<Milliseconds>(get_lastPacketReceivedTimestamp()).count(),
    double, averageRtcpInterval, get_averageRtcpInterval(),
    ulong, fecPacketsReceived, get_fecPacketsReceived(),
    ulong, bytesReceived, get_bytesReceived(),
    ulong, packetsFailedDecryption, get_packetsFailedDecryption(),
    size_t, perDscpPacketsReceived, ((bool)dscpPackets) ? dscpPackets->size() : 0
  );

  if (!ZS_EVENTING_IS_LOGGING(Debug))
    return;


  if (dscpPackets) {
    for (auto iter = dscpPackets->begin(); iter != dscpPackets->end(); ++iter) {
      ZS_EVENTING_2(
        x, i, Debug, RTCInboundRtpStreamStats_perDscpPacketsReceived, stats, Stats, Info,
        string, id, (*iter).first,
        uint64, perDscpPacketsSent, (*iter).second
      );
    }
  }

}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
Optional< uint32_t > wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_ssrc() noexcept
{
  return ImplRTCRtpStreamStats::get_ssrc(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_kind() noexcept
{
  return ImplRTCRtpStreamStats::get_kind(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_transportId() noexcept
{
  return ImplRTCRtpStreamStats::get_transportId(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_codecId() noexcept
{
  return ImplRTCRtpStreamStats::get_codecId(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_firCount() noexcept
{
  return ImplRTCRtpStreamStats::get_firCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_pliCount() noexcept
{
  return ImplRTCRtpStreamStats::get_pliCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_nackCount() noexcept
{
  return ImplRTCRtpStreamStats::get_nackCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_sliCount() noexcept
{
  return ImplRTCRtpStreamStats::get_sliCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_qpSum() noexcept
{
  return ImplRTCRtpStreamStats::get_qpSum(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_packetsReceived() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_packetsReceived(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_packetsLost() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_packetsLost(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_jitter() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_jitter(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_packetsDiscarded() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_packetsDiscarded(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_packetsRepaired() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_packetsRepaired(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_burstPacketsLost() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_burstPacketsLost(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_burstPacketsDiscarded() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_burstPacketsDiscarded(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_burstLossCount() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_burstLossCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_burstDiscardCount() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_burstDiscardCount(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_burstLossRate() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_burstLossRate(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_burstDiscardRate() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_burstDiscardRate(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_gapLossRate() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_gapLossRate(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_gapDiscardRate() noexcept
{
  return ImplRTCReceivedRtpStreamStats::get_gapDiscardRate(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_trackId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.track_id.is_defined()) return {};
  return (*converted.track_id);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_receiverId() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_remoteId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.associate_stats_id.is_defined()) return {};
  return (*converted.associate_stats_id);
}

//------------------------------------------------------------------------------
Optional< unsigned long > wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_framesDecoded() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.frames_decoded.is_defined()) return {};
  return static_cast<unsigned long>(SafeInt<unsigned long>(*converted.frames_decoded));
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_lastPacketReceivedTimestamp() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_averageRtcpInterval() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_fecPacketsReceived() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_bytesReceived() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.bytes_received.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.bytes_received);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_packetsFailedDecryption() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_packetsDuplicated() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
shared_ptr< map< String, unsigned long > > wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_perDscpPacketsReceived() noexcept
{
  typedef shared_ptr< map< String, unsigned long > > ResultType;
  return make_shared<ResultType::element_type>();
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
