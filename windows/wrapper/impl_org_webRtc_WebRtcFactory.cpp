
#include "impl_org_webRtc_WebRtcFactory.h"
#include "impl_org_webRtc_WebRtcFactoryConfiguration.h"
#include "impl_org_webRtc_WebRtcLib.h"
#include "impl_org_webRtc_AudioBufferEvent.h"
#include "impl_org_webRtc_AudioProcessingInitializeEvent.h"
#include "impl_org_webRtc_AudioProcessingRuntimeSettingEvent.h"
#include "impl_org_webRtc_helpers.h"

#include "impl_webrtc_IAudioDeviceWasapi.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "api/audio_codecs/builtin_audio_encoder_factory.h"
#include "api/peerconnectioninterface.h"
#include "api/peerconnectionfactoryproxy.h"
#include "api/test/fakeconstraints.h"
#include "rtc_base/event_tracer.h"
#include "third_party/winuwp_h264/winuwp_h264_factory.h"
#include "media/engine/webrtcvideocapturerfactory.h"
#include "pc/peerconnectionfactory.h"
#include "modules/audio_device/include/audio_device.h"
#include "impl_org_webRtc_post_include.h"

#include <zsLib/eventing/IHelper.h>
#include <zsLib/SafeInt.h>

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

// borrow definitions from class
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::WebRtcFactory::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::WebRtcLib, UseWebRtcLib);

typedef WrapperImplType::PeerConnectionFactoryInterfaceScopedPtr PeerConnectionFactoryInterfaceScopedPtr;
typedef WrapperImplType::PeerConnectionFactoryScopedPtr PeerConnectionFactoryScopedPtr;

ZS_DECLARE_TYPEDEF_PTR(::webrtc::PeerConnectionFactory, NativePeerConnectionFactory)
ZS_DECLARE_TYPEDEF_PTR(::webrtc::PeerConnectionFactoryInterface, NativePeerConnectionFactoryInterface)

ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::UseVideoDeviceCaptureFacrtory, UseVideoDeviceCaptureFacrtory);

ZS_DECLARE_TYPEDEF_PTR(::cricket::WebRtcVideoDeviceCapturerFactory, UseWebrtcVideoDeviceCaptureFacrtory);

ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::UseAudioBufferEvent, UseAudioBufferEvent);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::UseAudioInitEvent, UseAudioInitEvent);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::UseAudioRuntimeEvent, UseAudioRuntimeEvent);


namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
WrapperImplType::WebrtcObserver::WebrtcObserver(
  WrapperImplTypePtr wrapper,
  zsLib::IMessageQueuePtr queue,
  std::function<void(UseAudioBufferEventPtr)> bufferEvent,
  std::function<void(UseAudioInitEventPtr)> initEvent,
  std::function<void(UseAudioRuntimeEventPtr)> runtimeEvent
) noexcept :
  outer_(wrapper),
  queue_(queue),
  bufferEvent_(std::move(bufferEvent)),
  initEvent_(std::move(initEvent)),
  runtimeEvent_(std::move(runtimeEvent))
{
}

//------------------------------------------------------------------------------
void WrapperImplType::WebrtcObserver::Initialize(int sample_rate_hz, int num_channels)
{
  if (!enabled_) return;
  if (!enabled_) return;

  auto outer = outer_.lock();
  if (!outer) return;

  WebrtcObserver *pThis = this;

  auto event = UseAudioInitEvent::toWrapper(SafeInt<size_t>(sample_rate_hz), SafeInt<size_t>(num_channels));
  queue_->postClosure([outer, event, pThis]() { pThis->initEvent_(event); });
}

