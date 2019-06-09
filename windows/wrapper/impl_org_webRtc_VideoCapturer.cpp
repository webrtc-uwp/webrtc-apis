
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
#include "media/base/adapted_video_track_source.h"
#include "api/rtc_error.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoCapturer::NativeTypeScopedRefPtr, NativeTypeScopedRefPtr);

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
  native_ = {};
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoCapturerPtr wrapper::org::webRtc::VideoCapturer::create(wrapper::org::webRtc::VideoCapturerCreationParametersPtr params) noexcept
{
  String name;
  String id;
  bool enableMrc {false};
  ::cricket::VideoFormat format;

  UseFactoryPtr factory = UseFactory::toWrapper(params->factory);

  if (params) {
    name = params->name;
    id = params->id;
    enableMrc = params->enableMrc;
    format = *UseVideoFormat::toNative(params->format);
  }

  rtc::scoped_refptr<::rtc::AdaptedVideoTrackSource> capturer;

  if (factory) {
    auto capturerFactory = factory->videoDeviceCaptureFactory();
    if (capturerFactory) {
      ::webrtc::Device device;
      device.name = name;
      device.id = id;
      if (params->format) {
        device.format = format;
      }
      capturer = capturerFactory->Create(device);
      if (!capturer)
        return {};
    }
  }

  if (!capturer) {
    webrtc::IVideoCapturer::CreationProperties props;
    props.name_ = name.c_str();
    props.id_ = id.c_str();
    props.mrcEnabled_ = enableMrc;
    props.format_ = format;
    capturer = webrtc::IVideoCapturer::create(props);
    if (!capturer) return {};
  }

  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = std::move(capturer);
  result->setupObserver();
  return result;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::VideoCapturer::get_isScreencast() noexcept
{
  if (!native_)
    return {};

  return native_->is_screencast();
}

//------------------------------------------------------------------------------
Optional< bool > wrapper::impl::org::webRtc::VideoCapturer::get_needsDenoising() noexcept
{
  if (!native_)
    return {};

  auto value = native_->needs_denoising();
  if (!value.has_value())
    return {};

  return value.value();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoCapturerInputSizePtr wrapper::impl::org::webRtc::VideoCapturer::get_inputSize() noexcept
{
  if (!native_)
    return {};

  webrtc::VideoTrackSourceInterface *nativeBase = native_.get();
  if (!nativeBase)
    return {};

  webrtc::VideoTrackSourceInterface::Stats stats;
  auto result = nativeBase->GetStats(&stats);
  if (!result)
    return {};

  return UseVideoCapturerInputSize::toWrapper(stats.input_width, stats.input_height);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::MediaSourceState wrapper::impl::org::webRtc::VideoCapturer::get_state() noexcept
{
  if (!native_)
    return {};
  return UseEnum::toWrapper(native_->state());
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
WrapperImplTypePtr WrapperImplType::toWrapper(NativeType *native) noexcept
{
  if (!native) return WrapperImplTypePtr();

  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = NativeTypeScopedRefPtr(native);
  return result;
}

//------------------------------------------------------------------------------
NativeTypeScopedRefPtr WrapperImplType::toNative(WrapperTypePtr wrapper) noexcept
{
  if (!wrapper) return {};
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, wrapper);
  if (!converted) return {};
  return converted->native_;
}
