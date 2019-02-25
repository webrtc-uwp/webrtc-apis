
#include "impl_org_webRtc_VideoFrameBufferEvent.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFrameBufferEvent::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoFrameBufferEvent::VideoFrameBufferEvent() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFrameBufferEventPtr wrapper::org::webRtc::VideoFrameBufferEvent::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::VideoFrameBufferEvent>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoFrameBufferEvent::~VideoFrameBufferEvent() noexcept
{
  thisWeak_.reset();
  wrapper_dispose();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoFrameBufferEvent::wrapper_dispose() noexcept
{
  buffer_.reset();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFrameBufferPtr wrapper::impl::org::webRtc::VideoFrameBufferEvent::get_buffer() noexcept
{
  return buffer_;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(UseVideoFrameBufferPtr buffer) noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->buffer_ = buffer;
  return result;
}
