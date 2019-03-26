
#pragma once


#ifndef CPPWINRT_USE_GENERATED_ORG_WEBRTC_VIDEODATA

#include "types.h"

#include "VideoData.g.h"
#include <wrapper/generated/org_webRtc_VideoData.h>

namespace winrt {
  namespace Org {
    namespace WebRtc {
      namespace implementation {


        struct VideoData : VideoDataT<VideoData>
        {
          // internal
          wrapper::org::webRtc::VideoDataPtr native_;

          struct WrapperCreate {};
          VideoData(const WrapperCreate &) {}

          // ToCppWinrtImpl
          static winrt::com_ptr< Org::WebRtc::implementation::VideoData > ToCppWinrtImpl(wrapper::org::webRtc::VideoDataPtr value);
          static winrt::com_ptr< Org::WebRtc::implementation::VideoData > ToCppWinrtImpl(Org::WebRtc::VideoData const & value);
          static winrt::com_ptr< Org::WebRtc::implementation::VideoData > ToCppWinrtImpl(winrt::com_ptr< Org::WebRtc::implementation::VideoData > const & value);
          static winrt::com_ptr< Org::WebRtc::implementation::VideoData > ToCppWinrtImpl(Org::WebRtc::IVideoData const & value);

          // ToCppWinrt
          static Org::WebRtc::VideoData ToCppWinrt(wrapper::org::webRtc::VideoDataPtr value);
          static Org::WebRtc::VideoData ToCppWinrt(Org::WebRtc::VideoData const & value);
          static Org::WebRtc::VideoData ToCppWinrt(winrt::com_ptr< Org::WebRtc::implementation::VideoData > const & value);
          static Org::WebRtc::VideoData ToCppWinrt(Org::WebRtc::IVideoData const & value);

          // ToCppWinrtInterface
          static Org::WebRtc::IVideoData ToCppWinrtInterface(wrapper::org::webRtc::VideoDataPtr value);
          static Org::WebRtc::IVideoData ToCppWinrtInterface(Org::WebRtc::VideoData const & value);
          static Org::WebRtc::IVideoData ToCppWinrtInterface(winrt::com_ptr< Org::WebRtc::implementation::VideoData > const & value);
          static Org::WebRtc::IVideoData ToCppWinrtInterface(Org::WebRtc::IVideoData const & value);

          // FromCppWinrt
          static wrapper::org::webRtc::VideoDataPtr FromCppWinrt(wrapper::org::webRtc::VideoDataPtr value);
          static wrapper::org::webRtc::VideoDataPtr FromCppWinrt(winrt::com_ptr< Org::WebRtc::implementation::VideoData > const & value);
          static wrapper::org::webRtc::VideoDataPtr FromCppWinrt(Org::WebRtc::VideoData const & value);
          static wrapper::org::webRtc::VideoDataPtr FromCppWinrt(Org::WebRtc::IVideoData const & value);




        public:
          /// <summary>
          /// Cast from Org::WebRtc::IVideoData to VideoData
          /// </summary>
          static Org::WebRtc::VideoData Cast(Org::WebRtc::IVideoData const & value);

          // Windows.Foundation.IClosable
          void Close();

          bool Is8BitColorSpace();
          bool Is16BitColorSpace();
          /// <summary>
          /// Gets or sets the video 8 bit color space data. <summary>
          /// </summary>
          /// </summary>
          Windows::Foundation::IMemoryBuffer Data8bit();
          /// <summary>
          /// Gets or sets the video 16 bit color space data. <summary>
          /// </summary>
          /// </summary>
          Windows::Foundation::IMemoryBuffer Data16bit();

        };

      } // namespace implementation

      namespace factory_implementation {

        struct VideoData : VideoDataT<VideoData, implementation::VideoData>
        {
        };

      } // namespace factory_implementation

    } // namespace WebRtc
  } // namespace Org
} // namespace winrt
#endif //ifndef CPPWINRT_USE_GENERATED_ORG_WEBRTC_VIDEODATA
