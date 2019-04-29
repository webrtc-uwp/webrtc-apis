
#include "impl_org_webRtc_CustomAudioDevice.h"
#include "impl_org_webRtc_CustomAudioDeviceParameters.h"
#include "impl_org_webRtc_CustomAudioRecordingDeviceInfo.h"
#include "impl_org_webRtc_CustomAudioPlayoutDeviceInfo.h"
#include "impl_org_webRtc_CustomAudioDeviceSelectEvent.h"
#include "impl_org_webRtc_CustomAudioDeviceRequestStateEvent.h"
#include "impl_org_webRtc_CustomAudioDeviceRequestStereoEvent.h"
#include "impl_org_webRtc_CustomAudioMixerRequestStateEvent.h"
#include "impl_org_webRtc_CustomAudioMixerRequestMuteEvent.h"
#include "impl_org_webRtc_CustomAudioMixerRequestVolumeEvent.h"
#include "impl_org_webRtc_CustomAudioMixerRequestSettingsEvent.h"

#include "impl_org_webRtc_pre_include.h"
#include "modules/audio_device/audio_device_buffer.h"
#include "impl_org_webRtc_post_include.h"

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
using ::zsLib::AutoRecursiveLock;
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

ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::UsePlayoutDeviceInfo, UsePlayoutDeviceInfo);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::UseRecordingDeviceInfo, UseRecordingDeviceInfo);


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
  AutoRecursiveLock lock(lock_);
  buffer_.reset();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioDevicePtr wrapper::org::webRtc::CustomAudioDevice::create(wrapper::org::webRtc::CustomAudioDeviceParametersPtr params) noexcept
{
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;

  if (params) {
    if (params->playoutDevices) {
      for (auto iter = params->playoutDevices->begin(); iter != params->playoutDevices->end(); ++iter) {
        auto info = (*iter);
        if (!info) continue;
        result->playoutDevices_.push_back(UsePlayoutDeviceInfo::clone(info));
      }
    }
    if (params->recordingDevices) {
      for (auto iter = params->recordingDevices->begin(); iter != params->recordingDevices->end(); ++iter) {
        auto info = (*iter);
        if (!info) continue;
        result->recordingDevices_.push_back(UseRecordingDeviceInfo::clone(info));
      }
    }
  }

  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::updateDevices(wrapper::org::webRtc::CustomAudioDeviceParametersPtr params) noexcept
{
  ZS_ASSERT(params);

  if (!params)
    return;

  AutoRecursiveLock lock(lock_);

  if (params->playoutDevices) {
    playoutDevices_ = {};
    for (auto iter = params->playoutDevices->begin(); iter != params->playoutDevices->end(); ++iter) {
      auto info = (*iter);
      if (!info) continue;
      playoutDevices_.push_back(UsePlayoutDeviceInfo::clone(info));
    }
  }
  if (params->recordingDevices) {
    recordingDevices_ = {};
    for (auto iter = params->recordingDevices->begin(); iter != params->recordingDevices->end(); ++iter) {
      auto info = (*iter);
      if (!info) continue;
      recordingDevices_.push_back(UseRecordingDeviceInfo::clone(info));
    }
  }
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::updateCurrentPlayoutDelay(uint16_t delayMs) noexcept
{
  AutoRecursiveLock lock(lock_);
  playoutDelay_ = delayMs;
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
  AutoRecursiveLock lock(lock_);
  if (!buffer_)
    return false;

  return 0 == buffer_->NewMicLevel();
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioDevice::setTypingStatus(bool isTyping) noexcept
{
  AutoRecursiveLock lock(lock_);
  if (!buffer_)
    return false;

  return 0 == buffer_->SetTypingStatus(isTyping);
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
  AutoRecursiveLock lock(lock_);
  return playoutState_;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_playoutCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept
{
  AutoRecursiveLock lock(lock_);
  playoutState_ = value;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioState wrapper::impl::org::webRtc::CustomAudioDevice::get_recordingCurrentState() noexcept
{
  AutoRecursiveLock lock(lock_);
  return recordingState_;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_recordingCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept
{
  AutoRecursiveLock lock(lock_);
  recordingState_ = value;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioState wrapper::impl::org::webRtc::CustomAudioDevice::get_speakerCurrentState() noexcept
{
  AutoRecursiveLock lock(lock_);
  return speakerState_;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_speakerCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept
{
  AutoRecursiveLock lock(lock_);
  speakerState_ = value;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioState wrapper::impl::org::webRtc::CustomAudioDevice::get_microphoneCurrentState() noexcept
{
  AutoRecursiveLock lock(lock_);
  return microphoneState_;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_microphoneCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept
{
  AutoRecursiveLock lock(lock_);
  microphoneState_ = value;
}

//------------------------------------------------------------------------------
uint32_t wrapper::impl::org::webRtc::CustomAudioDevice::get_playbackSampleRateFsHz() noexcept
{
  AutoRecursiveLock lock(lock_);
  return playbackHzRate_;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_playbackSampleRateFsHz(uint32_t value) noexcept
{
  AutoRecursiveLock lock(lock_);
  if (buffer_) {
    if (value != playbackHzRate_) {
      buffer_->SetPlayoutSampleRate(value);
    }
  }
  playbackHzRate_ = value;
}

//------------------------------------------------------------------------------
uint32_t wrapper::impl::org::webRtc::CustomAudioDevice::get_recordingSampleRateFsHz() noexcept
{
  AutoRecursiveLock lock(lock_);
  return recordingHzRate_;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_recordingSampleRateFsHz(uint32_t value) noexcept
{
  AutoRecursiveLock lock(lock_);
  if (buffer_) {
    if (value != recordingHzRate_) {
      buffer_->SetRecordingSampleRate(value);
    }
  }
  recordingHzRate_ = value;
}

//------------------------------------------------------------------------------
int32_t wrapper::impl::org::webRtc::CustomAudioDevice::get_playoutChannels() noexcept
{
  AutoRecursiveLock lock(lock_);
  return playbackChannels_;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_playoutChannels(int32_t value) noexcept
{
  AutoRecursiveLock lock(lock_);
  if (buffer_) {
    if (value != playbackChannels_) {
      buffer_->SetPlayoutChannels(value);
    }
  }
  playbackChannels_ = value;
}

//------------------------------------------------------------------------------
int32_t wrapper::impl::org::webRtc::CustomAudioDevice::get_recordingChannels() noexcept
{
  AutoRecursiveLock lock(lock_);
  return recordingChannels_;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::set_recordingChannels(int32_t value) noexcept
{
  AutoRecursiveLock lock(lock_);
  if (buffer_) {
    if (value != recordingChannels_) {
      buffer_->SetRecordingChannels(value);
    }
  }
  recordingChannels_ = value;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioDevice::wrapper_onObserverCountChanged(size_t count) noexcept
{
  ZS_MAYBE_USED(count);
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::ActiveAudioLayer(AudioLayer* audioLayer) const
{
  ZS_ASSERT(audioLayer);
  if (audioLayer)
    *audioLayer = AudioDeviceModule::kPlatformDefaultAudio;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::RegisterAudioCallback(::webrtc::AudioTransport* audioCallback)
{
  AutoRecursiveLock lock(lock_);
  audioCallback_ = audioCallback;
  if (buffer_) {
    buffer_->RegisterAudioCallback(audioCallback_);
  }
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::Init()
{
  AutoRecursiveLock lock(lock_);
  prepareBuffer();
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::Terminate()
{
  AutoRecursiveLock lock(lock_);
  buffer_.reset();
}

//-----------------------------------------------------------------------------
bool WrapperImplType::Initialized() const
{
  AutoRecursiveLock lock(lock_);
  return (bool)buffer_;
}

//-----------------------------------------------------------------------------
int16_t WrapperImplType::PlayoutDevices()
{
  AutoRecursiveLock lock(lock_);
  return SafeInt<int16_t>(playoutDevices_.size());
}

//-----------------------------------------------------------------------------
int16_t WrapperImplType::RecordingDevices()
{
  AutoRecursiveLock lock(lock_);
  return SafeInt<int16_t>(recordingDevices_.size());
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::PlayoutDeviceName(uint16_t index,
  char name[::webrtc::kAdmMaxDeviceNameSize],
  char guid[::webrtc::kAdmMaxGuidSize])
{
  AutoRecursiveLock lock(lock_);
  ZS_ASSERT(playoutDevices_.size() >= index);

  if (playoutDevices_.size() <= index)
    return -1;

  auto iter = std::next(playoutDevices_.begin(), index);
  auto &value = (*iter);
  strncpy_s(name, sizeof(name), value->name.c_str(), value->name.length());
  strncpy_s(guid, sizeof(guid), value->guid.c_str(), value->guid.length());
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::RecordingDeviceName(uint16_t index,
  char name[::webrtc::kAdmMaxDeviceNameSize],
  char guid[::webrtc::kAdmMaxGuidSize])
{
  AutoRecursiveLock lock(lock_);
  ZS_ASSERT(recordingDevices_.size() >= index);

  if (recordingDevices_.size() <= index)
    return -1;

  auto iter = std::next(recordingDevices_.begin(), index);
  auto &value = (*iter);
  strncpy_s(name, sizeof(name), value->name.c_str(), value->name.length());
  strncpy_s(guid, sizeof(guid), value->guid.c_str(), value->guid.length());
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SetPlayoutDevice(uint16_t index)
{
  auto event = CustomAudioDeviceSelectEvent::toWrapper(index, false, true);
  {
    AutoRecursiveLock lock(lock_);
    ZS_ASSERT(playoutDevices_.size() >= index);

    if (playoutDevices_.size() <= index)
      return -1;

    auto iter = std::next(playoutDevices_.begin(), index);
    auto &value = (*iter);
    currentPlayoutDevice_ = value;
  }
  onSelectDevice(event);
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SetPlayoutDevice(WindowsDeviceType device)
{
  uint16_t id = 0;

  {
    AutoRecursiveLock lock(lock_);

    for (auto iter = playoutDevices_.begin(); iter != playoutDevices_.end(); ++iter, ++id) {
      auto &value = (*iter);
      switch (device)
      {
        case WindowsDeviceType::kDefaultCommunicationDevice: {
          if (value->isDefaultCommunicationDevice)
            goto found;
          break;
        }
        case WindowsDeviceType::kDefaultDevice: {
          if (value->isDefaultDevice)
            goto found;
          break;
        }
      }
    }

    return -1;
  }
found:
  {
    SetPlayoutDevice(id);
  }
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SetRecordingDevice(uint16_t index)
{
  auto event = CustomAudioDeviceSelectEvent::toWrapper(index, true, false);
  {
    AutoRecursiveLock lock(lock_);
    ZS_ASSERT(recordingDevices_.size() >= index);

    if (recordingDevices_.size() <= index)
      return -1;

    auto iter = std::next(recordingDevices_.begin(), index);
    auto &value = (*iter);
    currentRecordingDevice_ = value;
  }
  onSelectDevice(event);
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SetRecordingDevice(WindowsDeviceType device)
{
  uint16_t id = 0;

  {
    AutoRecursiveLock lock(lock_);

    for (auto iter = recordingDevices_.begin(); iter != recordingDevices_.end(); ++iter, ++id) {
      auto &value = (*iter);
      switch (device)
      {
        case WindowsDeviceType::kDefaultCommunicationDevice: {
          if (value->isDefaultCommunicationDevice)
            goto found;
          break;
        }
        case WindowsDeviceType::kDefaultDevice: {
          if (value->isDefaultDevice)
            goto found;
          break;
        }
      }
    }

    return -1;
  }
found:
  {
    SetRecordingDevice(id);
  }
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::PlayoutIsAvailable(bool* available)
{
  if (!available)
    return -1;

  AutoRecursiveLock lock(lock_);
  *available = playoutDevices_.size() > 0;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::InitPlayout()
{
  auto event = CustomAudioDeviceRequestStateEvent::toWrapper(false, true, wrapper::org::webRtc::CustomAudioRequestState::CustomAudioRequestState_initialize);
  onRequestDeviceState(event);
  return 0;
}

//-----------------------------------------------------------------------------
bool WrapperImplType::PlayoutIsInitialized() const
{
  AutoRecursiveLock lock(lock_);
  return playoutState_ > wrapper::org::webRtc::CustomAudioState::CustomAudioState_unprepared;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::RecordingIsAvailable(bool* available)
{
  if (!available)
    return -1;

  AutoRecursiveLock lock(lock_);
  *available = recordingDevices_.size() > 0;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::InitRecording()
{
  auto event = CustomAudioDeviceRequestStateEvent::toWrapper(true, false, wrapper::org::webRtc::CustomAudioRequestState::CustomAudioRequestState_initialize);
  onRequestDeviceState(event);
  return 0;
}

//-----------------------------------------------------------------------------
bool WrapperImplType::RecordingIsInitialized() const
{
  AutoRecursiveLock lock(lock_);
  return recordingState_ > wrapper::org::webRtc::CustomAudioState::CustomAudioState_unprepared;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::StartPlayout()
{
  auto event = CustomAudioDeviceRequestStateEvent::toWrapper(false, true, wrapper::org::webRtc::CustomAudioRequestState::CustomAudioRequestState_start);
  onRequestDeviceState(event);
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::StopPlayout()
{
  auto event = CustomAudioDeviceRequestStateEvent::toWrapper(false, true, wrapper::org::webRtc::CustomAudioRequestState::CustomAudioRequestState_stop);
  onRequestDeviceState(event);
  return 0;
}

//-----------------------------------------------------------------------------
bool WrapperImplType::Playing() const
{
  AutoRecursiveLock lock(lock_);
  return playoutState_ == wrapper::org::webRtc::CustomAudioState::CustomAudioState_started;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::StartRecording()
{
  auto event = CustomAudioDeviceRequestStateEvent::toWrapper(true, false, wrapper::org::webRtc::CustomAudioRequestState::CustomAudioRequestState_start);
  onRequestDeviceState(event);
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::StopRecording()
{
  auto event = CustomAudioDeviceRequestStateEvent::toWrapper(true, false, wrapper::org::webRtc::CustomAudioRequestState::CustomAudioRequestState_stop);
  onRequestDeviceState(event);
  return 0;
}

//-----------------------------------------------------------------------------
bool WrapperImplType::Recording() const
{
  AutoRecursiveLock lock(lock_);
  return recordingState_ == wrapper::org::webRtc::CustomAudioState::CustomAudioState_started;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::InitSpeaker()
{
  auto event = CustomAudioMixerRequestStateEvent::toWrapper(true, false, wrapper::org::webRtc::CustomAudioRequestState::CustomAudioRequestState_initialize);
  onRequestMixerState(event);
}

//-----------------------------------------------------------------------------
bool WrapperImplType::SpeakerIsInitialized() const
{
  AutoRecursiveLock lock(lock_);
  return speakerState_ > wrapper::org::webRtc::CustomAudioState::CustomAudioState_unprepared;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::InitMicrophone()
{
  auto event = CustomAudioMixerRequestStateEvent::toWrapper(false, true, wrapper::org::webRtc::CustomAudioRequestState::CustomAudioRequestState_initialize);
  onRequestMixerState(event);
  return 0;
}

//-----------------------------------------------------------------------------
bool WrapperImplType::MicrophoneIsInitialized() const
{
  AutoRecursiveLock lock(lock_);
  return microphoneState_ > wrapper::org::webRtc::CustomAudioState::CustomAudioState_unprepared;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SpeakerVolumeIsAvailable(bool* available)
{
  if (!available)
    return -1;

  AutoRecursiveLock lock(lock_);
  if (currentPlayoutDevice_)
    *available = currentPlayoutDevice_->speakerVolumeIsAvailable;
  else
    *available = false;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SetSpeakerVolume(uint32_t volume)
{
  auto event = CustomAudioMixerRequestVolumeEvent::toWrapper(true, false, volume);
  onRequestMixerVolume(event);

  AutoRecursiveLock lock(lock_);
  speakerVolume_ = volume;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SpeakerVolume(uint32_t* volume) const
{
  if (!volume)
    return -1;

  AutoRecursiveLock lock(lock_);
  *volume = speakerVolume_;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::MaxSpeakerVolume(uint32_t* maxVolume) const
{
  if (!maxVolume)
    return -1;

  AutoRecursiveLock lock(lock_);
  if (currentPlayoutDevice_)
    *maxVolume = currentPlayoutDevice_->maxSpeakerVolume;
  else
    *maxVolume = 0;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::MinSpeakerVolume(uint32_t* minVolume) const
{
  if (!minVolume)
    return -1;

  AutoRecursiveLock lock(lock_);
  if (currentPlayoutDevice_)
    *minVolume = currentPlayoutDevice_->minSpeakerVolume;
  else
    *minVolume = 0;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::MicrophoneVolumeIsAvailable(bool* available)
{
  if (!available)
    return -1;

  AutoRecursiveLock lock(lock_);
  if (currentRecordingDevice_)
    *available = currentRecordingDevice_->microphoneVolumeIsAvailable;
  else
    *available = false;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SetMicrophoneVolume(uint32_t volume)
{
  auto event = CustomAudioMixerRequestVolumeEvent::toWrapper(false, true, volume);
  onRequestMixerVolume(event);

  AutoRecursiveLock lock(lock_);
  microphoneVolume_ = volume;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::MicrophoneVolume(uint32_t* volume) const
{
  if (!volume)
    return -1;

  AutoRecursiveLock lock(lock_);
  *volume = microphoneVolume_;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::MaxMicrophoneVolume(uint32_t* maxVolume) const
{
  if (!maxVolume)
    return -1;

  AutoRecursiveLock lock(lock_);
  if (currentRecordingDevice_)
    *maxVolume = currentRecordingDevice_->maxMicrophoneVolume;
  else
    *maxVolume = 0;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::MinMicrophoneVolume(uint32_t* minVolume) const
{
  if (!minVolume)
    return -1;

  AutoRecursiveLock lock(lock_);
  if (currentRecordingDevice_)
    *minVolume = currentRecordingDevice_->minMicrophoneVolume;
  else
    *minVolume = 0;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SpeakerMuteIsAvailable(bool* available)
{
  if (!available)
    return -1;

  AutoRecursiveLock lock(lock_);
  if (currentPlayoutDevice_)
    *available = currentPlayoutDevice_->speakerMuteIsAvailable;
  else
    *available = false;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SetSpeakerMute(bool enable)
{
  auto event = CustomAudioMixerRequestMuteEvent::toWrapper(true, false, enable);
  onRequestMixerMute(event);

  AutoRecursiveLock lock(lock_);
  speakerMute_ = enable;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SpeakerMute(bool* enabled) const
{
  if (!enabled)
    return -1;

  AutoRecursiveLock lock(lock_);
  *enabled = speakerMute_;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::MicrophoneMuteIsAvailable(bool* available)
{
  if (!available)
    return -1;

  AutoRecursiveLock lock(lock_);
  if (currentRecordingDevice_)
    *available = currentRecordingDevice_->microphoneMuteIsAvailable;
  else
    *available = false;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SetMicrophoneMute(bool enable)
{
  auto event = CustomAudioMixerRequestMuteEvent::toWrapper(false, true, enable);
  onRequestMixerMute(event);

  AutoRecursiveLock lock(lock_);
  microphoneMute_ = enable;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::MicrophoneMute(bool* enabled) const
{
  if (!enabled)
    return -1;

  AutoRecursiveLock lock(lock_);
  *enabled = microphoneMute_;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::StereoPlayoutIsAvailable(bool* available) const
{
  if (!available)
    return -1;

  AutoRecursiveLock lock(lock_);
  if (currentPlayoutDevice_)
    *available = currentPlayoutDevice_->stereoPlayoutIsAvailable;
  else
    *available = false;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SetStereoPlayout(bool enable)
{
  auto event = CustomAudioDeviceRequestStereoEvent::toWrapper(false, true, enable);
  onRequestDeviceStereo(event);

  AutoRecursiveLock lock(lock_);
  stereoPlayout_ = enable;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::StereoPlayout(bool* enabled) const
{
  if (!enabled)
    return -1;

  AutoRecursiveLock lock(lock_);
  *enabled = stereoPlayout_;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::StereoRecordingIsAvailable(bool* available) const
{
  if (!available)
    return -1;

  AutoRecursiveLock lock(lock_);
  if (currentRecordingDevice_)
    *available = currentRecordingDevice_->stereoRecordingIsAvailable;
  else
    *available = false;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::SetStereoRecording(bool enable)
{
  auto event = CustomAudioDeviceRequestStereoEvent::toWrapper(true, false, enable);
  onRequestDeviceStereo(event);

  AutoRecursiveLock lock(lock_);
  stereoRecording_ = enable;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::StereoRecording(bool* enabled) const
{
  if (!enabled)
    return -1;

  AutoRecursiveLock lock(lock_);
  *enabled = stereoRecording_;
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::PlayoutDelay(uint16_t* delayMS) const
{
  if (!delayMS)
    return -1;

  AutoRecursiveLock lock(lock_);
  *delayMS = playoutDelay_;
  return 0;
}

//-----------------------------------------------------------------------------
bool WrapperImplType::BuiltInAECIsAvailable() const
{
  AutoRecursiveLock lock(lock_);
  if (currentRecordingDevice_)
    return currentRecordingDevice_->isBuiltInAecAvailable;
  return false;
}

//-----------------------------------------------------------------------------
bool WrapperImplType::BuiltInAGCIsAvailable() const
{
  AutoRecursiveLock lock(lock_);
  if (currentRecordingDevice_)
    return currentRecordingDevice_->isBuiltInAgcAvailable;
  return false;
}

//-----------------------------------------------------------------------------
bool WrapperImplType::BuiltInNSIsAvailable() const
{
  AutoRecursiveLock lock(lock_);
  if (currentRecordingDevice_)
    return currentRecordingDevice_->isBuiltInNsAvailable;
  return false;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::EnableBuiltInAEC(bool enable)
{
  auto event = CustomAudioMixerRequestSettingsEvent::toWrapper(false, true, enable, Optional<bool>(), Optional<bool>());
  onRequestMixerSettings(event);
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::EnableBuiltInAGC(bool enable)
{
  auto event = CustomAudioMixerRequestSettingsEvent::toWrapper(false, true, Optional<bool>(), enable, Optional<bool>());
  onRequestMixerSettings(event);
  return 0;
}

//-----------------------------------------------------------------------------
int32_t WrapperImplType::EnableBuiltInNS(bool enable)
{
  auto event = CustomAudioMixerRequestSettingsEvent::toWrapper(false, true, Optional<bool>(), Optional<bool>(), enable);
  onRequestMixerSettings(event);
  return 0;
}

//-----------------------------------------------------------------------------
WrapperImplType::NativeTypeScopedPtr WrapperImplType::toNative(WrapperType &wrapper) noexcept
{
  WrapperImplType &self = dynamic_cast<WrapperImplType &>(wrapper);
  auto pThis = self.thisWeak_.lock();
  ZS_ASSERT(pThis);
  if (!pThis)
    return {};
  NativeTypeScopedPtr result(new Proxy(pThis));
  return result;
}

//-----------------------------------------------------------------------------
WrapperImplType::NativeTypeScopedPtr WrapperImplType::toNative(WrapperType *wrapper) noexcept
{
  if (!wrapper)
    return {};
  return toNative(*wrapper);
}

//-----------------------------------------------------------------------------
WrapperImplType::NativeTypeScopedPtr WrapperImplType::toNative(WrapperTypePtr wrapper) noexcept
{
  if (!wrapper)
    return {};
  return toNative(*wrapper);
}

//-----------------------------------------------------------------------------
void WrapperImplType::prepareBuffer() noexcept
{
  if (buffer_)
    return;
  resetBuffer();
}

//-----------------------------------------------------------------------------
void WrapperImplType::resetBuffer() noexcept
{
  buffer_.reset();

  buffer_ = std::make_unique<NativeAudioDeviceBuffer>();
  if (audioCallback_) {
    buffer_->RegisterAudioCallback(audioCallback_);
  }

  buffer_->SetPlayoutSampleRate(playbackHzRate_);
  buffer_->SetRecordingSampleRate(recordingHzRate_);
  buffer_->SetRecordingChannels(playbackChannels_);
  buffer_->SetPlayoutChannels(recordingChannels_);

}
