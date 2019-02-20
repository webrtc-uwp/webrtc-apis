
#pragma once

#include "types.h"
#include "generated/org_webRtc_MediaSample.h"

#ifdef WINUWP
#ifdef __cplusplus_winrt
#include <wrl.h>
#include <mfidl.h>
#endif //__cplusplus_winrt
#ifdef CPPWINRT_VERSION
#include <mfidl.h>
#endif // CPPWINRT_VERSION
#else
#ifdef _WIN32
#include <mfidl.h>
#endif //_WIN32
#endif // WINUWP

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct MediaSample : public wrapper::org::webRtc::MediaSample
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::MediaSample, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::MediaSample, WrapperImplType);

          AnyPtr sample_{};
          MediaSampleWeakPtr thisWeak_;

          MediaSample() noexcept;
          virtual ~MediaSample() noexcept;


          // methods MediaSample
          void wrapper_init_org_webRtc_MediaSample(AnyPtr sample) noexcept override;

          // properties MediaSample
          AnyPtr get_sample() noexcept override;

#ifdef WINUWP
#ifdef __cplusplus_winrt
          ZS_NO_DISCARD() static wrapper::org::webRtc::MediaSamplePtr toWrapper(Microsoft::WRL::ComPtr<IMFSample> sample) noexcept;
          ZS_NO_DISCARD() static Microsoft::WRL::ComPtr<IMFSample> toNative_cx(wrapper::org::webRtc::MediaSamplePtr sample) noexcept;
#endif //__cplusplus_winrt
#ifdef CPPWINRT_VERSION
          ZS_NO_DISCARD() static wrapper::org::webRtc::MediaSamplePtr toWrapper(winrt::com_ptr<IMFSample> const & sample) noexcept;
          ZS_NO_DISCARD() static winrt::com_ptr<IMFSample> toNative_winrt(wrapper::org::webRtc::MediaSamplePtr sample) noexcept;
#endif // CPPWINRT_VERSION
#else
#ifdef _WIN32
          ZS_NO_DISCARD() static wrapper::org::webRtc::MediaSamplePtr toWrapper(IMFSample* sample) noexcept;
          ZS_NO_DISCARD() static IMFSample* toNative(wrapper::org::webRtc::MediaSamplePtr sample) noexcept;
#endif //_WIN32
#endif //WINUWP

        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

