
#pragma once

#include "types.h"
#include "generated/org_webRtc_MediaStream.h"

#include "impl_org_webRtc_pre_include.h"
#include "rtc_base/scoped_ref_ptr.h"
#include "api/mediastreaminterface.h"
#include "impl_org_webRtc_post_include.h"

#include <zsLib/IMessageQueue.h>

#include <set>

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct MediaStream : public wrapper::org::webRtc::MediaStream
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::MediaStream, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::MediaStream, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::MediaStreamInterface, NativeType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::WebRtcFactory, UseWebRtcFactory);

          typedef rtc::scoped_refptr<NativeType> NativeTypeScopedPtr;

          rtc::scoped_refptr<NativeType> native_;

          mutable zsLib::Lock lock_;

          MediaStreamWeakPtr thisWeak_;

          MediaStream() noexcept;
          virtual ~MediaStream() noexcept;
          void wrapper_dispose() noexcept override;

          // MediaStream
          String get_id() noexcept override;
          shared_ptr< list< wrapper::org::webRtc::MediaStreamTrackPtr > > getAudioTracks() noexcept override;
          shared_ptr< list< wrapper::org::webRtc::MediaStreamTrackPtr > > getVideoTracks() noexcept override;
          bool addTrack(ZS_MAYBE_USED() wrapper::org::webRtc::MediaStreamTrackPtr track) noexcept override;
          bool removeTrack(ZS_MAYBE_USED() wrapper::org::webRtc::MediaStreamTrackPtr track) noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeType *native) noexcept;
          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(NativeTypeScopedPtr native) noexcept;

          ZS_NO_DISCARD() static NativeTypeScopedPtr toNative(WrapperTypePtr wrapper) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

