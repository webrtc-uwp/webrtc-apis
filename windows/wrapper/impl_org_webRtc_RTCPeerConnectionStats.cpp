
#include "impl_org_webRtc_RTCPeerConnectionStats.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCPeerConnectionStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCPeerConnectionStats::RTCPeerConnectionStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCPeerConnectionStatsPtr wrapper::org::webRtc::RTCPeerConnectionStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCPeerConnectionStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCPeerConnectionStats::~RTCPeerConnectionStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCPeerConnectionStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_7(
    x, i, Detail, RTCPeerConnectionStats, stats, Stats, Info,
    string, type, type.has_value() ? UseEnum::toString(type.value()) : "",
    string, otherType, get_statsTypeOther(),
    string, id, get_id(),
    ulong, dataChannelsOpened, get_dataChannelsOpened(),
    ulong, dataChannelsClosed, get_dataChannelsClosed(),
    ulong, dataChannelsRequested, get_dataChannelsRequested(),
    ulong, dataChannelsAccepted, get_dataChannelsAccepted()
  );

}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCPeerConnectionStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCPeerConnectionStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCPeerConnectionStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCPeerConnectionStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCPeerConnectionStats::get_dataChannelsOpened() noexcept
{
  return get_dataChannelsOpened(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCPeerConnectionStats::get_dataChannelsClosed() noexcept
{
  return get_dataChannelsClosed(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCPeerConnectionStats::get_dataChannelsRequested() noexcept
{
  return get_dataChannelsRequested(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCPeerConnectionStats::get_dataChannelsAccepted() noexcept
{
  return get_dataChannelsAccepted(&cast());
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
unsigned long WrapperImplType::get_dataChannelsOpened(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->data_channels_opened.is_defined()) return {};
  return *(native->data_channels_opened);
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_dataChannelsClosed(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->data_channels_closed.is_defined()) return {};
  return *(native->data_channels_closed);
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_dataChannelsRequested(const NativeStats *) noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_dataChannelsAccepted(const NativeStats *) noexcept
{
  return {};
}

//------------------------------------------------------------------------------
const NativeStats &WrapperImplType::cast() noexcept
{
  ZS_ASSERT(native_);
  return native_->cast_to<NativeStats>();
}
