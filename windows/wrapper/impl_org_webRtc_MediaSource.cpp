
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


#ifdef CPPWINRT_VERSION

namespace wrapper { namespace impl { namespace org { namespace webRtc {
        ZS_DECLARE_STRUCT_PTR(MediaSourceWrapperAnyWinrt);

        struct MediaSourceWrapperAnyWinrt : Any
        {
          winrt::Windows::Media::Core::IMediaSource source_ {nullptr};
        };
} } } }

#endif // CPPWINRT_VERSION

#ifndef WINUWP
#ifdef _WIN32

namespace wrapper { namespace impl { namespace org { namespace webRtc {
        ZS_DECLARE_STRUCT_PTR(MediaSourceWrapperAny);

        struct MediaSourceWrapperAny : Any
        {
          HWND source_ {};
        };
} } } }

#endif //_WIN32
#endif //ndef WINUWP

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

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::MediaSource::wrapper_init_org_webRtc_MediaSource(AnyPtr source) noexcept
{
  ZS_ASSERT(source);
  source_ = source;
}

//------------------------------------------------------------------------------
AnyPtr wrapper::impl::org::webRtc::MediaSource::get_source() noexcept
{
  return source_;
}


#ifdef CPPWINRT_VERSION

WrapperImplTypePtr wrapper::impl::org::webRtc::MediaSource::toWrapper(winrt::Windows::Media::Core::IMediaSource const & source) noexcept
{
  auto any{ make_shared<wrapper::impl::org::webRtc::MediaSourceWrapperAnyWinrt>() };
  any->source_ = source;
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->source_ = any;
  return result;
}

winrt::Windows::Media::Core::IMediaSource wrapper::impl::org::webRtc::MediaSource::toNative_winrt(wrapper::org::webRtc::MediaSourcePtr source) noexcept
{
  if (!source) return nullptr;
  AnyPtr any = source->get_source();
  if (!any) return nullptr;
  auto castedAny = ZS_DYNAMIC_PTR_CAST(wrapper::impl::org::webRtc::MediaSourceWrapperAnyWinrt, any);
  if (!castedAny) {
    return nullptr;
  }
  return castedAny->source_;
}

#endif // CPPWINRT_VERSION
