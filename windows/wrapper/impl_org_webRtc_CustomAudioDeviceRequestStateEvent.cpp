
#include "impl_org_webRtc_CustomAudioDeviceRequestStateEvent.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioDeviceRequestStateEvent::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioDeviceRequestStateEvent::CustomAudioDeviceRequestStateEvent() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioDeviceRequestStateEventPtr wrapper::org::webRtc::CustomAudioDeviceRequestStateEvent::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomAudioDeviceRequestStateEvent>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioDeviceRequestStateEvent::~CustomAudioDeviceRequestStateEvent() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDeviceRequestStateEvent::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioDeviceRequestStateEvent::get_isRecordingDevice() noexcept
{
  bool result {};
  return result;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioDeviceRequestStateEvent::get_isPlayoutDevice() noexcept
{
  bool result {};
  return result;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioRequestState wrapper::impl::org::webRtc::CustomAudioDeviceRequestStateEvent::get_requestedState() noexcept
{
  wrapper::org::webRtc::CustomAudioRequestState result {};
  return result;
}


