
#include "impl_org_webRtc_CustomVideoCapturer.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturer::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomVideoCapturer::CustomVideoCapturer() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomVideoCapturerPtr wrapper::org::webRtc::CustomVideoCapturer::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomVideoCapturer>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomVideoCapturer::~CustomVideoCapturer() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomVideoCapturer::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomVideoCapturerPtr wrapper::org::webRtc::CustomVideoCapturer::create(wrapper::org::webRtc::CustomVideoCapturerParametersPtr params) noexcept
{
  wrapper::org::webRtc::CustomVideoCapturerPtr result {};
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomVideoCapturer::notifyFrame(
  wrapper::org::webRtc::VideoFrameBufferPtr frame,
  int origWidth,
  int origHeight
  ) noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoCaptureState wrapper::impl::org::webRtc::CustomVideoCapturer::get_currentState() noexcept
{
  wrapper::org::webRtc::VideoCaptureState result {};
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomVideoCapturer::set_currentState(wrapper::org::webRtc::VideoCaptureState value) noexcept
{
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomVideoCapturer::wrapper_onObserverCountChanged(size_t count) noexcept
{
}


