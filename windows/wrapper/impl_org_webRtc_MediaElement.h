
#pragma once

#include "types.h"
#include "generated/org_webRtc_MediaElement.h"

#ifdef CPPWINRT_VERSION
#include <winrt/Windows.UI.Xaml.Controls.h>
#endif // CPPWINRT_VERSION

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct MediaElement : public wrapper::org::webRtc::MediaElement
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::MediaElement, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::MediaElement, WrapperImplType);

          AnyPtr element_{};
          MediaElementWeakPtr thisWeak_;

#ifdef CPPWINRT_VERSION
          winrt::Windows::UI::Xaml::Controls::MediaElement elementXaml_ {nullptr};
#endif // CPPWINRT_VERSION

#ifndef WINUWP
#ifdef _WIN32
          HWND elementHwnd_{};
#endif //_WIN32
#endif //ndef WINUWP

          MediaElement() noexcept;
          virtual ~MediaElement() noexcept;

#ifdef CPPWINRT_VERSION
          ZS_NO_DISCARD() static wrapper::org::webRtc::MediaElementPtr toWrapper(winrt::Windows::UI::Xaml::Controls::MediaElement const & element) noexcept;
          ZS_NO_DISCARD() static winrt::Windows::UI::Xaml::Controls::MediaElement toNative_winrt(wrapper::org::webRtc::MediaElementPtr wrapper) noexcept;
#endif // CPPWINRT_VERSION

#ifndef WINUWP
#ifdef _WIN32
          ZS_NO_DISCARD() static wrapper::org::webRtc::MediaElementPtr toWrapper(HWND element) noexcept;
          ZS_NO_DISCARD() static HWND toNative(wrapper::org::webRtc::MediaElementPtr wrapper) noexcept;
#endif //_WIN32
#endif //ndef WINUWP

        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

