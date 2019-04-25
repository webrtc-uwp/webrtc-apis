
#include "impl_org_webRtc_CustomAudioDevice.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioDevice::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioDevice::CustomAudioDevice() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioDevicePtr wrapper::org::webRtc::CustomAudioDevice::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomAudioDevice>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioDevice::~CustomAudioDevice() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioDevicePtr wrapper::org::webRtc::CustomAudioDevice::create(wrapper::org::webRtc::CustomAudioDeviceParametersPtr params) noexcept
{
  wrapper::org::webRtc::CustomAudioDevicePtr result {};
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::updateDevices(wrapper::org::webRtc::CustomAudioDeviceParametersPtr params) noexcept
{
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::updateCurrentPlayoutDelay(int16_t delayMs) noexcept
{
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::setRecordedBuffer(wrapper::org::webRtc::AudioBufferPtr buffer) noexcept
{
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioDevice::deliverRecordedData() noexcept
{
  bool result {};
  return result;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioDevice::notifyNewMicrophoneLevel() noexcept
{
  bool result {};
  return result;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioDevice::setTypingStatus(bool isTyping) noexcept
{
  bool result {};
  return result;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioBufferPtr wrapper::impl::org::webRtc::CustomAudioDevice::requestPlayoutData() noexcept
{
  wrapper::org::webRtc::AudioBufferPtr result {};
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::updateVqeData(
  int playDelayMs,
  int recordDelayMs
  ) noexcept
{
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::notifyFrame(
  wrapper::org::webRtc::AudioBufferPtr frame,
  int origWidth,
  int origHeight
  ) noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioState wrapper::impl::org::webRtc::CustomAudioDevice::get_playoutCurrentState() noexcept
{
  wrapper::org::webRtc::CustomAudioState result {};
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_playoutCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioState wrapper::impl::org::webRtc::CustomAudioDevice::get_recurdingCurrentState() noexcept
{
  wrapper::org::webRtc::CustomAudioState result {};
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_recurdingCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioState wrapper::impl::org::webRtc::CustomAudioDevice::get_speakerCurrentState() noexcept
{
  wrapper::org::webRtc::CustomAudioState result {};
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_speakerCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioState wrapper::impl::org::webRtc::CustomAudioDevice::get_microphoneCurrentState() noexcept
{
  wrapper::org::webRtc::CustomAudioState result {};
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_microphoneCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept
{
}

//------------------------------------------------------------------------------
uint32_t wrapper::impl::org::webRtc::CustomAudioDevice::get_playbackSampleRateFsHz() noexcept
{
  uint32_t result {};
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_playbackSampleRateFsHz(uint32_t value) noexcept
{
}

//------------------------------------------------------------------------------
uint32_t wrapper::impl::org::webRtc::CustomAudioDevice::get_recordingSampleRateFsHz() noexcept
{
  uint32_t result {};
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_recordingSampleRateFsHz(uint32_t value) noexcept
{
}

//------------------------------------------------------------------------------
int32_t wrapper::impl::org::webRtc::CustomAudioDevice::get_playoutChannels() noexcept
{
  int32_t result {};
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_playoutChannels(int32_t value) noexcept
{
}

//------------------------------------------------------------------------------
int32_t wrapper::impl::org::webRtc::CustomAudioDevice::get_recordingChannels() noexcept
{
  int32_t result {};
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_recordingChannels(int32_t value) noexcept
{
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::wrapper_onObserverCountChanged(size_t count) noexcept
{
}


