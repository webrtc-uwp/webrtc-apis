
#include "impl_org_webRtc_RTCIceCandidateStats.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCIceCandidateStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCIceCandidateStats::RTCIceCandidateStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCIceCandidateStatsPtr wrapper::org::webRtc::RTCIceCandidateStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCIceCandidateStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCIceCandidateStats::~RTCIceCandidateStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCIceCandidateStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_14(
    x, i, Detail, RTCIceCandidateStats, stats, Stats, Info,
    string, type, type.has_value() ? UseEnum::toString(type.value()) : "",
    string, otherType, get_statsTypeOther(),
    string, id, get_id(),
    string, transportId, get_transportId(),
    string, networkType, UseEnum::toString(get_networkType()),
    string, ip, get_ip(),
    long, port, get_port(),
    string, protocol, get_protocol(),
    string, candidateType, UseEnum::toString(get_candidateType()),
    long, priority, get_priority(),
    string, url, get_url(),
    string, relayProtocol, get_relayProtocol(),
    bool, hasDeletedValue, get_deleted().has_value(),
    bool, deleted, get_deleted().has_value() ? get_deleted().value() : false
  );
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCIceCandidateStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCIceCandidateStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCIceCandidateStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCIceCandidateStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCIceCandidateStats::get_transportId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.transport_id.is_defined()) return {};
  return (*converted.transport_id);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCNetworkType wrapper::impl::org::webRtc::RTCIceCandidateStats::get_networkType() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.network_type.is_defined()) return {};
  try
  {
    return UseEnum::toWrapperRTCNetworkType((*converted.network_type).c_str());
  } catch (const InvalidParameters &) {
  }

  return wrapper::org::webRtc::RTCNetworkType::RTCNetworkType_unknown;
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCIceCandidateStats::get_ip() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.ip.is_defined()) return {};
  return (*converted.ip);
}

//------------------------------------------------------------------------------
long wrapper::impl::org::webRtc::RTCIceCandidateStats::get_port() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.port.is_defined()) return {};
  return SafeInt<long>(*converted.port);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCIceCandidateStats::get_protocol() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.protocol.is_defined()) return {};
  return (*converted.protocol);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCIceCandidateType wrapper::impl::org::webRtc::RTCIceCandidateStats::get_candidateType() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.candidate_type.is_defined()) return {};
  try
  {
    return UseEnum::toWrapperRTCIceCandidateType((*converted.candidate_type).c_str());
  } catch (const InvalidParameters &) {
  }

  return wrapper::org::webRtc::RTCIceCandidateType::RTCIceCandidateType_host;
}

//------------------------------------------------------------------------------
long wrapper::impl::org::webRtc::RTCIceCandidateStats::get_priority() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.priority.is_defined()) return {};
  return SafeInt<long>(*converted.priority);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCIceCandidateStats::get_url() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.url.is_defined()) return {};
  return (*converted.url);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCIceCandidateStats::get_relayProtocol() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
Optional< bool > wrapper::impl::org::webRtc::RTCIceCandidateStats::get_deleted() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.url.is_defined()) return {};
  return (*converted.deleted);
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
