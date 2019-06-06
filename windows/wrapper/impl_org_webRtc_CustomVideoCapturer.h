
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomVideoCapturer.h"

#include "impl_org_webRtc_pre_include.h"
#include <media/base/adapted_video_track_source.h>
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

          ZS_DECLARE_CLASS_PTR(Proxy);

          class Proxy : public ::rtc::AdaptedVideoTrackSource
          {
          public:
            WrapperImplTypePtr wrapper_;

            Proxy(WrapperImplTypePtr wrapper) : wrapper_(wrapper) {}
            ~Proxy() noexcept { wrapper_->destroyProxyReference(); }

            bool Start(const ::cricket::VideoFormat& capture_format) { return wrapper_->Start(capture_format); }
            void Stop() { return wrapper_->Stop(); }
            bool IsRunning() { return wrapper_->IsRunning(); }
            bool IsScreencast() const { return wrapper_->IsScreencast(); }
            bool GetPreferredFourccs(std::vector<uint32_t>* fourccs) { return wrapper_->GetPreferredFourccs(fourccs); }

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

          void wrapper_onObserverCountChanged(size_t count) noexcept override;

          // ::cricket::VideoCapturer
          bool Start(const ::cricket::VideoFormat& capture_format);
          void Stop();
          bool IsRunning();
          bool IsScreencast() const;
          bool GetPreferredFourccs(std::vector<uint32_t>* fourccs);

          void destroyProxyReference() noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr create() noexcept;

          ZS_NO_DISCARD() static std::unique_ptr<UseAdaptedVideoTrackSource> toNative(WrapperType *wrapperType) noexcept;
          ZS_NO_DISCARD() static std::unique_ptr<UseAdaptedVideoTrackSource> toNative(WrapperTypePtr wrapperType) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

