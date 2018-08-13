
#include "impl_org_webRtc_RTCOutboundRtpStreamStats.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);

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
::zsLib::Time wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_timestamp() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_statsType() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_statsTypeOther() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_id() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
Optional< uint32_t > wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_ssrc() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.ssrc.is_defined()) return {};
  return SafeInt<uint32_t>(*converted.ssrc);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_kind() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.media_type.is_defined()) return {};
  return (*converted.media_type);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_transportId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.transport_id.is_defined()) return {};
  return (*converted.transport_id);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_codecId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.codec_id.is_defined()) return {};
  return (*converted.codec_id);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_firCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.fir_count.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.fir_count);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_pliCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.pli_count.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.pli_count);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_nackCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.nack_count.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.nack_count);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_sliCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.sli_count.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.sli_count);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_qpSum() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.qp_sum.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.qp_sum);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_packetsSent() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.packets_sent.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.packets_sent);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_packetsDiscardedOnSend() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_fecPacketsSent() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_bytesSent() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.bytes_sent.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.bytes_sent);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCOutboundRtpStreamStats::get_bytesDiscardedOnSend() noexcept
{
  return {};
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
  return SafeInt<unsigned long>(*converted.frames_encoded);
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
