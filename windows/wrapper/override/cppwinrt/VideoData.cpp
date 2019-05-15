
#include "pch.h"

#ifndef CPPWINRT_USE_GENERATED_ORG_WEBRTC_VIDEODATA

#include "cppwinrt_Helpers.h"
#include "VideoData.h"
#include "VideoFormat.h"
#include "RTCRtcpFeedback.h"
#include "RTCRtpCodecCapability.h"
#include "RTCRtpContributingSource.h"
#include "RTCRtpDecodingParameters.h"
#include "RTCRtpSynchronizationSource.h"
#include "RTCIceServer.h"
#include "RTCRtpCodecParameters.h"
#include "RTCDtlsFingerprint.h"
#include "Constraint.h"
#include "RTCRtpHeaderExtensionCapability.h"
#include "RTCRtpHeaderExtensionParameters.h"
#include "VideoDeviceInfo.h"
#include "RTCStatsReport.h"
#include "RTCCertificate.h"
#include "RTCSessionDescription.h"
#include "RTCRtpReceiver.h"
#include "RTCRtpEncodingParameters.h"
#include "RTCIceCandidate.h"
#include "RTCRtpTransceiver.h"
#include "RTCRtpSender.h"

#include <zsLib/SafeInt.h>

using namespace winrt;

struct __declspec(uuid("5b0d3235-4dba-4d44-865e-8f1d0e4fd04d")) __declspec(novtable) IMemoryBufferByteAccess : ::IUnknown
{
  virtual HRESULT __stdcall GetBuffer(uint8_t** value, uint32_t* capacity) = 0;
};

//------------------------------------------------------------------------------
winrt::com_ptr< Org::WebRtc::implementation::VideoData > Org::WebRtc::implementation::VideoData::ToCppWinrtImpl(wrapper::org::webRtc::VideoDataPtr value)
{
  if (!value) return nullptr;
  auto result = winrt::make_self<Org::WebRtc::implementation::VideoData>(WrapperCreate{});
  result->native_ = value;
  return result;
}

//------------------------------------------------------------------------------
winrt::com_ptr< Org::WebRtc::implementation::VideoData > Org::WebRtc::implementation::VideoData::ToCppWinrtImpl(Org::WebRtc::VideoData const & value)
{
  winrt::com_ptr< Org::WebRtc::implementation::VideoData > impl {nullptr};
  impl.copy_from(winrt::from_abi<Org::WebRtc::implementation::VideoData>(value));
  return impl;
}

//------------------------------------------------------------------------------
winrt::com_ptr< Org::WebRtc::implementation::VideoData > Org::WebRtc::implementation::VideoData::ToCppWinrtImpl(winrt::com_ptr< Org::WebRtc::implementation::VideoData > const & value)
{
  return value;
}

//------------------------------------------------------------------------------
winrt::com_ptr< Org::WebRtc::implementation::VideoData > Org::WebRtc::implementation::VideoData::ToCppWinrtImpl(Org::WebRtc::IVideoData const & value)
{
  winrt::com_ptr< Org::WebRtc::implementation::VideoData > impl {nullptr};
  impl.copy_from(winrt::from_abi<Org::WebRtc::implementation::VideoData>(value));
  return impl;
}

//------------------------------------------------------------------------------
Org::WebRtc::VideoData Org::WebRtc::implementation::VideoData::ToCppWinrt(wrapper::org::webRtc::VideoDataPtr value)
{
  auto result = ToCppWinrtImpl(value);
  if (!result) return Org::WebRtc::VideoData {nullptr};
  return result.as< Org::WebRtc::VideoData >();
}

//------------------------------------------------------------------------------
Org::WebRtc::VideoData Org::WebRtc::implementation::VideoData::ToCppWinrt(Org::WebRtc::VideoData const & value)
{
  return value;
}

//------------------------------------------------------------------------------
Org::WebRtc::VideoData Org::WebRtc::implementation::VideoData::ToCppWinrt(winrt::com_ptr< Org::WebRtc::implementation::VideoData > const & value)
{
  if (!value) return Org::WebRtc::VideoData {nullptr};
  return value.as< Org::WebRtc::VideoData >();
}

