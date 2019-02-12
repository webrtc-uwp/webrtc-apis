#pragma once

#ifdef WINUWP

#ifdef __has_include
#if __has_include(<winrt/windows.media.effects.h>)
#include <winrt/windows.media.effects.h>
#endif //__has_include(<winrt/windows.media.effects.h>)
#endif //__has_include

#ifdef CPPWINRT_VERSION

#include <algorithm>

namespace webrtc {
  template<typename T, typename U>
  U GetValueFromPropertySet(winrt::Windows::Foundation::Collections::IPropertySet const& propertySet, winrt::hstring const& key, U defaultValue)
  {
    try
    {
      return static_cast<U>(safe_cast<T>(winrt::unbox_value<T>(propertySet.Lookup(key))));
    }
    catch (winrt::hresult_out_of_bounds const& /*e*/)
    {
      // The key is not present in the PropertySet. Return the default value.
      return defaultValue;
    }
  }
}

#endif //CPPWINRT_VERSION
#endif //WINUWP
