

#include "impl_org_webRtc_MediaStream.h"

#include "impl_org_webRtc_helpers.h"
#include "impl_org_webRtc_WebRtcFactory.h"
#include "impl_org_webRtc_MediaStreamTrack.h"
#include "impl_org_webRtc_enums.h"

#include "impl_org_webRtc_pre_include.h"
#include "impl_org_webRtc_post_include.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::MediaStream::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::UseWebRtcFactory, UseWebRtcFactory);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::MediaStreamTrack, UseMediaStreamTrack);
ZS_DECLARE_TYPEDEF_PTR(::webrtc::AudioTrackInterface, AudioTrackNativeType);
ZS_DECLARE_TYPEDEF_PTR(::webrtc::VideoTrackInterface, VideoTrackNativeType);

typedef WrapperImplType::NativeTypeScopedPtr NativeTypeScopedPtr;

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::MediaStream::MediaStream() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::MediaStreamPtr wrapper::org::webRtc::MediaStream::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::MediaStream>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::MediaStream::~MediaStream() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::MediaStream::wrapper_dispose() noexcept
{
  if (!native_) return;

  native_ = NativeTypeScopedPtr();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::MediaStreamPtr wrapper::org::webRtc::MediaStream::createLocalMediaStream(
  String streamId,
  wrapper::org::webRtc::WebRtcFactoryPtr factory
  ) noexcept
{
  ZS_ASSERT(factory);
  if (!factory) return WrapperTypePtr();

  auto factoryImpl = UseWebRtcFactory::toWrapper(factory);
  ZS_ASSERT(factoryImpl);
  if (!factoryImpl) return WrapperTypePtr();

  auto peerConnectionFactory = factoryImpl->peerConnectionFactory();
  ZS_ASSERT(peerConnectionFactory);
  if (!peerConnectionFactory) return WrapperTypePtr();

  auto native = peerConnectionFactory->CreateLocalMediaStream(streamId);

  return WrapperImplType::toWrapper(native);
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::MediaStream::get_id() noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return String();
  return native_->id();
}

//------------------------------------------------------------------------------
shared_ptr< list< wrapper::org::webRtc::MediaStreamTrackPtr > > wrapper::impl::org::webRtc::MediaStream::getAudioTracks() noexcept
{
  auto result = make_shared< list< wrapper::org::webRtc::MediaStreamTrackPtr > >();
  ZS_ASSERT(native_);
  if (!native_) return result;

  auto values = native_->GetAudioTracks();
  for (auto iter = values.begin(); iter != values.end(); ++iter) {
    auto wrapper = UseMediaStreamTrack::toWrapper(*iter);
    if (!wrapper) continue;
    result->push_back(wrapper);
  }
  return result;
}

//------------------------------------------------------------------------------
shared_ptr< list< wrapper::org::webRtc::MediaStreamTrackPtr > > wrapper::impl::org::webRtc::MediaStream::getVideoTracks() noexcept
{
  auto result = make_shared< list< wrapper::org::webRtc::MediaStreamTrackPtr > >();
  ZS_ASSERT(native_);
  if (!native_) return result;

  auto values = native_->GetVideoTracks();
  for (auto iter = values.begin(); iter != values.end(); ++iter) {
    auto wrapper = UseMediaStreamTrack::toWrapper(*iter);
    if (!wrapper) continue;
    result->push_back(wrapper);
  }
  return result;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::MediaStream::addTrack(ZS_MAYBE_USED() wrapper::org::webRtc::MediaStreamTrackPtr track) noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return false;

  auto nativeTrack = UseMediaStreamTrack::toNative(track);
  if (!nativeTrack) {
    return false;
  }

  auto audioTrack = dynamic_cast<AudioTrackNativeType*>(nativeTrack.get());
  if (audioTrack)
    return native_->AddTrack(audioTrack);

  auto videoTrack = dynamic_cast<VideoTrackNativeType*>(nativeTrack.get());
  if (videoTrack)
    return native_->AddTrack(videoTrack);

  return false;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::MediaStream::removeTrack(ZS_MAYBE_USED() wrapper::org::webRtc::MediaStreamTrackPtr track) noexcept
{
  ZS_ASSERT(native_);
  if (!native_) return false;

  auto nativeTrack = UseMediaStreamTrack::toNative(track);
  if (!nativeTrack) {
    return false;
  }

  auto audioTrack = dynamic_cast<AudioTrackNativeType*>(nativeTrack.get());
  if (audioTrack)
    return native_->RemoveTrack(audioTrack);

  auto videoTrack = dynamic_cast<VideoTrackNativeType*>(nativeTrack.get());
  if (videoTrack)
    return native_->RemoveTrack(videoTrack);

  return false;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeType *native) noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = native;
  return result;
}

//------------------------------------------------------------------------------
WrapperImplTypePtr WrapperImplType::toWrapper(NativeTypeScopedPtr native) noexcept
{
  return toWrapper(native.get());
}

//------------------------------------------------------------------------------
NativeTypeScopedPtr WrapperImplType::toNative(WrapperTypePtr wrapper) noexcept
{
  if (!wrapper) return rtc::scoped_refptr<NativeType>();
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, wrapper);
  if (!converted) return rtc::scoped_refptr<NativeType>();
  return converted->native_;
}
