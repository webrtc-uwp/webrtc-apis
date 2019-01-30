
#include "impl_org_webRtc_RTCDataChannelStats.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCDataChannelStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCDataChannelStats::RTCDataChannelStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCDataChannelStatsPtr wrapper::org::webRtc::RTCDataChannelStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCDataChannelStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCDataChannelStats::~RTCDataChannelStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCDataChannelStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_12(
    x, i, Detail, RTCDataChannelStats, stats, Stats, Info,
    string, type, type.has_value() ? UseEnum::toString(type.value()) : "",
    string, otherType, get_statsTypeOther(),
    string, id, get_id(),
    string, label, get_label(),
    string, protocol, get_protocol(),
    long, dataChannelIdentifier, get_dataChannelIdentifier(),
    string, transportId, get_transportId(),
    string, state, UseEnum::toString(get_state()),
    ulong, messagesSent, get_messagesSent(),
    ulong, bytesSent, get_bytesSent(),
    ulong, messagesReceived, get_messagesReceived(),
    ulong, bytesReceived, get_bytesReceived()
  );

}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCDataChannelStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCDataChannelStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCDataChannelStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCDataChannelStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCDataChannelStats::get_label() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.label.is_defined()) return {};
  return (*converted.label);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCDataChannelStats::get_protocol() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.protocol.is_defined()) return {};
  return (*converted.protocol);
}

//------------------------------------------------------------------------------
long wrapper::impl::org::webRtc::RTCDataChannelStats::get_dataChannelIdentifier() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.datachannelid.is_defined()) return {};
  return SafeInt<long>(*converted.datachannelid);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCDataChannelStats::get_transportId() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCDataChannelState wrapper::impl::org::webRtc::RTCDataChannelStats::get_state() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.state.is_defined()) return {};
  try {
    return UseEnum::toWrapperRTCDataChannelState((*converted.state).c_str());
  } catch (const InvalidParameters &) {
  }
  return wrapper::org::webRtc::RTCDataChannelState::RTCDataChannelState_closed;
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCDataChannelStats::get_messagesSent() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.messages_sent.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.messages_sent);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCDataChannelStats::get_bytesSent() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.bytes_sent.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.bytes_sent);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCDataChannelStats::get_messagesReceived() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.messages_received.is_defined()) return {};
  return SafeInt<unsigned long>(*converted.messages_received);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCDataChannelStats::get_bytesReceived() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  if (!converted.bytes_received.is_defined()) return {};
  return SafeInt<unsigned long long>(*converted.bytes_received);
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
