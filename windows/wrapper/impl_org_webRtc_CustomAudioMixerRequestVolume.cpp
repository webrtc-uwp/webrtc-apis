
#include "impl_org_webRtc_CustomAudioMixerRequestVolume.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioMixerRequestVolume::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioMixerRequestVolume::CustomAudioMixerRequestVolume() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioMixerRequestVolumePtr wrapper::org::webRtc::CustomAudioMixerRequestVolume::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomAudioMixerRequestVolume>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioMixerRequestVolume::~CustomAudioMixerRequestVolume() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioMixerRequestVolume::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioMixerRequestVolume::get_isSpeaker() noexcept
{
  bool result {};
  return result;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioMixerRequestVolume::get_isMicrophone() noexcept
{
  bool result {};
  return result;
}

//------------------------------------------------------------------------------
int32_t wrapper::impl::org::webRtc::CustomAudioMixerRequestVolume::get_requestedVolume() noexcept
{
  int32_t result {};
  return result;
}


