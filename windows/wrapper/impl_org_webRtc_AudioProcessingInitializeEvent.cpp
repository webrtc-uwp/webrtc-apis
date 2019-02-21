
#include "impl_org_webRtc_AudioProcessingInitializeEvent.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioProcessingInitializeEvent::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::AudioProcessingInitializeEvent::AudioProcessingInitializeEvent() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioProcessingInitializeEventPtr wrapper::org::webRtc::AudioProcessingInitializeEvent::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::AudioProcessingInitializeEvent>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::AudioProcessingInitializeEvent::~AudioProcessingInitializeEvent() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioProcessingInitializeEvent::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
uint64_t wrapper::impl::org::webRtc::AudioProcessingInitializeEvent::get_samplRateHz() noexcept
{
  return sampleHzRate_;
}

//------------------------------------------------------------------------------
uint64_t wrapper::impl::org::webRtc::AudioProcessingInitializeEvent::get_channels() noexcept
{
  return channels_;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(
  size_t sampleHzRate,
  size_t channels) noexcept
{
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->sampleHzRate_ = sampleHzRate;
  result->channels_ = channels;
  return result;
}
