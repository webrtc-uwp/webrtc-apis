
#include "impl_org_webRtc_VideoFramePlanarYuvaBuffer.h"
#include "impl_org_webRtc_VideoFramePlanarYuvBuffer.h"
#include "impl_org_webRtc_VideoData.h"
#include "impl_org_webRtc_enums.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/video/video_frame_buffer.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer, UseVideoFramePlanarYuvBuffer);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoData, UseVideoData);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::VideoFramePlanarYuvaBuffer() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvaBufferPtr wrapper::org::webRtc::VideoFramePlanarYuvaBuffer::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::~VideoFramePlanarYuvaBuffer() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::wrapper_dispose() noexcept
{
  native_ = {};
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::toI420() noexcept
{
  if (!native_)
    return {};

  auto i420Frame = native_->ToI420();
  return UseVideoFramePlanarYuvBuffer::toWrapper(i420Frame);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFrameBufferType wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_type() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return wrapper::org::webRtc::VideoFrameBufferType::VideoFrameBufferType_Native;
  return UseEnum::toWrapper(native_->type());
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_width() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return native_->width();
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_height() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return native_->height();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_yuvFrame() noexcept
{
  return thisWeak_.lock();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvaBufferPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_yuvaFrame() noexcept
{
  return thisWeak_.lock();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFrameNativeBufferPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_nativeFrame() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_chromaWidth() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return native_->ChromaWidth();
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_chromaHeight() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return native_->ChromaHeight();
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_strideY() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return native_->StrideY();
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_strideU() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return native_->StrideU();
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_strideV() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return native_->StrideY();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_y() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return UseVideoData::toWrapper(native_.get(), native_->DataY(), native_->StrideY() * native_->height());
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_u() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return UseVideoData::toWrapper(native_.get(), native_->DataU(), native_->StrideU() * ((native_->height() + 1) / 2));
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_v() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return UseVideoData::toWrapper(native_.get(), native_->DataV(), native_->StrideV() * ((native_->height() + 1) / 2));
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_strideA() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return native_->StrideA();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer::get_a() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return UseVideoData::toWrapper(native_.get(), native_->DataA(), native_->StrideA() * ((native_->height() + 1) / 2));
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeI420AType *native) noexcept
{
  if (!native)
    return {};
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = NativeI420ATypeScopedRefPtr(native);
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeI420ATypeScopedRefPtr native) noexcept
{
  if (!native)
    return {};
  return toWrapper(native.get());
}
