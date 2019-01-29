
#include "impl_org_webRtc_RTCRemoteOutboundRtpStreamStats.h"
#include "impl_org_webRtc_RTCSentRtpStreamStats.h"
#include "impl_org_webRtc_RTCReceivedRtpStreamStats.h"
#include "impl_org_webRtc_RTCRtpStreamStats.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCRtpStreamStats, ImplRTCRtpStreamStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCReceivedRtpStreamStats, ImplRTCReceivedRtpStreamStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }


//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::RTCRemoteOutboundRtpStreamStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCRemoteOutboundRtpStreamStatsPtr wrapper::org::webRtc::RTCRemoteOutboundRtpStreamStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::~RTCRemoteOutboundRtpStreamStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_20(
    x, i, Detail, RTCRemoteOutboundRtpStreamStats, stats, Stats, Info,
    string, type, type.has_value() ? UseEnum::toString(type.value()) : "",
    string, otherType, get_statsTypeOther(),
    string, id, get_id(),
    bool, hasSsrcValue, get_ssrc().has_value(),
    uint32, ssrc, get_ssrc().has_value() ? get_ssrc().value() : 0,
    string, kind, get_kind(),
    string, transportId, get_transportId(),
    string, codecId, get_codecId(),
    ulong, firCount, get_firCount(),
    ulong, pliCount, get_pliCount(),
    ulong, nackCount, get_nackCount(),
    ulong, sliCount, get_sliCount(),
    ulonglong, qpSum, get_qpSum(),
    ulong, packetsSent, get_packetsSent(),
    ulong, packetsDiscardedOnSend, get_packetsDiscardedOnSend(),
    ulong, fecPacketsSent, get_fecPacketsSent(),
    ulonglong, bytesSent, get_bytesSent(),
    ulonglong, bytesDiscardedOnSend, get_bytesDiscardedOnSend(),
    string, localId, get_localId(),
    duration, remoteTimestamp, zsLib::timeSinceEpoch<Milliseconds>(get_remoteTimestamp()).count()
  );

}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
Optional< uint32_t > wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_ssrc() noexcept
{
  return ImplRTCRtpStreamStats::get_ssrc(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_kind() noexcept
{
  return ImplRTCRtpStreamStats::get_kind(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_transportId() noexcept
{
  return ImplRTCRtpStreamStats::get_transportId(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_codecId() noexcept
{
  return ImplRTCRtpStreamStats::get_codecId(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_firCount() noexcept
{
  return ImplRTCRtpStreamStats::get_firCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_pliCount() noexcept
{
  return ImplRTCRtpStreamStats::get_pliCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_nackCount() noexcept
{
  return ImplRTCRtpStreamStats::get_nackCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_sliCount() noexcept
{
  return ImplRTCRtpStreamStats::get_sliCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_qpSum() noexcept
{
  return ImplRTCRtpStreamStats::get_qpSum(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_packetsSent() noexcept
{
  unsigned long result {};
  return result;
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_packetsDiscardedOnSend() noexcept
{
  unsigned long result {};
  return result;
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_fecPacketsSent() noexcept
{
  unsigned long result {};
  return result;
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_bytesSent() noexcept
{
  unsigned long long result {};
  return result;
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_bytesDiscardedOnSend() noexcept
{
  unsigned long long result {};
  return result;
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_localId() noexcept
{
  String result {};
  return result;
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCRemoteOutboundRtpStreamStats::get_remoteTimestamp() noexcept
{
  ::zsLib::Time result {};
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
