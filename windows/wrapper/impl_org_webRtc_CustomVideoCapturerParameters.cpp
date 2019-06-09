
#include "impl_org_webRtc_CustomVideoCapturerParameters.h"
#include "impl_org_webRtc_VideoCapturerInputSize.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomVideoCapturerParameters::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::VideoCapturerInputSize, UseVideoCapturerInputSize);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomVideoCapturerParameters::CustomVideoCapturerParameters() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::CustomVideoCapturerParametersPtr wrapper::org::webRtc::CustomVideoCapturerParameters::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::CustomVideoCapturerParameters>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::CustomVideoCapturerParameters::~CustomVideoCapturerParameters() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::CustomVideoCapturerParameters::wrapper_init_org_webRtc_CustomVideoCapturerParameters() noexcept
{
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::clone(const WrapperType &base) noexcept
{
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  ((WrapperType &)*result) = base;
  result->inputSize = UseVideoCapturerInputSize::clone(base.inputSize);
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::clone(const WrapperType *base) noexcept
{
  if (!base)
    return {};
  return clone(*base);
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::clone(WrapperTypePtr base) noexcept
{
  if (!base)
    return {};
  return clone(base.get());
}
