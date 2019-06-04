
#define ZS_DECLARE_TEMPLATE_GENERATE_IMPLEMENTATION

#ifdef __has_include
#if __has_include(<winrt/Windows.Media.Core.h>)
#include <winrt/Windows.Media.Core.h>
#endif //__has_include(<winrt/Windows.Media.Core.h>)
#endif //__has_include

#include "impl_org_webRtc_WebRtcLib.h"
#include "impl_org_webRtc_WebRtcLibConfiguration.h"
#include "impl_org_webRtc_EventQueue.h"
#include "impl_org_webRtc_helpers.h"

#include "impl_org_webRtc.h"
#include "impl_webrtc_IMediaStreamSource.h"
#include "impl_webrtc_IVideoCapturer.h"
#include "impl_webrtc_IVideoCaptureMediaSink.h"
#include "impl_webrtc_IAudioDeviceWasapi.h"

#include <zsLib/IMessageQueueThread.h>

#include "impl_org_webRtc_pre_include.h"
#include "rtc_base/event_tracer.h"
#include "rtc_base/win32_socket_init.h"
#include "rtc_base/ssl_adapter.h"
#include "impl_org_webRtc_post_include.h"

#include <zsLib/eventing/IHelper.h>


using ::zsLib::String;
using ::zsLib::Optional;
using ::zsLib::Any;
using ::zsLib::AnyPtr;
using ::zsLib::AnyHolder;
using ::zsLib::Promise;
using ::zsLib::PromisePtr;
using ::zsLib::PromiseWithHolder;
using ::zsLib::PromiseWithHolderPtr;
using ::zsLib::eventing::SecureByteBlock;
using ::zsLib::eventing::SecureByteBlockPtr;
using ::std::shared_ptr;
using ::std::weak_ptr;
using ::std::make_shared;
using ::std::list;
using ::std::set;
using ::std::map;

//namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

// borrow definitions from class
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::WebRtcLib::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::EventQueue, UseEventQueue);

ZS_DECLARE_TYPEDEF_PTR(zsLib::eventing::IHelper, UseHelper);

#ifdef CPPWINRT_VERSION
ZS_DECLARE_PROXY_IMPLEMENT(webrtc::IMediaStreamSourceDelegate)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_IMPLEMENT(webrtc::IMediaStreamSourceDelegate, webrtc::IMediaStreamSourceSubscription)
ZS_DECLARE_PROXY_IMPLEMENT(webrtc::IVideoCapturerDelegate)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_IMPLEMENT(webrtc::IVideoCapturerDelegate, webrtc::IVideoCapturerSubscription)
ZS_DECLARE_PROXY_IMPLEMENT(webrtc::IVideoCaptureMediaSinkDelegate)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_IMPLEMENT(webrtc::IVideoCaptureMediaSinkDelegate, webrtc::IVideoCaptureMediaSinkSubscription)
ZS_DECLARE_PROXY_IMPLEMENT(webrtc::IAudioDeviceWasapiDelegate)
ZS_DECLARE_PROXY_SUBSCRIPTIONS_IMPLEMENT(webrtc::IAudioDeviceWasapiDelegate, webrtc::IAudioDeviceWasapiSubscription)
#endif  // CPPWINRT_VERSION

