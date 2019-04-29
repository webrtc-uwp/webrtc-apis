
#include "impl_org_webRtc_CustomAudioRecordingDeviceInfo.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioRecordingDeviceInfo::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioRecordingDeviceInfo::CustomAudioRecordingDeviceInfo() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomAudioRecordingDeviceInfoPtr wrapper::org::webRtc::CustomAudioRecordingDeviceInfo::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomAudioRecordingDeviceInfo>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomAudioRecordingDeviceInfo::~CustomAudioRecordingDeviceInfo() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomAudioRecordingDeviceInfo::wrapper_init_org_webRtc_CustomAudioRecordingDeviceInfo() noexcept
{
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::clone(WrapperTypePtr wrapper) noexcept
{
  if (!wrapper)
    return {};
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  ((WrapperType &)(*result)) = *wrapper;
  return result;
}