//------------------------------------------------------------------------------
void WrapperImplType::WebrtcObserver::Process(NativeAudioBufferType* audio)
{
  if (!enabled_) return;

  auto outer = outer_.lock();
  if (!outer) return;

  WebrtcObserver *pThis = this;

  HANDLE handle = ::CreateEventEx(NULL, NULL, 0, EVENT_ALL_ACCESS);

  std::function<void(void)> callback = [handle]() { ::SetEvent(handle); };

  auto event = UseAudioBufferEvent::toWrapper(std::move(callback), audio);
  queue_->postClosure([outer, event, pThis]() { pThis->bufferEvent_(event); });

  ::WaitForSingleObjectEx(handle, INFINITE, FALSE /* ALERTABLE */);
  ::CloseHandle(handle);
}

//------------------------------------------------------------------------------
std::string WrapperImplType::WebrtcObserver::ToString() const
{
  return "WrapperImplType::WebrtcObserver";
}

//------------------------------------------------------------------------------
void WrapperImplType::WebrtcObserver::SetRuntimeSetting(::webrtc::AudioProcessing::RuntimeSetting setting)
{
  if (!enabled_) return;

  auto outer = outer_.lock();
  if (!outer) return;

  WebrtcObserver *pThis = this;

  auto event = UseAudioRuntimeEvent::toWrapper(setting);
  queue_->postClosure([outer, event, pThis]() { pThis->runtimeEvent_(event); });
}

