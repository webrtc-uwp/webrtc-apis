
#include "impl_org_webRtc_RTCSenderAudioTrackAttachmentStats.h"
#include "impl_org_webRtc_RTCAudioSenderStats.h"
#include "impl_org_webRtc_RTCAudioHandlerStats.h"
#include "impl_org_webRtc_RTCMediaHandlerStats.h"
#include "impl_org_webRtc_RTCStats.h"

#include "impl_org_webRtc_enums.h"
#include "Org.WebRtc.Glue.events.h"

#include <zsLib/SafeInt.h>

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCMediaHandlerStats, ImplRTCMediaHandlerStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCAudioHandlerStats, ImplRTCAudioHandlerStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCAudioSenderStats, ImplRTCAudioSenderStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::RTCSenderAudioTrackAttachmentStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCSenderAudioTrackAttachmentStatsPtr wrapper::org::webRtc::RTCSenderAudioTrackAttachmentStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::~RTCSenderAudioTrackAttachmentStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_18(
    x, i, Detail, RTCAudioSenderStats, stats, Stats, Info,
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
    bool, hasEchoReturnLossValue, get_echoReturnLoss().has_value(),
    double, echoReturnLoss, get_echoReturnLoss().has_value() ? get_echoReturnLoss().value() : 0,
    bool, hasEchoReturnLossEnhancementValue, get_echoReturnLossEnhancement().has_value(),
    double, echoReturnLossEnhancement, get_echoReturnLossEnhancement().has_value() ? get_echoReturnLossEnhancement().value() : 0,
    ulonglong, totalSamplesSent, get_totalSamplesSent()
  );
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_trackIdentifier() noexcept
{
  return ImplRTCMediaHandlerStats::get_trackIdentifier(&cast());
}

//------------------------------------------------------------------------------
Optional< bool > wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_remoteSource() noexcept
{
  return ImplRTCMediaHandlerStats::get_remoteSource(&cast());
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_ended() noexcept
{
  return ImplRTCMediaHandlerStats::get_ended(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_kind() noexcept
{
  return ImplRTCMediaHandlerStats::get_kind(&cast());
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCPriorityType wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_priority() noexcept
{
  return ImplRTCMediaHandlerStats::get_priority(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_audioLevel() noexcept
{
  return ImplRTCAudioHandlerStats::get_audioLevel(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_totalAudioEnergy() noexcept
{
  return ImplRTCAudioHandlerStats::get_totalAudioEnergy(&cast());
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_voiceActivityFlag() noexcept
{
  return ImplRTCAudioHandlerStats::get_voiceActivityFlag(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_totalSamplesDuration() noexcept
{
  return ImplRTCAudioHandlerStats::get_totalSamplesDuration(&cast());
}

//------------------------------------------------------------------------------
Optional< double > wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_echoReturnLoss() noexcept
{
  return ImplRTCAudioSenderStats::get_echoReturnLoss(&cast());
}

//------------------------------------------------------------------------------
Optional< double > wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_echoReturnLossEnhancement() noexcept
{
  return ImplRTCAudioSenderStats::get_echoReturnLossEnhancement(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_totalSamplesSent() noexcept
{
  return ImplRTCAudioSenderStats::get_totalSamplesSent(&cast());
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
