
#include "impl_org_webRtc_RTCTransportStats.h"
#include "impl_org_webRtc_RTCStats.h"
#include "impl_org_webRtc_enums.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCTransportStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCTransportStats::RTCTransportStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCTransportStatsPtr wrapper::org::webRtc::RTCTransportStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCTransportStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCTransportStats::~RTCTransportStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCTransportStats::get_timestamp() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCTransportStats::get_statsType() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCTransportStats::get_statsTypeOther() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCTransportStats::get_id() noexcept
{
  if (!native_) return {};
  ZS_ASSERT(native_);
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCTransportStats::get_packetsSent() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCTransportStats::get_packetsReceived() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCTransportStats::get_bytesSent() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.bytes_sent.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.bytes_sent);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCTransportStats::get_bytesReceived() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.bytes_sent.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.bytes_received);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCTransportStats::get_rtcpTransportStatsId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.rtcp_transport_stats_id.is_defined()) return {};
  return (*converted.rtcp_transport_stats_id);
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCIceRole > wrapper::impl::org::webRtc::RTCTransportStats::get_iceRole() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCDtlsTransportState wrapper::impl::org::webRtc::RTCTransportStats::get_dtlsState() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return wrapper::org::webRtc::RTCDtlsTransportState::RTCDtlsTransportState_closed;

  auto converted = cast();
  if (!converted.dtls_state.is_defined()) return {};
  try {
    return UseEnum::toWrapperRTCDtlsTransportState((*converted.dtls_state).c_str());
  } catch (const InvalidParameters &) {
  }
  return wrapper::org::webRtc::RTCDtlsTransportState::RTCDtlsTransportState_closed;
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCTransportStats::get_selectedCandidatePairId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.selected_candidate_pair_id.is_defined()) return {};
  return (*converted.selected_candidate_pair_id);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCTransportStats::get_localCertificateId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.local_certificate_id.is_defined()) return {};
  return (*converted.local_certificate_id);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCTransportStats::get_remoteCertificateId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.remote_certificate_id.is_defined()) return {};
  return (*converted.remote_certificate_id);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCTransportStats::get_dtlsCipher() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCTransportStats::get_srtpCipher() noexcept
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
