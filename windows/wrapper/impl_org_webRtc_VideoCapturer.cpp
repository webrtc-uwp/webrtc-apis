
#ifdef _WIN32
#include <WinSock2.h>
#include <unknwn.h>
#endif //_WIN32

#ifdef __has_include
#if __has_include(<winrt/Windows.Devices.Enumeration.h>)
#include <winrt/Windows.Devices.Enumeration.h>
#endif //__has_include(<winrt/Windows.Devices.Enumeration.h>)
#endif //__has_include

#include "impl_org_webRtc_VideoCapturer.h"
#include "impl_org_webRtc_VideoFormat.h"
#include "impl_org_webRtc_RTCError.h"
#include "impl_org_webRtc_VideoDeviceInfo.h"
#include "impl_org_webRtc_WebrtcLib.h"
#include "impl_org_webRtc_enums.h"
#include "impl_org_webRtc_VideoCapturerInputSize.h"
#include "impl_org_webRtc_VideoCapturerCreationParameters.h"
#include "impl_org_webRtc_WebrtcFactory.h"
#include "impl_webrtc_VideoCapturer.h"

#include "impl_org_webRtc_pre_include.h"
#include "media/engine/webrtcvideocapturer.h"
#include "api/rtcerror.h"
#include "impl_org_webRtc_post_include.h"

#include <experimental/generator>

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

// borrow types from call definitions
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoCapturer::WrapperType, WrapperType);
// borrow definitions from class
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoCapturer::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoCapturer::NativeType, NativeType);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::WebRtcLib, UseWebrtcLib);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCError, UseError);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoDeviceInfo, UseVideoDeviceInfo);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFormat, UseVideoFormat);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::WebRtcFactory, UseFactory);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoCapturerInputSize, UseVideoCapturerInputSize);


