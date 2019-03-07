
#pragma once


//#include <wrapper/impl_org_webRtc_pre_include.h>
//#include "rtc_base/logging.h"
//#include <wrapper/impl_org_webRtc_post_include.h>

#include <zsLib/types.h>

namespace webrtc
{
  namespace etw
  {
    ZS_DECLARE_INTERACTION_PTR(ILogger);

    interaction ILogger
    {
      static void setup();
    };
  }
}
