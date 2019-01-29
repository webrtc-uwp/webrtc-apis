
#include "impl_org_webRtc_RTCRtpContributingSourceStats.h"
#include "impl_org_webRtc_RTCStats.h"

#include "impl_org_webRtc_enums.h"
#include "Org.WebRtc.Glue.events.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCRtpContributingSourceStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCRtpContributingSourceStats::RTCRtpContributingSourceStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCRtpContributingSourceStatsPtr wrapper::org::webRtc::RTCRtpContributingSourceStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCRtpContributingSourceStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCRtpContributingSourceStats::~RTCRtpContributingSourceStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCRtpContributingSourceStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_8(
    x, i, Detail, RTCRtpContributingSourceStats, stats, Stats, Info,
    string, type, type.has_value() ? UseEnum::toString(type.value()) : "",
    string, otherType, get_statsTypeOther(),
    string, id, get_id(),
    ulong, contributorSsrc, get_contributorSsrc(),
    string, inboundRtpStreamId, get_inboundRtpStreamId(),
    ulong, packetsContributedTo, get_packetsContributedTo(),
    bool, hasAudioLevelValue, get_audioLevel().has_value(),
    double, audioLevel, get_audioLevel().has_value() ? get_audioLevel().value() : 0
  );
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCRtpContributingSourceStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCRtpContributingSourceStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRtpContributingSourceStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRtpContributingSourceStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRtpContributingSourceStats::get_contributorSsrc() noexcept
{
  return get_contributorSsrc(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRtpContributingSourceStats::get_inboundRtpStreamId() noexcept
{
  return get_inboundRtpStreamId(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRtpContributingSourceStats::get_packetsContributedTo() noexcept
{
  return get_packetsContributedTo(&cast());
}

//------------------------------------------------------------------------------
Optional< double > wrapper::impl::org::webRtc::RTCRtpContributingSourceStats::get_audioLevel() noexcept
{
  return get_audioLevel(&cast());
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
unsigned long WrapperImplType::get_contributorSsrc(const NativeStats *) noexcept
{
  return {};
}

//------------------------------------------------------------------------------
String WrapperImplType::get_inboundRtpStreamId(const NativeStats *) noexcept
{
  return {};
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_packetsContributedTo(const NativeStats *) noexcept
{
  return {};
}

//------------------------------------------------------------------------------
Optional< double > WrapperImplType::get_audioLevel(const NativeStats *) noexcept
{
  return {};
}

//------------------------------------------------------------------------------
const NativeStats &WrapperImplType::cast() noexcept
{
  ZS_ASSERT(native_);
  return native_->cast_to<NativeStats>();
}