//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoCapturer::VideoCapturer() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoCapturerPtr wrapper::org::webRtc::VideoCapturer::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::VideoCapturer>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoCapturer::~VideoCapturer() noexcept
{
  thisWeak_.reset();
  teardownObserver();
  wrapper_dispose();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoCapturer::wrapper_dispose() noexcept
{
  if (!native_) return;

  teardownObserver();
  if (!stopCalled_.exchange(true)) {
    native_->Stop();
  }
  native_.reset();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoCapturerPtr wrapper::org::webRtc::VideoCapturer::create(wrapper::org::webRtc::VideoCapturerCreationParametersPtr params) noexcept
{
  String name;
  String id;
  String videoProfileId;
  wrapper::org::webRtc::VideoProfileKind videoProfileKind =
      wrapper::org::webRtc::VideoProfileKind_unspecified;
  bool enableMrc {false};
  int width {0};           // unconstrained
  int height {0};          // unconstrained
  double framerate {0.0};  // unconstrained

  UseFactoryPtr factory = UseFactory::toWrapper(params->factory);

  if (params) {
    name = params->name;
    id = params->id;
    videoProfileId = params->videoProfileId;
    videoProfileKind = params->videoProfileKind;
    enableMrc = params->enableMrc;
    width = params->width;
    height = params->height;
    framerate = params->framerate;
  }

  std::unique_ptr<::cricket::VideoCapturer> capturer;

  if (factory) {
    auto capturerFactory = factory->videoDeviceCaptureFactory();
    if (capturerFactory) {
      ::cricket::Device device;
      device.name = name;
      device.id = id;
      capturer = capturerFactory->Create(device);
      if (!capturer)
        return {};
    }
  }

  if (!capturer) {
    webrtc::IVideoCapturer::CreationProperties props;
    props.name_ = name.c_str();
    props.id_ = id.c_str();
    props.videoProfileId_ = videoProfileId.c_str();
    props.videoProfileKind_ = videoProfileKind;
    props.mrcEnabled_ = enableMrc;
    props.width_ = width;
    props.height_ = height;
    props.framerate_ = framerate;
    capturer = NativeTypeUniPtr(dynamic_cast<webrtc::VideoCapturer*>(webrtc::IVideoCapturer::create(props).release()));
    if (!capturer) return {};
  }

  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = std::move(capturer);
  result->setupObserver();
  return result;
}

static bool alwaysTrue() { return true; }

//------------------------------------------------------------------------------
shared_ptr< PromiseWithHolderPtr< shared_ptr< list< wrapper::org::webRtc::VideoDeviceInfoPtr > > > > wrapper::org::webRtc::VideoCapturer::getDevices() noexcept
{
  typedef shared_ptr< PromiseWithHolderPtr< shared_ptr< list< wrapper::org::webRtc::VideoDeviceInfoPtr > > > > ResultType;
  typedef shared_ptr< list< wrapper::org::webRtc::VideoDeviceInfoPtr > > ResultListType;

  auto delegateQueue = UseWebrtcLib::delegateQueue();
  if (!delegateQueue) {
    auto failedResult = ResultType::element_type::create();
    UseError::rejectPromise(failedResult, ::webrtc::RTCError(::webrtc::RTCErrorType::INVALID_STATE));
    return failedResult;
  }

  auto promise = ResultType::element_type::create(delegateQueue);

#ifdef CPPWINRT_VERSION
  if (alwaysTrue()) {
    //auto results = winrt::Windows::Devices::Enumeration::DeviceInformation::FindAllAsync();
    //co_await results;
    delegateQueue->postClosure([promise]() {

      auto asyncResults = winrt::Windows::Devices::Enumeration::DeviceInformation::FindAllAsync(winrt::Windows::Devices::Enumeration::DeviceClass::VideoCapture);

      asyncResults.Completed([promise](auto &&asyncResults, ZS_MAYBE_USED() winrt::Windows::Foundation::AsyncStatus status) {
        auto results = asyncResults.GetResults();
        ZS_MAYBE_USED(status);
        auto output = make_shared<ResultListType::element_type>();
        for (auto device : results) {
          auto wrapper = UseVideoDeviceInfo::toWrapper(device);
          if (!wrapper) continue;
          output->push_back(wrapper);
        }
        promise->resolve(output);
      });
    });
    return promise;
  }
#endif // CPPWINRT_VERSION
  
  UseError::rejectPromise(promise, ::webrtc::RTCError(::webrtc::RTCErrorType::RESOURCE_EXHAUSTED));
  return promise;
}

//------------------------------------------------------------------------------
shared_ptr< list< wrapper::org::webRtc::VideoFormatPtr > > wrapper::impl::org::webRtc::VideoCapturer::getSupportedFormats() noexcept
{
  typedef shared_ptr< list< wrapper::org::webRtc::VideoFormatPtr > > ResultType;
  ResultType result = make_shared< ResultType::element_type >();

  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return result;
  }

  auto formats = native_->GetSupportedFormats();
  if (!formats) return result;

  for (auto iter = formats->begin(); iter != formats->end(); ++iter) {
    auto converted = UseVideoFormat::toWrapper(*iter);
    if (!converted) continue;
    result->push_back(converted);
  }

  return result;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFormatPtr wrapper::impl::org::webRtc::VideoCapturer::getBestCaptureFormat(wrapper::org::webRtc::VideoFormatPtr desired) noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return wrapper::org::webRtc::VideoFormatPtr();
  }

  ZS_ASSERT(desired);
  if (!desired) return wrapper::org::webRtc::VideoFormatPtr();

  auto converted = UseVideoFormat::toNative(desired);
  ZS_ASSERT(converted);
  if (!converted) return wrapper::org::webRtc::VideoFormatPtr();

  ::cricket::VideoFormat format;
  if (!native_->GetBestCaptureFormat(*converted, &format)) return wrapper::org::webRtc::VideoFormatPtr();

  return UseVideoFormat::toWrapper(format);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoCaptureState wrapper::impl::org::webRtc::VideoCapturer::start(wrapper::org::webRtc::VideoFormatPtr captureFormat) noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return wrapper::org::webRtc::VideoCaptureState::VideoCaptureState_failed;
  }

  ZS_ASSERT(captureFormat);
  if (!captureFormat) return wrapper::org::webRtc::VideoCaptureState::VideoCaptureState_failed;

  auto converted = UseVideoFormat::toNative(captureFormat);
  ZS_ASSERT(converted);
  if (!converted) return wrapper::org::webRtc::VideoCaptureState::VideoCaptureState_failed;

  return UseEnum::toWrapper(native_->Start(*converted));
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFormatPtr wrapper::impl::org::webRtc::VideoCapturer::getCaptureFormat() noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return wrapper::org::webRtc::VideoFormatPtr();
  }

  return UseVideoFormat::toWrapper(native_->GetCaptureFormat());
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoCapturer::stop() noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return;
  }
  stopCalled_ = true;
  native_->Stop();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoCapturer::constrainSupportedFormats(wrapper::org::webRtc::VideoFormatPtr maxFormat) noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return;
  }
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::VideoCapturer::get_id() noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return String();
  }
  return native_->GetId();
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::VideoCapturer::get_enableCameraList() noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return false;
  }
  return native_->enable_camera_list();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoCapturer::set_enableCameraList(bool value) noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return;
  }
  return native_->set_enable_camera_list(value);
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::VideoCapturer::get_enableVideoAdapter() noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return false;
  }
  return native_->enable_video_adapter();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoCapturer::set_enableVideoAdapter(bool value) noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return;
  }
  native_->set_enable_video_adapter(value);
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::VideoCapturer::get_isRunning() noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return false;
  }
  return native_->IsRunning();
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::VideoCapturer::get_applyRotation() noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return false;
  }
  return native_->apply_rotation();
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::VideoCapturer::get_isScreencast() noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return false;
  }
  return native_->IsScreencast();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoCapturerInputSizePtr wrapper::impl::org::webRtc::VideoCapturer::get_inputSize() noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return wrapper::org::webRtc::VideoCapturerInputSizePtr();
  }

  int width{};
  int height{};
  if (!native_->GetInputSize(&width, &height)) return wrapper::org::webRtc::VideoCapturerInputSizePtr();

  return UseVideoCapturerInputSize::toWrapper(width, height);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoCaptureState wrapper::impl::org::webRtc::VideoCapturer::get_state() noexcept
{
  if (!native_) {
    ZS_ASSERT_FAIL("Cannot call into VideoCapturer after VideoCapturer has been passed into to a VideoTrackSource.");
    return wrapper::org::webRtc::VideoCaptureState::VideoCaptureState_failed;
  }
  return UseEnum::toWrapper(native_->capture_state());
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoCapturer::wrapper_onObserverCountChanged(size_t count) noexcept
{
  bool needObservers = (0 != count);

  // scope: preform subscribe based on observers being attached
  {
    zsLib::AutoLock lock(lock_);

    bool hadObservers = (0 != totalObservers_);
    totalObservers_ = count;

    if (hadObservers == needObservers)
      return;

    if (!needObservers) {
      subscription_->cancel();
      subscription_.reset();
      return;
    }

    auto capturer = (dynamic_cast<webrtc::VideoCapturer*>(native_.get()));
    ZS_ASSERT(capturer);

    subscription_ = capturer->subscribe(videoObserver_);
  }
}

//------------------------------------------------------------------------------
void WrapperImplType::setupObserver() noexcept
{
  if (!native_) return;

  videoObserver_ = std::make_shared<WebrtcVideoObserver>(thisWeak_.lock(), UseWebrtcLib::videoFrameProcessingQueue());
}

//------------------------------------------------------------------------------
void WrapperImplType::teardownObserver() noexcept
{
  if (!native_) return;

  if (videoObserver_)
    videoObserver_.reset();
}

//------------------------------------------------------------------------------
void WrapperImplType::onWebrtcObserverVideoFrameReceived(UseVideoFrameBufferEventPtr event) noexcept
{
  onVideoFrame(event);
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeTypeUniPtr native) noexcept
{
  if (!native) return WrapperImplTypePtr();

  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = std::move(native);
  return result;
}

//------------------------------------------------------------------------------
NativeTypeUniPtr WrapperImplType::toNative(WrapperTypePtr wrapper) noexcept
{
  if (!wrapper) return NativeTypeUniPtr();
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, wrapper);
  if (!converted) return NativeTypeUniPtr();
  return NativeTypeUniPtr(std::move(converted->native_));
}
