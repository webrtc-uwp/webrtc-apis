

#ifndef CX_USE_GENERATED_ORG_WEBRTC_EVENTQUEUE

#include <wrapper/generated/cx/cx_Helpers.h>
#include <wrapper/generated/cx/Org_WebRtc_EventQueue.h>

//------------------------------------------------------------------------------
::Org::WebRtc::EventQueue^ Org::WebRtc::EventQueue::ToCx(wrapper::org::webRtc::EventQueuePtr value)
{
  if (!value) return nullptr;
  auto result = ref new EventQueue(WrapperCreate{});
  result->native_ = value;
  return result;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::EventQueuePtr Org::WebRtc::EventQueue::FromCx(::Org::WebRtc::EventQueue^ value)
{
  if (nullptr == value) return wrapper::org::webRtc::EventQueuePtr();
  return value->native_;
}

#if 0
//------------------------------------------------------------------------------
Org::WebRtc::EventQueue::EventQueue(Platform::Object^ queue)
 : native_(wrapper::org::webRtc::EventQueue::wrapper_create())
{
  if (!native_) {throw ref new Platform::NullReferenceException();}
  native_->wrapper_init_org_webRtc_EventQueue(::Internal::Helper::FromCx(queue));
}
#endif //0

//------------------------------------------------------------------------------
::Org::WebRtc::EventQueue^ Org::WebRtc::EventQueue::GetOrCreateThreadQueueByName(Platform::String^ queueName)
{
  ::Org::WebRtc::EventQueue^ result{};
  result = ::Internal::Helper::ToCx_Org_WebRtc_EventQueue(wrapper::org::webRtc::EventQueue::getOrCreateThreadQueueByName(::Internal::Helper::FromCx_String(queueName)));
  return result;
}

//------------------------------------------------------------------------------
::Org::WebRtc::EventQueue^ Org::WebRtc::EventQueue::CreateThreadQueuePool(
  Platform::String^ queueName,
  uint64 minimumNumberOfThreads
)
{
  ::Org::WebRtc::EventQueue^ result{};
  result = ::Internal::Helper::ToCx_Org_WebRtc_EventQueue(wrapper::org::webRtc::EventQueue::createThreadQueuePool(::Internal::Helper::FromCx_String(queueName), ::Internal::Helper::FromCx_Uint64(minimumNumberOfThreads)));
  return result;
}

//------------------------------------------------------------------------------
::Org::WebRtc::EventQueue^ Org::WebRtc::EventQueue::GetDefaultForUi()
{
  ::Org::WebRtc::EventQueue^ result {};
  result = ::Internal::Helper::ToCx_Org_WebRtc_EventQueue(wrapper::org::webRtc::EventQueue::getDefaultForUi());
  return result;
}

#if 0
//------------------------------------------------------------------------------
Platform::Object^ Org::WebRtc::EventQueue::Queue::get()
{
  if (!native_) {throw ref new Platform::NullReferenceException();}
  return ::Internal::Helper::ToCx(native_->get_queue());
}
#endif //0

#endif //ifndef CX_USE_GENERATED_ORG_WEBRTC_EVENTQUEUE
