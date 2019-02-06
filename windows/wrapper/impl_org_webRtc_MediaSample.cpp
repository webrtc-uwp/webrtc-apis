
#ifdef WINUWP

#ifdef __cplusplus_winrt
#include <windows.ui.xaml.controls.h>
#endif //__cplusplus_winrt

#ifdef __has_include
#if __has_include(<winrt/base.h>)
#include <winrt/base.h>
#endif //__has_include(<winrt/base.h>)
#endif //__has_include

#else

#ifdef _WIN32
#include <Windows.h>
#endif //_WIN32

#endif //WINUWP

#include "impl_org_webRtc_MediaSample.h"
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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::MediaSample::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

#ifdef WINUWP
#ifdef __cplusplus_winrt

namespace wrapper { namespace impl { namespace org { namespace webRtc {
        ZS_DECLARE_STRUCT_PTR(MediaSampleWrapperAnyCx);

        struct MediaSampleWrapperAnyCx : Any
        {
          Microsoft::WRL::ComPtr<IMFSample> sample_ {};
        };
} } } }

#endif //__cplusplus_winrt

#ifdef CPPWINRT_VERSION

namespace wrapper { namespace impl { namespace org { namespace webRtc {
        ZS_DECLARE_STRUCT_PTR(MediaSampleWrapperAnyCx);

        struct MediaSampleWrapperAnyWinrt : Any
        {
          winrt::com_ptr<IMFSample> sample_ {};
        };
} } } }

#endif // CPPWINRT_VERSION

#else


namespace wrapper { namespace impl { namespace org { namespace webRtc {
        ZS_DECLARE_STRUCT_PTR(MediaSampleWrapperAny);

        struct MediaSampletWrapperAny : Any
        {
          IMFSample* sample_{};
        };
} } } }

#endif //WINUWP

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::MediaSample::MediaSample() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::MediaSamplePtr wrapper::org::webRtc::MediaSample::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::MediaSample>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::MediaSample::~MediaSample() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::MediaSample::wrapper_init_org_webRtc_MediaSample(AnyPtr sample) noexcept
{
  ZS_ASSERT(sample);
  sample_ = sample;
}

//------------------------------------------------------------------------------
AnyPtr wrapper::impl::org::webRtc::MediaSample::get_sample() noexcept
{
  return sample_;
}


#ifdef WINUWP
#ifdef __cplusplus_winrt

wrapper::org::webRtc::MediaSamplePtr wrapper::impl::org::webRtc::MediaSample::toWrapper(Microsoft::WRL::ComPtr<IMFSample> sample) noexcept
{
  auto any{ make_shared<wrapper::impl::org::webRtc::MediaSampleWrapperAnyCx>() };
  any->sample_ = sample;
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->sample_ = any;
  return result;
}

Microsoft::WRL::ComPtr<IMFSample> wrapper::impl::org::webRtc::MediaSample::toNative_cx(wrapper::org::webRtc::MediaSamplePtr sample) noexcept
{
  if (!sample) return nullptr;
  AnyPtr any = sample->get_sample();
  if (!any) return nullptr;
  auto castedAny = ZS_DYNAMIC_PTR_CAST(wrapper::impl::org::webRtc::MediaSampleWrapperAnyCx, any);
  if (!castedAny) {
#ifdef CPPWINRT_VERSION
    auto result = toNative_winrt(sample);
    if (result) return Microsoft::WRL::ComPtr<IMFSample>(result.get());
#endif //CPPWINRT_VERSION
    return nullptr;
  }
  return castedAny->sample_;
}
#endif //__cplusplus_winrt

#ifdef CPPWINRT_VERSION

wrapper::org::webRtc::MediaSamplePtr wrapper::impl::org::webRtc::MediaSample::toWrapper(winrt::com_ptr<IMFSample> const & sample) noexcept
{
  auto any{ make_shared<wrapper::impl::org::webRtc::MediaSampleWrapperAnyWinrt>() };
  any->sample_ = sample;
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->sample_ = any;
  return result;
}

winrt::com_ptr<IMFSample> wrapper::impl::org::webRtc::MediaSample::toNative_winrt(wrapper::org::webRtc::MediaSamplePtr sample) noexcept
{
  if (!sample) return nullptr;
  AnyPtr any = sample->get_sample();
  if (!any) return nullptr;
  auto castedAny = ZS_DYNAMIC_PTR_CAST(wrapper::impl::org::webRtc::MediaSampleWrapperAnyWinrt, any);
  if (!castedAny) {
#ifdef __cplusplus_winrt
    auto result = toNative_cx(sample);
    winrt::com_ptr<IMFSample> result_winrt;
    if (result) {
      result_winrt.attach(result.Get());
      return result_winrt;
    }
#endif //__cplusplus_winrt
    return nullptr;
  }
  return castedAny->sample_;
}

#endif // CPPWINRT_VERSION

#else

wrapper::org::webRtc::MediaSamplePtr wrapper::impl::org::webRtc::MediaSample::toWrapper(IMFSample* sample) noexcept
{
  auto any{ make_shared<wrapper::impl::org::webRtc::MediaSampleWrapperAny>() };
  any->sample_ = sample;
  auto result = wrapper::org::webRtc::MediaSample::wrapper_create();
  any->sample_ = sample;
  return result;
}

IMFSample* wrapper::impl::org::webRtc::MediaSample::toNative(wrapper::org::webRtc::MediaSamplePtr sample) noexcept
{
  if (!sample) return nullptr;
  AnyPtr any = sample->get_sample();
  if (!any) return nullptr;
  auto castedAny = ZS_DYNAMIC_PTR_CAST(wrapper::impl::org::webRtc::MediaSampleWrapperAny, any);
  if (!castedAny) return nullptr;
  return castedAny->sample_;
}

#endif //WINUWP

