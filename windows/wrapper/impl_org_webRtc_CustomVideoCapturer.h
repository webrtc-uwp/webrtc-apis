
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomVideoCapturer.h"

#include "impl_org_webRtc_pre_include.h"
#include <media/base/videocapturerfactory.h>
#include <media/base/videocapturer.h>
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

          ZS_DECLARE_TYPEDEF_PTR(::cricket::VideoCapturer, UseVideoCapturer);

          ZS_DECLARE_CLASS_PTR(Proxy);

          class Proxy : public ::cricket::VideoCapturer
          {
          public:
            WrapperImplTypePtr wrapper_;

            Proxy(WrapperImplTypePtr wrapper) : wrapper_(wrapper) {}
            ~Proxy() noexcept { wrapper_->destroyProxyReference(); }

            ::cricket::CaptureState Start(const ::cricket::VideoFormat& capture_format) override { return wrapper_->Start(capture_format); }
            void Stop() override { return wrapper_->Stop(); }
            bool IsRunning() override { return wrapper_->IsRunning(); }
            bool IsScreencast() const override { return wrapper_->IsScreencast(); }
            bool GetPreferredFourccs(std::vector<uint32_t>* fourccs) override { return wrapper_->GetPreferredFourccs(fourccs); }

            void notifyOnFrame(const webrtc::VideoFrame& frame,
              int orig_width,
              int orig_height)
            {
              OnFrame(frame, orig_width, orig_height);
            }
          };

          ::zsLib::IMessageQueuePtr queue_;
          mutable zsLib::RecursiveLock lock_;
          CustomVideoCapturerWeakPtr thisWeak_;
          wrapper::org::webRtc::VideoCaptureState state_ {};
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
            wrapper::org::webRtc::VideoRotation rotation,
            int origWidth,
            int origHeight
          ) noexcept override;

          // properties CustomVideoCapturer
          wrapper::org::webRtc::MediaSourceState get_currentState() noexcept override;
          void set_currentState(wrapper::org::webRtc::MediaSourceState value) noexcept override;

          void wrapper_onObserverCountChanged(size_t count) noexcept override;

          // ::cricket::VideoCapturer
          ::cricket::CaptureState Start(const ::cricket::VideoFormat& capture_format);
          void Stop();
          bool IsRunning();
          bool IsScreencast() const;
          bool GetPreferredFourccs(std::vector<uint32_t>* fourccs);

          void destroyProxyReference() noexcept;

          ZS_NO_DISCARD() static WrapperImplTypePtr create() noexcept;

          ZS_NO_DISCARD() static std::unique_ptr<UseVideoCapturer> toNative(WrapperType *wrapperType) noexcept;
          ZS_NO_DISCARD() static std::unique_ptr<UseVideoCapturer> toNative(WrapperTypePtr wrapperType) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

