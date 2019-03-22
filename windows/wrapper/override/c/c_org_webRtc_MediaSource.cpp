
#ifndef C_USE_GENERATED_ORG_WEBRTC_MEDIASOURCE

#include "c_helpers.h"
#include <zsLib/types.h>
#include <zsLib/eventing/types.h>
#include <zsLib/SafeInt.h>

#include "c_org_webRtc_MediaSource.h"
#include "../org_webRtc_MediaSource.h"

using namespace wrapper;

//------------------------------------------------------------------------------
org_webRtc_MediaSource_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaSource_wrapperClone(org_webRtc_MediaSource_t handle)
{
  typedef wrapper::org::webRtc::MediaSourcePtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return 0;
  return reinterpret_cast<org_webRtc_MediaSource_t>(new WrapperTypePtr(*reinterpret_cast<WrapperTypePtrRawPtr>(handle)));
}

//------------------------------------------------------------------------------
void ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaSource_wrapperDestroy(org_webRtc_MediaSource_t handle)
{
  typedef wrapper::org::webRtc::MediaSourcePtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return;
  delete reinterpret_cast<WrapperTypePtrRawPtr>(handle);
}

//------------------------------------------------------------------------------
instance_id_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaSource_wrapperInstanceId(org_webRtc_MediaSource_t handle)
{
  typedef wrapper::org::webRtc::MediaSourcePtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return 0;
  return reinterpret_cast<instance_id_t>((*reinterpret_cast<WrapperTypePtrRawPtr>(handle)).get());
}

//------------------------------------------------------------------------------
org_webRtc_MediaSource_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaSource_wrapperCreate_MediaSourceWithNativeSource(zs_Any_t source)
{
  auto wrapperThis = wrapper::org::webRtc::MediaSource::wrapper_create();
  wrapperThis->wrapper_init_org_webRtc_MediaSource(wrapper::zs_Any_wrapperFromHandle(source));
  return wrapper::org_webRtc_MediaSource_wrapperToHandle(wrapperThis);
}

//------------------------------------------------------------------------------
zs_Any_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaSource_get_source(org_webRtc_MediaSource_t wrapperThisHandle)
{
  auto wrapperThis = wrapper::org_webRtc_MediaSource_wrapperFromHandle(wrapperThisHandle);
  return wrapper::zs_Any_wrapperToHandle(wrapperThis->get_source());
}


namespace wrapper
{
  //----------------------------------------------------------------------------
  org_webRtc_MediaSource_t org_webRtc_MediaSource_wrapperToHandle(wrapper::org::webRtc::MediaSourcePtr value)
  {
    typedef org_webRtc_MediaSource_t CType;
    typedef wrapper::org::webRtc::MediaSourcePtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (!value) return 0;
    return reinterpret_cast<CType>(new WrapperTypePtr(value));
  }

  //----------------------------------------------------------------------------
  wrapper::org::webRtc::MediaSourcePtr org_webRtc_MediaSource_wrapperFromHandle(org_webRtc_MediaSource_t handle)
  {
    typedef wrapper::org::webRtc::MediaSourcePtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (0 == handle) return WrapperTypePtr();
    return (*reinterpret_cast<WrapperTypePtrRawPtr>(handle));
  }


} /* namespace wrapper */

#endif /* ifndef C_USE_GENERATED_ORG_WEBRTC_MEDIASOURCE */
