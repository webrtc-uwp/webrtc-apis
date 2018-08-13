
#include "impl_org_webRtc_VideoTrackSourceStats.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoTrackSourceStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, NativeType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoTrackSourceStats::VideoTrackSourceStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoTrackSourceStatsPtr wrapper::org::webRtc::VideoTrackSourceStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::VideoTrackSourceStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoTrackSourceStats::~VideoTrackSourceStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoTrackSourceStats::wrapper_init_org_webRtc_VideoTrackSourceStats() noexcept
{
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(const NativeType &native) noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->inputWidth = SafeInt<decltype(result->inputWidth)>(native.input_width);
  result->inputHeight = SafeInt<decltype(result->inputWidth)>(native.input_height);
  return result;
}
