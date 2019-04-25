
#pragma once

#include "types.h"
#include "generated/org_webRtc_CustomAudioDeviceRequestStateEvent.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct CustomAudioDeviceRequestStateEvent : public wrapper::org::webRtc::CustomAudioDeviceRequestStateEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::CustomAudioDeviceRequestStateEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::CustomAudioDeviceRequestStateEvent, WrapperImplType);
          CustomAudioDeviceRequestStateEventWeakPtr thisWeak_;

          CustomAudioDeviceRequestStateEvent() noexcept;
          virtual ~CustomAudioDeviceRequestStateEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties CustomAudioDeviceRequestStateEvent
          bool get_isRecordingDevice() noexcept override;
          bool get_isPlayoutDevice() noexcept override;
          wrapper::org::webRtc::CustomAudioRequestState get_requestedState() noexcept override;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

