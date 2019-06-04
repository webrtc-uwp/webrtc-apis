
#include "impl_org_webRtc_RTCStatsReport.h"
#include "impl_org_webRtc_RTCStats.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtc_stats.h"
#include "api/stats/rtc_stats_report.h"
#include "impl_org_webRtc_post_include.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStatsReport::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::ScopedConstNativeTypePtr, ScopedConstNativeTypePtr);


//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCStatsReport::RTCStatsReport() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCStatsReportPtr wrapper::org::webRtc::RTCStatsReport::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCStatsReport>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCStatsReport::~RTCStatsReport() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCStatsPtr wrapper::impl::org::webRtc::RTCStatsReport::getStats(String id) noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return wrapper::org::webRtc::RTCStatsPtr();

  auto stat = native_->Get(id);
  if (!stat) return wrapper::org::webRtc::RTCStatsPtr();

  auto statCopy = stat->copy();
  if (!statCopy) return wrapper::org::webRtc::RTCStatsPtr();

  return RTCStats::toWrapper(std::move(statCopy));
}

//------------------------------------------------------------------------------
uint64_t wrapper::impl::org::webRtc::RTCStatsReport::get_objectId() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return 0;

  uintptr_t ptrNumber = reinterpret_cast<uintptr_t>(native_.get());
  return SafeInt<uint64_t>(ptrNumber);
}

//------------------------------------------------------------------------------
shared_ptr< list< String > > wrapper::impl::org::webRtc::RTCStatsReport::get_statsIds() noexcept
{
  auto result = make_shared<list<String> >();

  ZS_ASSERT(native_);
  if (!native_) return result;

  for (auto iter = native_->begin(); iter != native_->end(); ++iter) {
    auto& value = *iter;
    (*result).push_back(value.id());
  }

  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(const ScopedConstNativeTypePtr &value) noexcept
{
  if (!value) return WrapperImplTypePtr();
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = value;
  return result;
}

//------------------------------------------------------------------------------
ScopedConstNativeTypePtr WrapperImplType::toNative(WrapperTypePtr value) noexcept
{
  if (!value) return ScopedConstNativeTypePtr();
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, value);
  if (!converted) return ScopedConstNativeTypePtr();
  return converted->native_;
}
