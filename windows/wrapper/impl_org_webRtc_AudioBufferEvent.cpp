
#include "impl_org_webRtc_AudioBufferEvent.h"
#include "impl_org_webRtc_AudioBuffer.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioBufferEvent::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, UseAudioBuffer);


//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::AudioBufferEvent::AudioBufferEvent() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioBufferEventPtr wrapper::org::webRtc::AudioBufferEvent::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::AudioBufferEvent>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::AudioBufferEvent::~AudioBufferEvent() noexcept
{
  thisWeak_.reset();
  wrapper_dispose();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioBufferEvent::wrapper_dispose() noexcept
{
  std::function<void(void)> complete;
  {
    zsLib::AutoLock lock(lock_);
    complete = std::move(complete_);
  }
  if (!complete)
    return;
  complete();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioBufferPtr wrapper::impl::org::webRtc::AudioBufferEvent::get_buffer() noexcept
{
  return buffer_;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(
  std::function<void(void)> completeFunction,
  AudioBufferNativeType *buffer
) noexcept
{
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->complete_ = std::move(completeFunction);
  result->buffer_ = UseAudioBuffer::toWrapper(buffer);
  return result;
}
