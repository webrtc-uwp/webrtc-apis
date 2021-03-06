
#include "impl_org_webRtc_VideoFrameBuffer.h"
#include "impl_org_webRtc_VideoFramePlanarYuvBuffer.h"
#include "impl_org_webRtc_VideoFramePlanarYuvaBuffer.h"
#include "impl_org_webRtc_VideoFrameNativeBuffer.h"
#include "impl_org_webRtc_VideoData.h"
#include "impl_org_webRtc_enums.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/video/video_frame_buffer.h"
#include "impl_org_webRtc_post_include.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFrameBuffer::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFramePlanarYuvBuffer, UseVideoFramePlanarYuvBuffer);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFramePlanarYuvaBuffer, UseVideoFramePlanarYuvaBuffer);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoFrameNativeBuffer, UseVideoFrameNativeBuffer);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoFrameBuffer::VideoFrameBuffer() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFrameBufferPtr wrapper::org::webRtc::VideoFrameBuffer::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::VideoFrameBuffer>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoFrameBuffer::~VideoFrameBuffer() noexcept
{
  thisWeak_.reset();
  wrapper_dispose();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoFrameBuffer::wrapper_dispose() noexcept
{
  native_ = NativeTypeScopedRefPtr();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr wrapper::impl::org::webRtc::VideoFrameBuffer::toI420() noexcept
{
  if (!native_)
    return {};

  auto i420Frame = native_->ToI420();
  return UseVideoFramePlanarYuvBuffer::toWrapper(i420Frame);
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFrameBufferType wrapper::impl::org::webRtc::VideoFrameBuffer::get_type() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return wrapper::org::webRtc::VideoFrameBufferType::VideoFrameBufferType_Native;
  return UseEnum::toWrapper(native_->type());
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFrameBuffer::get_width() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};

  return native_->width();
}

//------------------------------------------------------------------------------
int wrapper::impl::org::webRtc::VideoFrameBuffer::get_height() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};

  return native_->height();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvBufferPtr wrapper::impl::org::webRtc::VideoFrameBuffer::get_yuvFrame() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};

  switch (native_->type())
  {
    case ::webrtc::VideoFrameBuffer::Type::kNative: return {};
    case ::webrtc::VideoFrameBuffer::Type::kI420:   return UseVideoFramePlanarYuvBuffer::toWrapper(native_->GetI420());
    case ::webrtc::VideoFrameBuffer::Type::kI420A:  return UseVideoFramePlanarYuvBuffer::toWrapper(native_->GetI420A());
    case ::webrtc::VideoFrameBuffer::Type::kI444:   return UseVideoFramePlanarYuvBuffer::toWrapper(native_->GetI444());
    case ::webrtc::VideoFrameBuffer::Type::kI010:   return UseVideoFramePlanarYuvBuffer::toWrapper(native_->GetI010());
  }

  return {};
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFramePlanarYuvaBufferPtr wrapper::impl::org::webRtc::VideoFrameBuffer::get_yuvaFrame() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};

  switch (native_->type())
  {
    case ::webrtc::VideoFrameBuffer::Type::kNative: return {};
    case ::webrtc::VideoFrameBuffer::Type::kI420:   return {};
    case ::webrtc::VideoFrameBuffer::Type::kI420A:  return UseVideoFramePlanarYuvaBuffer::toWrapper(native_->GetI420A());
    case ::webrtc::VideoFrameBuffer::Type::kI444:   return {};
    case ::webrtc::VideoFrameBuffer::Type::kI010:   return {};
  }

  return {};
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFrameNativeBufferPtr wrapper::impl::org::webRtc::VideoFrameBuffer::get_nativeFrame() noexcept
{
  ZS_ASSERT(native_);
  if (!native_)
    return {};

  switch (native_->type())
  {
    case ::webrtc::VideoFrameBuffer::Type::kNative: return UseVideoFrameNativeBuffer::toWrapper(reinterpret_cast<::webrtc::NativeHandleBuffer *>(native_.get()));
    case ::webrtc::VideoFrameBuffer::Type::kI420:   return {};
    case ::webrtc::VideoFrameBuffer::Type::kI420A:  return {};
    case ::webrtc::VideoFrameBuffer::Type::kI444:   return {};
    case ::webrtc::VideoFrameBuffer::Type::kI010:   return {};
  }

  return {};
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeType *native) noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = NativeTypeScopedRefPtr(native);
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeTypeScopedRefPtr native) noexcept
{
  if (!native)
    return {};
  return toWrapper(native.get());
}
