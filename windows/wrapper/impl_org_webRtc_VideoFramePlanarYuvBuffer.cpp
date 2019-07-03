
#include "impl_org_webRtc_VideoFramePlanarYuvBuffer.h"
#include "impl_org_webRtc_VideoFramePlanarYuvaBuffer.h"
#include "impl_org_webRtc_VideoData.h"
#include "impl_org_webRtc_VideoFrameBuffer.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer, UseVideoFramePlanarYuvaBuffer);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoData, UseVideoData);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::VideoFramePlanarYuvBuffer() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr wrapper::org::webRtc::VideoFramePlanarYuvBuffer::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::~VideoFramePlanarYuvBuffer() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::wrapper_dispose() noexcept
{
  native_ = nullptr;
  nativeYuv_ = nullptr;
  nativeYuv8_ = nullptr;
  nativeYuv16_ = nullptr;

  nativeI420_ = {};
  nativeI420A_ = {};
  nativeI444_ = {};
  nativeI010_ = {};
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::toI420() noexcept
{
  if (!native_)
    return {};

  auto i420Frame = native_->ToI420();
  return toWrapper(i420Frame);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr WrapperImplType::toARGB() noexcept
{
  return UseVideoFrameBuffer::toARGB(native_);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr WrapperImplType::toBGRA() noexcept
{
  return UseVideoFrameBuffer::toBGRA(native_);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr WrapperImplType::toABGR() noexcept
{
  return UseVideoFrameBuffer::toABGR(native_);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr WrapperImplType::toRGBA() noexcept
{
  return UseVideoFrameBuffer::toRGBA(native_);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr WrapperImplType::toRGB24() noexcept
{
  return UseVideoFrameBuffer::toRGB24(native_);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFrameBufferType wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_type() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return wrapper::org::webRtc::VideoFrameBufferType::VideoFrameBufferType_native;
  return UseEnum::toWrapper(native_->type());
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_width() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return native_->width();
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_height() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return native_->height();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_yuvFrame() noexcept
{
  return thisWeak_.lock();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvaBufferPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_yuvaFrame() noexcept
{
  return UseVideoFramePlanarYuvaBuffer::toWrapper(nativeI420A_);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFrameNativeBufferPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_nativeFrame() noexcept
{
  return {};
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_chromaWidth() noexcept
{
  ZS_ASSERT(nativeYuv_);
  if (!nativeYuv_)
    return {};
  return nativeYuv_->ChromaWidth();
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_chromaHeight() noexcept
{
  ZS_ASSERT(nativeYuv_);
  if (!nativeYuv_)
    return {};
  return nativeYuv_->ChromaHeight();
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_strideY() noexcept
{
  ZS_ASSERT(nativeYuv_);
  if (!nativeYuv_)
    return {};
  return nativeYuv_->StrideY();
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_strideU() noexcept
{
  ZS_ASSERT(nativeYuv_);
  if (!nativeYuv_)
    return {};
  return nativeYuv_->StrideU();
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_strideV() noexcept
{
  ZS_ASSERT(nativeYuv_);
  if (!nativeYuv_)
    return {};
  return nativeYuv_->StrideV();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_y() noexcept
{
  if (nativeYuv8_) {
    ZS_ASSERT(native_);
    ZS_ASSERT(nativeYuv_);
    return UseVideoData::toWrapper(native_, nativeYuv8_->DataY(), nativeYuv_->StrideY() * nativeYuv_->height());
  } else if (nativeYuv16_) {
    ZS_ASSERT(native_);
    ZS_ASSERT(nativeYuv_);
    return UseVideoData::toWrapper(native_, nativeYuv16_->DataY(), nativeYuv_->StrideY() * nativeYuv_->height());
  }
  ZS_ASSERT_FAIL("native pointer is gone");
  return {};
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_u() noexcept
{
  if (nativeYuv8_) {
    ZS_ASSERT(native_);
    ZS_ASSERT(nativeYuv_);
    return UseVideoData::toWrapper(native_, nativeYuv8_->DataU(), nativeYuv_->StrideU() * ((nativeYuv_->height()+1)/2));
  }
  else if (nativeYuv16_) {
    ZS_ASSERT(native_);
    ZS_ASSERT(nativeYuv_);
    return UseVideoData::toWrapper(native_, nativeYuv16_->DataU(), nativeYuv_->StrideU() * ((nativeYuv_->height() + 1) / 2));
  }
  ZS_ASSERT_FAIL("native pointer is gone");
  return {};
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer::get_v() noexcept
{
  if (nativeYuv8_) {
    ZS_ASSERT(native_);
    ZS_ASSERT(nativeYuv_);
    return UseVideoData::toWrapper(native_, nativeYuv8_->DataV(), nativeYuv_->StrideV() * ((nativeYuv_->height() + 1) / 2));
  }
  else if (nativeYuv16_) {
    ZS_ASSERT(native_);
    ZS_ASSERT(nativeYuv_);
    return UseVideoData::toWrapper(native_, nativeYuv16_->DataV(), nativeYuv_->StrideV() * ((nativeYuv_->height() + 1) / 2));
  }
  ZS_ASSERT_FAIL("native pointer is gone");
  return {};
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeI420Type *native) noexcept
{
  if (!native)
    return {};
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = native;
  result->nativeYuv_ = native;
  result->nativeYuv8_ = native;
  result->nativeI420_ = NativeI420TypeScopedRefPtr(native);
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeI420TypeScopedRefPtr native) noexcept
{
  if (!native)
    return {};
  return toWrapper(native.get());
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeI420AType *native) noexcept
{
  if (!native)
    return {};
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = native;
  result->nativeYuv_ = native;
  result->nativeYuv8_ = native;
  result->nativeI420_ = NativeI420TypeScopedRefPtr(native);
  result->nativeI420A_ = NativeI420ATypeScopedRefPtr(native);
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeI420ATypeScopedRefPtr native) noexcept
{
  if (!native)
    return {};
  return toWrapper(native.get());
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeI444Type *native) noexcept
{
  if (!native)
    return {};
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = native;
  result->nativeYuv_ = native;
  result->nativeYuv8_ = native;
  result->nativeI444_ = NativeI444TypeScopedRefPtr(native);
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeI444TypeScopedRefPtr native) noexcept
{
  if (!native)
    return {};
  return toWrapper(native.get());
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeI010Type *native) noexcept
{
  if (!native)
    return {};
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = native;
  result->nativeYuv_ = native;
  result->nativeYuv16_ = native;
  result->nativeI010_ = NativeI010TypeScopedRefPtr(native);
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeI010TypeScopedRefPtr native) noexcept
{
  if (!native)
    return {};
  return toWrapper(native.get());
}
