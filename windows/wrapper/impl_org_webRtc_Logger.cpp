
#include "impl_org_webRtc_Logger.h"
#include "impl_org_webRtc_enums.h"

#include <zsLib/Log.h>

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

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

// borrow definitions from class
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::Logger::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::Logger::~Logger() noexcept
{
}

//------------------------------------------------------------------------------
void wrapper::org::webRtc::Logger::setLogLevel(
  wrapper::org::webRtc::Component component,
  wrapper::org::webRtc::Level level
  ) noexcept
{
  zsLib::Log::setOutputLevelByName(UseEnum::toNative(component), UseEnum::toNative(level));
}

//------------------------------------------------------------------------------
void wrapper::org::webRtc::Logger::setLogLevel(
  String component,
  wrapper::org::webRtc::Level level
  ) noexcept
{
  zsLib::Log::setOutputLevelByName(component, UseEnum::toNative(level));
}

//------------------------------------------------------------------------------
void wrapper::org::webRtc::Logger::setDefaultEventingLevel(
  wrapper::org::webRtc::Component component,
  wrapper::org::webRtc::Level level
  ) noexcept
{
  zsLib::Log::setDefaultEventingLevelByName(UseEnum::toNative(component), UseEnum::toNative(level));
}

//------------------------------------------------------------------------------
void wrapper::org::webRtc::Logger::setDefaultEventingLevel(
  String component,
  wrapper::org::webRtc::Level level
  ) noexcept
{
  zsLib::Log::setDefaultEventingLevelByName(component, UseEnum::toNative(level));
}

//------------------------------------------------------------------------------
void wrapper::org::webRtc::Logger::setEventingLevel(
  wrapper::org::webRtc::Component component,
  wrapper::org::webRtc::Level level
  ) noexcept
{
  zsLib::Log::setEventingLevelByName(UseEnum::toNative(component), UseEnum::toNative(level));
}

//------------------------------------------------------------------------------
void wrapper::org::webRtc::Logger::setEventingLevel(
  String component,
  wrapper::org::webRtc::Level level
  ) noexcept
{
  zsLib::Log::setEventingLevelByName(component, UseEnum::toNative(level));
}


