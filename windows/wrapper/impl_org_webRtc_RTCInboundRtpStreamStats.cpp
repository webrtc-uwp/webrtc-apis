
#include "impl_org_webRtc_RTCInboundRtpStreamStats.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);

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
::zsLib::Time wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_timestamp() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_statsType() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_statsTypeOther() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_id() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
Optional< uint32_t > wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_ssrc() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.ssrc.is_defined()) return {};
  return SafeInt<uint32_t>(*converted.ssrc);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_kind() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.media_type.is_defined()) return {};
  return (*converted.media_type);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_transportId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.transport_id.is_defined()) return {};
  return (*converted.transport_id);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_codecId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.codec_id.is_defined()) return {};
  return (*converted.codec_id);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_firCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.fir_count.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.fir_count);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_pliCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.pli_count.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.pli_count);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_nackCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.nack_count.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.nack_count);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_sliCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.sli_count.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.sli_count);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_qpSum() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.qp_sum.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.qp_sum);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_packetsReceived() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.packets_received.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.packets_received);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_packetsLost() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.packets_lost.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.packets_lost);
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_jitter() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.jitter.is_defined()) return {};
  return (*converted.jitter);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_packetsDiscarded() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.packets_discarded.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.packets_discarded);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_packetsRepaired() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.packets_repaired.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.packets_repaired);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_burstPacketsLost() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.burst_packets_lost.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.burst_packets_lost);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_burstPacketsDiscarded() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.packets_discarded.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.packets_discarded);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_burstLossCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.burst_loss_count.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.burst_loss_count);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_burstDiscardCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.burst_discard_count.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.burst_discard_count);
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_burstLossRate() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.burst_loss_rate.is_defined()) return {};
  return (*converted.burst_loss_rate);
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_burstDiscardRate() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.burst_discard_rate.is_defined()) return {};
  return (*converted.burst_discard_rate);
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_gapLossRate() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.gap_loss_rate.is_defined()) return {};
  return (*converted.gap_loss_rate);
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCInboundRtpStreamStats::get_gapDiscardRate() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.gap_discard_rate.is_defined()) return {};
  return (*converted.gap_discard_rate);
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
  return SafeInt<unsigned long>(*converted.frames_decoded);
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
