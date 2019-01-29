
#include "impl_org_webRtc_RTCAudioReceiverStats.h"
#include "impl_org_webRtc_RTCAudioHandlerStats.h"
#include "impl_org_webRtc_RTCMediaHandlerStats.h"
#include "impl_org_webRtc_RTCStats.h"

#include "impl_org_webRtc_enums.h"
#include "Org.WebRtc.Glue.events.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCAudioReceiverStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCMediaHandlerStats, ImplRTCMediaHandlerStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCAudioHandlerStats, ImplRTCAudioHandlerStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }


//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCAudioReceiverStats::RTCAudioReceiverStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCAudioReceiverStatsPtr wrapper::org::webRtc::RTCAudioReceiverStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCAudioReceiverStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCAudioReceiverStats::~RTCAudioReceiverStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCAudioReceiverStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_19(
    x, i, Detail, RTCAudioReceiverStats, stats, Stats, Info,
    string, type, type.has_value() ? UseEnum::toString(type.value()) : "",
    string, otherType, get_statsTypeOther(),
    string, id, get_id(),
    string, trackIdentifier, get_trackIdentifier(),
    bool, hasRemoteSourceValue, get_remoteSource().has_value(),
    bool, remoteSource, get_remoteSource().has_value() ? get_remoteSource().value() : false,
    bool, ended, get_ended(),
    string, kind, get_kind(),
    string, priority, UseEnum::toString(get_priority()),
    double, audioLevel, get_audioLevel(),
    double, totalAudioEnergy, get_totalAudioEnergy(),
    bool, voiceActivityFlag, get_voiceActivityFlag(),
    double, totalSamplesDuration, get_totalSamplesDuration(),
    duration, estimatedPlayoutTimestamp, zsLib::timeSinceEpoch<Milliseconds>(get_estimatedPlayoutTimestamp()).count(),
    duration, jitterBufferDelay, get_jitterBufferDelay().count(),
    ulonglong, jitterBufferEmittedCount, get_jitterBufferEmittedCount(),
    ulonglong, totalSamplesReceived, get_totalSamplesReceived(),
    ulonglong, concealedSamples, get_concealedSamples(),
    ulonglong, concealmentEvents, get_concealmentEvents()
  );
  
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_trackIdentifier() noexcept
{
  return ImplRTCMediaHandlerStats::get_trackIdentifier(&cast());
}

//------------------------------------------------------------------------------
Optional< bool > wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_remoteSource() noexcept
{
  return ImplRTCMediaHandlerStats::get_remoteSource(&cast());
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_ended() noexcept
{
  return ImplRTCMediaHandlerStats::get_ended(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_kind() noexcept
{
  return ImplRTCMediaHandlerStats::get_kind(&cast());
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCPriorityType wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_priority() noexcept
{
  return ImplRTCMediaHandlerStats::get_priority(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_audioLevel() noexcept
{
  return ImplRTCAudioHandlerStats::get_audioLevel(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_totalAudioEnergy() noexcept
{
  return ImplRTCAudioHandlerStats::get_totalAudioEnergy(&cast());
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_voiceActivityFlag() noexcept
{
  return ImplRTCAudioHandlerStats::get_voiceActivityFlag(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_totalSamplesDuration() noexcept
{
  return ImplRTCAudioHandlerStats::get_totalSamplesDuration(&cast());
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_estimatedPlayoutTimestamp() noexcept
{
  return get_estimatedPlayoutTimestamp(&cast());
}

//------------------------------------------------------------------------------
::zsLib::Milliseconds wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_jitterBufferDelay() noexcept
{
  return get_jitterBufferDelay(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_jitterBufferEmittedCount() noexcept
{
  return get_jitterBufferEmittedCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_totalSamplesReceived() noexcept
{
  return get_totalSamplesReceived(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_concealedSamples() noexcept
{
  return get_concealedSamples(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCAudioReceiverStats::get_concealmentEvents() noexcept
{
  return get_concealmentEvents(&cast());
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
::zsLib::Time WrapperImplType::get_estimatedPlayoutTimestamp(const NativeStats *) noexcept
{
  return {};
}

//------------------------------------------------------------------------------
::zsLib::Milliseconds WrapperImplType::get_jitterBufferDelay(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->audio_level.is_defined()) return {};
  return zsLib::Milliseconds(static_cast<zsLib::Microseconds::rep>((*(native->audio_level)) * 1000));
}

//------------------------------------------------------------------------------
unsigned long long WrapperImplType::get_jitterBufferEmittedCount(const NativeStats *) noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long long WrapperImplType::get_totalSamplesReceived(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->total_samples_received.is_defined()) return {};
  return *(native->total_samples_received);
}

//------------------------------------------------------------------------------
unsigned long long WrapperImplType::get_concealedSamples(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->concealed_samples.is_defined()) return {};
  return *(native->concealed_samples);
}

//------------------------------------------------------------------------------
unsigned long long WrapperImplType::get_concealmentEvents(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->concealment_events.is_defined()) return {};
  return *(native->concealment_events);
}

//------------------------------------------------------------------------------
const NativeStats &WrapperImplType::cast() noexcept
{
  ZS_ASSERT(native_);
  return native_->cast_to<NativeStats>();
}
