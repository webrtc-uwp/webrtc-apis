
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomVideoCapturerFactory.h"

#include "impl_org_webRtc_pre_include.h"
#include "impl_org_webRtc_post_include.h"

#include "impl_webrtc_IVideoCapturer.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomVideoCapturerFactory : public wrapper::org::webRtc::CustomVideoCapturerFactory,
                                            public ::webrtc::VideoDeviceCapturerFactory
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomVideoCapturerFactory, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturerFactory, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::rtc::AdaptedVideoTrackSource, UseAdaptedVideoTrackSource);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::VideoDeviceCapturerFactory, UseVideoDeviceCapturerFactory);

          CustomVideoCapturerFactoryWeakPtr thisWeak_;

          CustomVideoCapturerFactory() noexcept;
          virtual ~CustomVideoCapturerFactory() noexcept;
          void wrapper_dispose() noexcept override;


          void wrapper_onObserverCountChanged(size_t count) noexcept override;

          std::unique_ptr<UseAdaptedVideoTrackSource> Create(const ::webrtc::Device& device) override;

          ZS_NO_DISCARD() static WrapperImplTypePtr create() noexcept;

          ZS_NO_DISCARD() static UseVideoDeviceCapturerFactoryPtr toNative(WrapperTypePtr wrapper) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

