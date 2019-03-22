
#ifndef C_USE_GENERATED_ORG_WEBRTC_MEDIAELEMENTMAKER

#include "c_helpers.h"
#include <zsLib/types.h>
#include <zsLib/eventing/types.h>
#include <zsLib/SafeInt.h>

#include "c_org_webRtc_MediaElementMaker.h"
#include "../org_webRtc_MediaElementMaker.h"
#include "c_org_webRtc_MediaElement.h"

using namespace wrapper;

//------------------------------------------------------------------------------
org_webRtc_MediaElement_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaElementMaker_bind(zs_Any_t element)
{
  return {};
  //return wrapper::org_webRtc_MediaElement_wrapperToHandle(wrapper::org::webRtc::MediaElementMaker::bind(wrapper::zs_Any_wrapperFromHandle(element)));
#define WARNING_TODO 1
#define WARNING_TODO 2
}

//------------------------------------------------------------------------------
zs_Any_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaElementMaker_extract(org_webRtc_MediaElement_t element)
{
  //return wrapper::zs_Any_wrapperToHandle(wrapper::org::webRtc::MediaElementMaker::extract(wrapper::org_webRtc_MediaElement_wrapperFromHandle(element)));
  return {};
#define WARNING_TODO 1
#define WARNING_TODO 2
}


namespace wrapper
{
  //----------------------------------------------------------------------------
  org_webRtc_MediaElementMaker_t org_webRtc_MediaElementMaker_wrapperToHandle(wrapper::org::webRtc::MediaElementMakerPtr value)
  {
    typedef org_webRtc_MediaElementMaker_t CType;
    typedef wrapper::org::webRtc::MediaElementMakerPtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (!value) return 0;
    return reinterpret_cast<CType>(new WrapperTypePtr(value));
  }

  //----------------------------------------------------------------------------
  wrapper::org::webRtc::MediaElementMakerPtr org_webRtc_MediaElementMaker_wrapperFromHandle(org_webRtc_MediaElementMaker_t handle)
  {
    typedef wrapper::org::webRtc::MediaElementMakerPtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (0 == handle) return WrapperTypePtr();
    return (*reinterpret_cast<WrapperTypePtrRawPtr>(handle));
  }


} /* namespace wrapper */

#endif /* ifndef C_USE_GENERATED_ORG_WEBRTC_MEDIAELEMENTMAKER */
