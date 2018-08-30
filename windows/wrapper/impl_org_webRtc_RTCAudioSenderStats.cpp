// Generated by zsLibEventingTool

#include "impl_org_webRtc_RTCAudioSenderStats.h"

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::RTCAudioSenderStats::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCAudioSenderStats::RTCAudioSenderStats() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCAudioSenderStatsPtr wrapper::org::webRtc::RTCAudioSenderStats::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::RTCAudioSenderStats>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::RTCAudioSenderStats::~RTCAudioSenderStats() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
::zsLib::Time wrapper::impl::org::webRtc::RTCAudioSenderStats::get_timestamp() noexcept
{
  ::zsLib::Time result {};
  return result;
}

//------------------------------------------------------------------------------
Optional< wrapper::org::webRtc::RTCStatsType > wrapper::impl::org::webRtc::RTCAudioSenderStats::get_statsType() noexcept
{
  Optional< wrapper::org::webRtc::RTCStatsType > result {};
  return result;
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCAudioSenderStats::get_statsTypeOther() noexcept
{
  String result {};
  return result;
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCAudioSenderStats::get_id() noexcept
{
  String result {};
  return result;
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCAudioSenderStats::get_trackIdentifier() noexcept
{
  String result {};
  return result;
}

//------------------------------------------------------------------------------
Optional< bool > wrapper::impl::org::webRtc::RTCAudioSenderStats::get_remoteSource() noexcept
{
  Optional< bool > result {};
  return result;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::RTCAudioSenderStats::get_ended() noexcept
{
  bool result {};
  return result;
}

//------------------------------------------------------------------------------
String wrapper::impl::org::webRtc::RTCAudioSenderStats::get_kind() noexcept
{
  String result {};
  return result;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::RTCPriorityType wrapper::impl::org::webRtc::RTCAudioSenderStats::get_priority() noexcept
{
  wrapper::org::webRtc::RTCPriorityType result {};
  return result;
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCAudioSenderStats::get_audioLevel() noexcept
{
  double result {};
  return result;
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCAudioSenderStats::get_totalAudioEnergy() noexcept
{
  double result {};
  return result;
}

//------------------------------------------------------------------------------
bool wrapper::impl::org::webRtc::RTCAudioSenderStats::get_voiceActivityFlag() noexcept
{
  bool result {};
  return result;
}

//------------------------------------------------------------------------------
double wrapper::impl::org::webRtc::RTCAudioSenderStats::get_totalSamplesDuration() noexcept
{
  double result {};
  return result;
}

//------------------------------------------------------------------------------
Optional< double > wrapper::impl::org::webRtc::RTCAudioSenderStats::get_echoReturnLoss() noexcept
{
  Optional< double > result {};
  return result;
}

//------------------------------------------------------------------------------
Optional< double > wrapper::impl::org::webRtc::RTCAudioSenderStats::get_echoReturnLossEnhancement() noexcept
{
  Optional< double > result {};
  return result;
}

//------------------------------------------------------------------------------
unsigned long long wrapper::impl::org::webRtc::RTCAudioSenderStats::get_totalSamplesSent() noexcept
{
  unsigned long long result {};
  return result;
}

