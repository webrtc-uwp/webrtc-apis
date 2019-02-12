#pragma once

#include "impl_webrtc_MRCEffectTemplate.h"

#ifdef WINUWP
#ifdef CPPWINRT_VERSION

// This class provides an IAudioEffectDefinition which can be used
// to configure and create a MixedRealityCaptureVideoEffect
// object. See https://developer.microsoft.com/en-us/windows/holographic/mixed_reality_capture_for_developers#creating_a_custom_mixed_reality_capture_.28mrc.29_recorder
// for more information about the effect definition properties.

#define RUNTIMECLASS_MIXEDREALITYCAPTURE_VIDEO_EFFECT L"Windows.Media.MixedRealityCapture.MixedRealityCaptureVideoEffect"

//
// StreamType: Describe which capture stream this effect is used for.
// Type: Windows::Media::Capture::MediaStreamType as UINT32
// Default: VideoRecord
//
#define PROPERTY_STREAMTYPE L"StreamType"

//
// HologramCompositionEnabled: Flag to enable or disable holograms in video capture.
// Type: bool
// Default: True
//
#define PROPERTY_HOLOGRAMCOMPOSITIONENABLED L"HologramCompositionEnabled"

//
// RecordingIndicatorEnabled: Flag to enable or disable recording indicator on screen during hologram capturing.
// Type: bool
// Default: True
//
#define PROPERTY_RECORDINGINDICATORENABLED L"RecordingIndicatorEnabled"


//
// VideoStabilizationEnabled: Flag to enable or disable video stabilization powered by the HoloLens tracker.
// Type : bool
// Default: False
//
#define PROPERTY_VIDEOSTABILIZATIONENABLED L"VideoStabilizationEnabled"

//
// VideoStabilizationBufferLength: Set how many historical frames are used for video stabilization.
// Type : UINT32 (Max num is 30)
// Default: 0
//
#define PROPERTY_VIDEOSTABILIZATIONBUFFERLENGTH L"VideoStabilizationBufferLength"

//
// GlobalOpacityCoefficient: Set global opacity coefficient of hologram.
// Type : float (0.0 to 1.0)
// Default: 0.9
//
#define PROPERTY_GLOBALOPACITYCOEFFICIENT L"GlobalOpacityCoefficient"

//
// Maximum value of VideoStabilizationBufferLength
// This number is defined and used in MixedRealityCaptureVideoEffect
//
#define PROPERTY_MAX_VSBUFFER 30U

#include <wrapper/impl_org_webRtc_pre_include.h>
#include "typedefs.h"
#include <wrapper/impl_org_webRtc_post_include.h>

namespace webrtc {
  class MrcVideoEffectDefinition : public winrt::implements<MrcVideoEffectDefinition, winrt::Windows::Media::Effects::IVideoEffectDefinition>
  {
  public:
    MrcVideoEffectDefinition();

    //
    // IVideoEffectDefinition
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
    winrt::Windows::Media::Capture::MediaStreamType StreamType()
    {
      return GetValueFromPropertySet<uint32_t>(m_propertySet, PROPERTY_STREAMTYPE, DefaultStreamType);
    }

    void StreamType(winrt::Windows::Media::Capture::MediaStreamType newValue)
    {
      m_propertySet.Insert(PROPERTY_STREAMTYPE, winrt::box_value(static_cast<uint32_t>(newValue)));
    }

    bool HologramCompositionEnabled()
    {
      return GetValueFromPropertySet<bool>(m_propertySet, PROPERTY_HOLOGRAMCOMPOSITIONENABLED, DefaultHologramCompositionEnabled);
    }

    void HologramCompositionEnabled(bool newValue)
    {
      m_propertySet.Insert(PROPERTY_HOLOGRAMCOMPOSITIONENABLED, winrt::box_value(newValue));
    }

    bool RecordingIndicatorEnabled()
    {
      return GetValueFromPropertySet<bool>(m_propertySet, PROPERTY_RECORDINGINDICATORENABLED, DefaultRecordingIndicatorEnabled);
    }

    void RecordingIndicatorEnabled(bool newValue)
    {
      m_propertySet.Insert(PROPERTY_RECORDINGINDICATORENABLED, winrt::box_value(newValue));
    }

    bool VideoStabilizationEnabled()
    {
        return GetValueFromPropertySet<bool>(m_propertySet, PROPERTY_VIDEOSTABILIZATIONENABLED, DefaultVideoStabilizationEnabled);
    }

    void VideoStabilizationEnabled(bool newValue)
    {
      m_propertySet.Insert(PROPERTY_VIDEOSTABILIZATIONENABLED, winrt::box_value(newValue));
    }

    uint32_t VideoStabilizationBufferLength()
    {
      return GetValueFromPropertySet<uint32_t>(m_propertySet, PROPERTY_VIDEOSTABILIZATIONBUFFERLENGTH, DefaultVideoStabilizationBufferLength);
    }

    void VideoStabilizationBufferLength(uint32_t newValue)
    {
      m_propertySet.Insert(PROPERTY_VIDEOSTABILIZATIONBUFFERLENGTH, winrt::box_value((std::min)(newValue, PROPERTY_MAX_VSBUFFER)));
    }

    float GlobalOpacityCoefficient()
    {
      return GetValueFromPropertySet<float>(m_propertySet, PROPERTY_GLOBALOPACITYCOEFFICIENT, DefaultGlobalOpacityCoefficient);
    }

    void GlobalOpacityCoefficient(float newValue)
    {
      m_propertySet.Insert(PROPERTY_GLOBALOPACITYCOEFFICIENT, winrt::box_value(newValue));
    }

    uint32_t VideoStabilizationMaximumBufferLength()
    {
      return PROPERTY_MAX_VSBUFFER;
    }

  private:
    static constexpr winrt::Windows::Media::Capture::MediaStreamType DefaultStreamType = winrt::Windows::Media::Capture::MediaStreamType::VideoRecord;
    static constexpr bool DefaultHologramCompositionEnabled = true;
    static constexpr bool DefaultRecordingIndicatorEnabled = true;
    static constexpr bool DefaultVideoStabilizationEnabled = false;
    static constexpr uint32_t DefaultVideoStabilizationBufferLength = 0U;
    static constexpr float DefaultGlobalOpacityCoefficient = 0.9f;
  private:
    winrt::hstring m_activatableClassId{ RUNTIMECLASS_MIXEDREALITYCAPTURE_VIDEO_EFFECT };
    winrt::Windows::Foundation::Collections::PropertySet m_propertySet;
  };
}

#endif //CPPWINRT_VERSION
#endif //WINUWP
