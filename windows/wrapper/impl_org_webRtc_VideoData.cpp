
#include "impl_org_webRtc_VideoData.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/video/video_frame.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoData::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoData::VideoData() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr wrapper::org::webRtc::VideoData::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::VideoData>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::VideoData::~VideoData() noexcept
{
  thisWeak_.reset();
  wrapper_dispose();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoData::wrapper_dispose() noexcept
{
  native_ = NativeTypeScopedRefPtr();
  buffer8bit_ = nullptr;
  buffer16bit_ = nullptr;
  size_ = 0;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::VideoData::get_is8BitColorSpace() noexcept
{
  return nullptr != buffer8bit_;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::VideoData::get_is16BitColorSpace() noexcept
{
  return nullptr != buffer16bit_;
}

//------------------------------------------------------------------------------
const uint8_t * wrapper::impl::org::webRtc::VideoData::get_data8bit() noexcept
{
  return buffer8bit_;
}

//------------------------------------------------------------------------------
const uint16_t * wrapper::impl::org::webRtc::VideoData::get_data16bit() noexcept
{
  return buffer16bit_;
}


//------------------------------------------------------------------------------
size_t wrapper::impl::org::webRtc::VideoData::get_size() noexcept
{
  return size_;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(
  NativeType *native,
  const uint8_t *buffer,
  size_t size) noexcept
{
  if (!native)
    return {};
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = NativeTypeScopedRefPtr(native);
  result->buffer8bit_ = buffer;
  result->size_ = size;
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(
  NativeTypeScopedRefPtr native,
  const uint8_t *buffer,
  size_t size) noexcept
{
  if (!native)
    return {};
  return toWrapper(native.get(), buffer, size);
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(
  NativeType *native,
  const uint16_t *buffer,
  size_t size) noexcept
{
  if (!native)
    return {};
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = NativeTypeScopedRefPtr(native);
  result->buffer16bit_ = buffer;
  result->size_ = size;
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(
  NativeTypeScopedRefPtr native,
  const uint16_t *buffer,
  size_t size) noexcept
{
  if (!native)
    return {};
  return toWrapper(native.get(), buffer, size);
}
