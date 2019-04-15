
#pragma once

#include "types.h"
#include "generated/org_webRtc_MediaSource.h"

#ifdef CPPWINRT_VERSION
#include <winrt/Windows.Media.Core.h>
#endif // CPPWINRT_VERSION

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct MediaSource : public wrapper::org::webRtc::MediaSource
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::MediaSource, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::MediaSource, WrapperImplType);

          MediaSourceWeakPtr thisWeak_;
#ifdef CPPWINRT_VERSION
          winrt::Windows::Media::Core::IMediaSource source_ {nullptr};
#endif // CPPWINRT_VERSION

          MediaSource() noexcept;
          virtual ~MediaSource() noexcept;


          // methods MediaSource

#ifdef CPPWINRT_VERSION
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(winrt::Windows::Media::Core::IMediaSource const & source) noexcept;
          ZS_NO_DISCARD() static winrt::Windows::Media::Core::IMediaSource toNative_winrt(wrapper::org::webRtc::MediaSourcePtr source) noexcept;
#endif // CPPWINRT_VERSION

        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

