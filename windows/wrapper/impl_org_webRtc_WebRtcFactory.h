
#pragma once

#include "types.h"
#include "generated/org_webRtc_WebRtcFactory.h"

#include "impl_org_webRtc_pre_include.h"
#include "rtc_base/scoped_ref_ptr.h"
#include "media/base/videocapturerfactory.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct WebRtcFactory : public wrapper::org::webRtc::WebRtcFactory
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::WebRtcFactory, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::WebRtcFactory, WrapperImplType);

          ZS_DECLARE_TYPEDEF_PTR(::cricket::VideoDeviceCapturerFactory, UseVideoDeviceCaptureFacrtory);

          typedef rtc::scoped_refptr<::webrtc::PeerConnectionFactoryInterface> PeerConnectionFactoryInterfaceScopedPtr;
          typedef rtc::scoped_refptr<::webrtc::PeerConnectionFactory> PeerConnectionFactoryScopedPtr;

          WebRtcFactoryWeakPtr thisWeak_;

          zsLib::RecursiveLock lock_;
          PeerConnectionFactoryInterfaceScopedPtr peerConnectionFactory_;
          UseVideoDeviceCaptureFacrtoryPtr videoDeviceCaptureFactory_;

          std::unique_ptr<rtc::Thread> networkThread;
          std::unique_ptr<rtc::Thread> workerThread;
          std::unique_ptr<rtc::Thread> signalingThread;

          WebRtcFactory() noexcept;
          virtual ~WebRtcFactory() noexcept;
          void wrapper_dispose() noexcept override;


          // methods WebRtcFactory
          void wrapper_init_org_webRtc_WebRtcFactory(wrapper::org::webRtc::WebRtcFactoryConfigurationPtr configuration) noexcept override;

          void wrapper_onObserverCountChanged(size_t count) noexcept override;

          PeerConnectionFactoryInterfaceScopedPtr peerConnectionFactory() noexcept;
          PeerConnectionFactoryScopedPtr realPeerConnectionFactory() noexcept;
          UseVideoDeviceCaptureFacrtoryPtr videoDeviceCaptureFactory() noexcept;

          static WrapperImplTypePtr toWrapper(WrapperTypePtr wrapper) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

