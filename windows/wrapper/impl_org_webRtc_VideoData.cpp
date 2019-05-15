
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
  allocatedRawBuffer8Bit_.reset();
  allocatedRawBuffer16Bit_.reset();
  buffer8bit_ = nullptr;
  buffer16bit_ = nullptr;
  creationSize_ = size_ = 0;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoData::wrapper_init_org_webRtc_VideoData(size_t size) noexcept
{
  wrapper_dispose();
  creationSize_ = size;
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
  prepareCreation(PrepareMode::mode8Bit);
  return buffer8bit_;
}

//------------------------------------------------------------------------------
const uint16_t * wrapper::impl::org::webRtc::VideoData::get_data16bit() noexcept
{
  prepareCreation(PrepareMode::mode16Bit);
  return buffer16bit_;
}

//------------------------------------------------------------------------------
uint8_t *wrapper::impl::org::webRtc::VideoData::get_mutableData8bit() noexcept
{
  prepareCreation(PrepareMode::mode8Bit);
  return allocatedRawBuffer8Bit_.get();
}

//------------------------------------------------------------------------------
uint16_t *wrapper::impl::org::webRtc::VideoData::get_mutableData16bit() noexcept
{
  prepareCreation(PrepareMode::mode16Bit);
  return allocatedRawBuffer16Bit_.get();
}

//------------------------------------------------------------------------------
size_t wrapper::impl::org::webRtc::VideoData::get_size() noexcept
{
  if (0 != creationSize_)
    return creationSize_;
  return size_;
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::VideoData::prepareCreation(PrepareMode mode) noexcept
{
  if (0 == creationSize_)
    return;

  size_ = creationSize_;
  creationSize_ = 0;

  switch (mode)
  {
    case PrepareMode::mode8Bit: {
      allocatedRawBuffer8Bit_ = std::unique_ptr<uint8_t>(new uint8_t[size_]);
      buffer8bit_ = allocatedRawBuffer8Bit_.get();
      break;
    }
    case PrepareMode::mode16Bit: {
      allocatedRawBuffer16Bit_ = std::unique_ptr<uint16_t>(new uint16_t[size_]);
      buffer16bit_ = allocatedRawBuffer16Bit_.get();
      break;
    }
  }
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

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(
  std::unique_ptr<uint8_t> allocatedRawBuffer,
  size_t size) noexcept
{
  if (!allocatedRawBuffer)
    return {};

  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->allocatedRawBuffer8Bit_ = std::move(allocatedRawBuffer);
  result->buffer8bit_ = result->allocatedRawBuffer8Bit_.get();
  result->size_ = size;
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(
  std::unique_ptr<uint16_t> allocatedRawBuffer,
  size_t size) noexcept
{
  if (!allocatedRawBuffer)
    return {};

  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->allocatedRawBuffer16Bit_ = std::move(allocatedRawBuffer);
  result->buffer16bit_ = result->allocatedRawBuffer16Bit_.get();
  result->size_ = size;
  return result;
}
