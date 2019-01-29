
#include "impl_org_webRtc_RTCSenderVideoTrackAttachmentStats.h"
#include "impl_org_webRtc_RTCVideoSenderStats.h"
#include "impl_org_webRtc_RTCVideoHandlerStats.h"
#include "impl_org_webRtc_RTCMediaHandlerStats.h"
#include "impl_org_webRtc_RTCStats.h"

#include "impl_org_webRtc_enums.h"
#include "Org.WebRtc.Glue.events.h"

#include <zsLib/SafeInt.h>

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

// borrow definitions from class
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeType, NativeType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::NativeStats, NativeStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCStats, ImplRTCStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCMediaHandlerStats, ImplRTCMediaHandlerStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCVideoHandlerStats, ImplRTCVideoHandlerStats);
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCVideoSenderStats, ImplRTCVideoSenderStats);

ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::IEnum, UseEnum);

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::RTCSenderVideoTrackAttachmentStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCSenderVideoTrackAttachmentStatsPtr wrapper::org::webRtc::RTCSenderVideoTrackAttachmentStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::~RTCSenderVideoTrackAttachmentStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
void wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::trace() noexcept
{
  if (!ZS_EVENTING_IS_LOGGING(Detail))
    return;

  auto type = get_statsType();

  ZS_EVENTING_16(
    x, i, Detail, RTCSenderVideoTrackAttachmentStats, stats, Stats, Info,
    string, type, type.has_value() ? UseEnum::toString(type.value()) : "",
    string, otherType, get_statsTypeOther(),
    string, id, get_id(),
    string, trackIdentifier, get_trackIdentifier(),
    bool, hasRemoteSourceValue, get_remoteSource().has_value(),
    bool, remoteSource, get_remoteSource().has_value() ? get_remoteSource().value() : false,
    bool, ended, get_ended(),
    string, kind, get_kind(),
    string, priority, UseEnum::toString(get_priority()),
    ulong, frameWidth, get_frameWidth(),
    ulong, frameHeight, get_frameHeight(),
    double, framesPerSecond, get_framesPerSecond(),
    ulong, framesCaptured, get_framesCaptured(),
    ulong, framesSent, get_framesSent(),
    ulong, hugeFramesSent, get_hugeFramesSent(),
    ulong, keyFramesSent, get_keyFramesSent()
  );
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_timestamp() noexcept
{
  return ImplRTCStats::get_timestamp(native_.get());
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_statsType() noexcept
{
  return ImplRTCStats::get_statsType(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_statsTypeOther() noexcept
{
  return ImplRTCStats::get_statsTypeOther(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_id() noexcept
{
  return ImplRTCStats::get_id(native_.get());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_trackIdentifier() noexcept
{
  return ImplRTCMediaHandlerStats::get_trackIdentifier(&cast());
}

//------------------------------------------------------------------------------
Optional< bool > wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_remoteSource() noexcept
{
  return ImplRTCMediaHandlerStats::get_remoteSource(&cast());
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_ended() noexcept
{
  return ImplRTCMediaHandlerStats::get_ended(&cast());
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_kind() noexcept
{
  return ImplRTCMediaHandlerStats::get_kind(&cast());
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCPriorityType wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_priority() noexcept
{
  return ImplRTCMediaHandlerStats::get_priority(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_frameWidth() noexcept
{
  return ImplRTCVideoHandlerStats::get_frameWidth(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_frameHeight() noexcept
{
  return ImplRTCVideoHandlerStats::get_frameHeight(&cast());
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_framesPerSecond() noexcept
{
  return ImplRTCVideoHandlerStats::get_framesPerSecond(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_framesCaptured() noexcept
{
  return ImplRTCVideoSenderStats::get_framesCaptured(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_framesSent() noexcept
{
  return ImplRTCVideoSenderStats::get_framesSent(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_hugeFramesSent() noexcept
{
  return ImplRTCVideoSenderStats::get_hugeFramesSent(&cast());
}

//------------------------------------------------------------------------------
unsigned long wrapper::impl::org::webRtc::RTCSenderVideoTrackAttachmentStats::get_keyFramesSent() noexcept
{
  return ImplRTCVideoSenderStats::get_keyFramesSent(&cast());
}

//------------------------------------------------------------------------------
WrapperTypePtr WrapperImplType::toWrapper(NativeTypeUniPtr value) noexcept
{
  if (!value) return WrapperTypePtr();
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->native_ = std::move(value);
  return result;
}

//------------------------------------------------------------------------------
const NativeStats &WrapperImplType::cast() noexcept
{
  ZS_ASSERT(native_);
  return native_->cast_to<NativeStats>();
}
