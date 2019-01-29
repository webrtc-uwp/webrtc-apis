
#include "impl_org_webRtc_RTCSentRtpStreamStats.h"
#include "impl_org_webRtc_RTCRtpStreamStats.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCSentRtpStreamStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCRtpStreamStats, ImplRTCRtpStreamStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCSentRtpStreamStats::RTCSentRtpStreamStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCSentRtpStreamStatsPtr wrapper::org::webRtc::RTCSentRtpStreamStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCSentRtpStreamStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCSentRtpStreamStats::~RTCSentRtpStreamStats() noexcept
{
  thisWeak_.reset();
}


//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCSentRtpStreamStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_18(
    x, i, Detail, RTCSentRtpStreamStats, stats, Stats, Info,
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
    ulonglong, bytesDiscardedOnSend, get_bytesDiscardedOnSend()
  );
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
Optional< uint32_t > wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_ssrc() noexcept
{
  return ImplRTCRtpStreamStats::get_ssrc(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_kind() noexcept
{
  return ImplRTCRtpStreamStats::get_kind(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_transportId() noexcept
{
  return ImplRTCRtpStreamStats::get_transportId(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_codecId() noexcept
{
  return ImplRTCRtpStreamStats::get_codecId(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_firCount() noexcept
{
  return ImplRTCRtpStreamStats::get_firCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_pliCount() noexcept
{
  return ImplRTCRtpStreamStats::get_pliCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_nackCount() noexcept
{
  return ImplRTCRtpStreamStats::get_nackCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_sliCount() noexcept
{
  return ImplRTCRtpStreamStats::get_sliCount(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_qpSum() noexcept
{
  return ImplRTCRtpStreamStats::get_qpSum(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_packetsSent() noexcept
{
  return get_packetsSent(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_packetsDiscardedOnSend() noexcept
{
  return get_packetsDiscardedOnSend(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_fecPacketsSent() noexcept
{
  return get_fecPacketsSent(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_bytesSent() noexcept
{
  return get_bytesSent(&cast());
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCSentRtpStreamStats::get_bytesDiscardedOnSend() noexcept
{
  return get_bytesDiscardedOnSend(&cast());
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
unsigned long WrapperImplType::get_packetsSent(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->packets_sent.is_defined()) return {};
  return SafeInt<unsigned long>(*(native->packets_sent));
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_packetsDiscardedOnSend(const NativeStats *) noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_fecPacketsSent(const NativeStats *) noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long long WrapperImplType::get_bytesSent(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->bytes_sent.is_defined()) return {};
  return SafeInt<unsigned long long>(*(native->bytes_sent));
}

//------------------------------------------------------------------------------
unsigned long long WrapperImplType::get_bytesDiscardedOnSend(const NativeStats *) noexcept
{
  return {};
}

//------------------------------------------------------------------------------
const NativeStats &WrapperImplType::cast() noexcept
{
  ZS_ASSERT(native_);
  return native_->cast_to<NativeStats>();
}
