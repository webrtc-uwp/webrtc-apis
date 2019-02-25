
#pragma once

#include "types.h"

#include "generated/org_webRtc_WebRtcLib.h"

#include "impl_org_webRtc_pre_include.h"
#include "rtc_base/scoped_ref_ptr.h"
#include "media/base/videocapturerfactory.h"
#include "impl_org_webRtc_post_include.h"

#include <zsLib/Singleton.h>

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct WebRtcLib : public wrapper::org::webRtc::WebRtcLib,
                           public zsLib::ISingletonManagerDelegate
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::WebRtcLib, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::WebRtcLib, WrapperImplType);

          WebRtcLib() noexcept;
          WebRtcLib(const WebRtcLib &) noexcept = delete;
          virtual ~WebRtcLib() noexcept;

          WebRtcLibWeakPtr thisWeak_;
          std::atomic_flag setupCalledOnce_{};
          std::atomic_bool setupComplete_ {};
          std::atomic_bool alreadyCleaned_{};
          std::atomic_flag didSetupZsLib_ {};
          std::atomic_flag isTracingStartOrStopping_ {};
          std::atomic_bool isTracing_ {};
          zsLib::Lock lock_;
          ::zsLib::Milliseconds ntpServerTime_;
          ::zsLib::IMessageQueuePtr audioCaptureFrameProcessingQueue_;
          ::zsLib::IMessageQueuePtr audioRenderFrameProcessingQueue_;
          ::zsLib::IMessageQueuePtr videoFrameProcessingQueue_;

          // constructor
          static WrapperImplTypePtr create() noexcept;

          // overrides of static base class
          virtual void actual_setup() noexcept;
          virtual void actual_setup(wrapper::org::webRtc::WebRtcLibConfigurationPtr configuration) noexcept;
          virtual void actual_startMediaTracing() noexcept;
          virtual void actual_stopMediaTracing() noexcept;
          virtual bool actual_isMediaTracing() noexcept;
          virtual bool actual_startMediaTrace(String filename) noexcept;
          virtual bool actual_startMediaTrace(
                                             String host,
                                             int port
                                             ) noexcept;

          virtual ::zsLib::Milliseconds actual_get_ntpServerTime() noexcept;
          virtual void actual_set_ntpServerTime(::zsLib::Milliseconds value) noexcept;

          // addition methods needed
          virtual bool actual_checkSetup(bool assert = true) noexcept;
          virtual zsLib::IMessageQueuePtr actual_delegateQueue() noexcept;
          virtual zsLib::IMessageQueuePtr actual_audioCaptureFrameProcessingQueue() noexcept;
          virtual zsLib::IMessageQueuePtr actual_audioRenderFrameProcessingQueue() noexcept;
          virtual zsLib::IMessageQueuePtr actual_videoFrameProcessingQueue() noexcept;

          //-------------------------------------------------------------------
          //
          // zsLib::ISingletonManagerDelegate
          // 
          void notifySingletonCleanup() noexcept override;

          // public methods
          static WebRtcLibPtr singleton() noexcept;

          // addition methods needed
          static bool checkSetup(bool assert = true) noexcept;
          static zsLib::IMessageQueuePtr delegateQueue() noexcept;
          static zsLib::IMessageQueuePtr audioCaptureFrameProcessingQueue() noexcept;
          static zsLib::IMessageQueuePtr audioRenderFrameProcessingQueue() noexcept;
          static zsLib::IMessageQueuePtr videoFrameProcessingQueue() noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

