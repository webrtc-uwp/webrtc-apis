
#pragma once

#include "types.h"
#include "generated/org_webRtc_VideoTrackSource.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/scoped_refptr.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct VideoTrackSource : public wrapper::org::webRtc::VideoTrackSource
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::VideoTrackSource, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoTrackSource, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::VideoTrackSourceInterface, NativeType);

          typedef rtc::scoped_refptr<NativeType> NativeTypeScopedPtr;
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::WebRtcFactory, UseWebRtcFactory);

          VideoTrackSourceWeakPtr thisWeak_;
          NativeTypeScopedPtr native_;
          UseWebRtcFactoryPtr factory_;

          VideoTrackSource() noexcept;
          virtual ~VideoTrackSource() noexcept;
          void wrapper_dispose() noexcept override;


          // properties MediaTrackSource
          wrapper::org::webRtc::MediaSourceState get_state() noexcept override;
          bool get_remote() noexcept override;

          // properties VideoTrackSource
          bool get_isScreencast() noexcept override;
          Optional< bool > get_needsDenoising() noexcept override;
          Optional< wrapper::org::webRtc::VideoTrackSourceStatsPtr > get_stats() noexcept override;

          UseWebRtcFactoryPtr factory() noexcept { return factory_; }

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeType *native) noexcept;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeTypeScopedPtr native) noexcept;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(WrapperTypePtr wrapper) noexcept;

          ZS_NO_DISCARD() static NativeTypeScopedPtr toNative(WrapperTypePtr wrapper) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

