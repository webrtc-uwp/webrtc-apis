
#pragma once

#include "types.h"
#include "generated/org_webRtc_WebRtcFactory.h"

#include "impl_org_webRtc_pre_include.h"
#include "rtc_base/scoped_ref_ptr.h"
#include "media/base/videocapturerfactory.h"
#include "modules/audio_processing/include/audio_processing.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct WebRtcFactory : public wrapper::org::webRtc::WebRtcFactory
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::WebRtcFactory, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::WebRtcFactory, WrapperImplType);

          ZS_DECLARE_TYPEDEF_PTR(::webrtc::AudioBuffer, NativeAudioBufferType);
          ZS_DECLARE_TYPEDEF_PTR(::cricket::VideoDeviceCapturerFactory, UseVideoDeviceCaptureFacrtory);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioBufferEvent, UseAudioBufferEvent);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioProcessingInitializeEvent, UseAudioInitEvent);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioProcessingRuntimeSettingEvent, UseAudioRuntimeEvent);

          typedef rtc::scoped_refptr<::webrtc::PeerConnectionFactoryInterface> PeerConnectionFactoryInterfaceScopedPtr;
          typedef rtc::scoped_refptr<::webrtc::PeerConnectionFactory> PeerConnectionFactoryScopedPtr;


          ZS_DECLARE_STRUCT_PTR(WebrtcObserver);

          struct WebrtcObserver : public ::webrtc::CustomProcessing
          {
            WebrtcObserver(
              WrapperImplTypePtr wrapper,
              IMessageQueuePtr queue,
              std::function<void(UseAudioBufferEventPtr)> bufferEvent,
              std::function<void(UseAudioInitEventPtr)> initEvent,
              std::function<void(UseAudioRuntimeEventPtr)> runtimeEvent
            ) noexcept;

            void Initialize(int sample_rate_hz, int num_channels) final;
            void Process(NativeAudioBufferType* audio) final;
            std::string ToString() const final;
            void SetRuntimeSetting(::webrtc::AudioProcessing::RuntimeSetting setting) final;

            void enabled(bool enabled) noexcept { enabled_ = enabled; }

          private:
            std::atomic_bool enabled_;
            WrapperImplTypeWeakPtr outer_;
            IMessageQueuePtr queue_;
            std::function<void(UseAudioBufferEventPtr)> bufferEvent_;
            std::function<void(UseAudioInitEventPtr)> initEvent_;
            std::function<void(UseAudioRuntimeEventPtr)> runtimeEvent_;
          };


          WebRtcFactoryWeakPtr thisWeak_;

          zsLib::RecursiveLock lock_;
          PeerConnectionFactoryInterfaceScopedPtr peerConnectionFactory_;
          UseVideoDeviceCaptureFacrtoryPtr videoDeviceCaptureFactory_;

          std::unique_ptr<rtc::Thread> networkThread;
          std::unique_ptr<rtc::Thread> workerThread;
          std::unique_ptr<rtc::Thread> signalingThread;

          WebrtcObserverPtr AudioPostCapture_;
          WebrtcObserverPtr AudioPreRender_;

          WebRtcFactory() noexcept;
          virtual ~WebRtcFactory() noexcept;
          void wrapper_dispose() noexcept override;


          // methods WebRtcFactory
          void wrapper_init_org_webRtc_WebRtcFactory(wrapper::org::webRtc::WebRtcFactoryConfigurationPtr configuration) noexcept override;

          void wrapper_onObserverCountChanged(size_t count) noexcept override;

          PeerConnectionFactoryInterfaceScopedPtr peerConnectionFactory() noexcept;
          PeerConnectionFactoryScopedPtr realPeerConnectionFactory() noexcept;
          UseVideoDeviceCaptureFacrtoryPtr videoDeviceCaptureFactory() noexcept;

          void onAudioPostCapture_Init(UseAudioInitEventPtr event);
          void onAudioPostCapture_SetRuntimeSetting(UseAudioRuntimeEventPtr event);
          void onAudioPostCapture_Process(UseAudioBufferEventPtr event);

          void onAudioPreRender_Init(UseAudioInitEventPtr event);
          void onAudioPreRender_SetRuntimeSetting(UseAudioRuntimeEventPtr event);
          void onAudioPreRender_Process(UseAudioBufferEventPtr event);

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(WrapperTypePtr wrapper) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

