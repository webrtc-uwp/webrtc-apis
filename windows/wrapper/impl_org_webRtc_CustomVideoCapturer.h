
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

        struct CustomVideoCapturer : public wrapper::org::webRtc::CustomVideoCapturer,
                                     public ::cricket::VideoCapturer
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomVideoCapturer, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturer, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFormat, UseVideoFormat);

          ZS_DECLARE_TYPEDEF_PTR(::cricket::VideoCapturer, UseVideoCapturer);

          class Factory : public ::cricket::VideoDeviceCapturerFactory {
            // ::cricket::VideoDeviceCapturerFactory
            std::unique_ptr<UseVideoCapturer> Create(const ::cricket::Device& device) override;
          };
          
          class Proxy : public ::cricket::VideoCapturer
          {
          public:
            WrapperImplTypePtr wrapper_;

            Proxy(WrapperImplTypePtr wrapper) : wrapper_(wrapper) {}

            ::cricket::CaptureState Start(const ::cricket::VideoFormat& capture_format) override { return wrapper_->Start(capture_format); }
            void Stop() override { return wrapper_->Stop(); }
            bool IsRunning() override { return wrapper_->IsRunning(); }
            bool IsScreencast() const override { return wrapper_->IsScreencast(); }
            bool GetPreferredFourccs(std::vector<uint32_t>* fourccs) override { return wrapper_->GetPreferredFourccs(fourccs); }
          };

          mutable zsLib::RecursiveLock lock_;
          CustomVideoCapturerWeakPtr thisWeak_;
          wrapper::org::webRtc::VideoCaptureState state_ {};
          CustomVideoCapturerParametersPtr params_ {};

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
          wrapper::org::webRtc::VideoCaptureState get_currentState() noexcept override;
          void set_currentState(wrapper::org::webRtc::VideoCaptureState value) noexcept override;

          void wrapper_onObserverCountChanged(size_t count) noexcept override;

          // ::cricket::VideoCapturer
          ::cricket::CaptureState Start(const ::cricket::VideoFormat& capture_format) override;
          void Stop() override;
          bool IsRunning() override;
          bool IsScreencast() const override;
          bool GetPreferredFourccs(std::vector<uint32_t>* fourccs) override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

