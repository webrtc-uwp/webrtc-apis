
#include "impl_org_webRtc_CustomAudioMixerRequestSettingsEvent.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioMixerRequestSettingsEvent::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioMixerRequestSettingsEvent::CustomAudioMixerRequestSettingsEvent() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioMixerRequestSettingsEventPtr wrapper::org::webRtc::CustomAudioMixerRequestSettingsEvent::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomAudioMixerRequestSettingsEvent>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioMixerRequestSettingsEvent::~CustomAudioMixerRequestSettingsEvent() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioMixerRequestSettingsEvent::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioMixerRequestSettingsEvent::get_isSpeaker() noexcept
{
  return isSpeaker_;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::CustomAudioMixerRequestSettingsEvent::get_isMicrophone() noexcept
{
  return isMicrophone_;
}

//------------------------------------------------------------------------------
Optional< bool > wrapper::impl::org::webRtc::CustomAudioMixerRequestSettingsEvent::get_enableBuiltInAec() noexcept
{
  return enableBuiltInAec_;
}

//------------------------------------------------------------------------------
Optional< bool > wrapper::impl::org::webRtc::CustomAudioMixerRequestSettingsEvent::get_enableBuiltInAgc() noexcept
{
  return enableBuiltInAgc_;
}

//------------------------------------------------------------------------------
Optional< bool > wrapper::impl::org::webRtc::CustomAudioMixerRequestSettingsEvent::get_enableBuiltInNs() noexcept
{
  return enableBuiltInNs_;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(
  bool isSpeaker,
  bool isMicrophone,
  const Optional< bool > &enableBuiltInAec,
  const Optional< bool > &enableBuiltInAgc,
  const Optional< bool > &enableBuiltInNs) noexcept
{
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->isSpeaker_ = isSpeaker;
  result->isMicrophone_ = isMicrophone;
  result->enableBuiltInAec_ = enableBuiltInAec;
  result->enableBuiltInAgc_ = enableBuiltInAgc;
  result->enableBuiltInNs_ = enableBuiltInNs;
  return result;
}
