
#include "impl_org_webRtc_RTCSenderAudioTrackAttachmentStats.h"
#include "impl_org_webRtc_RTCStats.h"

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
::zsLib::Time wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_timestamp() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_statsType() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_statsTypeOther() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_id() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_trackIdentifier() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.track_identifier.is_defined()) return {};
  return (*converted.track_identifier);
}

//------------------------------------------------------------------------------
Optional< bool > wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_remoteSource() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.remote_source.is_defined()) return {};
  return (*converted.remote_source);
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_ended() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.ended.is_defined()) return {};
  return (*converted.ended);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_kind() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.kind.is_defined()) return {};
  return (*converted.kind);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCPriorityType wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_priority() noexcept
{
  return wrapper::org::webRtc::RTCPriorityType::RTCPriorityType_medium;
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_audioLevel() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.audio_level.is_defined()) return {};
  return (*converted.audio_level);
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_totalAudioEnergy() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.total_audio_energy.is_defined()) return {};
  return (*converted.total_audio_energy);
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_voiceActivityFlag() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_totalSamplesDuration() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.total_samples_duration.is_defined()) return {};
  return (*converted.total_samples_duration);
}

//------------------------------------------------------------------------------
Optional< double > wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_echoReturnLoss() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.echo_return_loss.is_defined()) return {};
  return (*converted.echo_return_loss);
}

//------------------------------------------------------------------------------
Optional< double > wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_echoReturnLossEnhancement() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.echo_return_loss_enhancement.is_defined()) return {};
  return (*converted.echo_return_loss_enhancement);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCSenderAudioTrackAttachmentStats::get_totalSamplesSent() noexcept
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