//------------------------------------------------------------------------------
Org::WebRtc::VideoData Org::WebRtc::implementation::VideoData::ToCppWinrt(Org::WebRtc::IVideoData const & value)
{
  if (!value) return Org::WebRtc::VideoData {nullptr};
  return value.as< Org::WebRtc::VideoData >();
}

//------------------------------------------------------------------------------
Org::WebRtc::IVideoData Org::WebRtc::implementation::VideoData::ToCppWinrtInterface(wrapper::org::webRtc::VideoDataPtr value)
{
  auto result = ToCppWinrtImpl(value);
  if (!result) return Org::WebRtc::IVideoData {nullptr};
  return result.as< Org::WebRtc::IVideoData >();
}

//------------------------------------------------------------------------------
Org::WebRtc::IVideoData Org::WebRtc::implementation::VideoData::ToCppWinrtInterface(Org::WebRtc::VideoData const & value)
{
  if (!value) return Org::WebRtc::IVideoData {nullptr};
  return value.as< Org::WebRtc::IVideoData >();
}

//------------------------------------------------------------------------------
Org::WebRtc::IVideoData Org::WebRtc::implementation::VideoData::ToCppWinrtInterface(winrt::com_ptr< Org::WebRtc::implementation::VideoData > const & value)
{
  if (!value) return Org::WebRtc::IVideoData {nullptr};
  return value.as< Org::WebRtc::IVideoData >();
}

