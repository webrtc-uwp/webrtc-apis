
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomVideoCapturer.h"

#include "impl_org_webRtc_pre_include.h"
#include <media/base/adapted_video_track_source.h>
#include <rtc_base/ref_counted_object.h>
#include "impl_org_webRtc_post_include.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomVideoCapturer : public wrapper::org::webRtc::CustomVideoCapturer
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomVideoCapturer, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturer, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFormat, UseVideoFormat);

          ZS_DECLARE_TYPEDEF_PTR(::rtc::AdaptedVideoTrackSource, UseAdaptedVideoTrackSource);

          typedef rtc::scoped_refptr<UseAdaptedVideoTrackSource> UseAdaptedVideoTrackSourceScopedPtr;

          ZS_DECLARE_CLASS_PTR(Proxy);

          class Proxy : public ::rtc::RefCountedObject<::rtc::AdaptedVideoTrackSource>
          {
          public:
            WrapperImplTypePtr wrapper_;

            Proxy(WrapperImplTypePtr wrapper) : wrapper_(wrapper) {}
            ~Proxy() noexcept { wrapper_->destroyProxyReference(); }

            // webrtc::MediaSourceInterface
            SourceState state() const override { return wrapper_->state(); }
            bool remote() const override { return wrapper_->remote(); }

            // webrtc::VideoTrackSourceInterface
            bool is_screencast() const { return wrapper_->is_screencast(); }
            absl::optional<bool> needs_denoising() const { return wrapper_->needs_denoising(); }
            bool GetStats(Stats* stats) override { return wrapper_->GetStats(stats); }

            void notifyOnFrame(const webrtc::VideoFrame& frame)
            {
              OnFrame(frame);
            }
          };

          ::zsLib::IMessageQueuePtr queue_;
          mutable zsLib::RecursiveLock lock_;
          CustomVideoCapturerWeakPtr thisWeak_;
          wrapper::org::webRtc::MediaSourceState state_ {};
          CustomVideoCapturerParametersPtr params_ {};

          mutable zsLib::RecursiveLock ProxyReferencelock_;
          Proxy *proxyReference_ {};

          CustomVideoCapturer() noexcept;
          virtual ~CustomVideoCapturer() noexcept;
          void wrapper_dispose() noexcept override;


          // methods CustomVideoCapturer
          void notifyFrame(
            wrapper::org::webRtc::VideoFrameBufferPtr frame,
            int64_t timestamp,
            wrapper::org::webRtc::VideoRotation rotation
            ) noexcept override;

          // properties CustomVideoCapturer
          wrapper::org::webRtc::MediaSourceState get_currentState() noexcept override;
          void set_currentState(wrapper::org::webRtc::MediaSourceState value) noexcept override;

          // webrtc::MediaSourceInterface
          webrtc::MediaSourceInterface::SourceState state() const noexcept;
          bool remote() const noexcept;

          // webrtc::VideoTrackSourceInterface
          bool is_screencast() const noexcept;
          absl::optional<bool> needs_denoising() const noexcept;
          bool GetStats(webrtc::VideoTrackSourceInterface::Stats* stats) noexcept;

          void destroyProxyReference() noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr create() noexcept;

          ZS_NO_DISCARD() static UseAdaptedVideoTrackSourceScopedPtr toNative(WrapperType *wrapperType) noexcept;
          ZS_NO_DISCARD() static UseAdaptedVideoTrackSourceScopedPtr toNative(WrapperTypePtr wrapperType) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

