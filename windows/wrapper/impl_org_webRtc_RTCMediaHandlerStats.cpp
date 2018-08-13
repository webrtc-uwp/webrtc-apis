
#include "impl_org_webRtc_RTCMediaHandlerStats.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCMediaHandlerStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCMediaHandlerStats::RTCMediaHandlerStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCMediaHandlerStatsPtr wrapper::org::webRtc::RTCMediaHandlerStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCMediaHandlerStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCMediaHandlerStats::~RTCMediaHandlerStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCMediaHandlerStats::get_timestamp() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCMediaHandlerStats::get_statsType() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCMediaHandlerStats::get_statsTypeOther() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCMediaHandlerStats::get_id() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCMediaHandlerStats::get_trackIdentifier() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.track_identifier.is_defined()) return {};
  return (*converted.track_identifier);
}

//------------------------------------------------------------------------------
Optional< bool > wrapper::impl::org::webRtc::RTCMediaHandlerStats::get_remoteSource() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.remote_source.is_defined()) return {};
  return (*converted.remote_source);
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::RTCMediaHandlerStats::get_ended() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.ended.is_defined()) return {};
  return (*converted.ended);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCMediaHandlerStats::get_kind() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.kind.is_defined()) return {};
  return (*converted.kind);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCPriorityType wrapper::impl::org::webRtc::RTCMediaHandlerStats::get_priority() noexcept
{
  return wrapper::org::webRtc::RTCPriorityType::RTCPriorityType_medium;
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
