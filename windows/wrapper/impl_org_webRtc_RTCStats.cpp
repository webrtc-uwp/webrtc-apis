
#include "impl_org_webRtc_RTCStats.h"
#include "impl_org_webRtc_RTCCodecStats.h"
#include "impl_org_webRtc_RTCInboundRtpStreamStats.h"
#include "impl_org_webRtc_RTCOutboundRtpStreamStats.h"
#include "impl_org_webRtc_RTCPeerConnectionStats.h"
#include "impl_org_webRtc_RTCDataChannelStats.h"
#include "impl_org_webRtc_RTCMediaStreamStats.h"
#include "impl_org_webRtc_RTCMediaHandlerStats.h"
#include "impl_org_webRtc_RTCSenderAudioTrackAttachmentStats.h"
#include "impl_org_webRtc_RTCSenderVideoTrackAttachmentStats.h"
#include "impl_org_webRtc_RTCTransportStats.h"
#include "impl_org_webRtc_RTCIceCandidatePairStats.h"
#include "impl_org_webRtc_RTCIceCandidateStats.h"
#include "impl_org_webRtc_RTCCertificateStats.h"

#include "impl_org_webRtc_enums.h"

#include "impl_org_webRtc_pre_include.h"
#include "api/stats/rtc_stats.h"
#include "api/stats/rtcstats_objects.h"
#include "impl_org_webRtc_post_include.h"

#include <zsLib/SafeInt.h>
#include <zsLib/date.h>
#include <zsLib/helpers.h>

#include "Org.WebRtc.Glue.events.h"

using ::zsLib::Milliseconds;
using ::zsLib::String;
using ::zsLib::Optional;
using ::zsLib::Any;
using ::zsLib::AnyPtr;
using ::zsLib::AnyHolder;
using ::zsLib::Promise;
using ::zsLib::PromisePtr;
using ::zsLib::PromiseWithHolder;
using ::zsLib::PromiseWithHolderPtr;
using ::zsLib::eventing::SecureByteBlock;
using ::zsLib::eventing::SecureByteBlockPtr;
using ::std::shared_ptr;
using ::std::weak_ptr;
using ::std::make_shared;
using ::std::list;
using ::std::set;
using ::std::map;

using namespace date;

