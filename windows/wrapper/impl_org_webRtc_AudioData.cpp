
#include "impl_org_webRtc_AudioData.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioData::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::AudioData::AudioData() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioDataPtr wrapper::org::webRtc::AudioData::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::AudioData>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::AudioData::~AudioData() noexcept
{
  thisWeak_.reset();
  wrapper_dispose();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioData::wrapper_dispose() noexcept
{
  zsLib::AutoLock lock(lock_);
  mutableData_ = {};
  data_ = {};
  size_ = {};
  buffer_.clear();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioData::wrapper_init_org_webRtc_AudioData() noexcept
{
  wrapper_dispose();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioData::wrapper_init_org_webRtc_AudioData(size_t size) noexcept
{
  if (size < 1) {
    wrapper_dispose();
    return;
  }

  zsLib::AutoLock lock(lock_);
  buffer_.resize(size);
  mutableData_ = &(buffer_.front());
  data_ = mutableData_;
  size_ = size;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::AudioData::readOnly() noexcept
{
  zsLib::AutoLock lock(lock_);
  return ((!mutableData_) && (data_));
}

//------------------------------------------------------------------------------
const int16_t *wrapper::impl::org::webRtc::AudioData::data() noexcept
{
  zsLib::AutoLock lock(lock_);
  return data_;
}

//------------------------------------------------------------------------------
int16_t *wrapper::impl::org::webRtc::AudioData::mutableData() noexcept
{
  zsLib::AutoLock lock(lock_);
  return mutableData_;
}

//------------------------------------------------------------------------------
size_t wrapper::impl::org::webRtc::AudioData::size() noexcept
{
  zsLib::AutoLock lock(lock_);
  return size_;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(
  int16_t *value,
  size_t size) noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->mutableData_ = value;
  result->data_ = value;
  result->size_ = size;
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(
  const int16_t *value,
  size_t size) noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->data_ = value;
  result->size_ = size;
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(WrapperTypePtr wrapper) noexcept
{
  if (!wrapper)
    return {};

  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, wrapper);
  return converted;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(size_t sampleCount) noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->wrapper_init_org_webRtc_AudioData(sampleCount);
  return result;
}
