
#include "impl_org_webRtc_RTCCodecStats.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCCodecStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCCodecStats::RTCCodecStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCCodecStatsPtr wrapper::org::webRtc::RTCCodecStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCCodecStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCCodecStats::~RTCCodecStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCCodecStats::get_timestamp() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCCodecStats::get_statsType() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCCodecStats::get_statsTypeOther() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCCodecStats::get_id() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
Optional< uint8_t > wrapper::impl::org::webRtc::RTCCodecStats::get_payloadType() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.payload_type.is_defined()) return {};
  return SafeInt<uint8_t>(*converted.payload_type);
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCCodecType > wrapper::impl::org::webRtc::RTCCodecStats::get_codecType() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCCodecStats::get_transportId() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCCodecStats::get_mimeType() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.mime_type.is_defined()) return {};
  return (*converted.mime_type);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCCodecStats::get_clockRate() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.clock_rate.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.clock_rate);
}

//------------------------------------------------------------------------------
Optional< unsigned long > wrapper::impl::org::webRtc::RTCCodecStats::get_channels() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.channels.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.channels);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCCodecStats::get_sdpFmtpLine() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.sdp_fmtp_line.is_defined()) return {};
  return (*converted.sdp_fmtp_line);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCCodecStats::get_implementation() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.implementation.is_defined()) return {};
  return (*converted.implementation);
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
