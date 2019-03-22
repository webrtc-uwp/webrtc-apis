
#ifndef C_USE_GENERATED_ORG_WEBRTC_AUDIODATA

#include "c_helpers.h"
#include <zsLib/types.h>
#include <zsLib/eventing/types.h>
#include <zsLib/SafeInt.h>

#include "c_org_webRtc_AudioData.h"
#include "../org_webRtc_AudioData.h"

using namespace wrapper;

//------------------------------------------------------------------------------
org_webRtc_AudioData_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_AudioData_wrapperClone(org_webRtc_AudioData_t handle)
{
  typedef wrapper::org::webRtc::AudioDataPtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return 0;
  return reinterpret_cast<org_webRtc_AudioData_t>(new WrapperTypePtr(*reinterpret_cast<WrapperTypePtrRawPtr>(handle)));
}

//------------------------------------------------------------------------------
void ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_AudioData_wrapperDestroy(org_webRtc_AudioData_t handle)
{
  typedef wrapper::org::webRtc::AudioDataPtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return;
  delete reinterpret_cast<WrapperTypePtrRawPtr>(handle);
}

//------------------------------------------------------------------------------
instance_id_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_AudioData_wrapperInstanceId(org_webRtc_AudioData_t handle)
{
  typedef wrapper::org::webRtc::AudioDataPtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return 0;
  return reinterpret_cast<instance_id_t>((*reinterpret_cast<WrapperTypePtrRawPtr>(handle)).get());
}

//------------------------------------------------------------------------------
void ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_AudioData_wrapperDispose(org_webRtc_AudioData_t handle)
{
  typedef wrapper::org::webRtc::AudioDataPtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return;
  (*reinterpret_cast<WrapperTypePtrRawPtr>(handle))->wrapper_dispose();
}

//------------------------------------------------------------------------------
org_webRtc_AudioData_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_AudioData_wrapperCreate_AudioData()
{
  auto wrapperThis = wrapper::org::webRtc::AudioData::wrapper_create();
  wrapperThis->wrapper_init_org_webRtc_AudioData();
  return wrapper::org_webRtc_AudioData_wrapperToHandle(wrapperThis);
}

//------------------------------------------------------------------------------
bool_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_AudioData_get_readOnly(org_webRtc_AudioData_t wrapperThisHandle)
{
  auto wrapperThis = wrapper::org_webRtc_AudioData_wrapperFromHandle(wrapperThisHandle);
  return (wrapperThis->readOnly());
}

//------------------------------------------------------------------------------
std_list_int16_t_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_AudioData_get_data(org_webRtc_AudioData_t wrapperThisHandle)
{
  auto wrapperThis = wrapper::org_webRtc_AudioData_wrapperFromHandle(wrapperThisHandle);
  return {}; // wrapper::std_list_int16_t_wrapperToHandle(wrapperThis->get_data());

#define WARNING_TODO 1
#define WARNING_TODO 2
}

//------------------------------------------------------------------------------
void ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_AudioData_set_data(org_webRtc_AudioData_t wrapperThisHandle, std_list_int16_t_t value)
{
  auto wrapperThis = wrapper::org_webRtc_AudioData_wrapperFromHandle(wrapperThisHandle);
  //wrapperThis->set_data(wrapper::std_list_int16_t_wrapperFromHandle(value));

#define WARNING_TODO 1
#define WARNING_TODO 2
}


namespace wrapper
{
  //----------------------------------------------------------------------------
  org_webRtc_AudioData_t org_webRtc_AudioData_wrapperToHandle(wrapper::org::webRtc::AudioDataPtr value)
  {
    typedef org_webRtc_AudioData_t CType;
    typedef wrapper::org::webRtc::AudioDataPtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (!value) return 0;
    return reinterpret_cast<CType>(new WrapperTypePtr(value));
  }

  //----------------------------------------------------------------------------
  wrapper::org::webRtc::AudioDataPtr org_webRtc_AudioData_wrapperFromHandle(org_webRtc_AudioData_t handle)
  {
    typedef wrapper::org::webRtc::AudioDataPtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (0 == handle) return WrapperTypePtr();
    return (*reinterpret_cast<WrapperTypePtrRawPtr>(handle));
  }


} /* namespace wrapper */

#endif /* ifndef C_USE_GENERATED_ORG_WEBRTC_AUDIODATA */