//------------------------------------------------------------------------------
NativePeerConnectionFactoryInterface *unproxy(NativePeerConnectionFactoryInterface *native)
{
  if (!native) return native;
  return WRAPPER_DEPROXIFY_CLASS(::webrtc::PeerConnectionFactory, ::webrtc::PeerConnectionFactory, native);
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::WebRtcFactory::WebRtcFactory() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::WebRtcFactoryPtr wrapper::org::webRtc::WebRtcFactory::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::WebRtcFactory>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::WebRtcFactory::~WebRtcFactory() noexcept
{
  thisWeak_.reset();
  wrapper_dispose();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::WebRtcFactory::wrapper_dispose() noexcept
{
  zsLib::AutoRecursiveLock lock(lock_);
  if (!peerConnectionFactory_) return;

  // reset the factory (cannot be used anymore)...
  peerConnectionFactory_ = PeerConnectionFactoryInterfaceScopedPtr();
  videoDeviceCaptureFactory_.reset();

#pragma ZS_BUILD_NOTE("TODO","(mosa) shutdown threads need something more?")

  networkThread.reset();
  workerThread.reset();
  signalingThread.reset();

}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::WebRtcFactory::wrapper_init_org_webRtc_WebRtcFactory(wrapper::org::webRtc::WebRtcFactoryConfigurationPtr configuration) noexcept
{
  AudioPostCapture_ = std::make_shared<WebrtcObserver>(
    thisWeak_.lock(),
    UseWebRtcLib::audioFrameProcessingQueue(),
    [this](UseAudioBufferEventPtr event) { this->onAudioPostCapture_Process(std::move(event)); },
    [this](UseAudioInitEventPtr event) { this->onAudioPostCapture_Init(std::move(event)); },
    [this](UseAudioRuntimeEventPtr event) { this->onAudioPostCapture_SetRuntimeSetting(std::move(event)); }
  );
  AudioPreRender_ = std::make_shared<WebrtcObserver>(
    thisWeak_.lock(),
    UseWebRtcLib::audioFrameProcessingQueue(),
    [this](UseAudioBufferEventPtr event) { this->onAudioPreRender_Process(std::move(event)); },
    [this](UseAudioInitEventPtr event) { this->onAudioPreRender_Init(std::move(event)); },
    [this](UseAudioRuntimeEventPtr event) { this->onAudioPreRender_SetRuntimeSetting(std::move(event)); }
  );

  bool audioCapturingEnabled = configuration ? configuration->audioCapturingEnabled : true;
  bool audioRenderingEnabled = configuration ? configuration->audioRenderingEnabled : true;

  networkThread = rtc::Thread::CreateWithSocketServer();
  networkThread->Start();

  workerThread = rtc::Thread::Create();
  workerThread->Start();

  signalingThread = rtc::Thread::Create();
  signalingThread->Start();


  auto encoderFactory = new ::webrtc::WinUWPH264EncoderFactory();
  auto decoderFactory = new ::webrtc::WinUWPH264DecoderFactory();

  rtc::scoped_refptr<::webrtc::AudioDeviceModule> audioDeviceModule;
  audioDeviceModule = workerThread->Invoke<rtc::scoped_refptr<::webrtc::AudioDeviceModule>>(
    RTC_FROM_HERE, [audioCapturingEnabled, audioRenderingEnabled]() {
    webrtc::IAudioDeviceWasapi::CreationProperties props;
    props.id_ = "";
    props.playoutEnabled_ = audioCapturingEnabled;
    props.recordingEnabled_ = audioRenderingEnabled;
    return rtc::scoped_refptr<::webrtc::AudioDeviceModule>(webrtc::IAudioDeviceWasapi::create(props));
  });

  peerConnectionFactory_ = ::webrtc::CreatePeerConnectionFactory(
    networkThread.get(),
    workerThread.get(),
    signalingThread.get(),
    audioDeviceModule.release(),
    ::webrtc::CreateBuiltinAudioEncoderFactory(),
    ::webrtc::CreateBuiltinAudioDecoderFactory(),
    encoderFactory,
    decoderFactory
  );

#ifdef WINUWP
  videoDeviceCaptureFactory_ = make_shared<::cricket::WebRtcVideoDeviceCapturerFactory>();
#else
#error PLATFORM REQUIRES FACTORY
#endif //WEBRTC
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::WebRtcFactory::wrapper_onObserverCountChanged(size_t count) noexcept
{
  zsLib::AutoRecursiveLock lock(lock_);
  AudioPostCapture_->enabled(count > 0);
  AudioPreRender_->enabled(count > 0);
}

//------------------------------------------------------------------------------
PeerConnectionFactoryInterfaceScopedPtr WrapperImplType::peerConnectionFactory() noexcept
{
  zsLib::AutoRecursiveLock lock(lock_);
  return peerConnectionFactory_;
}

//------------------------------------------------------------------------------
PeerConnectionFactoryScopedPtr WrapperImplType::realPeerConnectionFactory() noexcept
{
  zsLib::AutoRecursiveLock lock(lock_);
  auto realInterface = unproxy(peerConnectionFactory_);
  return dynamic_cast<NativePeerConnectionFactory *>(realInterface);
}

//------------------------------------------------------------------------------
UseVideoDeviceCaptureFacrtoryPtr WrapperImplType::videoDeviceCaptureFactory() noexcept
{
  zsLib::AutoRecursiveLock lock(lock_);
  return videoDeviceCaptureFactory_;
}

//------------------------------------------------------------------------------
void WrapperImplType::onAudioPostCapture_Init(UseAudioInitEventPtr event)
{
  onAudioPostCaptureInitialize(std::move(event));
}

//------------------------------------------------------------------------------
void WrapperImplType::onAudioPostCapture_SetRuntimeSetting(UseAudioRuntimeEventPtr event)
{
  onAudioPostCaptureRuntimeSetting(std::move(event));
}

//------------------------------------------------------------------------------
void WrapperImplType::onAudioPostCapture_Process(UseAudioBufferEventPtr event)
{
  onAudioPostCapture(std::move(event));
}

//------------------------------------------------------------------------------
void WrapperImplType::onAudioPreRender_Init(UseAudioInitEventPtr event)
{
  onAudioPreRenderInitialize(std::move(event));
}

//------------------------------------------------------------------------------
void WrapperImplType::onAudioPreRender_SetRuntimeSetting(UseAudioRuntimeEventPtr event)
{
  onAudioPreRenderRuntimeSetting(std::move(event));
}

//------------------------------------------------------------------------------
void WrapperImplType::onAudioPreRender_Process(UseAudioBufferEventPtr event)
{
  onAudioPreRender(std::move(event));
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(WrapperTypePtr wrapper) noexcept
{
  if (!wrapper) return WrapperImplTypePtr();
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, wrapper);
  return converted;
}
