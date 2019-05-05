
#pragma once

#ifdef __has_include
#if __has_include(<winrt/windows.ui.core.h>)
#include <winrt/windows.ui.core.h>
#endif //__has_include(<winrt/windows.ui.core.h>)
#endif //__has_include

#include "types.h"
#include "generated/org_webRtc_EventQueue.h"


namespace wrapper {
  namespace impl {
    namespace org {
      namespace webRtc {

        struct EventQueue : public wrapper::org::webRtc::EventQueue
        {
          ZS_DECLARE_TYPEDEF_PTR(wrapper::org::webRtc::EventQueue, WrapperType);
          ZS_DECLARE_TYPEDEF_PTR(wrapper::impl::org::webRtc::EventQueue, WrapperImplType);

          EventQueueWeakPtr thisWeak_;

#ifdef CPPWINRT_VERSION
          winrt::Windows::UI::Core::CoreDispatcher coreDispatcher_ {nullptr};
          winrt::Windows::System::DispatcherQueue dispatcherQueue_ {nullptr};
#endif // CPPWINRT_VERSION
          zsLib::IMessageQueuePtr queue_;

          EventQueue() noexcept;
          virtual ~EventQueue() noexcept;

          ZS_NO_DISCARD() static wrapper::org::webRtc::EventQueuePtr toWrapper(winrt::Windows::UI::Core::CoreDispatcher queue) noexcept;
          ZS_NO_DISCARD() static winrt::Windows::UI::Core::CoreDispatcher toNative_winrtCoreDispatcher(WrapperTypePtr queue) noexcept;
          ZS_NO_DISCARD() static wrapper::org::webRtc::EventQueuePtr toWrapper(winrt::Windows::System::DispatcherQueue  queue) noexcept;
          ZS_NO_DISCARD() static winrt::Windows::System::DispatcherQueue toNative_winrtDispatcherQueue(WrapperTypePtr queue) noexcept;

          ZS_NO_DISCARD() static wrapper::org::webRtc::EventQueuePtr toWrapper(::zsLib::IMessageQueuePtr queue) noexcept;
          ZS_NO_DISCARD() static ::zsLib::IMessageQueuePtr toNative(WrapperTypePtr queue) noexcept;

        };

      } // webRtc
    } // org
  } // namespace impl
} // namespace wrapper

