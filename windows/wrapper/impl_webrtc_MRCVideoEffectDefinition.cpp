#include "impl_webrtc_MRCVideoEffectDefinition.h"

namespace webrtc {
  MrcVideoEffectDefinition::MrcVideoEffectDefinition()
  {
    StreamType(DefaultStreamType);
    HologramCompositionEnabled(DefaultHologramCompositionEnabled);
    RecordingIndicatorEnabled(DefaultRecordingIndicatorEnabled);
    VideoStabilizationEnabled(DefaultVideoStabilizationEnabled);
    VideoStabilizationBufferLength(DefaultVideoStabilizationBufferLength);
    //VideoStabilizationBufferLength(0);
    GlobalOpacityCoefficient(DefaultGlobalOpacityCoefficient);
  }
}
