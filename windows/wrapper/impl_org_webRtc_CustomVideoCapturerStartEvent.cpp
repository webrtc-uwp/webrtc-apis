
#include "impl_org_webRtc_CustomVideoCapturerStartEvent.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturerStartEvent::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomVideoCapturerStartEvent::CustomVideoCapturerStartEvent() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomVideoCapturerStartEventPtr wrapper::org::webRtc::CustomVideoCapturerStartEvent::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomVideoCapturerStartEvent>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomVideoCapturerStartEvent::~CustomVideoCapturerStartEvent() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomVideoCapturerStartEvent::wrapper_dispose() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoFormatPtr wrapper::impl::org::webRtc::CustomVideoCapturerStartEvent::get_format() noexcept
{
  wrapper::org::webRtc::VideoFormatPtr result {};
  return result;
}


