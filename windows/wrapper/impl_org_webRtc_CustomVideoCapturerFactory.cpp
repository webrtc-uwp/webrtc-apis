
#include "impl_org_webRtc_CustomVideoCapturerFactory.h"
#include "impl_org_webRtc_CustomVideoCapturer.h"
#include "impl_org_webRtc_CustomVideoCapturerCreateEvent.h"
#include "impl_org_webRtc_WebRtcLib.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturerFactory::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomVideoCapturerFactory::CustomVideoCapturerFactory() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomVideoCapturerFactoryPtr wrapper::org::webRtc::CustomVideoCapturerFactory::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomVideoCapturerFactory>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomVideoCapturerFactory::~CustomVideoCapturerFactory() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomVideoCapturerFactory::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomVideoCapturerFactoryPtr wrapper::org::webRtc::CustomVideoCapturerFactory::create() noexcept
{
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomVideoCapturerFactory::wrapper_onObserverCountChanged(size_t /* count */) noexcept
{
}

//------------------------------------------------------------------------------
std::unique_ptr<WrapperImplType::UseVideoCapturer> WrapperImplType::Create(const ::cricket::Device& device)
{
  auto event = CustomVideoCapturerCreateEvent::toWrapper(device.id, device.name);
  if (!event)
    return {};

  auto pThis = thisWeak_.lock();

  auto queue = WebRtcLib::customVideoQueue();

  HANDLE handle = ::CreateEventEx(NULL, NULL, 0, EVENT_ALL_ACCESS);

  std::function<void(void)> callback = [handle]() { ::SetEvent(handle); };

  queue->postClosure([pThis, event, callback]() { pThis->onCreateCustomVideoCapturer(event); callback(); });

  ::WaitForSingleObjectEx(handle, INFINITE, FALSE /* ALERTABLE */);
  ::CloseHandle(handle);

  callback = {};

  auto capturer = CustomVideoCapturerCreateEvent::extractCapturer(event);
  if (!capturer)
    return {};

  return CustomVideoCapturer::toNative(capturer);
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::create() noexcept
{
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  return result;
}

//------------------------------------------------------------------------------
WrapperImplType::UseVideoDeviceCapturerFactoryPtr WrapperImplType::toNative(WrapperTypePtr wrapper) noexcept
{
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, wrapper);
  return converted;
}
