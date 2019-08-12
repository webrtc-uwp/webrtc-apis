
#pragma once


#ifndef CPPWINRT_USE_GENERATED_ORG_WEBRTC_AUDIODATA

#include "types.h"

#include "AudioData.g.h"
#include <wrapper/generated/org_webRtc_AudioData.h>

namespace winrt {
  namespace Org {
    namespace WebRtc {
      namespace implementation {


        struct AudioData : AudioDataT<AudioData>
        {
          // internal
          wrapper::org::webRtc::AudioDataPtr native_;

          struct WrapperCreate {};
          AudioData(const WrapperCreate &) {}

          // ToCppWinrtImpl
          static winrt::com_ptr< Org::WebRtc::implementation::AudioData > ToCppWinrtImpl(wrapper::org::webRtc::AudioDataPtr value);
          static winrt::com_ptr< Org::WebRtc::implementation::AudioData > ToCppWinrtImpl(Org::WebRtc::AudioData const & value);
          static winrt::com_ptr< Org::WebRtc::implementation::AudioData > ToCppWinrtImpl(winrt::com_ptr< Org::WebRtc::implementation::AudioData > const & value);
          static winrt::com_ptr< Org::WebRtc::implementation::AudioData > ToCppWinrtImpl(Org::WebRtc::IAudioData const & value);

          // ToCppWinrt
          static Org::WebRtc::AudioData ToCppWinrt(wrapper::org::webRtc::AudioDataPtr value);
          static Org::WebRtc::AudioData ToCppWinrt(Org::WebRtc::AudioData const & value);
          static Org::WebRtc::AudioData ToCppWinrt(winrt::com_ptr< Org::WebRtc::implementation::AudioData > const & value);
          static Org::WebRtc::AudioData ToCppWinrt(Org::WebRtc::IAudioData const & value);

          // ToCppWinrtInterface
          static Org::WebRtc::IAudioData ToCppWinrtInterface(wrapper::org::webRtc::AudioDataPtr value);
          static Org::WebRtc::IAudioData ToCppWinrtInterface(Org::WebRtc::AudioData const & value);
          static Org::WebRtc::IAudioData ToCppWinrtInterface(winrt::com_ptr< Org::WebRtc::implementation::AudioData > const & value);
          static Org::WebRtc::IAudioData ToCppWinrtInterface(Org::WebRtc::IAudioData const & value);

          // FromCppWinrt
          static wrapper::org::webRtc::AudioDataPtr FromCppWinrt(wrapper::org::webRtc::AudioDataPtr value);
          static wrapper::org::webRtc::AudioDataPtr FromCppWinrt(winrt::com_ptr< Org::WebRtc::implementation::AudioData > const & value);
          static wrapper::org::webRtc::AudioDataPtr FromCppWinrt(Org::WebRtc::AudioData const & value);
          static wrapper::org::webRtc::AudioDataPtr FromCppWinrt(Org::WebRtc::IAudioData const & value);




        public:
          /// <summary>
          /// Cast from Org::WebRtc::IAudioData to AudioData
          /// </summary>
          static Org::WebRtc::AudioData Cast(Org::WebRtc::IAudioData const & value);

          // ::org::webRtc::AudioData

          /// <summary>
          /// Constructs a new audio data object. <summary> </summary>
          /// </summary>
          AudioData();
          AudioData(uint64_t Size);

          // Windows.Foundation.IClosable
          void Close();

          /// <summary>
          /// Gets if the data is read-only. <summary> </summary>
          /// </summary>
          bool ReadOnly();
          /// <summary>
          /// Gets or sets the audio samples data. <summary> </summary>
          /// </summary>
          Windows::Foundation::IMemoryBuffer Data();
          void Data(Windows::Foundation::IMemoryBuffer const& value);

          uint64_t Length();
          uint64_t GetData(array_view<int16_t> values);
          uint64_t SetData(array_view<int16_t const> values);

          uint64_t GetDataWithPtr(uint64_t bufferPtr, uint64_t bufferLengthInSamples);
          uint64_t SetDataWithPtr(uint64_t bufferPtr, uint64_t bufferLengthInSamples);
        };

      } // namespace implementation

      namespace factory_implementation {

        struct AudioData : AudioDataT<AudioData, implementation::AudioData>
        {
        };

      } // namespace factory_implementation

    } // namespace WebRtc
  } // namespace Org
} // namespace winrt
#endif //ifndef CPPWINRT_USE_GENERATED_ORG_WEBRTC_AUDIODATA
