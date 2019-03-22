
#ifndef C_USE_GENERATED_ORG_WEBRTC_MEDIASAMPLE

#include "c_helpers.h"
#include <zsLib/types.h>
#include <zsLib/eventing/types.h>
#include <zsLib/SafeInt.h>

#include "c_org_webRtc_MediaSample.h"
#include "../org_webRtc_MediaSample.h"

using namespace wrapper;

//------------------------------------------------------------------------------
org_webRtc_MediaSample_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaSample_wrapperClone(org_webRtc_MediaSample_t handle)
{
  typedef wrapper::org::webRtc::MediaSamplePtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return 0;
  return reinterpret_cast<org_webRtc_MediaSample_t>(new WrapperTypePtr(*reinterpret_cast<WrapperTypePtrRawPtr>(handle)));
}

//------------------------------------------------------------------------------
void ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaSample_wrapperDestroy(org_webRtc_MediaSample_t handle)
{
  typedef wrapper::org::webRtc::MediaSamplePtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return;
  delete reinterpret_cast<WrapperTypePtrRawPtr>(handle);
}

//------------------------------------------------------------------------------
instance_id_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaSample_wrapperInstanceId(org_webRtc_MediaSample_t handle)
{
  typedef wrapper::org::webRtc::MediaSamplePtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return 0;
  return reinterpret_cast<instance_id_t>((*reinterpret_cast<WrapperTypePtrRawPtr>(handle)).get());
}

//------------------------------------------------------------------------------
std_list_float_t_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaSample_getCameraViewTransform(org_webRtc_MediaSample_t wrapperThisHandle)
{
  auto wrapperThis = wrapper::org_webRtc_MediaSample_wrapperFromHandle(wrapperThisHandle);
  if (!wrapperThis) return std_list_float_t_t();
  //return wrapper::std_list_float_t_wrapperToHandle(wrapperThis->getCameraViewTransform());
  return {};
#define WARNING_TODO 1
#define WARNING_TODO 2
}

//------------------------------------------------------------------------------
std_list_float_t_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaSample_getCameraProjectionTransform(org_webRtc_MediaSample_t wrapperThisHandle)
{
  auto wrapperThis = wrapper::org_webRtc_MediaSample_wrapperFromHandle(wrapperThisHandle);
  if (!wrapperThis) return std_list_float_t_t();
  //return wrapper::std_list_float_t_wrapperToHandle(wrapperThis->getCameraProjectionTransform());
  return {};
#define WARNING_TODO 1
#define WARNING_TODO 2
}


namespace wrapper
{
  //----------------------------------------------------------------------------
  org_webRtc_MediaSample_t org_webRtc_MediaSample_wrapperToHandle(wrapper::org::webRtc::MediaSamplePtr value)
  {
    typedef org_webRtc_MediaSample_t CType;
    typedef wrapper::org::webRtc::MediaSamplePtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (!value) return 0;
    return reinterpret_cast<CType>(new WrapperTypePtr(value));
  }

  //----------------------------------------------------------------------------
  wrapper::org::webRtc::MediaSamplePtr org_webRtc_MediaSample_wrapperFromHandle(org_webRtc_MediaSample_t handle)
  {
    typedef wrapper::org::webRtc::MediaSamplePtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (0 == handle) return WrapperTypePtr();
    return (*reinterpret_cast<WrapperTypePtrRawPtr>(handle));
  }


} /* namespace wrapper */

#endif /* ifndef C_USE_GENERATED_ORG_WEBRTC_MEDIASAMPLE */
