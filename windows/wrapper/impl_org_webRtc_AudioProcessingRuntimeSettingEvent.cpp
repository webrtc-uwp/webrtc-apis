
#include "impl_org_webRtc_AudioProcessingRuntimeSettingEvent.h"
#include "impl_org_webRtc_enums.h"

#include "impl_org_webRtc_pre_include.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioProcessingRuntimeSettingEvent::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::AudioProcessingRuntimeSettingEvent::AudioProcessingRuntimeSettingEvent() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioProcessingRuntimeSettingEventPtr wrapper::org::webRtc::AudioProcessingRuntimeSettingEvent::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::AudioProcessingRuntimeSettingEvent>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::AudioProcessingRuntimeSettingEvent::~AudioProcessingRuntimeSettingEvent() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::AudioProcessingRuntimeSettingEvent::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RuntimeSetting wrapper::impl::org::webRtc::AudioProcessingRuntimeSettingEvent::get_type() noexcept
{
  return type_;
}

//------------------------------------------------------------------------------
float wrapper::impl::org::webRtc::AudioProcessingRuntimeSettingEvent::get_value() noexcept
{
  return value_;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(const NativeType &native) noexcept
{
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->type_ = UseEnum::toWrapper(native.type());
  float value{};
  native.GetFloat(&value);
  result->value_ = value;
  return result;
}
