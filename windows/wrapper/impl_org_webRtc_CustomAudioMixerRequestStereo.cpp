
#include "impl_org_webRtc_CustomAudioMixerRequestStereo.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioMixerRequestStereo::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioMixerRequestStereo::CustomAudioMixerRequestStereo() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioMixerRequestStereoPtr wrapper::org::webRtc::CustomAudioMixerRequestStereo::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomAudioMixerRequestStereo>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioMixerRequestStereo::~CustomAudioMixerRequestStereo() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioMixerRequestStereo::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioMixerRequestStereo::get_isSpeaker() noexcept
{
  bool result {};
  return result;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioMixerRequestStereo::get_isMicrophone() noexcept
{
  bool result {};
  return result;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioMixerRequestStereo::get_stereo() noexcept
{
  bool result {};
  return result;
}


