
#ifndef C_USE_GENERATED_ORG_WEBRTC_EVENTQUEUEMAKER

#include "c_helpers.h"
#include <zsLib/types.h>
#include <zsLib/eventing/types.h>
#include <zsLib/SafeInt.h>

#include "c_org_webRtc_EventQueueMaker.h"
#include "../org_webRtc_EventQueueMaker.h"
#include "c_org_webRtc_EventQueue.h"

using namespace wrapper;


namespace wrapper
{
  //----------------------------------------------------------------------------
  org_webRtc_EventQueueMaker_t org_webRtc_EventQueueMaker_wrapperToHandle(wrapper::org::webRtc::EventQueueMakerPtr value)
  {
    typedef org_webRtc_EventQueueMaker_t CType;
    typedef wrapper::org::webRtc::EventQueueMakerPtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (!value) return 0;
    return reinterpret_cast<CType>(new WrapperTypePtr(value));
  }

  //----------------------------------------------------------------------------
  wrapper::org::webRtc::EventQueueMakerPtr org_webRtc_EventQueueMaker_wrapperFromHandle(org_webRtc_EventQueueMaker_t handle)
  {
    typedef wrapper::org::webRtc::EventQueueMakerPtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (0 == handle) return WrapperTypePtr();
    return (*reinterpret_cast<WrapperTypePtrRawPtr>(handle));
  }


} /* namespace wrapper */

#endif /* ifndef C_USE_GENERATED_ORG_WEBRTC_EVENTQUEUEMAKER */
