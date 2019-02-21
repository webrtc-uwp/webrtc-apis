
#include "impl_org_webRtc_AudioFrame.h"
#include "impl_org_webRtc_AudioData.h"
#include "impl_org_webRtc_enums.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/audio/audio_frame.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioFrame::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioData, UseAudioData);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::AudioFrame::AudioFrame() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioFramePtr wrapper::org::webRtc::AudioFrame::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::AudioFrame>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::AudioFrame::~AudioFrame() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioFrame::wrapper_init_org_webRtc_AudioFrame() noexcept
{
}

NativeTypeUniPtr WrapperImplType::toNative(WrapperTypePtr wrapper) noexcept
{
  auto result = std::make_unique<NativeType>();
  result->vad_activity_ = UseEnum::toNative(wrapper->activity);
  result->num_channels_ = SafeInt<decltype(result->num_channels_)>(wrapper->channels);
  result->samples_per_channel_ = SafeInt<decltype(result->samples_per_channel_)>(wrapper->samplesPerChannel);

  auto &data = wrapper->data;
  if (!data)
    return result;

  auto size = data->size();
  size_t maxSamples = SafeInt<size_t>(NativeType::kMaxDataSizeSamples);

  auto max = size > maxSamples ? maxSamples : size;
  
  auto mutableData = result->mutable_data();

  if (!mutableData)
    return result;

  memcpy(mutableData, data->data(), sizeof(*mutableData)*max);

  return result;
}
