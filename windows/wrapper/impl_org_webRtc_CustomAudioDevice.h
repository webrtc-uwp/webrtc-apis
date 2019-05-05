
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioDevice.h"

#include "impl_org_webRtc_pre_include.h"
#include "modules/audio_device/include/audio_device.h"
#include "rtc_base/refcountedobject.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioDevice : public wrapper::org::webRtc::CustomAudioDevice,
                                   ::rtc::RefCountedObject<::webrtc::AudioDeviceModule>
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioDevice, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioDevice, WrapperImplType);

          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioPlayoutDeviceInfo, UsePlayoutDeviceInfo);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioRecordingDeviceInfo, UseRecordingDeviceInfo);

          ZS_DECLARE_TYPEDEF_PTR(::webrtc::AudioDeviceModule, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::AudioDeviceBuffer, NativeAudioDeviceBuffer);

          typedef rtc::scoped_refptr<NativeType> NativeTypeScopedPtr;

          class Proxy : public ::rtc::RefCountedObject<::webrtc::AudioDeviceModule>
          {
          protected:
            WrapperImplTypePtr this_;

          public:
            Proxy(WrapperImplTypePtr value) : this_(value) {}
            int32_t ActiveAudioLayer(AudioLayer* audioLayer) const override { return this_->ActiveAudioLayer(audioLayer); }
            int32_t RegisterAudioCallback(::webrtc::AudioTransport* audioCallback) override { return this_->RegisterAudioCallback(audioCallback); }
            int32_t Init() override { return this_->Init(); }
            int32_t Terminate() override { return this_->Terminate(); }
            bool Initialized() const override { return this_->Initialized(); }
            int16_t PlayoutDevices() override { return this_->PlayoutDevices(); }
            int16_t RecordingDevices() override { return this_->RecordingDevices(); }
            int32_t PlayoutDeviceName(uint16_t index,
              char name[::webrtc::kAdmMaxDeviceNameSize],
              char guid[::webrtc::kAdmMaxGuidSize]) override { return this_->PlayoutDeviceName(index, name, guid); }
            int32_t RecordingDeviceName(uint16_t index,
              char name[::webrtc::kAdmMaxDeviceNameSize],
              char guid[::webrtc::kAdmMaxGuidSize]) override {return this_->RecordingDeviceName(index, name, guid); }
            int32_t SetPlayoutDevice(uint16_t index) override { return this_->SetPlayoutDevice(index); }
            int32_t SetPlayoutDevice(WindowsDeviceType device) override { return this_->SetPlayoutDevice(device); }
            int32_t SetRecordingDevice(uint16_t index) override { return this_->SetRecordingDevice(index); }
            int32_t SetRecordingDevice(WindowsDeviceType device) override { return this_->SetRecordingDevice(device); }
            int32_t PlayoutIsAvailable(bool* available) override { return this_->PlayoutIsAvailable(available); }
            int32_t InitPlayout() override { return this_->InitPlayout(); }
            bool PlayoutIsInitialized() const override { return this_->PlayoutIsInitialized(); }
            int32_t RecordingIsAvailable(bool* available) override { return this_->RecordingIsAvailable(available); }
            int32_t InitRecording() override { return this_->InitRecording(); }
            bool RecordingIsInitialized() const override { return this_->RecordingIsInitialized(); }
            int32_t StartPlayout() override { return this_->StartPlayout(); }
            int32_t StopPlayout() override { return this_->StopPlayout(); }
            bool Playing() const override { return this_->Playing(); }
            int32_t StartRecording() override { return this_->StartRecording(); }
            int32_t StopRecording() override { return this_->StopRecording(); }
            bool Recording() const override { return this_->Recording(); }
            int32_t InitSpeaker() override { return this_->InitSpeaker(); }
            bool SpeakerIsInitialized() const override { return this_->SpeakerIsInitialized(); }
            int32_t InitMicrophone() override { return this_->InitMicrophone(); }
            bool MicrophoneIsInitialized() const override { return this_->MicrophoneIsInitialized(); }
            int32_t SpeakerVolumeIsAvailable(bool* available) override { return this_->SpeakerVolumeIsAvailable(available); }
            int32_t SetSpeakerVolume(uint32_t volume) override { return this_->SetSpeakerVolume(volume); }
            int32_t SpeakerVolume(uint32_t* volume) const override { return this_->SpeakerVolume(volume); }
            int32_t MaxSpeakerVolume(uint32_t* maxVolume) const override { return this_->MaxSpeakerVolume(maxVolume); }
            int32_t MinSpeakerVolume(uint32_t* minVolume) const override { return this_->MinSpeakerVolume(minVolume); }
            int32_t MicrophoneVolumeIsAvailable(bool* available) override { return this_->MicrophoneVolumeIsAvailable(available); }
            int32_t SetMicrophoneVolume(uint32_t volume) override { return this_->SetMicrophoneVolume(volume); }
            int32_t MicrophoneVolume(uint32_t* volume) const override { return this_->MicrophoneVolume(volume); }
            int32_t MaxMicrophoneVolume(uint32_t* maxVolume) const override { return this_->MaxMicrophoneVolume(maxVolume); }
            int32_t MinMicrophoneVolume(uint32_t* minVolume) const override { return this_->MinMicrophoneVolume(minVolume); }
            int32_t SpeakerMuteIsAvailable(bool* available) override { return this_->SpeakerMuteIsAvailable(available); }
            int32_t SetSpeakerMute(bool enable) override { return this_->SetSpeakerMute(enable); }
            int32_t SpeakerMute(bool* enabled) const override { return this_->SpeakerMute(enabled); }
            int32_t MicrophoneMuteIsAvailable(bool* available) override { return this_->MicrophoneMuteIsAvailable(available); }
            int32_t SetMicrophoneMute(bool enable) override { return this_->SetMicrophoneMute(enable); }
            int32_t MicrophoneMute(bool* enabled) const override { return this_->MicrophoneMute(enabled); }
            int32_t StereoPlayoutIsAvailable(bool* available) const override { return this_->StereoPlayoutIsAvailable(available); }
            int32_t SetStereoPlayout(bool enable) override { return this_->SetStereoPlayout(enable); }
            int32_t StereoPlayout(bool* enabled) const override { return this_->StereoPlayout(enabled); }
            int32_t StereoRecordingIsAvailable(bool* available) const override { return this_->StereoRecordingIsAvailable(available); }
            int32_t SetStereoRecording(bool enable) override { return this_->SetStereoRecording(enable); }
            int32_t StereoRecording(bool* enabled) const override { return this_->StereoRecording(enabled); }
            int32_t PlayoutDelay(uint16_t* delayMS) const override { return this_->PlayoutDelay(delayMS); }
            bool BuiltInAECIsAvailable() const override { return this_->BuiltInAECIsAvailable(); }
            bool BuiltInAGCIsAvailable() const override { return this_->BuiltInAGCIsAvailable(); }
            bool BuiltInNSIsAvailable() const override { return this_->BuiltInNSIsAvailable(); }
            int32_t EnableBuiltInAEC(bool enable) override { return this_->EnableBuiltInAEC(enable); }
            int32_t EnableBuiltInAGC(bool enable) override { return this_->EnableBuiltInAGC(enable); }
            int32_t EnableBuiltInNS(bool enable) override { return this_->EnableBuiltInNS(enable); }
          };

          CustomAudioDeviceWeakPtr thisWeak_;
          ::zsLib::IMessageQueuePtr queue_;

          mutable zsLib::RecursiveLock lock_;
          list< wrapper::org::webRtc::CustomAudioPlayoutDeviceInfoPtr > playoutDevices_;
          list< wrapper::org::webRtc::CustomAudioRecordingDeviceInfoPtr > recordingDevices_;

          NativeAudioDeviceBufferPtr buffer_;
          ::webrtc::AudioTransport* audioCallback_ {};

          wrapper::org::webRtc::CustomAudioState playoutState_ {};
          wrapper::org::webRtc::CustomAudioState recordingState_{};
          wrapper::org::webRtc::CustomAudioState speakerState_ {};
          wrapper::org::webRtc::CustomAudioState microphoneState_ {};

          uint32_t playbackHzRate_ {};
          uint32_t recordingHzRate_ {};
          int32_t playbackChannels_ {};
          int32_t recordingChannels_ {};
          int playDelayMs_ {};
          int recordDelayMs_ {};

          wrapper::org::webRtc::CustomAudioPlayoutDeviceInfoPtr currentPlayoutDevice_;
          wrapper::org::webRtc::CustomAudioRecordingDeviceInfoPtr currentRecordingDevice_;

          uint32_t speakerVolume_ {};
          uint32_t microphoneVolume_ {};
          bool speakerMute_ {};
          bool microphoneMute_ {};
          bool stereoPlayout_ {};
          bool stereoRecording_ {};
          uint16_t playoutDelay_ {};

          CustomAudioDevice() noexcept;
          virtual ~CustomAudioDevice() noexcept;
          void wrapper_dispose() noexcept override;

          // methods CustomAudioDevice
          void updateDevices(wrapper::org::webRtc::CustomAudioDeviceParametersPtr params) noexcept override;
          void updateCurrentPlayoutDelay(uint16_t delayMs) noexcept override;
          void setRecordedBuffer(wrapper::org::webRtc::AudioDataPtr buffer) noexcept override;
          bool deliverRecordedData() noexcept override;
          bool notifyNewMicrophoneLevel() noexcept override;
          bool setTypingStatus(bool isTyping) noexcept override;
          wrapper::org::webRtc::AudioDataPtr requestPlayoutData(uint64_t samplesPerChannel) noexcept override;
          void updateVqeData(
            int playDelayMs,
            int recordDelayMs
            ) noexcept override;

          // properties CustomAudioDevice
          wrapper::org::webRtc::CustomAudioState get_playoutCurrentState() noexcept override;
          void set_playoutCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept override;
          wrapper::org::webRtc::CustomAudioState get_recordingCurrentState() noexcept override;
          void set_recordingCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept override;
          wrapper::org::webRtc::CustomAudioState get_speakerCurrentState() noexcept override;
          void set_speakerCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept override;
          wrapper::org::webRtc::CustomAudioState get_microphoneCurrentState() noexcept override;
          void set_microphoneCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept override;
          uint32_t get_playbackSampleRateFsHz() noexcept override;
          void set_playbackSampleRateFsHz(uint32_t value) noexcept override;
          uint32_t get_recordingSampleRateFsHz() noexcept override;
          void set_recordingSampleRateFsHz(uint32_t value) noexcept override;
          int32_t get_playoutChannels() noexcept override;
          void set_playoutChannels(int32_t value) noexcept override;
          int32_t get_recordingChannels() noexcept override;
          void set_recordingChannels(int32_t value) noexcept override;

          void wrapper_onObserverCountChanged(size_t count) noexcept override;

          int32_t ActiveAudioLayer(AudioLayer* audioLayer) const override;

          // Full-duplex transportation of PCM audio
          int32_t RegisterAudioCallback(::webrtc::AudioTransport* audioCallback) override;

          // Main initialization and termination
          int32_t Init() override;
          int32_t Terminate() override;
          bool Initialized() const override;

          // Device enumeration
          int16_t PlayoutDevices() override;
          int16_t RecordingDevices() override;
          int32_t PlayoutDeviceName(uint16_t index,
            char name[::webrtc::kAdmMaxDeviceNameSize],
            char guid[::webrtc::kAdmMaxGuidSize]) override;
          int32_t RecordingDeviceName(uint16_t index,
            char name[::webrtc::kAdmMaxDeviceNameSize],
            char guid[::webrtc::kAdmMaxGuidSize]) override;

          // Device selection
          int32_t SetPlayoutDevice(uint16_t index) override;
          int32_t SetPlayoutDevice(WindowsDeviceType device) override;
          int32_t SetRecordingDevice(uint16_t index) override;
          int32_t SetRecordingDevice(WindowsDeviceType device) override;

          // Audio transport initialization
          int32_t PlayoutIsAvailable(bool* available) override;
          int32_t InitPlayout() override;
          bool PlayoutIsInitialized() const override;
          int32_t RecordingIsAvailable(bool* available) override;
          int32_t InitRecording() override;
          bool RecordingIsInitialized() const override;

          // Audio transport control
          int32_t StartPlayout() override;
          int32_t StopPlayout() override;
          bool Playing() const override;
          int32_t StartRecording() override;
          int32_t StopRecording() override;
          bool Recording() const override;

          // Audio mixer initialization
          int32_t InitSpeaker() override;
          bool SpeakerIsInitialized() const override;
          int32_t InitMicrophone() override;
          bool MicrophoneIsInitialized() const override;

          // Speaker volume controls
          int32_t SpeakerVolumeIsAvailable(bool* available) override;
          int32_t SetSpeakerVolume(uint32_t volume) override;
          int32_t SpeakerVolume(uint32_t* volume) const override;
          int32_t MaxSpeakerVolume(uint32_t* maxVolume) const override;
          int32_t MinSpeakerVolume(uint32_t* minVolume) const override;

          // Microphone volume controls
          int32_t MicrophoneVolumeIsAvailable(bool* available) override;
          int32_t SetMicrophoneVolume(uint32_t volume) override;
          int32_t MicrophoneVolume(uint32_t* volume) const override;
          int32_t MaxMicrophoneVolume(uint32_t* maxVolume) const override;
          int32_t MinMicrophoneVolume(uint32_t* minVolume) const override;

          // Speaker mute control
          int32_t SpeakerMuteIsAvailable(bool* available) override;
          int32_t SetSpeakerMute(bool enable) override;
          int32_t SpeakerMute(bool* enabled) const override;

          // Microphone mute control
          int32_t MicrophoneMuteIsAvailable(bool* available) override;
          int32_t SetMicrophoneMute(bool enable) override;
          int32_t MicrophoneMute(bool* enabled) const override;

          // Stereo support
          int32_t StereoPlayoutIsAvailable(bool* available) const override;
          int32_t SetStereoPlayout(bool enable) override;
          int32_t StereoPlayout(bool* enabled) const override;
          int32_t StereoRecordingIsAvailable(bool* available) const override;
          int32_t SetStereoRecording(bool enable) override;
          int32_t StereoRecording(bool* enabled) const override;

          // Playout delay
          int32_t PlayoutDelay(uint16_t* delayMS) const override;

          // Only supported on Android.
          bool BuiltInAECIsAvailable() const override;
          bool BuiltInAGCIsAvailable() const override;
          bool BuiltInNSIsAvailable() const override;

          // Enables the built-in audio effects. Only supported on Android.
          int32_t EnableBuiltInAEC(bool enable) override;
          int32_t EnableBuiltInAGC(bool enable) override;
          int32_t EnableBuiltInNS(bool enable) override;

          ZS_NO_DISCARD() static NativeTypeScopedPtr toNative(WrapperType &wrapper) noexcept;
          ZS_NO_DISCARD() static NativeTypeScopedPtr toNative(WrapperType *wrapper) noexcept;
          ZS_NO_DISCARD() static NativeTypeScopedPtr toNative(WrapperTypePtr wrapper) noexcept;

        protected:
          void prepareBuffer() noexcept;
          void resetBuffer() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

