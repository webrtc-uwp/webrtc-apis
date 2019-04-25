

#ifdef __has_include
#if __has_include(<winrt/base.h>)
#include <winrt/base.h>
#endif //__has_include(<winrt/base.h>)
#endif //__has_include

#include "impl_org_webRtc_VideoFrameNativeBuffer.h"
#include "impl_org_webRtc_VideoFramePlanarYuvBuffer.h"
#include "impl_org_webRtc_MediaSample.h"
#include "impl_org_webRtc_enums.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/video/video_frame_buffer.h"
#include "third_party/winuwp_h264/native_handle_buffer.h"
#include "impl_org_webRtc_post_include.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFrameNativeBuffer::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFrameNativeBuffer::NativeNativeHandleBufferTypeScopedRefPtr, NativeNativeHandleBufferTypeScopedRefPtr);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::MediaSample, UseMediaSample);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer, UseVideoFramePlanarYuvBuffer);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoFrameNativeBuffer::VideoFrameNativeBuffer() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFrameNativeBufferPtr wrapper::org::webRtc::VideoFrameNativeBuffer::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::VideoFrameNativeBuffer>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoFrameNativeBuffer::~VideoFrameNativeBuffer() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoFrameNativeBuffer::wrapper_dispose() noexcept
{
  native_ = {};
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr wrapper::impl::org::webRtc::VideoFrameNativeBuffer::toI420() noexcept
{
  if (!native_)
    return {};

  auto i420Frame = native_->ToI420();
  return UseVideoFramePlanarYuvBuffer::toWrapper(i420Frame);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFrameBufferType wrapper::impl::org::webRtc::VideoFrameNativeBuffer::get_type() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return wrapper::org::webRtc::VideoFrameBufferType::VideoFrameBufferType_native;
  return UseEnum::toWrapper(native_->type());
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFrameNativeBuffer::get_width() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return native_->width();
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFrameNativeBuffer::get_height() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return native_->height();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr wrapper::impl::org::webRtc::VideoFrameNativeBuffer::get_yuvFrame() noexcept
{
  return toI420();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvaBufferPtr wrapper::impl::org::webRtc::VideoFrameNativeBuffer::get_yuvaFrame() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFrameNativeBufferPtr wrapper::impl::org::webRtc::VideoFrameNativeBuffer::get_nativeFrame() noexcept
{
  return thisWeak_.lock();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::MediaSamplePtr wrapper::impl::org::webRtc::VideoFrameNativeBuffer::get_sample() noexcept
{
  if (!native_)
    return {};

  winrt::com_ptr<IMFSample> sample;

  auto *nativeHandleBuffer = reinterpret_cast<::webrtc::NativeHandleBuffer *>(native_.get());
  if (!nativeHandleBuffer)
    return {};

  IMFSample *rawSample = reinterpret_cast<IMFSample *>(nativeHandleBuffer->native_handle());
  sample.copy_from(rawSample);

  return UseMediaSample::toWrapper(sample);
}

//------------------------------------------------------------------------------
NativeNativeHandleBufferTypeScopedRefPtr WrapperImplType::toNative(WrapperTypePtr wrapper) noexcept
{
  if (!wrapper)
    return {};
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, wrapper);
  if (!converted)
    return {};
  return converted->native_;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeNativeHandleBufferType *native) noexcept
{
  if (!native)
    return {};

  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = NativeNativeHandleBufferTypeScopedRefPtr(native);
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeNativeHandleBufferTypeScopedRefPtr native) noexcept
{
  if (!native)
    return {};
  return toWrapper(native.get());
}
