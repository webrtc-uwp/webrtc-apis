
#include "impl_org_webRtc_RTCStatsProvider.h"
#include "impl_org_webRtc_RTCStatsReport.h"
#include "impl_org_webRtc_RTCError.h"
#include "impl_org_webRtc_WebRtcLib.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/rtcerror.h"
#include "impl_org_webRtc_post_include.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStatsProvider::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::StatsWebrtcObserverScopedPtr, StatsWebrtcObserverScopedPtr);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::WebRtcLib, UseWebrtcLib);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCStatsProvider::RTCStatsProvider() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCStatsProvider::~RTCStatsProvider() noexcept
{
}

//------------------------------------------------------------------------------
shared_ptr< PromiseWithHolderPtr< wrapper::org::webRtc::RTCStatsReportPtr > > wrapper::impl::org::webRtc::RTCStatsProvider::getStats(wrapper::org::webRtc::RTCStatsTypeSetPtr statTypes) noexcept(false)
{
  typedef shared_ptr< PromiseWithHolderPtr< wrapper::org::webRtc::RTCStatsReportPtr > > ResultType;

  ::rtc::scoped_refptr<::webrtc::RTCStatsReport> report(new ::rtc::RefCountedObject<::webrtc::RTCStatsReport>(0));

  return ResultType::element_type::createResolved(RTCStatsReport::toWrapper(report), UseWebrtcLib::delegateQueue());
}

//------------------------------------------------------------------------------
void WrapperImplType::onWebrtcObserverStatsDelivered(
                                                     shared_ptr< PromiseWithHolderPtr< wrapper::org::webRtc::RTCStatsReportPtr > > promise,
                                                     rtc::scoped_refptr<const ::webrtc::RTCStatsReport> report
                                                     ) noexcept
{
  if (!promise) return; // promise is disconnected

  auto wrapper = RTCStatsReport::toWrapper(report);
  if (!wrapper) {
    auto error = RTCError::toWrapper(::webrtc::RTCError(::webrtc::RTCErrorType::INVALID_STATE));
    error->reject(promise);
    return;
  }

  promise->resolve(wrapper);
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(const shared_ptr< PromiseWithHolderPtr< wrapper::org::webRtc::RTCStatsReportPtr > > &value)
{
  if (!value) return WrapperImplTypePtr();
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->observer_ = StatsWebrtcObserverScopedPtr(new ::rtc::RefCountedObject<StatsWebrtcObserver>(result, UseWebrtcLib::delegateQueue(), value));

  // Hold a reference to the stats provider inside the promise
  // (which then holds a reference to the observer).
  auto holder = make_shared< AnyHolder<WrapperImplTypePtr> >();
  holder->value_ = result;
  value->setUserData(holder);
  return result;
}

//------------------------------------------------------------------------------
StatsWebrtcObserverScopedPtr WrapperImplType::getObserver(WrapperTypePtr value)
{
  if (!value) return StatsWebrtcObserverScopedPtr();
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, value);
  if (!converted) return StatsWebrtcObserverScopedPtr();
  return converted->observer_;
}
