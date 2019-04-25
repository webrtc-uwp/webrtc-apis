
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioDevice.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioDevice : public wrapper::org::webRtc::CustomAudioDevice
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioDevice, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioDevice, WrapperImplType);
          CustomAudioDeviceWeakPtr thisWeak_;

          CustomAudioDevice() noexcept;
          virtual ~CustomAudioDevice() noexcept;
          void wrapper_dispose() noexcept override;


          // methods CustomAudioDevice
          void updateDevices(wrapper::org::webRtc::CustomAudioDeviceParametersPtr params) noexcept override;
          void updateCurrentPlayoutDelay(int16_t delayMs) noexcept override;
          void setRecordedBuffer(wrapper::org::webRtc::AudioBufferPtr buffer) noexcept override;
          bool deliverRecordedData() noexcept override;
          bool notifyNewMicrophoneLevel() noexcept override;
          bool setTypingStatus(bool isTyping) noexcept override;
          wrapper::org::webRtc::AudioBufferPtr requestPlayoutData() noexcept override;
          void updateVqeData(
            int playDelayMs,
            int recordDelayMs
            ) noexcept override;
          void notifyFrame(
            wrapper::org::webRtc::AudioBufferPtr frame,
            int origWidth,
            int origHeight
            ) noexcept override;

          // properties CustomAudioDevice
          wrapper::org::webRtc::CustomAudioState get_playoutCurrentState() noexcept override;
          void set_playoutCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept override;
          wrapper::org::webRtc::CustomAudioState get_recurdingCurrentState() noexcept override;
          void set_recurdingCurrentState(wrapper::org::webRtc::CustomAudioState value) noexcept override;
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
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

