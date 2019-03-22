
#ifndef C_USE_GENERATED_ORG_WEBRTC_MEDIAELEMENTMAKER

#pragma once

#include "types.h"


ORG_WEBRTC_WRAPPER_C_PLUS_PLUS_BEGIN_GUARD


/* org_webRtc_MediaElementMaker*/

ORG_WEBRTC_WRAPPER_C_EXPORT_API org_webRtc_MediaElement_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaElementMaker_bind(zs_Any_t element);
ORG_WEBRTC_WRAPPER_C_EXPORT_API zs_Any_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaElementMaker_extract(org_webRtc_MediaElement_t element);


ORG_WEBRTC_WRAPPER_C_PLUS_PLUS_END_GUARD

#ifdef __cplusplus


namespace wrapper
{
  org_webRtc_MediaElementMaker_t org_webRtc_MediaElementMaker_wrapperToHandle(wrapper::org::webRtc::MediaElementMakerPtr value);
  wrapper::org::webRtc::MediaElementMakerPtr org_webRtc_MediaElementMaker_wrapperFromHandle(org_webRtc_MediaElementMaker_t handle);

} /* namespace wrapper */
#endif /* __cplusplus */

#endif /* ifndef C_USE_GENERATED_ORG_WEBRTC_MEDIAELEMENTMAKER */
