
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

#ifdef WINUWP
#ifdef CPPWINRT_VERSION
//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::MediaSample::wrapper_dispose() noexcept
{
  zsLib::AutoLock lock(lock_);
  sample_ = {};
}

wrapper::org::webRtc::MediaSamplePtr wrapper::impl::org::webRtc::MediaSample::toWrapper(winrt::com_ptr<IMFSample> const & sample) noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->sample_ = sample;
  return result;
}

winrt::com_ptr<IMFSample> wrapper::impl::org::webRtc::MediaSample::toNative(wrapper::org::webRtc::MediaSamplePtr sample) noexcept
{
  if (!sample)
    return {};
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, sample);
  if (!converted)
    return {};
  return converted->sample_;
}

#endif // CPPWINRT_VERSION
#endif //WINUWP

