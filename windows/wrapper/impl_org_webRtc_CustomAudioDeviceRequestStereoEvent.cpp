
#include "impl_org_webRtc_CustomAudioDeviceRequestStereoEvent.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioDeviceRequestStereoEvent::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioDeviceRequestStereoEvent::CustomAudioDeviceRequestStereoEvent() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioDeviceRequestStereoEventPtr wrapper::org::webRtc::CustomAudioDeviceRequestStereoEvent::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomAudioDeviceRequestStereoEvent>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioDeviceRequestStereoEvent::~CustomAudioDeviceRequestStereoEvent() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDeviceRequestStereoEvent::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioDeviceRequestStereoEvent::get_isRecordingDevice() noexcept
{
  return isRecordingDevice_;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioDeviceRequestStereoEvent::get_isPlayoutDevice() noexcept
{
  return isPlayoutDevice_;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioDeviceRequestStereoEvent::get_stereo() noexcept
{
  return stereo_;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(
  bool isRecordingDevice,
  bool isPlayoutDevice,
  bool stereo) noexcept
{
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->isRecordingDevice_ = isRecordingDevice;
  result->isPlayoutDevice_ = isPlayoutDevice;
  result->stereo_ = stereo;
  return result;
}
