
#include "impl_org_webRtc_RTCIceCandidatePairStats.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCIceCandidatePairStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCIceCandidatePairStats::RTCIceCandidatePairStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCIceCandidatePairStatsPtr wrapper::org::webRtc::RTCIceCandidatePairStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCIceCandidatePairStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCIceCandidatePairStats::~RTCIceCandidatePairStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCIceCandidatePairStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_33(
    x, i, Detail, RTCIceCandidatePairStats, stats, Stats, Info,
    string, type, type.has_value() ? UseEnum::toString(type.value()) : "",
    string, otherType, get_statsTypeOther(),
    string, id, get_id(),
    duration, timestamp, zsLib::timeSinceEpoch<Milliseconds>(get_timestamp()).count(),
    string, transportId, get_transportId(),
    string, localCandidateId, get_localCandidateId(),
    string, remoteCandidateId, get_remoteCandidateId(),
    string, state, UseEnum::toString(get_state()),
    bool, nominated, get_nominated(),
    ulong, packetsSent, get_packetsSent(),
    ulong, packetsReceived, get_packetsReceived(),
    ulonglong, bytesSent, get_bytesSent(),
    ulonglong, bytesReceived, get_bytesReceived(),
    duration, lastPacketSentTimestamp, zsLib::timeSinceEpoch<Milliseconds>(get_lastPacketSentTimestamp()).count(),
    duration, lastPacketReceivedTimestamp, zsLib::timeSinceEpoch<Milliseconds>(get_lastPacketReceivedTimestamp()).count(),
    duration, firstRequestTimestamp, zsLib::timeSinceEpoch<Milliseconds>(get_firstRequestTimestamp()).count(),
    duration, lastRequestTimestamp, zsLib::timeSinceEpoch<Milliseconds>(get_lastRequestTimestamp()).count(),
    duration, lastResponseTimestamp, zsLib::timeSinceEpoch<Milliseconds>(get_lastResponseTimestamp()).count(),
    duration, totalRoundTripTime, get_totalRoundTripTime().count(),
    duration, currentRoundTripTime, get_currentRoundTripTime().count(),
    bool, hasAvailableOutgoingBitrateValue, get_availableOutgoingBitrate().has_value(),
    double, availableOutgoingBitrate, get_availableOutgoingBitrate().has_value() ? get_availableOutgoingBitrate().value() : 0,
    bool, hasAvailableIncomingBitrateValue, get_availableIncomingBitrate().has_value(),
    double, availableIncomingBitrate, get_availableIncomingBitrate().has_value() ? get_availableIncomingBitrate().value() : 0,
    ulong, circuitBreakerTriggerCount, get_circuitBreakerTriggerCount(),
    ulonglong, requestsReceived, get_requestsReceived(),
    ulonglong, requestsSent, get_requestsSent(),
    ulonglong, responsesReceived, get_responsesReceived(),
    ulonglong, responsesSent, get_responsesSent(),
    ulonglong, retransmissionsReceived, get_retransmissionsReceived(),
    ulonglong, retransmissionsSent, get_retransmissionsSent(),
    ulonglong, consentRequestsSent, get_consentRequestsSent(),
    duration, consentExpiredTimestamp, zsLib::timeSinceEpoch<Milliseconds>(get_consentExpiredTimestamp()).count()
    );
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_transportId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.transport_id.is_defined()) return {};
  return (*converted.transport_id);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_localCandidateId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.local_candidate_id.is_defined()) return {};
  return (*converted.local_candidate_id);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_remoteCandidateId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.remote_candidate_id.is_defined()) return {};
  return (*converted.remote_candidate_id);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCStatsIceCandidatePairState wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_state() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.state.is_defined()) return {};
  try
  {
    return UseEnum::toWrapperRTCStatsIceCandidatePairState((*converted.state).c_str());
  } catch (const InvalidParameters &) {
  }
  return wrapper::org::webRtc::RTCStatsIceCandidatePairState::RTCStatsIceCandidatePairState_cancelled;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_nominated() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.nominated.is_defined()) return {};
  return (*converted.nominated);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_packetsSent() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_packetsReceived() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_bytesSent() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.bytes_sent.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.bytes_sent);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_bytesReceived() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.bytes_received.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.bytes_received);
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_lastPacketSentTimestamp() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_lastPacketReceivedTimestamp() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_firstRequestTimestamp() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_lastRequestTimestamp() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_lastResponseTimestamp() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
::zsLib::Milliseconds wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_totalRoundTripTime() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.total_round_trip_time.is_defined()) return {};
  return ::zsLib::Milliseconds(::zsLib::Milliseconds::rep(*converted.total_round_trip_time));
}

//------------------------------------------------------------------------------
::zsLib::Milliseconds wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_currentRoundTripTime() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.total_round_trip_time.is_defined()) return {};
  return ::zsLib::Milliseconds(::zsLib::Milliseconds::rep(*converted.current_round_trip_time));
}

//------------------------------------------------------------------------------
Optional< double > wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_availableOutgoingBitrate() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.available_outgoing_bitrate.is_defined()) return {};
  return (double)SafeInt<unsigned long long>(*converted.available_outgoing_bitrate);
}

//------------------------------------------------------------------------------
Optional< double > wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_availableIncomingBitrate() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.available_outgoing_bitrate.is_defined()) return {};
  return (double)SafeInt<unsigned long long>(*converted.available_incoming_bitrate);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_circuitBreakerTriggerCount() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_requestsReceived() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.requests_received.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.requests_received);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_requestsSent() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.requests_sent.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.requests_sent);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_responsesReceived() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.responses_received.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.responses_received);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_responsesSent() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.responses_sent.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.responses_sent);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_retransmissionsReceived() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.retransmissions_received.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.retransmissions_received);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_retransmissionsSent() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.retransmissions_sent.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.retransmissions_sent);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_consentRequestsSent() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.consent_requests_sent.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.consent_requests_sent);
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCIceCandidatePairStats::get_consentExpiredTimestamp() noexcept
{
  return {};
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
