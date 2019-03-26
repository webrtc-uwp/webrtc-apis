
#ifndef C_USE_GENERATED_ORG_WEBRTC_MEDIASOURCE

#pragma once

#include "types.h"


ORG_WEBRTC_WRAPPER_C_PLUS_PLUS_BEGIN_GUARD


/* org_webRtc_MediaSource*/

ORG_WEBRTC_WRAPPER_C_EXPORT_API org_webRtc_MediaSource_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaSource_wrapperClone(org_webRtc_MediaSource_t handle);
ORG_WEBRTC_WRAPPER_C_EXPORT_API void ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaSource_wrapperDestroy(org_webRtc_MediaSource_t handle);
ORG_WEBRTC_WRAPPER_C_EXPORT_API instance_id_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaSource_wrapperInstanceId(org_webRtc_MediaSource_t handle);


ORG_WEBRTC_WRAPPER_C_PLUS_PLUS_END_GUARD

#ifdef __cplusplus


namespace wrapper
{
  org_webRtc_MediaSource_t org_webRtc_MediaSource_wrapperToHandle(wrapper::org::webRtc::MediaSourcePtr value);
  wrapper::org::webRtc::MediaSourcePtr org_webRtc_MediaSource_wrapperFromHandle(org_webRtc_MediaSource_t handle);

} /* namespace wrapper */
#endif /* __cplusplus */

#endif /* ifndef C_USE_GENERATED_ORG_WEBRTC_MEDIASOURCE */
