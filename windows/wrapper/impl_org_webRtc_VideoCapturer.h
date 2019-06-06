
#pragma once

#include "types.h"
#include "generated/org_webRtc_VideoCapturer.h"

#include "impl_webrtc_IVideoCapturer.h"

#include "impl_org_webRtc_pre_include.h"
//#include "rtc_base/scoped_ref_ptr.h"
#include "media/base/adapted_video_track_source.h"
#include "impl_org_webRtc_post_include.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct VideoCapturer : public wrapper::org::webRtc::VideoCapturer
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::VideoCapturer, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoCapturer, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::rtc::AdaptedVideoTrackSource, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::MediaSample, UseMediaSample);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::VideoFrameBufferEvent, UseVideoFrameBufferEvent);

          typedef rtc::scoped_refptr<NativeType> NativeTypeScopedRefPtr;

#ifdef CPPWINRT_VERSION
          ZS_DECLARE_TYPEDEF_PTR(webrtc::IVideoCapturer, UseVideoCapturer);
#endif // CPPWINRT_VERSION

          ZS_DECLARE_STRUCT_PTR(WebrtcVideoObserver);

          struct WebrtcVideoObserver : public zsLib::MessageQueueAssociator
#ifdef CPPWINRT_VERSION
                                     , public ::webrtc::IVideoCapturerDelegate
#endif // CPPWINRT_VERSION
          {
            WebrtcVideoObserver(
                                WrapperImplTypePtr wrapper,
                                IMessageQueuePtr queue
                                ) noexcept : zsLib::MessageQueueAssociator(queue), outer_(wrapper) {}

#ifdef CPPWINRT_VERSION
            void onVideoFrameReceived(UseVideoFrameBufferEventPtr event) override
            {
              auto outer = outer_.lock();
              if (!outer) return;
              outer->onWebrtcObserverVideoFrameReceived(event);
            }
#endif // CPPWINRT_VERSION

          private:
            WrapperImplTypeWeakPtr outer_;
          };

          WebrtcVideoObserverPtr videoObserver_;

          std::atomic_bool stopCalled_{};
          NativeTypeScopedRefPtr native_;
          VideoCapturerWeakPtr thisWeak_;

          zsLib::Lock lock_;
          size_t totalObservers_{};
          webrtc::IVideoCapturerSubscriptionPtr subscription_;

          VideoCapturer() noexcept;
          virtual ~VideoCapturer() noexcept;
          void wrapper_dispose() noexcept override;


          // methods VideoCapturer
          // properties VideoCapturer
          bool get_enableCameraList() noexcept override;
          void set_enableCameraList(bool value) noexcept override;
          bool get_enableVideoAdapter() noexcept override;
          void set_enableVideoAdapter(bool value) noexcept override;
          bool get_isRunning() noexcept override;
          bool get_applyRotation() noexcept override;
          bool get_isScreencast() noexcept override;
          Optional< bool > get_needsDenoising() noexcept override;
          wrapper::org::webRtc::VideoCapturerInputSizePtr get_inputSize() noexcept override;
          wrapper::org::webRtc::MediaSourceState get_state() noexcept override;

          virtual void wrapper_onObserverCountChanged(size_t count) noexcept override;

          void setupObserver() noexcept;
          void teardownObserver() noexcept;

          // WebrtcObserver methods
          void onWebrtcObserverVideoFrameReceived(UseVideoFrameBufferEventPtr event) noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeType *native) noexcept;
          ZS_NO_DISCARD() static NativeTypeScopedRefPtr toNative(WrapperTypePtr wrapper) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