//------------------------------------------------------------------------------
WrapperImplType::WebRtcLib() noexcept
{
  wrapper::impl::org::webRtc::initSubsystems();
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::WebRtcLib::~WebRtcLib() noexcept
{
  thisWeak_.reset();
  notifySingletonCleanup();
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::create() noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  return result;
}

//------------------------------------------------------------------------------
void wrapper::org::webRtc::WebRtcLib::setup() noexcept
{
  auto singleton = WrapperImplType::singleton();
  singleton->actual_setup();
}

//------------------------------------------------------------------------------
void wrapper::org::webRtc::WebRtcLib::setup(wrapper::org::webRtc::WebRtcLibConfigurationPtr configuration) noexcept
{
  auto singleton = WrapperImplType::singleton();
  singleton->actual_setup(configuration);
}

//------------------------------------------------------------------------------
void wrapper::org::webRtc::WebRtcLib::startMediaTracing() noexcept
{
  auto singleton = WrapperImplType::singleton();
  singleton->actual_startMediaTracing();
}

//------------------------------------------------------------------------------
void wrapper::org::webRtc::WebRtcLib::stopMediaTracing() noexcept
{
  auto singleton = WrapperImplType::singleton();
  singleton->actual_stopMediaTracing();
}

//------------------------------------------------------------------------------
bool wrapper::org::webRtc::WebRtcLib::isMediaTracing() noexcept
{
  auto singleton = WrapperImplType::singleton();
  return singleton->actual_isMediaTracing();
}

//------------------------------------------------------------------------------
bool wrapper::org::webRtc::WebRtcLib::startMediaTrace(String filename) noexcept
{
  auto singleton = WrapperImplType::singleton();
  return singleton->actual_startMediaTrace(filename);
}

//------------------------------------------------------------------------------
bool wrapper::org::webRtc::WebRtcLib::startMediaTrace(
  String host,
  int port
  ) noexcept
{
  auto singleton = WrapperImplType::singleton();
  return singleton->actual_startMediaTrace(host, port);
}

//------------------------------------------------------------------------------
::zsLib::Milliseconds wrapper::org::webRtc::WebRtcLib::get_ntpServerTime() noexcept
{
  auto singleton = WrapperImplType::singleton();
  return singleton->actual_get_ntpServerTime();
}

//------------------------------------------------------------------------------
void wrapper::org::webRtc::WebRtcLib::set_ntpServerTime(::zsLib::Milliseconds value) noexcept
{
  auto singleton = WrapperImplType::singleton();
  singleton->actual_set_ntpServerTime(value);
}

//------------------------------------------------------------------------------
void WrapperImplType::actual_setup() noexcept
{
  auto configuration = make_shared<wrapper::org::webRtc::WebRtcLibConfiguration>();
  actual_setup(configuration);
}

//------------------------------------------------------------------------------
void WrapperImplType::actual_setup(wrapper::org::webRtc::WebRtcLibConfigurationPtr configuration) noexcept
{
  // prevent multiple setups being called simultaneously
  if (setupCalledOnce_.test_and_set()) return;

  wrapper::org::webRtc::EventQueuePtr queue = configuration ? configuration->queue : nullptr;
  wrapper::org::webRtc::EventQueuePtr audioCaptureFrameProcessingQueue = configuration ? configuration->audioCaptureFrameProcessingQueue : nullptr;
  wrapper::org::webRtc::EventQueuePtr audioRenderFrameProcessingQueue = configuration ? configuration->audioRenderFrameProcessingQueue : nullptr;
  wrapper::org::webRtc::EventQueuePtr videoFrameProcessingQueue = configuration ? configuration->videoFrameProcessingQueue : nullptr;

  // Setup for WinWUP...

#ifdef CPPWINRT_VERSION

  {
    // Setup if WinUWP CppWinRT is defined...
    auto nativeCppWinrt = UseEventQueue::toNative_winrt(queue);
    if ((nativeCppWinrt) && (!didSetupZsLib_.test_and_set())) {
      UseHelper::setup(nativeCppWinrt);
    }
  }

#endif //CPPWINRT_VERSION

  if (!didSetupZsLib_.test_and_set()) {
    UseHelper::setup();
  }

  rtc::EnsureWinsockInit();
  rtc::InitializeSSL();

  // scope: setup audio frame processing queue
  {
     auto nativeCaptureQueue = EventQueue::toNative(audioCaptureFrameProcessingQueue);
     auto nativeRenderQueue = EventQueue::toNative(audioRenderFrameProcessingQueue);
     // use the native queue if available otherwise use delegate queue
     audioCaptureFrameProcessingQueue_ = nativeCaptureQueue ? nativeCaptureQueue : actual_delegateQueue();
     audioRenderFrameProcessingQueue_ = nativeRenderQueue ? nativeRenderQueue : actual_delegateQueue();
  }

  // scope: setup audio frame processing queue
  {
    auto nativeQueue = EventQueue::toNative(videoFrameProcessingQueue);
    // use the native queue if available otherwise use delegate queue
    videoFrameProcessingQueue_ = nativeQueue ? nativeQueue : actual_delegateQueue();
  }

  rtc::tracing::SetupInternalTracer();

  if (setupComplete_.exchange(true)) {
    ZS_ASSERT_FAIL("already setup WebRtc wrapper");
    return;
  }
}

//------------------------------------------------------------------------------
void WrapperImplType::actual_startMediaTracing() noexcept
{
  if (!actual_checkSetup()) return;

  // prevent multiple calls to start or stop simultaneously
  if (isTracingStartOrStopping_.test_and_set()) return;

  if (isTracing_.exchange(false)) {
    isTracingStartOrStopping_.clear();
    return;
  }

  //rtc::tracing::StartInternalCapture();
#pragma ZS_BUILD_NOTE("TODO","(mosa) actual_startMediaTrace no options")

  isTracingStartOrStopping_.clear();
}

//------------------------------------------------------------------------------
void WrapperImplType::actual_stopMediaTracing() noexcept
{
  if (!actual_checkSetup()) return;

  // prevent multiple calls to start or stop simultaneously
  if (isTracingStartOrStopping_.test_and_set()) return;

  if (isTracing_.exchange(false)) {
    isTracingStartOrStopping_.clear();
    return;
  }

  rtc::tracing::StopInternalCapture();

  isTracingStartOrStopping_.clear();
}

//------------------------------------------------------------------------------
bool WrapperImplType::actual_isMediaTracing() noexcept
{
  if (!actual_checkSetup(false)) return false;
  return isTracing_;
}

//------------------------------------------------------------------------------
bool WrapperImplType::actual_startMediaTrace(String filename) noexcept
{
  if (!actual_checkSetup()) return false;

  // prevent multiple calls to start or stop simultaneously
  if (isTracingStartOrStopping_.test_and_set()) return false;

  ZS_ASSERT(!isTracing_);
  if (isTracing_.exchange(true)) {
    isTracingStartOrStopping_.clear();
    return false;
  }

  rtc::tracing::StartInternalCapture(filename.c_str());

  isTracingStartOrStopping_.clear();
  return false;
}

//------------------------------------------------------------------------------
bool WrapperImplType::actual_startMediaTrace(
                                            String host,
                                            int port
                                            ) noexcept
{
  if (!actual_checkSetup()) return false;

  // prevent multiple calls to start or stop simultaneously
  if (isTracingStartOrStopping_.test_and_set()) return false;

  ZS_ASSERT(!isTracing_);
  if (isTracing_.exchange(true)) {
    isTracingStartOrStopping_.clear();
    return false;
  }

#pragma ZS_BUILD_NOTE("TODO","(mosa) actual_startMediaTrace host/port")

  isTracingStartOrStopping_.clear();
  return false;
}


//------------------------------------------------------------------------------
::zsLib::Milliseconds WrapperImplType::actual_get_ntpServerTime() noexcept
{
  if (!actual_checkSetup()) return ::zsLib::Milliseconds();
  zsLib::AutoLock lock(lock_);
  return ntpServerTime_;
}

//------------------------------------------------------------------------------
void WrapperImplType::actual_set_ntpServerTime(::zsLib::Milliseconds value) noexcept
{
  if (!actual_checkSetup()) return;

  {
    zsLib::AutoLock lock(lock_);
    ntpServerTime_ = value;
  }

#pragma ZS_BUILD_NOTE("TODO","(mosa) set the NTP time from the server inside webrtc engine here")

}

//------------------------------------------------------------------------------
bool WrapperImplType::actual_checkSetup(bool assert) noexcept
{
  if ((assert) && ((!setupComplete_) && (!alreadyCleaned_))) {
    ZS_ASSERT_FAIL("Setup was never called on wrapper");
  }
  return setupComplete_ && (!alreadyCleaned_);
}

//------------------------------------------------------------------------------
zsLib::IMessageQueuePtr WrapperImplType::actual_delegateQueue() noexcept
{
  return zsLib::IMessageQueueThread::singletonUsingCurrentGUIThreadsMessageQueue();
}

//------------------------------------------------------------------------------
zsLib::IMessageQueuePtr WrapperImplType::actual_audioCaptureFrameProcessingQueue() noexcept
{
  ::zsLib::AutoLock lock(lock_);
  return audioCaptureFrameProcessingQueue_;
}

//------------------------------------------------------------------------------
zsLib::IMessageQueuePtr WrapperImplType::actual_audioRenderFrameProcessingQueue() noexcept
{
  ::zsLib::AutoLock lock(lock_);
  return audioRenderFrameProcessingQueue_;
}

//------------------------------------------------------------------------------
zsLib::IMessageQueuePtr WrapperImplType::actual_videoFrameProcessingQueue() noexcept
{
  ::zsLib::AutoLock lock(lock_);
  return videoFrameProcessingQueue_;
}

//------------------------------------------------------------------------------
void WrapperImplType::notifySingletonCleanup() noexcept
{
  // prevent clean-up twice
  if (!actual_checkSetup()) return;
  if (alreadyCleaned_.exchange(true)) return;

  // Add what is needed to shutdown webrtc...

#pragma ZS_BUILD_NOTE("TODO","(mosa) shutdown webrtc engine here")

  rtc::tracing::ShutdownInternalTracer();

  rtc::CleanupSSL();
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::singleton() noexcept
{
  static zsLib::SingletonLazySharedPtr<WrapperImplType> singleton(WrapperImplType::create());

  auto result = singleton.singleton();

  static zsLib::SingletonManager::Register registerSingleton("org.webrtc.WebRtcLib", result);

  // prevent crashes when accessing singleton during shutdown
  if (!result) {
    class BogusSingleton : public WrapperImplType {

    private:

      void actual_setup() noexcept final {}
      void actual_setup(ZS_MAYBE_USED() wrapper::org::webRtc::WebRtcLibConfigurationPtr configuration) noexcept final {}
      void actual_startMediaTracing() noexcept final {}
      void actual_stopMediaTracing() noexcept final {}
      bool actual_isMediaTracing() noexcept final { return false; }
      bool actual_startMediaTrace(String) noexcept final { return false; }
      bool actual_startMediaTrace(
                                 String,
                                 int
                                 ) noexcept final { return false; }

      ::zsLib::Milliseconds actual_get_ntpServerTime() noexcept final { return zsLib::Milliseconds(); }
      void actual_set_ntpServerTime(::zsLib::Milliseconds) noexcept final {}

      bool actual_checkSetup(bool) noexcept final { return false; }

      //-----------------------------------------------------------------------
      zsLib::IMessageQueuePtr actual_delegateQueue() noexcept final
      {
        return zsLib::IMessageQueueThread::singletonUsingCurrentGUIThreadsMessageQueue();
      }

      //-----------------------------------------------------------------------
      zsLib::IMessageQueuePtr actual_audioCaptureFrameProcessingQueue() noexcept final
      {
        return actual_delegateQueue();
      }

      //-----------------------------------------------------------------------
      zsLib::IMessageQueuePtr actual_audioRenderFrameProcessingQueue() noexcept final
      {
        return actual_delegateQueue();
      }

      //-----------------------------------------------------------------------
      zsLib::IMessageQueuePtr actual_videoFrameProcessingQueue() noexcept final
      {
        return actual_delegateQueue();
      }

      void notifySingletonCleanup() noexcept final {}
    };
    return make_shared<BogusSingleton>();
  }
  return result;
}

//------------------------------------------------------------------------------
bool WrapperImplType::checkSetup(bool assert) noexcept
{
  auto singleton = WrapperImplType::singleton();
  return singleton->actual_checkSetup(assert);
}

//------------------------------------------------------------------------------
zsLib::IMessageQueuePtr WrapperImplType::delegateQueue() noexcept
{
  auto singleton = WrapperImplType::singleton();
  return singleton->actual_delegateQueue();
}

//------------------------------------------------------------------------------
zsLib::IMessageQueuePtr WrapperImplType::audioCaptureFrameProcessingQueue() noexcept
{
  auto singleton = WrapperImplType::singleton();
  return singleton->actual_audioCaptureFrameProcessingQueue();
}

//------------------------------------------------------------------------------
zsLib::IMessageQueuePtr WrapperImplType::audioRenderFrameProcessingQueue() noexcept
{
  auto singleton = WrapperImplType::singleton();
  return singleton->actual_audioRenderFrameProcessingQueue();
}

//------------------------------------------------------------------------------
zsLib::IMessageQueuePtr WrapperImplType::videoFrameProcessingQueue() noexcept
{
  auto singleton = WrapperImplType::singleton();
  return singleton->actual_videoFrameProcessingQueue();
}
