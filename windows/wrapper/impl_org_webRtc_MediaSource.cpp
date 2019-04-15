
#ifdef __has_include
#if __has_include(<winrt/Windows.Media.Core.h>)
#include <winrt/Windows.Media.Core.h>
#endif //__has_include(<winrt/Windows.Media.Core.h>)
#endif //__has_include

#include "impl_org_webRtc_MediaSource.h"
#include "impl_org_webRtc_helpers.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::MediaSource::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);


//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::MediaSource::MediaSource() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::MediaSourcePtr wrapper::org::webRtc::MediaSource::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::MediaSource>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::MediaSource::~MediaSource() noexcept
{
  thisWeak_.reset();
}


#ifdef CPPWINRT_VERSION

//------------------------------------------------------------------------------
WrapperImplTypePtr wrapper::impl::org::webRtc::MediaSource::toWrapper(winrt::Windows::Media::Core::IMediaSource const & source) noexcept
{
  if (!source)
    return {};

  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->source_ = source;
  return result;
}

//------------------------------------------------------------------------------
winrt::Windows::Media::Core::IMediaSource wrapper::impl::org::webRtc::MediaSource::toNative_winrt(wrapper::org::webRtc::MediaSourcePtr source) noexcept
{
  if (!source)
    return {nullptr};

  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, source);
  if (!converted)
    return {nullptr};

  return converted->source_;
}

#endif // CPPWINRT_VERSION
