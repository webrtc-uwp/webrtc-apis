
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

using namespace winrt;

template <typename TValueType>
struct VideoDataVectorView : implements<
  VideoDataVectorView<TValueType>,
  Windows::Foundation::Collections::IVectorView<TValueType>,
  Windows::Foundation::Collections::IIterable<TValueType>>,
  winrt::vector_view_base<VideoDataVectorView<TValueType>, TValueType>
{
  VideoDataVectorView(
    const TValueType * const data,
    size_t size
  ) : container_(data, size)
  {}

  auto& get_container() const noexcept
  {
    return container_;
  }

  auto& get_container() noexcept
  {
    return container_;
  }

private:

  struct Container
  {
    Container(
      const TValueType * const data,
      size_t size) :
      first_(data),
      last_(data + size)
    {}

    TValueType const* const first_;
    TValueType const* const last_;

    auto begin() const noexcept
    {
      return first_;
    }

    auto end() const noexcept
    {
      return last_;
    }
  };

  Container container_;
};

typedef VideoDataVectorView<uint8_t> VideoData8BitVectorView;
typedef VideoDataVectorView<uint16_t> VideoData16BitVectorView;

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
Windows::Foundation::Collections::IVectorView< uint8_t > Org::WebRtc::implementation::VideoData::Data8bit()
{
  if (!native_) { throw hresult_error(E_POINTER); }

  auto data = native_->get_data8bit();
  auto size = native_->get_size();

  return winrt::make<VideoData8BitVectorView>(data, size);
}

//------------------------------------------------------------------------------
Windows::Foundation::Collections::IVectorView< uint16_t > Org::WebRtc::implementation::VideoData::Data16bit()
{
  if (!native_) { throw hresult_error(E_POINTER); }

  auto data = native_->get_data16bit();
  auto size = native_->get_size();

  return winrt::make<VideoData16BitVectorView>(data, size);
}


#endif //ifndef CPPWINRT_USE_GENERATED_ORG_WEBRTC_VIDEODATA
