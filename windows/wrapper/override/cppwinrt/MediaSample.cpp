
#include "pch.h"

#ifndef CPPWINRT_USE_GENERATED_ORG_WEBRTC_MEDIASAMPLE

#include <wrapper/generated/cppwinrt/cppwinrt_Helpers.h>
#include <wrapper/override/cppwinrt/MediaSample.h>

#include <wrapper/impl_org_webRtc_MediaSample.h>

#include <windows.perception.spatial.h>

EXTERN_GUID(MFSampleExtension_Spatial_CameraViewTransform, 0x4e251fa4, 0x830f, 0x4770, 0x85, 0x9a, 0x4b, 0x8d, 0x99, 0xaa, 0x80, 0x9b);
EXTERN_GUID(MFSampleExtension_Spatial_CameraCoordinateSystem, 0x9d13c82f, 0x2199, 0x4e67, 0x91, 0xcd, 0xd1, 0xa4, 0x18, 0x1f, 0x25, 0x34);
EXTERN_GUID(MFSampleExtension_Spatial_CameraProjectionTransform, 0x47f9fcb5, 0x2a02, 0x4f26, 0xa4, 0x77, 0x79, 0x2f, 0xdf, 0x95, 0x88, 0x6a);

using namespace winrt;

//------------------------------------------------------------------------------
winrt::com_ptr< Org::WebRtc::implementation::MediaSample > Org::WebRtc::implementation::MediaSample::ToCppWinrtImpl(wrapper::org::webRtc::MediaSamplePtr value)
{
  if (!value) return nullptr;
  auto result = winrt::make_self<Org::WebRtc::implementation::MediaSample>(WrapperCreate{});
  result->native_ = value;
  return result;
}

//------------------------------------------------------------------------------
winrt::com_ptr< Org::WebRtc::implementation::MediaSample > Org::WebRtc::implementation::MediaSample::ToCppWinrtImpl(Org::WebRtc::MediaSample const & value)
{
  winrt::com_ptr< Org::WebRtc::implementation::MediaSample > impl {nullptr};
  impl.copy_from(winrt::from_abi<Org::WebRtc::implementation::MediaSample>(value));
  return impl;
}

//------------------------------------------------------------------------------
winrt::com_ptr< Org::WebRtc::implementation::MediaSample > Org::WebRtc::implementation::MediaSample::ToCppWinrtImpl(winrt::com_ptr< Org::WebRtc::implementation::MediaSample > const & value)
{
  return value;
}

//------------------------------------------------------------------------------
winrt::com_ptr< Org::WebRtc::implementation::MediaSample > Org::WebRtc::implementation::MediaSample::ToCppWinrtImpl(Org::WebRtc::IMediaSample const & value)
{
  winrt::com_ptr< Org::WebRtc::implementation::MediaSample > impl {nullptr};
  impl.copy_from(winrt::from_abi<Org::WebRtc::implementation::MediaSample>(value));
  return impl;
}

//------------------------------------------------------------------------------
Org::WebRtc::MediaSample Org::WebRtc::implementation::MediaSample::ToCppWinrt(wrapper::org::webRtc::MediaSamplePtr value)
{
  auto result = ToCppWinrtImpl(value);
  if (!result) return Org::WebRtc::MediaSample{nullptr};
  return result.as< Org::WebRtc::MediaSample >();
}

//------------------------------------------------------------------------------
Org::WebRtc::MediaSample Org::WebRtc::implementation::MediaSample::ToCppWinrt(Org::WebRtc::MediaSample const & value)
{
  return value;
}

//------------------------------------------------------------------------------
Org::WebRtc::MediaSample Org::WebRtc::implementation::MediaSample::ToCppWinrt(winrt::com_ptr< Org::WebRtc::implementation::MediaSample > const & value)
{
  if (!value) return Org::WebRtc::MediaSample{nullptr};
  return value.as< Org::WebRtc::MediaSample >();
}

//------------------------------------------------------------------------------
Org::WebRtc::MediaSample Org::WebRtc::implementation::MediaSample::ToCppWinrt(Org::WebRtc::IMediaSample const & value)
{
  if (!value) return Org::WebRtc::MediaSample{nullptr};
  return value.as< Org::WebRtc::MediaSample >();
}

