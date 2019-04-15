
#include "impl_org_webRtc_RTCOutboundRtpStreamStats.h"
#include "impl_org_webRtc_RTCSentRtpStreamStats.h"
#include "impl_org_webRtc_RTCRtpStreamStats.h"
#include "impl_org_webRtc_RTCStats.h"
#include "impl_org_webRtc_enums.h"
#include "Org.WebRtc.Glue.events.h"

#include <zsLib/SafeInt.h>

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCRtpStreamStats, ImplRTCRtpStreamStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCSentRtpStreamStats, ImplRTCSentRtpStreamStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::RTCOutboundRtpStreamStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCOutboundRtpStreamStatsPtr wrapper::org::webRtc::RTCOutboundRtpStreamStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::~RTCOutboundRtpStreamStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  auto durations = get_qualityLimitationDurations();
  auto dscpPackets = get_perDscpPacketsSent();

  ZS_EVENTING_31(
    x, i, Detail, RTCOutboundRtpStreamStats, stats, Stats, Info,
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
    ulong, packetsSent, get_packetsSent(),
    ulong, packetsDiscardedOnSend, get_packetsDiscardedOnSend(),
    ulong, fecPacketsSent, get_fecPacketsSent(),
    ulonglong, bytesSent, get_bytesSent(),
    ulonglong, bytesDiscardedOnSend, get_bytesDiscardedOnSend(),
    string, trackId, get_trackId(),
    string, senderId, get_senderId(),
    string, remoteId, get_remoteId(),
    duration, lastPacketSentTimestamp, zsLib::timeSinceEpoch<Milliseconds>(get_lastPacketSentTimestamp()).count(),
    double, targetBitrate, get_targetBitrate(),
    bool, hasFramesEncodedValue, get_framesEncoded().has_value(),
    ulong, framesEncoded, get_framesEncoded().has_value() ? get_framesEncoded().value() : 0,
    duration, totalEncodeTime, get_totalEncodeTime().count(),
    double, averageRtcpInterval, get_averageRtcpInterval(),
    bool, hasQualityLimitationReasonValue, get_qualityLimitationReason().has_value(),
    string, qualityLimitationReason, get_qualityLimitationReason().has_value() ? UseEnum::toString(get_qualityLimitationReason().value()) : "",
    size_t, qualityLimitationDurations, ((bool)durations) ? durations->size() : 0,
    size_t, perDscpPacketsSent, ((bool)dscpPackets) ? dscpPackets->size() : 0
  );

  if (!ZS_EVENTING_IS_LOGGING(Debug))
    return;

  if (durations) {
    for (auto iter = durations->begin(); iter != durations->end(); ++iter) {
      ZS_EVENTING_2(
        x, i, Debug, RTCOutboundRtpStreamStats_qualityLimitationDuration, stats, Stats, Info,
        string, reason, UseEnum::toString((*iter).first),
        duration, qualityLimitationDuration, ((*iter).second).count()
        );
    }
  }

  if (dscpPackets) {
    for (auto iter = dscpPackets->begin(); iter != dscpPackets->end(); ++iter) {
      ZS_EVENTING_2(
        x, i, Debug, RTCOutboundRtpStreamStats_perDscpPacketsSent, stats, Stats, Info,
        string, id, (*iter).first,
        uint64, perDscpPacketsSent, (*iter).second
      );
    }
  }

}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
Optional< uint32_t > wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_ssrc() noexcept
{
  return ImplRTCRtpStreamStats::get_ssrc(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_kind() noexcept
{
  return ImplRTCRtpStreamStats::get_kind(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_transportId() noexcept
{
  return ImplRTCRtpStreamStats::get_transportId(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_codecId() noexcept
{
  return ImplRTCRtpStreamStats::get_codecId(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_firCount() noexcept
{
  return ImplRTCRtpStreamStats::get_firCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_pliCount() noexcept
{
  return ImplRTCRtpStreamStats::get_pliCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_nackCount() noexcept
{
  return ImplRTCRtpStreamStats::get_nackCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_sliCount() noexcept
{
  return ImplRTCRtpStreamStats::get_sliCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_qpSum() noexcept
{
  return ImplRTCRtpStreamStats::get_qpSum(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_packetsSent() noexcept
{
  return ImplRTCSentRtpStreamStats::get_packetsSent(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_packetsDiscardedOnSend() noexcept
{
  return ImplRTCSentRtpStreamStats::get_packetsDiscardedOnSend(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_fecPacketsSent() noexcept
{
  return ImplRTCSentRtpStreamStats::get_fecPacketsSent(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_bytesSent() noexcept
{
  return ImplRTCSentRtpStreamStats::get_bytesSent(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_bytesDiscardedOnSend() noexcept
{
  return ImplRTCSentRtpStreamStats::get_bytesDiscardedOnSend(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_trackId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.track_id.is_defined()) return {};
  return (*converted.track_id);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_senderId() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_remoteId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.associate_stats_id.is_defined()) return {};
  return (*converted.associate_stats_id);
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_lastPacketSentTimestamp() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_targetBitrate() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.target_bitrate.is_defined()) return {};
  return (*converted.target_bitrate);
}

//------------------------------------------------------------------------------
Optional< unsigned long > wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_framesEncoded() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.frames_encoded.is_defined()) return {};
  return static_cast<unsigned long>(SafeInt<unsigned long>(*converted.frames_encoded));
}

//------------------------------------------------------------------------------
::zsLib::Milliseconds wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_totalEncodeTime() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_averageRtcpInterval() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCQualityLimitationReason > wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_qualityLimitationReason() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
shared_ptr< map< wrapper::org::webRtc::RTCQualityLimitationReason, ::zsLib::Milliseconds > > wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_qualityLimitationDurations() noexcept
{
  typedef shared_ptr< map< wrapper::org::webRtc::RTCQualityLimitationReason, ::zsLib::Milliseconds > > ResultType;
  return make_shared< ResultType::element_type >();
}

//------------------------------------------------------------------------------
shared_ptr< map< String, unsigned long > > wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_perDscpPacketsSent() noexcept
{
  typedef shared_ptr< map< String, unsigned long > > ResultType;
  return make_shared< ResultType::element_type >();
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
