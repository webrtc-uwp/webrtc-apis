

#ifndef CX_USE_GENERATED_ORG_WEBRTC_MEDIASAMPLE

#include <wrapper/generated/cx/cx_Helpers.h>
#include <wrapper/generated/cx/Org_WebRtc_MediaSample.h>

#include <wrapper/impl_org_webRtc_MediaSample.h>

#include <windows.perception.spatial.h>

EXTERN_GUID(MFSampleExtension_Spatial_CameraViewTransform, 0x4e251fa4, 0x830f, 0x4770, 0x85, 0x9a, 0x4b, 0x8d, 0x99, 0xaa, 0x80, 0x9b);
EXTERN_GUID(MFSampleExtension_Spatial_CameraCoordinateSystem, 0x9d13c82f, 0x2199, 0x4e67, 0x91, 0xcd, 0xd1, 0xa4, 0x18, 0x1f, 0x25, 0x34);
EXTERN_GUID(MFSampleExtension_Spatial_CameraProjectionTransform, 0x47f9fcb5, 0x2a02, 0x4f26, 0xa4, 0x77, 0x79, 0x2f, 0xdf, 0x95, 0x88, 0x6a);

//------------------------------------------------------------------------------
::Org::WebRtc::MediaSample^ Org::WebRtc::MediaSample::ToCx(wrapper::org::webRtc::MediaSamplePtr value)
{
  if (!value) return nullptr;
  auto result = ref new MediaSample(WrapperCreate{});
  result->native_ = value;
  return result;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::MediaSamplePtr Org::WebRtc::MediaSample::FromCx(::Org::WebRtc::MediaSample^ value)
{
  if (nullptr == value) return wrapper::org::webRtc::MediaSamplePtr();
  return value->native_;
}

//------------------------------------------------------------------------------
Windows::Foundation::Collections::IVectorView< Internal::Helper::HelperFloat >^ Org::WebRtc::MediaSample::GetCameraViewTransform()
{
  if (!native_) { throw ref new Platform::NullReferenceException(); }
  Windows::Foundation::Collections::IVectorView< Internal::Helper::HelperFloat >^ result{};

  Microsoft::WRL::ComPtr<IMFSample> pSample = wrapper::impl::org::webRtc::MediaSample::toNative_cx(native_);

  HRESULT hr;
  Microsoft::WRL::ComPtr<IUnknown> spUnknown;
  Microsoft::WRL::ComPtr<ABI::Windows::Perception::Spatial::ISpatialCoordinateSystem> spSpatialCoordinateSystem;
  Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::Windows::Foundation::Numerics::Matrix4x4> > spTransformRef;
  ABI::Windows::Foundation::Numerics::Matrix4x4 viewMatrix;
  UINT32 cbBlobSize = 0;
  hr = pSample->GetUnknown(MFSampleExtension_Spatial_CameraCoordinateSystem, __uuidof(ABI::Windows::Perception::Spatial::ISpatialCoordinateSystem), &spUnknown);
  if (!SUCCEEDED(hr))
    return result;
  hr = spUnknown.As(&spSpatialCoordinateSystem);
  if (!SUCCEEDED(hr))
    return result;
  hr = pSample->GetBlob(MFSampleExtension_Spatial_CameraViewTransform,
    (UINT8*)(&viewMatrix),
    sizeof(viewMatrix),
    &cbBlobSize);
  if (!SUCCEEDED(hr) || cbBlobSize != sizeof(ABI::Windows::Foundation::Numerics::Matrix4x4))
    return result;
  Windows::Foundation::Collections::IVector< Internal::Helper::HelperFloat >^ viewMatrixVector = ref new Platform::Collections::Vector< Internal::Helper::HelperFloat >();
  viewMatrixVector->Append(viewMatrix.M11);
  viewMatrixVector->Append(viewMatrix.M12);
  viewMatrixVector->Append(viewMatrix.M13);
  viewMatrixVector->Append(viewMatrix.M14);
  viewMatrixVector->Append(viewMatrix.M21);
  viewMatrixVector->Append(viewMatrix.M22);
  viewMatrixVector->Append(viewMatrix.M23);
  viewMatrixVector->Append(viewMatrix.M24);
  viewMatrixVector->Append(viewMatrix.M31);
  viewMatrixVector->Append(viewMatrix.M32);
  viewMatrixVector->Append(viewMatrix.M33);
  viewMatrixVector->Append(viewMatrix.M34);
  viewMatrixVector->Append(viewMatrix.M41);
  viewMatrixVector->Append(viewMatrix.M42);
  viewMatrixVector->Append(viewMatrix.M43);
  viewMatrixVector->Append(viewMatrix.M44);
  result = viewMatrixVector->GetView();
  return result;
}

//------------------------------------------------------------------------------
Windows::Foundation::Collections::IVectorView< Internal::Helper::HelperFloat >^ Org::WebRtc::MediaSample::GetCameraProjectionTransform()
{
  if (!native_) { throw ref new Platform::NullReferenceException(); }
  Windows::Foundation::Collections::IVectorView< Internal::Helper::HelperFloat >^ result{};

  Microsoft::WRL::ComPtr<IMFSample> pSample = wrapper::impl::org::webRtc::MediaSample::toNative_cx(native_);

  HRESULT hr;
  Microsoft::WRL::ComPtr<IUnknown> spUnknown;
  Microsoft::WRL::ComPtr<ABI::Windows::Perception::Spatial::ISpatialCoordinateSystem> spSpatialCoordinateSystem;
  Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::Windows::Foundation::Numerics::Matrix4x4> > spTransformRef;
  ABI::Windows::Foundation::Numerics::Matrix4x4 projectionMatrix;
  UINT32 cbBlobSize = 0;
  hr = pSample->GetUnknown(MFSampleExtension_Spatial_CameraCoordinateSystem, __uuidof(ABI::Windows::Perception::Spatial::ISpatialCoordinateSystem), &spUnknown);
  if (!SUCCEEDED(hr))
    return result;
  hr = spUnknown.As(&spSpatialCoordinateSystem);
  if (!SUCCEEDED(hr))
    return result;
  hr = pSample->GetBlob(MFSampleExtension_Spatial_CameraProjectionTransform,
    (UINT8*)(&projectionMatrix),
    sizeof(projectionMatrix),
    &cbBlobSize);
  if (!SUCCEEDED(hr) || cbBlobSize != sizeof(ABI::Windows::Foundation::Numerics::Matrix4x4))
    return result;
  Windows::Foundation::Collections::IVector< Internal::Helper::HelperFloat >^ projectionMatrixVector = ref new Platform::Collections::Vector< Internal::Helper::HelperFloat >();
  projectionMatrixVector->Append(projectionMatrix.M11);
  projectionMatrixVector->Append(projectionMatrix.M12);
  projectionMatrixVector->Append(projectionMatrix.M13);
  projectionMatrixVector->Append(projectionMatrix.M14);
  projectionMatrixVector->Append(projectionMatrix.M21);
  projectionMatrixVector->Append(projectionMatrix.M22);
  projectionMatrixVector->Append(projectionMatrix.M23);
  projectionMatrixVector->Append(projectionMatrix.M24);
  projectionMatrixVector->Append(projectionMatrix.M31);
  projectionMatrixVector->Append(projectionMatrix.M32);
  projectionMatrixVector->Append(projectionMatrix.M33);
  projectionMatrixVector->Append(projectionMatrix.M34);
  projectionMatrixVector->Append(projectionMatrix.M41);
  projectionMatrixVector->Append(projectionMatrix.M42);
  projectionMatrixVector->Append(projectionMatrix.M43);
  projectionMatrixVector->Append(projectionMatrix.M44);
  result = projectionMatrixVector->GetView();
  return result;
}


#endif //ifndef CX_USE_GENERATED_ORG_WEBRTC_MEDIASAMPLE
