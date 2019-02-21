
#include "pch.h"

#ifndef CPPWINRT_USE_GENERATED_ORG_WEBRTC_AUDIODATA
#include "cppwinrt_Helpers.h"
#include "AudioData.h"
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

struct AudioDataVectorView : implements<
  AudioDataVectorView,
  Windows::Foundation::Collections::IVectorView<int16_t>,
  Windows::Foundation::Collections::IIterable<int16_t>>,
  winrt::vector_view_base<AudioDataVectorView, int16_t>
{
  AudioDataVectorView(
    const int16_t * const data,
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
      const int16_t * const data,
      size_t size) :
      first_(data),
      last_(data + size)
    {}

    int16_t const* const first_;
    int16_t const* const last_;

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

#if 0
struct AudioDataVector : implements<
  AudioDataVector,
  Windows::Foundation::Collections::IVector<int16_t>,
  Windows::Foundation::Collections::IVectorView<int16_t>,
  Windows::Foundation::Collections::IIterable<int16_t>>,
  winrt::vector_base<AudioDataVector, int16_t>
{
  AudioDataVector(
    int16_t * const data,
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
      int16_t * const data,
      size_t size) :
      first_(data),
      last_(data + size)
    {}

    int16_t * const first_;
    int16_t * const last_;

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
#endif //0

//------------------------------------------------------------------------------
winrt::com_ptr< Org::WebRtc::implementation::AudioData > Org::WebRtc::implementation::AudioData::ToCppWinrtImpl(wrapper::org::webRtc::AudioDataPtr value)
{
  if (!value) return nullptr;
  auto result = winrt::make_self<Org::WebRtc::implementation::AudioData>(WrapperCreate{});
  result->native_ = value;
  return result;
}

//------------------------------------------------------------------------------
winrt::com_ptr< Org::WebRtc::implementation::AudioData > Org::WebRtc::implementation::AudioData::ToCppWinrtImpl(Org::WebRtc::AudioData const & value)
{
  winrt::com_ptr< Org::WebRtc::implementation::AudioData > impl {nullptr};
  impl.copy_from(winrt::from_abi<Org::WebRtc::implementation::AudioData>(value));
  return impl;
}

//------------------------------------------------------------------------------
winrt::com_ptr< Org::WebRtc::implementation::AudioData > Org::WebRtc::implementation::AudioData::ToCppWinrtImpl(winrt::com_ptr< Org::WebRtc::implementation::AudioData > const & value)
{
  return value;
}

//------------------------------------------------------------------------------
winrt::com_ptr< Org::WebRtc::implementation::AudioData > Org::WebRtc::implementation::AudioData::ToCppWinrtImpl(Org::WebRtc::IAudioData const & value)
{
  winrt::com_ptr< Org::WebRtc::implementation::AudioData > impl {nullptr};
  impl.copy_from(winrt::from_abi<Org::WebRtc::implementation::AudioData>(value));
  return impl;
}

//------------------------------------------------------------------------------
Org::WebRtc::AudioData Org::WebRtc::implementation::AudioData::ToCppWinrt(wrapper::org::webRtc::AudioDataPtr value)
{
  auto result = ToCppWinrtImpl(value);
  if (!result) return Org::WebRtc::AudioData {nullptr};
  return result.as< Org::WebRtc::AudioData >();
}

//------------------------------------------------------------------------------
Org::WebRtc::AudioData Org::WebRtc::implementation::AudioData::ToCppWinrt(Org::WebRtc::AudioData const & value)
{
  return value;
}

//------------------------------------------------------------------------------
Org::WebRtc::AudioData Org::WebRtc::implementation::AudioData::ToCppWinrt(winrt::com_ptr< Org::WebRtc::implementation::AudioData > const & value)
{
  if (!value) return Org::WebRtc::AudioData {nullptr};
  return value.as< Org::WebRtc::AudioData >();
}

//------------------------------------------------------------------------------
Org::WebRtc::AudioData Org::WebRtc::implementation::AudioData::ToCppWinrt(Org::WebRtc::IAudioData const & value)
{
  if (!value) return Org::WebRtc::AudioData {nullptr};
  return value.as< Org::WebRtc::AudioData >();
}

//------------------------------------------------------------------------------
Org::WebRtc::IAudioData Org::WebRtc::implementation::AudioData::ToCppWinrtInterface(wrapper::org::webRtc::AudioDataPtr value)
{
  auto result = ToCppWinrtImpl(value);
  if (!result) return Org::WebRtc::IAudioData {nullptr};
  return result.as< Org::WebRtc::IAudioData >();
}

//------------------------------------------------------------------------------
Org::WebRtc::IAudioData Org::WebRtc::implementation::AudioData::ToCppWinrtInterface(Org::WebRtc::AudioData const & value)
{
  if (!value) return Org::WebRtc::IAudioData {nullptr};
  return value.as< Org::WebRtc::IAudioData >();
}

//------------------------------------------------------------------------------
Org::WebRtc::IAudioData Org::WebRtc::implementation::AudioData::ToCppWinrtInterface(winrt::com_ptr< Org::WebRtc::implementation::AudioData > const & value)
{
  if (!value) return Org::WebRtc::IAudioData {nullptr};
  return value.as< Org::WebRtc::IAudioData >();
}

//------------------------------------------------------------------------------
Org::WebRtc::IAudioData Org::WebRtc::implementation::AudioData::ToCppWinrtInterface(Org::WebRtc::IAudioData const & value)
{
  return value;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioDataPtr Org::WebRtc::implementation::AudioData::FromCppWinrt(winrt::com_ptr< Org::WebRtc::implementation::AudioData > const & value)
{
  if (!value) return wrapper::org::webRtc::AudioDataPtr();
  return value->native_;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioDataPtr Org::WebRtc::implementation::AudioData::FromCppWinrt(Org::WebRtc::AudioData const & value)
{
  return FromCppWinrt(ToCppWinrtImpl(value));
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioDataPtr Org::WebRtc::implementation::AudioData::FromCppWinrt(wrapper::org::webRtc::AudioDataPtr value)
{
  return value;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::AudioDataPtr Org::WebRtc::implementation::AudioData::FromCppWinrt(Org::WebRtc::IAudioData const & value)
{
  return FromCppWinrt(ToCppWinrtImpl(value));
}

//------------------------------------------------------------------------------
Org::WebRtc::AudioData Org::WebRtc::implementation::AudioData::Cast(Org::WebRtc::IAudioData const & value)
{
  if (!value) return nullptr;
  auto nativeObject = ::Internal::Helper::FromCppWinrt_Org_WebRtc_AudioData(value);  
  if (!nativeObject) return nullptr;
  auto result = std::dynamic_pointer_cast< wrapper::org::webRtc::AudioData >(nativeObject);
  if (!result) return nullptr;
  return ToCppWinrt(result);
}

//------------------------------------------------------------------------------
Org::WebRtc::implementation::AudioData::AudioData()
 : native_(wrapper::org::webRtc::AudioData::wrapper_create())
{
  if (!native_) {throw hresult_error(E_POINTER);}
  native_->wrapper_init_org_webRtc_AudioData();
}

//------------------------------------------------------------------------------
bool Org::WebRtc::implementation::AudioData::ReadOnly()
{
  if (!native_) {throw hresult_error(E_POINTER);}
  return ::Internal::Helper::ToCppWinrt_Bool(native_->readOnly());
}

//------------------------------------------------------------------------------
Windows::Foundation::Collections::IVectorView< int16_t > Org::WebRtc::implementation::AudioData::Data()
{
  if (!native_) { throw hresult_error(E_POINTER); }

  auto data = native_->data();
  auto size = native_->size();

  return AudioDataVectorView(data, size);
}

//------------------------------------------------------------------------------
void Org::WebRtc::implementation::AudioData::Data(Windows::Foundation::Collections::IVectorView< int16_t > const & value)
{
  if (!native_)
    throw hresult_error(E_POINTER);

  if (!value) {
    native_->wrapper_init_org_webRtc_AudioData();
    return;
  }

  auto data = native_->data();
  if (!data) {
    native_->wrapper_init_org_webRtc_AudioData(SafeInt<size_t>(value.Size()));
  }

  ZS_ASSERT(!native_->readOnly());

  auto bufferSize = native_->size();
  decltype(bufferSize) passedSize = SafeInt<decltype(bufferSize)>(value.Size());

  ZS_ASSERT(passedSize <= bufferSize);

  if (passedSize > bufferSize)
    passedSize = bufferSize;

  int16_t * const firstData = native_->mutableData();
  int16_t * const lastData = firstData + passedSize;

  if (!firstData)
    throw hresult_error(E_UNEXPECTED);

  winrt::array_view<int16_t> view(firstData, lastData);
  value.GetMany(0, view);
}


#endif //ifndef CPPWINRT_USE_GENERATED_ORG_WEBRTC_AUDIODATA
