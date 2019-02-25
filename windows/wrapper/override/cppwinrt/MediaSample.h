
#pragma once


#ifndef CPPWINRT_USE_GENERATED_ORG_WEBRTC_MEDIASAMPLE

#include <wrapper/generated/cppwinrt/types.h>

#include "MediaSample.g.h"
#include <wrapper/generated/org_webRtc_MediaSample.h>

namespace winrt {
  namespace Org {
    namespace WebRtc {
      namespace implementation {


        /// <summary>
        /// MediaSample represents an object holder for a platform specific
        /// media sample.
        /// </summary>
        struct MediaSample : MediaSampleT<MediaSample>
        {
          // internal
          wrapper::org::webRtc::MediaSamplePtr native_;

          struct WrapperCreate {};
          MediaSample(const WrapperCreate &) {}

          // ToCppWinrtImpl
          static winrt::com_ptr< Org::WebRtc::implementation::MediaSample > ToCppWinrtImpl(wrapper::org::webRtc::MediaSamplePtr value);
          static winrt::com_ptr< Org::WebRtc::implementation::MediaSample > ToCppWinrtImpl(Org::WebRtc::MediaSample const & value);
          static winrt::com_ptr< Org::WebRtc::implementation::MediaSample > ToCppWinrtImpl(winrt::com_ptr< Org::WebRtc::implementation::MediaSample > const & value);
          static winrt::com_ptr< Org::WebRtc::implementation::MediaSample > ToCppWinrtImpl(Org::WebRtc::IMediaSample const & value);

          // ToCppWinrt
          static Org::WebRtc::MediaSample ToCppWinrt(wrapper::org::webRtc::MediaSamplePtr value);
          static Org::WebRtc::MediaSample ToCppWinrt(Org::WebRtc::MediaSample const & value);
          static Org::WebRtc::MediaSample ToCppWinrt(winrt::com_ptr< Org::WebRtc::implementation::MediaSample > const & value);
          static Org::WebRtc::MediaSample ToCppWinrt(Org::WebRtc::IMediaSample const & value);

          // ToCppWinrtInterface
          static Org::WebRtc::IMediaSample ToCppWinrtInterface(wrapper::org::webRtc::MediaSamplePtr value);
          static Org::WebRtc::IMediaSample ToCppWinrtInterface(Org::WebRtc::MediaSample const & value);
          static Org::WebRtc::IMediaSample ToCppWinrtInterface(winrt::com_ptr< Org::WebRtc::implementation::MediaSample > const & value);
          static Org::WebRtc::IMediaSample ToCppWinrtInterface(Org::WebRtc::IMediaSample const & value);

          // FromCppWinrt
          static wrapper::org::webRtc::MediaSamplePtr FromCppWinrt(wrapper::org::webRtc::MediaSamplePtr value);
          static wrapper::org::webRtc::MediaSamplePtr FromCppWinrt(winrt::com_ptr< Org::WebRtc::implementation::MediaSample > const & value);
          static wrapper::org::webRtc::MediaSamplePtr FromCppWinrt(Org::WebRtc::MediaSample const & value);
          static wrapper::org::webRtc::MediaSamplePtr FromCppWinrt(Org::WebRtc::IMediaSample const & value);




        public:
          /// <summary>
          /// Cast from Org::WebRtc::IMediaSample to MediaSample
          /// </summary>
          static Org::WebRtc::MediaSample Cast(Org::WebRtc::IMediaSample const & value);

          // ::org::webRtc::MediaSample

          /// <summary>
          /// Returns camera view transform which maps from the coordinate
          /// system to the camera.
          /// </summary>
          Windows::Foundation::Collections::IVectorView< float > GetCameraViewTransform();
          /// <summary>
          /// Returns camera projection transform which maps from the camera to
          /// pixels in the image.
          /// </summary>
          Windows::Foundation::Collections::IVectorView< float > GetCameraProjectionTransform();
          // Windows.Foundation.IClosable
          void Close();


        };

      } // namespace implementation

      namespace factory_implementation {

        struct MediaSample : MediaSampleT<MediaSample, implementation::MediaSample>
        {
        };

      } // namespace factory_implementation

    } // namespace WebRtc
  } // namespace Org
} // namespace winrt
#endif //ifndef CPPWINRT_USE_GENERATED_ORG_WEBRTC_MEDIASAMPLE
