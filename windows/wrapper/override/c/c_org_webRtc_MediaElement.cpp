
#ifndef C_USE_GENERATED_ORG_WEBRTC_MEDIAELEMENT

#include "c_helpers.h"
#include <zsLib/types.h>
#include <zsLib/eventing/types.h>
#include <zsLib/SafeInt.h>

#include "c_org_webRtc_MediaElement.h"
#include "../org_webRtc_MediaElement.h"

using namespace wrapper;

//------------------------------------------------------------------------------
org_webRtc_MediaElement_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaElement_wrapperClone(org_webRtc_MediaElement_t handle)
{
  typedef wrapper::org::webRtc::MediaElementPtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return 0;
  return reinterpret_cast<org_webRtc_MediaElement_t>(new WrapperTypePtr(*reinterpret_cast<WrapperTypePtrRawPtr>(handle)));
}

//------------------------------------------------------------------------------
void ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaElement_wrapperDestroy(org_webRtc_MediaElement_t handle)
{
  typedef wrapper::org::webRtc::MediaElementPtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return;
  delete reinterpret_cast<WrapperTypePtrRawPtr>(handle);
}

//------------------------------------------------------------------------------
instance_id_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaElement_wrapperInstanceId(org_webRtc_MediaElement_t handle)
{
  typedef wrapper::org::webRtc::MediaElementPtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return 0;
  return reinterpret_cast<instance_id_t>((*reinterpret_cast<WrapperTypePtrRawPtr>(handle)).get());
}

//------------------------------------------------------------------------------
org_webRtc_MediaElement_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaElement_wrapperCreate_MediaElementWithNativeQueue(zs_Any_t element)
{
  auto wrapperThis = wrapper::org::webRtc::MediaElement::wrapper_create();
  wrapperThis->wrapper_init_org_webRtc_MediaElement(wrapper::zs_Any_wrapperFromHandle(element));
  return wrapper::org_webRtc_MediaElement_wrapperToHandle(wrapperThis);
}

//------------------------------------------------------------------------------
zs_Any_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaElement_get_element(org_webRtc_MediaElement_t wrapperThisHandle)
{
  auto wrapperThis = wrapper::org_webRtc_MediaElement_wrapperFromHandle(wrapperThisHandle);
  return wrapper::zs_Any_wrapperToHandle(wrapperThis->get_element());
}


namespace wrapper
{
  //----------------------------------------------------------------------------
  org_webRtc_MediaElement_t org_webRtc_MediaElement_wrapperToHandle(wrapper::org::webRtc::MediaElementPtr value)
  {
    typedef org_webRtc_MediaElement_t CType;
    typedef wrapper::org::webRtc::MediaElementPtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (!value) return 0;
    return reinterpret_cast<CType>(new WrapperTypePtr(value));
  }

  //----------------------------------------------------------------------------
  wrapper::org::webRtc::MediaElementPtr org_webRtc_MediaElement_wrapperFromHandle(org_webRtc_MediaElement_t handle)
  {
    typedef wrapper::org::webRtc::MediaElementPtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (0 == handle) return WrapperTypePtr();
    return (*reinterpret_cast<WrapperTypePtrRawPtr>(handle));
  }


} /* namespace wrapper */

#endif /* ifndef C_USE_GENERATED_ORG_WEBRTC_MEDIAELEMENT */
