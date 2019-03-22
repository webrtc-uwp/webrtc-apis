
#ifndef C_USE_GENERATED_ORG_WEBRTC_EVENTQUEUEMAKER

#pragma once

#include "types.h"


ORG_WEBRTC_WRAPPER_C_PLUS_PLUS_BEGIN_GUARD


/* org_webRtc_EventQueueMaker*/

ORG_WEBRTC_WRAPPER_C_EXPORT_API org_webRtc_EventQueue_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_EventQueueMaker_bind(zs_Any_t queue);
ORG_WEBRTC_WRAPPER_C_EXPORT_API zs_Any_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_EventQueueMaker_extract(org_webRtc_EventQueue_t queue);


ORG_WEBRTC_WRAPPER_C_PLUS_PLUS_END_GUARD

#ifdef __cplusplus


namespace wrapper
{
  org_webRtc_EventQueueMaker_t org_webRtc_EventQueueMaker_wrapperToHandle(wrapper::org::webRtc::EventQueueMakerPtr value);
  wrapper::org::webRtc::EventQueueMakerPtr org_webRtc_EventQueueMaker_wrapperFromHandle(org_webRtc_EventQueueMaker_t handle);

} /* namespace wrapper */
#endif /* __cplusplus */

#endif /* ifndef C_USE_GENERATED_ORG_WEBRTC_EVENTQUEUEMAKER */
