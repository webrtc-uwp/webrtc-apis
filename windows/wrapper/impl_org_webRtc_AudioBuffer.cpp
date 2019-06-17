
#include "impl_org_webRtc_AudioBuffer.h"
#include "impl_org_webRtc_AudioBufferConfiguration.h"
#include "impl_org_webRtc_AudioData.h"
#include "impl_org_webRtc_AudioFrame.h"
#include "impl_org_webRtc_enums.h"

#include "impl_org_webRtc_pre_include.h"
#include "modules/audio_processing/audio_buffer.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioBuffer::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioData, UseAudioData);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioFrame, UseAudioFrame);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::AudioBuffer::AudioBuffer() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioBufferPtr wrapper::org::webRtc::AudioBuffer::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::AudioBuffer>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::AudioBuffer::~AudioBuffer() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioBuffer::wrapper_dispose() noexcept
{
  zsLib::AutoLock lock(lock_);
  native_ = {};
  nativeStorage_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioBuffer::wrapper_init_org_webRtc_AudioBuffer(wrapper::org::webRtc::AudioBufferConfigurationPtr config) noexcept
{
  nativeStorage_ = std::make_unique<NativeType>(
    SafeInt<size_t>(config->inputSamplesPerChannel),
    SafeInt<size_t>(config->inputChannels),
    SafeInt<size_t>(config->procesSamplesPerChannel),
    SafeInt<size_t>(config->processChannels),
    SafeInt<size_t>(config->outputChannels));
  native_ = nativeStorage_.get();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioDataPtr wrapper::impl::org::webRtc::AudioBuffer::channel(uint64_t channel) noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return UseAudioData::toWrapper(native_->channels()[channel], native_->num_frames());
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioDataPtr wrapper::impl::org::webRtc::AudioBuffer::splitBand(
  uint64_t channel,
  wrapper::org::webRtc::Band band
  ) noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return UseAudioData::toWrapper(native_->split_bands(SafeInt<size_t>(channel))[UseEnum::toNative(band)], native_->num_frames_per_band());
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioDataPtr wrapper::impl::org::webRtc::AudioBuffer::splitChannel(
  wrapper::org::webRtc::Band band,
  uint64_t channel
  ) noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return UseAudioData::toWrapper(native_->split_channels(UseEnum::toNative(band))[channel], native_->num_frames_per_band());
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioDataPtr wrapper::impl::org::webRtc::AudioBuffer::lowPassReference(uint64_t channel) noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return UseAudioData::toWrapper(native_->low_pass_reference(SafeInt<int>(channel)), native_->num_frames_per_band());
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioBuffer::deinterleaveFrom(wrapper::org::webRtc::AudioFramePtr frame) noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return;

  auto nativeFrame = UseAudioFrame::toNative(frame);
  if (!nativeFrame)
    return;
  native_->DeinterleaveFrom(nativeFrame.get());
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioBuffer::interleaveTo(wrapper::org::webRtc::AudioFramePtr frame) noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return;

  auto nativeFrame = UseAudioFrame::toNative(frame);
  if (!nativeFrame)
    return;
  native_->InterleaveTo(nativeFrame.get(), true);
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioBuffer::copyLowPassToReference() noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return;
  native_->CopyLowPassToReference();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioBuffer::splitIntoFrequencyBands() noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return;
  native_->SplitIntoFrequencyBands();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioBuffer::mergeFrequencyBands() noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return;
  native_->MergeFrequencyBands();
}

//------------------------------------------------------------------------------
uint64_t wrapper::impl::org::webRtc::AudioBuffer::get_channels() noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return SafeInt<uint64_t>(native_->num_channels());
}

//------------------------------------------------------------------------------
uint64_t wrapper::impl::org::webRtc::AudioBuffer::get_samplesPerChannel() noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return SafeInt<uint64_t>(native_->num_frames());
}

//------------------------------------------------------------------------------
uint64_t wrapper::impl::org::webRtc::AudioBuffer::get_bands() noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return SafeInt<uint64_t>(native_->num_bands());
}

//------------------------------------------------------------------------------
uint64_t wrapper::impl::org::webRtc::AudioBuffer::get_framesPerBand() noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return SafeInt<uint64_t>(native_->num_frames_per_band());
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioDataPtr wrapper::impl::org::webRtc::AudioBuffer::get_mixedLowPassData() noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return UseAudioData::toWrapper(native_->mixed_low_pass_data(), native_->num_frames_per_band());
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VadActivity wrapper::impl::org::webRtc::AudioBuffer::get_activity() noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return {};
  return UseEnum::toWrapper(native_->activity());
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioBuffer::set_activity(wrapper::org::webRtc::VadActivity value) noexcept
{
  zsLib::AutoLock lock(lock_);
  ZS_ASSERT(native_);
  if (!native_)
    return;
  native_->set_activity(UseEnum::toNative(value));
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeType *native) noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = native;
  return result;
}

//------------------------------------------------------------------------------
NativeType *WrapperImplType::toNative(WrapperTypePtr wrapper) noexcept
{
  if (!wrapper)
    return {};
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, wrapper);
  if (!converted)
    return {};

  zsLib::AutoLock lock(converted->lock_);
  return converted->native_;
}
