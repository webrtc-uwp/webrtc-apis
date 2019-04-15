
#ifdef __has_include
#if __has_include(<winrt/Windows.UI.Xaml.Controls.h>)
#include <winrt/Windows.UI.Xaml.Controls.h>
#endif //__has_include(<winrt/Windows.UI.Xaml.Controls.h>)
#endif //__has_include

#ifndef WINUWP
#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#endif //_WIN32
#endif //ndef WINUWP

#include "impl_org_webRtc_MediaElement.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::MediaElement::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::MediaElement::MediaElement() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::MediaElementPtr wrapper::org::webRtc::MediaElement::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::MediaElement>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::MediaElement::~MediaElement() noexcept
{
  thisWeak_.reset();
}


#ifdef CPPWINRT_VERSION

wrapper::org::webRtc::MediaElementPtr wrapper::impl::org::webRtc::MediaElement::toWrapper(winrt::Windows::UI::Xaml::Controls::MediaElement const & element) noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->elementXaml_ = element;
  return result;
}

winrt::Windows::UI::Xaml::Controls::MediaElement wrapper::impl::org::webRtc::MediaElement::toNative_winrt(wrapper::org::webRtc::MediaElementPtr wrapper) noexcept
{
  if (!wrapper) return {nullptr};
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, wrapper);
  ZS_ASSERT(converted);
  if (!converted) return {nullptr};
  return converted->elementXaml_;
}

#endif // CPPWINRT_VERSION

#ifndef WINUWP
#ifdef _WIN32

wrapper::org::webRtc::MediaElementPtr wrapper::impl::org::webRtc::MediaElement::toWrapper(HWND element) noexcept
{
  if (NULL == element) return {};
  auto result = std::make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->elementHwnd_ = element;
  return result;
}

HWND wrapper::impl::org::webRtc::MediaElement::toNative(wrapper::org::webRtc::MediaElementPtr wrapper) noexcept
{
  if (!wrapper) return {};
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, wrapper);
  ZS_ASSERT(converted);
  if (!converted) return {};
  return converted->elementHwnd_;
}

#endif //_WIN32
#endif //ndef WINUWP

