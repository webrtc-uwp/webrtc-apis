
#include "impl_org_webRtc_CustomVideoCapturerCreateEvent.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturerCreateEvent::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomVideoCapturerCreateEvent::CustomVideoCapturerCreateEvent() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomVideoCapturerCreateEventPtr wrapper::org::webRtc::CustomVideoCapturerCreateEvent::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomVideoCapturerCreateEvent>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomVideoCapturerCreateEvent::~CustomVideoCapturerCreateEvent() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomVideoCapturerCreateEvent::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::CustomVideoCapturerCreateEvent::get_deviceId() noexcept
{
  return deviceId_;
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::CustomVideoCapturerCreateEvent::get_deviceName() noexcept
{
  return deviceName_;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomVideoCapturerPtr wrapper::impl::org::webRtc::CustomVideoCapturerCreateEvent::get_createdCapturer() noexcept
{
  return capturer_;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomVideoCapturerCreateEvent::set_createdCapturer(wrapper::org::webRtc::CustomVideoCapturerPtr value) noexcept
{
  capturer_ = value;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomVideoCapturerPtr WrapperImplType::extractCapturer(WrapperType &wrapperType) noexcept
{
  auto &converted = dynamic_cast<WrapperImplType &>(wrapperType);
  return converted.capturer_;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomVideoCapturerPtr WrapperImplType::extractCapturer(WrapperType *wrapperType) noexcept
{
  if (!wrapperType)
    return {};
  return extractCapturer(*wrapperType);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomVideoCapturerPtr WrapperImplType::extractCapturer(WrapperTypePtr wrapperType) noexcept
{
  if (!wrapperType)
    return {};
  return extractCapturer(wrapperType.get());
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(
  const std::string &deviceId,
  const std::string &deviceName) noexcept
{
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->deviceId_ = deviceId;
  result->deviceName_ = deviceName;
  return result;
}
