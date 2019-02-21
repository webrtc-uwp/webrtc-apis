
#pragma once

#include "types.h"
#include "generated/org_webRtc_AudioProcessingRuntimeSettingEvent.h"

#include "impl_org_webRtc_pre_include.h"
#include "modules/audio_processing/include/audio_processing.h"
#include "impl_org_webRtc_post_include.h"

namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct AudioProcessingRuntimeSettingEvent : public wrapper::org::webRtc::AudioProcessingRuntimeSettingEvent
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::AudioProcessingRuntimeSettingEvent, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::AudioProcessingRuntimeSettingEvent, WrapperImplType);
          ZS_DECLARE_TYPEDEF_PTR(::webrtc::AudioProcessing::RuntimeSetting, NativeType);

          AudioProcessingRuntimeSettingEventWeakPtr thisWeak_;

          wrapper::org::webRtc::RuntimeSetting type_ {};
          float value_ {};

          AudioProcessingRuntimeSettingEvent() noexcept;
          virtual ~AudioProcessingRuntimeSettingEvent() noexcept;
          void wrapper_dispose() noexcept override;


          // properties AudioProcessingRuntimeSettingEvent
          wrapper::org::webRtc::RuntimeSetting get_type() noexcept override;
          float get_value() noexcept override;

          ZS_NO_DISCARD() static WrapperImplTypePtr toWrapper(const NativeType &native) noexcept;
        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