// borrow definitions from class
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCStats::RTCStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCStatsPtr wrapper::org::webRtc::RTCStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCStats::~RTCStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCStats::get_timestamp() noexcept
{
  ZS_ASSERT(native_);
  return get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCStats::get_statsType() noexcept
{
  ZS_ASSERT(native_);
  return get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCStats::get_statsTypeOther() noexcept
{
  ZS_ASSERT(native_);
  return get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCStats::get_id() noexcept
{
  ZS_ASSERT(native_);
  return get_id(native_.get());
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_4(
    x, i, Detail, RTCStats, stats, Stats, Info,
    string, type, type.has_value() ? UseEnum::toString(type.value()) : "",
    string, otherType, get_statsTypeOther(),
    string, id, get_id(),
    duration, timestamp, zsLib::timeSinceEpoch<Milliseconds>(get_timestamp()).count()
  );
}

//------------------------------------------------------------------------------
WrapperTypePtr WrapperImplType::toWrapper(NativeTypeUniPtr value) noexcept
{
  if (!value) return WrapperImplTypePtr();

  auto statsType = get_statsType(value.get());
  if (statsType.has_value()) {
    switch (statsType.value())
    {
      case wrapper::org::webRtc::RTCStatsType::RTCStatsType_codec:
      {
        return RTCCodecStats::toWrapper(std::move(value));
      }
      case wrapper::org::webRtc::RTCStatsType::RTCStatsType_inboundRtp:
      {
        return RTCInboundRtpStreamStats::toWrapper(std::move(value));
      }
      case wrapper::org::webRtc::RTCStatsType::RTCStatsType_outboundRtp:
      {
        return RTCOutboundRtpStreamStats::toWrapper(std::move(value));
      }
      case wrapper::org::webRtc::RTCStatsType::RTCStatsType_peerConnection:
      {
        return RTCPeerConnectionStats::toWrapper(std::move(value));
      }
      case wrapper::org::webRtc::RTCStatsType::RTCStatsType_dataChannel:
      {
        return RTCDataChannelStats::toWrapper(std::move(value));
      }
      case wrapper::org::webRtc::RTCStatsType::RTCStatsType_stream:
      {
        return RTCMediaStreamStats::toWrapper(std::move(value));
      }
      case wrapper::org::webRtc::RTCStatsType::RTCStatsType_track:
      {
        auto converted = value->cast_to<::webrtc::RTCMediaStreamTrackStats>();

        try {
          auto result = UseEnum::toNativeMediaType((*(converted.kind)).c_str());
          switch (result) {
            case ::cricket::MediaType::MEDIA_TYPE_AUDIO:
            {
              return RTCSenderAudioTrackAttachmentStats::toWrapper(std::move(value));
            }
            case ::cricket::MediaType::MEDIA_TYPE_VIDEO:
            {
              return RTCSenderVideoTrackAttachmentStats::toWrapper(std::move(value));
            }
            case ::cricket::MediaType::MEDIA_TYPE_DATA: break;
          }
        } catch (const InvalidParameters &) {
        }

        return RTCMediaHandlerStats::toWrapper(std::move(value));
      }
      case wrapper::org::webRtc::RTCStatsType::RTCStatsType_transport:
      {
        return RTCTransportStats::toWrapper(std::move(value));
      }
      case wrapper::org::webRtc::RTCStatsType::RTCStatsType_candidatePair:
      {
        return RTCIceCandidatePairStats::toWrapper(std::move(value));
      }
      case wrapper::org::webRtc::RTCStatsType::RTCStatsType_localCandidate:
      {
        return RTCIceCandidateStats::toWrapper(std::move(value));
      }
      case wrapper::org::webRtc::RTCStatsType::RTCStatsType_remoteCandidate:
      {
        return RTCIceCandidateStats::toWrapper(std::move(value));
      }
      case wrapper::org::webRtc::RTCStatsType::RTCStatsType_certificate:
      {
        return RTCCertificateStats::toWrapper(std::move(value));
      }
    }
  } else {
    auto other = get_statsTypeOther(value.get());
    if (other == ::webrtc::RTCIceCandidateStats::kType) {
      return RTCIceCandidateStats::toWrapper(std::move(value));
    }
  }

  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = std::move(value);
  return result;
}

//------------------------------------------------------------------------------
::zsLib::Time WrapperImplType::get_timestamp(const NativeType *native) noexcept
{
  if (!native) return ::zsLib::Time();

  auto since1970 = native->timestamp_us();
  zsLib::Time t = sys_days(jan / 1 / 1970);
  zsLib::Microseconds converted = zsLib::Microseconds(SafeInt<zsLib::Microseconds::rep>(since1970));
  return t + converted;
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > WrapperImplType::get_statsType(const NativeType *native) noexcept
{
  if (!native) return Optional< wrapper::org::webRtc::RTCStatsType >();

  try {
    return UseEnum::toWrapperRTCStatsType(native->type());
  } catch (const InvalidParameters &) {
  }
  return Optional<wrapper::org::webRtc::RTCStatsType>();
}

//------------------------------------------------------------------------------
String WrapperImplType::get_statsTypeOther(const NativeType *native) noexcept
{
  if (!native) return String();

  return String(native->type());
}

//------------------------------------------------------------------------------
String WrapperImplType::get_id(const NativeType *native) noexcept
{
  if (!native) return String();
  return native->id();
}

//------------------------------------------------------------------------------
NativeTypeUniPtr WrapperImplType::toNative(WrapperImplTypePtr value) noexcept
{
  if (!value) return NativeTypeUniPtr();

  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, value);
  if (!converted) return NativeTypeUniPtr();
  return converted->native_->copy();
}