//------------------------------------------------------------------------------
Org::WebRtc::IVideoData Org::WebRtc::implementation::VideoData::ToCppWinrtInterface(Org::WebRtc::IVideoData const & value)
{
  return value;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr Org::WebRtc::implementation::VideoData::FromCppWinrt(winrt::com_ptr< Org::WebRtc::implementation::VideoData > const & value)
{
  if (!value) return wrapper::org::webRtc::VideoDataPtr();
  return value->native_;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr Org::WebRtc::implementation::VideoData::FromCppWinrt(Org::WebRtc::VideoData const & value)
{
  return FromCppWinrt(ToCppWinrtImpl(value));
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr Org::WebRtc::implementation::VideoData::FromCppWinrt(wrapper::org::webRtc::VideoDataPtr value)
{
  return value;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::VideoDataPtr Org::WebRtc::implementation::VideoData::FromCppWinrt(Org::WebRtc::IVideoData const & value)
{
  return FromCppWinrt(ToCppWinrtImpl(value));
}

//------------------------------------------------------------------------------
Org::WebRtc::implementation::VideoData::VideoData(uint64_t Size)
  : native_(wrapper::org::webRtc::VideoData::wrapper_create())
{
  if (!native_) { throw hresult_error(E_POINTER); }
  native_->wrapper_init_org_webRtc_VideoData(SafeInt<size_t>(Size));
}

//------------------------------------------------------------------------------
Org::WebRtc::VideoData Org::WebRtc::implementation::VideoData::Cast(Org::WebRtc::IVideoData const & value)
{
  if (!value) return nullptr;
  auto nativeObject = ::Internal::Helper::FromCppWinrt_Org_WebRtc_VideoData(value);  
  if (!nativeObject) return nullptr;
  auto result = std::dynamic_pointer_cast< wrapper::org::webRtc::VideoData >(nativeObject);
  if (!result) return nullptr;
  return ToCppWinrt(result);
}

//------------------------------------------------------------------------------
void Org::WebRtc::implementation::VideoData::Close()
{
  if (native_) native_->wrapper_dispose();
  native_.reset();
}

//------------------------------------------------------------------------------
bool Org::WebRtc::implementation::VideoData::Is8BitColorSpace()
{
  if (!native_) {throw hresult_error(E_POINTER);}
  return ::Internal::Helper::ToCppWinrt_Bool(native_->get_is8BitColorSpace());
}

//------------------------------------------------------------------------------
bool Org::WebRtc::implementation::VideoData::Is16BitColorSpace()
{
  if (!native_) {throw hresult_error(E_POINTER);}
  return ::Internal::Helper::ToCppWinrt_Bool(native_->get_is16BitColorSpace());
}

//------------------------------------------------------------------------------
uint64_t Org::WebRtc::implementation::VideoData::Length()
{
  if (!native_)
    return 0;

  return SafeInt<uint64_t>(native_->get_size());
}

//------------------------------------------------------------------------------
uint64_t Org::WebRtc::implementation::VideoData::GetData8bit(array_view<uint8_t> values)
{
  if (!native_)
    return 0;

  uint64_t inSize = SafeInt<decltype(inSize)>(values.size());

  uint64_t size = native_->get_size();

  size = inSize < size ? inSize : size;

  auto dest = values.data();
  auto source = native_->get_data8bit();

  if ((!dest) ||
    (!source))
    return 0;

  memcpy(dest, source, SafeInt<size_t>(sizeof(uint8_t) * size));

  return size;
}

//------------------------------------------------------------------------------
uint64_t Org::WebRtc::implementation::VideoData::SetData8bit(ZS_MAYBE_USED() array_view<uint8_t const> values)
{
  if (!native_)
    return 0;

  uint64_t inSize = SafeInt<decltype(inSize)>(values.size());

  uint64_t size = native_->get_size();

  size = inSize < size ? inSize : size;

  auto source = values.data();
  auto dest = native_->get_mutableData8bit();

  if ((!dest) ||
      (!source))
    return 0;

  memcpy(dest, source, SafeInt<size_t>(sizeof(uint8_t) * size));

  return size;
}

//------------------------------------------------------------------------------
uint64_t Org::WebRtc::implementation::VideoData::GetData16bit(array_view<uint16_t> values)
{
  if (!native_)
    return 0;

  uint64_t inSize = SafeInt<decltype(inSize)>(values.size());
  uint64_t size = native_->get_size();

  size = inSize < size ? inSize : size;

  auto dest = values.data();
  auto source = native_->get_data16bit();

  if ((!dest) ||
      (!source))
    return 0;

  memcpy(dest, source, SafeInt<size_t>(sizeof(uint16_t) * size));

  return size;
}

//------------------------------------------------------------------------------
uint64_t Org::WebRtc::implementation::VideoData::SetData16bit(ZS_MAYBE_USED() array_view<uint16_t const> values)
{
  if (!native_)
    return 0;

  uint64_t inSize = SafeInt<decltype(inSize)>(values.size());

  uint64_t size = native_->get_size();

  size = inSize < size ? inSize : size;

  auto source = values.data();
  auto dest = native_->get_mutableData16bit();

  if ((!dest) ||
      (!source))
    return 0;

  memcpy(dest, source, SafeInt<size_t>(sizeof(uint16_t) * size));

  return size;
}

//------------------------------------------------------------------------------
winrt::Windows::Foundation::IMemoryBuffer Org::WebRtc::implementation::VideoData::Data8bit()
{
  if (!native_)
    return {nullptr};

  Windows::Foundation::MemoryBuffer memBuffer{ static_cast<uint32_t>(sizeof(uint8_t)*native_->get_size()) };

  auto ref = memBuffer.CreateReference();

  auto byteAccess = ref.as<IMemoryBufferByteAccess>();
  if (!byteAccess)
    return {nullptr};

  uint8_t* dest{};
  uint32_t destSize {};
  if (FAILED(byteAccess->GetBuffer(&dest, &destSize)))
    return {nullptr};

  if (destSize != (sizeof(uint8_t)*native_->get_size()))
    return {nullptr};

  memcpy(dest, native_->get_data8bit(), destSize);

  return memBuffer;
}

//------------------------------------------------------------------------------
winrt::Windows::Foundation::IMemoryBuffer Org::WebRtc::implementation::VideoData::Data16bit()
{
  if (!native_)
    return {nullptr};

  Windows::Foundation::MemoryBuffer memBuffer{ static_cast<uint32_t>(sizeof(uint16_t)*native_->get_size()) };

  auto ref = memBuffer.CreateReference();

  auto byteAccess = ref.as<IMemoryBufferByteAccess>();
  if (!byteAccess)
    return {nullptr};

  uint8_t* dest{};
  uint32_t destSize {};
  if (FAILED(byteAccess->GetBuffer(&dest, &destSize)))
    return {nullptr};

  if (destSize != (sizeof(uint16_t)*native_->get_size()))
    return {nullptr};

  memcpy(dest, native_->get_data16bit(), destSize);

  return memBuffer;
}

#endif //ifndef CPPWINRT_USE_GENERATED_ORG_WEBRTC_VIDEODATA
