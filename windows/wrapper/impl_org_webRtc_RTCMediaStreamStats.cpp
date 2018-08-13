
#include "impl_org_webRtc_RTCMediaStreamStats.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCMediaStreamStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);


//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCMediaStreamStats::RTCMediaStreamStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCMediaStreamStatsPtr wrapper::org::webRtc::RTCMediaStreamStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCMediaStreamStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCMediaStreamStats::~RTCMediaStreamStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCMediaStreamStats::get_timestamp() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCMediaStreamStats::get_statsType() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCMediaStreamStats::get_statsTypeOther() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCMediaStreamStats::get_id() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCMediaStreamStats::get_streamIdentifier() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.stream_identifier.is_defined()) return {};
  return (*converted.stream_identifier);
}

//------------------------------------------------------------------------------
shared_ptr< list< String > > wrapper::impl::org::webRtc::RTCMediaStreamStats::get_trackIds() noexcept
{
  typedef shared_ptr< list< String > > ResultType;

  auto result = make_shared<ResultType::element_type>();

  ZS_ASSERT(native_);
  if (!native_) return result;

  auto converted = cast();
  if (!converted.track_ids.is_defined()) return result;

  auto &trackIds = (*converted.track_ids);
  for (auto iter = trackIds.begin(); iter != trackIds.end(); ++iter) {
    auto &trackId = (*iter);
    result->push_back(trackId);
  }
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
