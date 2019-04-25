
#include "impl_org_webRtc_CustomAudioDeviceSelectEvent.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioDeviceSelectEvent::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioDeviceSelectEvent::CustomAudioDeviceSelectEvent() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioDeviceSelectEventPtr wrapper::org::webRtc::CustomAudioDeviceSelectEvent::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomAudioDeviceSelectEvent>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioDeviceSelectEvent::~CustomAudioDeviceSelectEvent() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDeviceSelectEvent::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
uint16_t wrapper::impl::org::webRtc::CustomAudioDeviceSelectEvent::get_deviceId() noexcept
{
  uint16_t result {};
  return result;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioDeviceSelectEvent::get_isRecordingDevice() noexcept
{
  bool result {};
  return result;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioDeviceSelectEvent::get_isPlayoutDevice() noexcept
{
  bool result {};
  return result;
}


