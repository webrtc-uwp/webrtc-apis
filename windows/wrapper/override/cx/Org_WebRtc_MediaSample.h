

#ifndef CX_USE_GENERATED_ORG_WEBRTC_MEDIASAMPLE

#pragma once

#include <wrapper/generated/cx/types.h>
#include <wrapper/generated/org_webRtc_MediaSample.h>

namespace Org {
  namespace WebRtc {



    /// <summary>
    /// MediaSample represents an object holder for a platform specific media
    /// element.
    /// </summary>
    public ref class MediaSample sealed
    {
    internal:
      wrapper::org::webRtc::MediaSamplePtr native_;

      struct WrapperCreate {};
      MediaSample(const WrapperCreate &) {}

      static MediaSample^ ToCx(wrapper::org::webRtc::MediaSamplePtr value);
      static wrapper::org::webRtc::MediaSamplePtr FromCx(MediaSample^ value);



    public:
      // ::org::webRtc::MediaSample

      /// <summary>
      /// Returns camera view transform which maps from the coordinate system to
      /// the camera.
      /// </summary>
      Windows::Foundation::Collections::IVectorView< Internal::Helper::HelperFloat >^ GetCameraViewTransform();
      /// <summary>
      /// Returns camera projection transform which maps from the camera to
      /// pixels in the image.
      /// </summary>
      Windows::Foundation::Collections::IVectorView< Internal::Helper::HelperFloat >^ GetCameraProjectionTransform();

    };

  } // namespace WebRtc
} // namespace Org
#endif //ifndef CX_USE_GENERATED_ORG_WEBRTC_MEDIASAMPLE
