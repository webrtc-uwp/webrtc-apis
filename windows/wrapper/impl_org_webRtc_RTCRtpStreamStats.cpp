
#include "impl_org_webRtc_RTCRtpStreamStats.h"
#include "impl_org_webRtc_RTCStats.h"

#include "impl_org_webRtc_enums.h"
#include "Org.WebRtc.Glue.events.h"

#include <zsLib/SafeInt.h>
#include <zsLib/helpers.h>

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCRtpStreamStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }


//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCRtpStreamStats::RTCRtpStreamStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCRtpStreamStatsPtr wrapper::org::webRtc::RTCRtpStreamStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCRtpStreamStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCRtpStreamStats::~RTCRtpStreamStats() noexcept
{
  thisWeak_.reset();
}


//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCRtpStreamStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_13(
    x, i, Detail, RTCRtpStreamStats, stats, Stats, Info,
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
    ulonglong, qpSum, get_qpSum()
  );

}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCRtpStreamStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCRtpStreamStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRtpStreamStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRtpStreamStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
Optional< uint32_t > wrapper::impl::org::webRtc::RTCRtpStreamStats::get_ssrc() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  return get_ssrc(&converted);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRtpStreamStats::get_kind() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  return get_kind(&converted);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRtpStreamStats::get_transportId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  return get_transportId(&converted);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCRtpStreamStats::get_codecId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  return get_codecId(&converted);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRtpStreamStats::get_firCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  return get_firCount(&converted);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRtpStreamStats::get_pliCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  return get_pliCount(&converted);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRtpStreamStats::get_nackCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  return get_nackCount(&converted);
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCRtpStreamStats::get_sliCount() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  return get_sliCount(&converted);
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCRtpStreamStats::get_qpSum() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return {};

  auto converted = cast();
  return get_qpSum(&converted);
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
Optional< uint32_t > WrapperImplType::get_ssrc(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->ssrc.is_defined()) return {};
  return SafeInt<uint32_t>(*native->ssrc);
}

//------------------------------------------------------------------------------
String WrapperImplType::get_kind(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->media_type.is_defined()) return {};
  return *(native->media_type);
}

//------------------------------------------------------------------------------
String WrapperImplType::get_transportId(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->transport_id.is_defined()) return {};
  return *(native->transport_id);
}

//------------------------------------------------------------------------------
String WrapperImplType::get_codecId(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->codec_id.is_defined()) return {};
  return *(native->codec_id);
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_firCount(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->fir_count.is_defined()) return {};
  return SafeInt<unsigned long>(*(native->fir_count));
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_pliCount(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->pli_count.is_defined()) return {};
  return SafeInt<unsigned long>(*(native->pli_count));
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_nackCount(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->nack_count.is_defined()) return {};
  return SafeInt<unsigned long>(*(native->nack_count));
}

//------------------------------------------------------------------------------
unsigned long WrapperImplType::get_sliCount(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->sli_count.is_defined()) return {};
  return SafeInt<unsigned long>(*(native->sli_count));
}

//------------------------------------------------------------------------------
unsigned long long WrapperImplType::get_qpSum(const NativeStats *native) noexcept
{
  ZS_ASSERT(native);
  if (!native) return {};

  if (!native->qp_sum.is_defined()) return {};
  return SafeInt<unsigned long long>(*(native->qp_sum));
}

//------------------------------------------------------------------------------
const NativeStats &WrapperImplType::cast() noexcept
{
  ZS_ASSERT(native_);
  return native_->cast_to<NativeStats>();
}

