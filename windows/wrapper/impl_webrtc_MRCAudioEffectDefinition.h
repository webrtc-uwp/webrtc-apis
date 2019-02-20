#pragma once

#include "impl_webrtc_MRCEffectTemplate.h"

#ifdef WINUWP
#ifdef CPPWINRT_VERSION

// This class provides an IAudioEffectDefinition which can be used
// to configure and create a MixedRealityCaptureAudioEffect
// object. See https://developer.microsoft.com/en-us/windows/holographic/mixed_reality_capture_for_developers#creating_a_custom_mixed_reality_capture_.28mrc.29_recorder
// for more information about the effect definition properties.

#define RUNTIMECLASS_MIXEDREALITYCAPTURE_AUDIO_EFFECT L"Windows.Media.MixedRealityCapture.MixedRealityCaptureAudioEffect"

//
// MixerMode
// Type: AudioMixerMode as UINT32
//  0: Mic audio only
//  1: System audio only
//  2: Mixing mic and system audio (default)
//
#define PROPERTY_MIXERMODE  L"MixerMode"

namespace webrtc {
  enum class AudioMixerMode
  {
    Mic = 0,
    Loopback = 1,
    MicAndLoopback = 2
  };

  class MrcAudioEffectDefinition : public winrt::implements<MrcAudioEffectDefinition, winrt::Windows::Media::Effects::IAudioEffectDefinition>
  {
  public:
    MrcAudioEffectDefinition();

    //
    // IAudioEffectDefinition
    //
    winrt::hstring ActivatableClassId()
    {
      return m_activatableClassId;
    }

    winrt::Windows::Foundation::Collections::IPropertySet Properties()
    {
      return m_propertySet;
    }

    //
    // Mixed Reality Capture effect properties
    //
    AudioMixerMode MixerMode()
    {
      return GetValueFromPropertySet<uint32_t>(m_propertySet, PROPERTY_MIXERMODE, DefaultAudioMixerMode);
    }

    void MixerMode(AudioMixerMode newValue)
    {
      m_propertySet.Insert(PROPERTY_MIXERMODE, winrt::box_value(static_cast<uint32_t>(newValue)));
    }

  private:
    static constexpr AudioMixerMode DefaultAudioMixerMode = AudioMixerMode::MicAndLoopback;
  private:
    winrt::hstring m_activatableClassId{ RUNTIMECLASS_MIXEDREALITYCAPTURE_AUDIO_EFFECT };
    winrt::Windows::Foundation::Collections::PropertySet m_propertySet;
  };
}

#endif //CPPWINRT_VERSION
#endif //WINUWP
