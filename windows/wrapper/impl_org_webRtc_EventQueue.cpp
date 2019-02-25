
#ifdef WINUWP

#ifdef __cplusplus_winrt
#include <windows.ui.core.h>
#endif //__cplusplus_winrt

#ifdef __has_include
#if __has_include(<winrt/windows.ui.core.h>)
#include <winrt/windows.ui.core.h>
#endif //__has_include(<winrt/windows.ui.core.h>)
#endif //__has_include

#else

#include <zsLib/IMessageQueue.h>
#endif //WINUWP

#include "impl_org_webRtc_EventQueue.h"
#include "impl_org_webRtc_helpers.h"

#include <zsLib/IMessageQueueManager.h>
#include <zsLib/IMessageQueueThread.h>
#include <zsLib/IMessageQueueDispatcher.h>

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
ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::EventQueue::WrapperImplType, WrapperImplType);
ZS_DECLARE_TYPEDEF_PTR(WrapperImplType::WrapperType, WrapperType);

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::EventQueue::EventQueue() noexcept
{
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::EventQueuePtr wrapper::org::webRtc::EventQueue::wrapper_create() noexcept
{
  auto pThis = make_shared<wrapper::impl::org::webRtc::EventQueue>();
  pThis->thisWeak_ = pThis;
  return pThis;
}

//------------------------------------------------------------------------------
wrapper::impl::org::webRtc::EventQueue::~EventQueue() noexcept
{
  thisWeak_.reset();
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::EventQueuePtr wrapper::org::webRtc::EventQueue::getOrCreateThreadQueueByName(String queueName) noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->queue_ = zsLib::IMessageQueueManager::getMessageQueue(queueName);
  return result;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::EventQueuePtr wrapper::org::webRtc::EventQueue::createThreadQueuePool(
  String queueName,
  uint64_t minimumNumberOfThreads
  ) noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->queue_ = zsLib::IMessageQueueManager::getThreadPoolQueue(queueName, SafeInt<size_t>(minimumNumberOfThreads));
  return result;
}

//------------------------------------------------------------------------------
wrapper::org::webRtc::EventQueuePtr wrapper::org::webRtc::EventQueue::getDefaultForUi() noexcept
{
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->queue_ = zsLib::IMessageQueueThread::singletonUsingCurrentGUIThreadsMessageQueue();
  return result;
}

#ifdef WINUWP
#ifdef CPPWINRT_VERSION

wrapper::org::webRtc::EventQueuePtr wrapper::impl::org::webRtc::EventQueue::toWrapper(winrt::Windows::UI::Core::CoreDispatcher queue) noexcept
{  
  if (!queue)
    return {};
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->dispatcher_ = queue;
  return result;
}

winrt::Windows::UI::Core::CoreDispatcher wrapper::impl::org::webRtc::EventQueue::toNative_winrt(WrapperTypePtr queue) noexcept
{            
  if (!queue)
    return {nullptr};
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, queue);
  if (!converted)
    return {nullptr};
  return converted->dispatcher_;
}

#endif // CPPWINRT_VERSION

#endif //WINUWP

wrapper::org::webRtc::EventQueuePtr wrapper::impl::org::webRtc::EventQueue::toWrapper(::zsLib::IMessageQueuePtr queue) noexcept
{
  if (!queue)
    return {};
  auto result = make_shared<WrapperImplType>();
  result->thisWeak_ = result;
  result->queue_ = queue;
  return result;
}

::zsLib::IMessageQueuePtr wrapper::impl::org::webRtc::EventQueue::toNative(wrapper::org::webRtc::EventQueuePtr queue) noexcept
{
  if (!queue)
    return {};
  auto converted = ZS_DYNAMIC_PTR_CAST(WrapperImplType, queue);
  if (!converted)
    return {};
  if (converted->dispatcher_)
    return zsLib::IMessageQueueDispatcher::create(converted->dispatcher_);
  return converted->queue_;
}
