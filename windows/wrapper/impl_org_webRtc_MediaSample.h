
#pragma once

#include "types.h"
#include "generated/org_webRtc_MediaSample.h"

#include <mfidl.h>

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct MediaSample : public wrapper::org::webRtc::MediaSample
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::MediaSample, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::MediaSample, WrapperImplType);

          MediaSampleWeakPtr thisWeak_;
          zsLib::Lock lock_;

#ifdef CPPWINRT_VERSION
          winrt::com_ptr<IMFSample> sample_;
#endif //CPPWINRT_VERSION

          MediaSample() noexcept;
          virtual ~MediaSample() noexcept;

          void wrapper_dispose() noexcept override;

#ifdef CPPWINRT_VERSION
          ZS_NO_DISCARD() static wrapper::org::webRtc::MediaSamplePtr toWrapper(winrt::com_ptr<IMFSample> const & sample) noexcept;
          ZS_NO_DISCARD() static winrt::com_ptr<IMFSample> toNative(wrapper::org::webRtc::MediaSamplePtr sample) noexcept;
#endif //CPPWINRT_VERSION

        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

