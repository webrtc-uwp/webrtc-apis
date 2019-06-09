
#include "impl_org_webRtc_CustomVideoCapturer.h"
#include "impl_org_webRtc_CustomVideoCapturerParameters.h"
#include "impl_org_webRtc_VideoCapturerInputSize.h"
#include "impl_org_webRtc_VideoFormat.h"
#include "impl_org_webRtc_VideoFrameBuffer.h"
#include "impl_org_webRtc_WebRtcLib.h"
#include "impl_org_webRtc_enums.h"

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
using ::zsLib::AutoRecursiveLock;
using ::zsLib::eventing::SecureByteBlock;
using ::zsLib::eventing::SecureByteBlockPtr;
using ::std::shared_ptr;
using ::std::weak_ptr;
using ::std::make_shared;
using ::std::list;
using ::std::set;
using ::std::map;

// borrow definitions from class
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturer::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomVideoCapturer::CustomVideoCapturer() noexcept :
  queue_(WebRtcLib::customVideoQueue())
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomVideoCapturerPtr wrapper::org::webRtc::CustomVideoCapturer::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomVideoCapturer>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomVideoCapturer::~CustomVideoCapturer() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomVideoCapturer::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomVideoCapturerPtr wrapper::org::webRtc::CustomVideoCapturer::create(wrapper::org::webRtc::CustomVideoCapturerParametersPtr params) noexcept
{
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->params_ = wrapper::impl::org::webRtc::CustomVideoCapturerParameters::clone(params);
  return result;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomVideoCapturer::notifyFrame(
  wrapper::org::webRtc::VideoFrameBufferPtr frame,
  int64_t timestamp,
  wrapper::org::webRtc::VideoRotation rotation
) noexcept
{
  if (!frame)
    return;

  auto native = VideoFrameBuffer::toNative(frame);

  ::webrtc::VideoFrame::Builder builder;
  builder.set_video_frame_buffer(native);
  builder.set_timestamp_ms(timestamp);
  builder.set_rotation(UseEnum::toNative(rotation));

  AutoRecursiveLock lock(ProxyReferencelock_);
  if (!proxyReference_)
    return;
  proxyReference_->notifyOnFrame(builder.build());
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::MediaSourceState wrapper::impl::org::webRtc::CustomVideoCapturer::get_currentState() noexcept
{
  AutoRecursiveLock lock(lock_);
  return state_;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomVideoCapturer::set_currentState(wrapper::org::webRtc::MediaSourceState value) noexcept
{
  AutoRecursiveLock lock(lock_);
  state_ = value;
}

//------------------------------------------------------------------------------
webrtc::MediaSourceInterface::SourceState WrapperImplType::state() const noexcept
{
  AutoRecursiveLock lock(lock_);
  return UseEnum::toNative(state_);
}

//------------------------------------------------------------------------------
bool WrapperImplType::remote() const noexcept
{
  if (!params_)
    return false;
  return params_->isRemote;
}

//------------------------------------------------------------------------------
bool WrapperImplType::is_screencast() const noexcept
{
  if (!params_)
    return {};
  return params_->isScreencast;
}

//------------------------------------------------------------------------------
absl::optional<bool> WrapperImplType::needs_denoising() const noexcept
{
  if (!params_)
    return {};
  if (!params_->needsDenoising.has_value())
    return {};

  return params_->needsDenoising.value();
}

//------------------------------------------------------------------------------
bool WrapperImplType::GetStats(webrtc::VideoTrackSourceInterface::Stats* stats) noexcept
{
  if (!params_)
    return {};

  if (!stats)
    return {};

  if (!params_->inputSize)
    return {};

  stats->input_height = SafeInt<decltype(stats->input_height)>(params_->inputSize->height);
  stats->input_width = SafeInt<decltype(stats->input_width)>(params_->inputSize->width);
  return true;
}

//------------------------------------------------------------------------------
void WrapperImplType::destroyProxyReference() noexcept
{
  AutoRecursiveLock lock(ProxyReferencelock_);
  proxyReference_ = {};
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::create() noexcept
{
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  return result;
}

//------------------------------------------------------------------------------
WrapperImplType::UseAdaptedVideoTrackSourceScopedPtr WrapperImplType::toNative(WrapperType *wrapperType) noexcept
{
  if (!wrapperType)
    return {};

  auto converted = dynamic_cast<WrapperImplType *>(wrapperType);
  if (!converted)
    return {};

  auto proxy = new Proxy(converted->thisWeak_.lock());
  auto result = WrapperImplType::UseAdaptedVideoTrackSourceScopedPtr(proxy);

  {
    AutoRecursiveLock lock(converted->ProxyReferencelock_);
    converted->proxyReference_ = proxy;
  }

  return result;
}

//------------------------------------------------------------------------------
WrapperImplType::UseAdaptedVideoTrackSourceScopedPtr WrapperImplType::toNative(WrapperTypePtr wrapperType) noexcept
{
  if (!wrapperType)
    return {};
  return toNative(wrapperType.get());
}