//------------------------------------------------------------------------------
Org::WebRtc::IMediaSample Org::WebRtc::implementation::MediaSample::ToCppWinrtInterface(wrapper::org::webRtc::MediaSamplePtr value)
{
  auto result = ToCppWinrtImpl(value);
  if (!result) return Org::WebRtc::IMediaSample{nullptr};
  return result.as< Org::WebRtc::IMediaSample >();
}

//------------------------------------------------------------------------------
Org::WebRtc::IMediaSample Org::WebRtc::implementation::MediaSample::ToCppWinrtInterface(Org::WebRtc::MediaSample const & value)
{
  if (!value) return Org::WebRtc::IMediaSample{nullptr};
  return value.as< Org::WebRtc::IMediaSample >();
}

//------------------------------------------------------------------------------
Org::WebRtc::IMediaSample Org::WebRtc::implementation::MediaSample::ToCppWinrtInterface(winrt::com_ptr< Org::WebRtc::implementation::MediaSample > const & value)
{
  if (!value) return Org::WebRtc::IMediaSample{nullptr};
  return value.as< Org::WebRtc::IMediaSample >();
}

//------------------------------------------------------------------------------
Org::WebRtc::IMediaSample Org::WebRtc::implementation::MediaSample::ToCppWinrtInterface(Org::WebRtc::IMediaSample const & value)
{
  return value;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::MediaSamplePtr Org::WebRtc::implementation::MediaSample::FromCppWinrt(winrt::com_ptr< Org::WebRtc::implementation::MediaSample > const & value)
{
  if (!value) return wrapper::org::webRtc::MediaSamplePtr();
  return value->native_;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::MediaSamplePtr Org::WebRtc::implementation::MediaSample::FromCppWinrt(Org::WebRtc::MediaSample const & value)
{
  return FromCppWinrt(ToCppWinrtImpl(value));
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::MediaSamplePtr Org::WebRtc::implementation::MediaSample::FromCppWinrt(wrapper::org::webRtc::MediaSamplePtr value)
{
  return value;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::MediaSamplePtr Org::WebRtc::implementation::MediaSample::FromCppWinrt(Org::WebRtc::IMediaSample const & value)
{
  return FromCppWinrt(ToCppWinrtImpl(value));
}

//------------------------------------------------------------------------------
Org::WebRtc::MediaSample Org::WebRtc::implementation::MediaSample::Cast(Org::WebRtc::IMediaSample const & value)
{
  if (!value) return nullptr;
  auto nativeObject = ::Internal::Helper::FromCppWinrt_Org_WebRtc_MediaSample(value);
  if (!nativeObject) return nullptr;
  auto result = std::dynamic_pointer_cast< wrapper::org::webRtc::MediaSample>(nativeObject);
  if (!result) return nullptr;
  return ToCppWinrt(result);
}

//------------------------------------------------------------------------------
Windows::Foundation::Collections::IVectorView< float > Org::WebRtc::implementation::MediaSample::GetCameraViewTransform()
{
  if (!native_) {throw hresult_error(E_POINTER);}

  Windows::Foundation::Collections::IVectorView< float > result{ nullptr };
  winrt::com_ptr<IMFSample> pSample = wrapper::impl::org::webRtc::MediaSample::toNative_winrt(native_);

  HRESULT hr;
  winrt::com_ptr<IUnknown> spUnknown;
  winrt::com_ptr<ABI::Windows::Perception::Spatial::ISpatialCoordinateSystem> spSpatialCoordinateSystem;
  winrt::com_ptr<ABI::Windows::Foundation::IReference<ABI::Windows::Foundation::Numerics::Matrix4x4> > spTransformRef;
  ABI::Windows::Foundation::Numerics::Matrix4x4 viewMatrix;
  UINT32 cbBlobSize = 0;
  hr = pSample->GetUnknown(MFSampleExtension_Spatial_CameraCoordinateSystem, __uuidof(ABI::Windows::Perception::Spatial::ISpatialCoordinateSystem), spUnknown.put_void());
  if (!SUCCEEDED(hr))
    return result;
  if (!spUnknown.try_as(spSpatialCoordinateSystem))
    return result;
  hr = pSample->GetBlob(MFSampleExtension_Spatial_CameraViewTransform,
    (UINT8*)(&viewMatrix),
    sizeof(viewMatrix),
    &cbBlobSize);
  if (!SUCCEEDED(hr) || cbBlobSize != sizeof(ABI::Windows::Foundation::Numerics::Matrix4x4))
    return result;
  Windows::Foundation::Collections::IVector viewMatrixVector = single_threaded_vector< float >();
  viewMatrixVector.Append(viewMatrix.M11);
  viewMatrixVector.Append(viewMatrix.M12);
  viewMatrixVector.Append(viewMatrix.M13);
  viewMatrixVector.Append(viewMatrix.M14);
  viewMatrixVector.Append(viewMatrix.M21);
  viewMatrixVector.Append(viewMatrix.M22);
  viewMatrixVector.Append(viewMatrix.M23);
  viewMatrixVector.Append(viewMatrix.M24);
  viewMatrixVector.Append(viewMatrix.M31);
  viewMatrixVector.Append(viewMatrix.M32);
  viewMatrixVector.Append(viewMatrix.M33);
  viewMatrixVector.Append(viewMatrix.M34);
  viewMatrixVector.Append(viewMatrix.M41);
  viewMatrixVector.Append(viewMatrix.M42);
  viewMatrixVector.Append(viewMatrix.M43);
  viewMatrixVector.Append(viewMatrix.M44);
  result = viewMatrixVector.GetView();
  return result;
}

//------------------------------------------------------------------------------
Windows::Foundation::Collections::IVectorView< float > Org::WebRtc::implementation::MediaSample::GetCameraProjectionTransform()
{
  if (!native_) { throw hresult_error(E_POINTER); }

  Windows::Foundation::Collections::IVectorView< float > result{ nullptr };
  winrt::com_ptr<IMFSample> pSample = wrapper::impl::org::webRtc::MediaSample::toNative_winrt(native_);

  HRESULT hr;
  winrt::com_ptr<IUnknown> spUnknown;
  winrt::com_ptr<ABI::Windows::Perception::Spatial::ISpatialCoordinateSystem> spSpatialCoordinateSystem;
  winrt::com_ptr<ABI::Windows::Foundation::IReference<ABI::Windows::Foundation::Numerics::Matrix4x4>> spTransformRef;
  ABI::Windows::Foundation::Numerics::Matrix4x4 projectionMatrix;
  UINT32 cbBlobSize = 0;
  hr = pSample->GetUnknown(MFSampleExtension_Spatial_CameraCoordinateSystem, __uuidof(ABI::Windows::Perception::Spatial::ISpatialCoordinateSystem), spUnknown.put_void());
  if (!SUCCEEDED(hr))
    return result;
  if (!spUnknown.try_as(spSpatialCoordinateSystem))
    return result;
  hr = pSample->GetBlob(MFSampleExtension_Spatial_CameraProjectionTransform,
    (UINT8*)(&projectionMatrix),
    sizeof(projectionMatrix),
    &cbBlobSize);
  if (!SUCCEEDED(hr) || cbBlobSize != sizeof(ABI::Windows::Foundation::Numerics::Matrix4x4))
    return result;
  Windows::Foundation::Collections::IVector projectionMatrixVector = single_threaded_vector< float >();
  projectionMatrixVector.Append(projectionMatrix.M11);
  projectionMatrixVector.Append(projectionMatrix.M12);
  projectionMatrixVector.Append(projectionMatrix.M13);
  projectionMatrixVector.Append(projectionMatrix.M14);
  projectionMatrixVector.Append(projectionMatrix.M21);
  projectionMatrixVector.Append(projectionMatrix.M22);
  projectionMatrixVector.Append(projectionMatrix.M23);
  projectionMatrixVector.Append(projectionMatrix.M24);
  projectionMatrixVector.Append(projectionMatrix.M31);
  projectionMatrixVector.Append(projectionMatrix.M32);
  projectionMatrixVector.Append(projectionMatrix.M33);
  projectionMatrixVector.Append(projectionMatrix.M34);
  projectionMatrixVector.Append(projectionMatrix.M41);
  projectionMatrixVector.Append(projectionMatrix.M42);
  projectionMatrixVector.Append(projectionMatrix.M43);
  projectionMatrixVector.Append(projectionMatrix.M44);
  result = projectionMatrixVector.GetView();
  return result;
}


#endif //ifndef CPPWINRT_USE_GENERATED_ORG_WEBRTC_MEDIASAMPLE
