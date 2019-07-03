
#ifndef C_USE_GENERATED_ORG_WEBRTC_VIDEODATA

#include "c_helpers.h"
#include <zsLib/types.h>
#include <zsLib/eventing/types.h>
#include <zsLib/SafeInt.h>

#include "c_org_webRtc_VideoData.h"
#include "../org_webRtc_VideoData.h"

using namespace wrapper;

//------------------------------------------------------------------------------
org_webRtc_VideoData_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_VideoData_wrapperClone(org_webRtc_VideoData_t handle)
{
  typedef wrapper::org::webRtc::VideoDataPtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return 0;
  return reinterpret_cast<org_webRtc_VideoData_t>(new WrapperTypePtr(*reinterpret_cast<WrapperTypePtrRawPtr>(handle)));
}

//------------------------------------------------------------------------------
void ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_VideoData_wrapperDestroy(org_webRtc_VideoData_t handle)
{
  typedef wrapper::org::webRtc::VideoDataPtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return;
  delete reinterpret_cast<WrapperTypePtrRawPtr>(handle);
}

//------------------------------------------------------------------------------
instance_id_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_VideoData_wrapperInstanceId(org_webRtc_VideoData_t handle)
{
  typedef wrapper::org::webRtc::VideoDataPtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return 0;
  return reinterpret_cast<instance_id_t>((*reinterpret_cast<WrapperTypePtrRawPtr>(handle)).get());
}

//------------------------------------------------------------------------------
void ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_VideoData_wrapperDispose(org_webRtc_VideoData_t handle)
{
  typedef wrapper::org::webRtc::VideoDataPtr WrapperTypePtr;
  typedef WrapperTypePtr * WrapperTypePtrRawPtr;
  if (0 == handle) return;
  (*reinterpret_cast<WrapperTypePtrRawPtr>(handle))->wrapper_dispose();
}

//------------------------------------------------------------------------------
org_webRtc_VideoData_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_VideoData_wrapperCreate_VideoData(uint64_t size)
{
  auto wrapperThis = wrapper::org::webRtc::VideoData::wrapper_create();
  wrapperThis->wrapper_init_org_webRtc_VideoData((size));
  return wrapper::org_webRtc_VideoData_wrapperToHandle(wrapperThis);
}

//------------------------------------------------------------------------------
bool_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_VideoData_get_is8BitColorSpace(org_webRtc_VideoData_t wrapperThisHandle)
{
  auto wrapperThis = wrapper::org_webRtc_VideoData_wrapperFromHandle(wrapperThisHandle);
  return (wrapperThis->get_is8BitColorSpace());
}

//------------------------------------------------------------------------------
bool_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_VideoData_get_is16BitColorSpace(org_webRtc_VideoData_t wrapperThisHandle)
{
  auto wrapperThis = wrapper::org_webRtc_VideoData_wrapperFromHandle(wrapperThisHandle);
  return (wrapperThis->get_is16BitColorSpace());
}

//------------------------------------------------------------------------------
binary_size_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_VideoData_get_size(org_webRtc_VideoData_t wrapperThisHandle)
{
  auto wrapperThis = wrapper::org_webRtc_VideoData_wrapperFromHandle(wrapperThisHandle);
  return wrapperThis->get_size();
}

//------------------------------------------------------------------------------
void ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_VideoData_get_data8bit(
  org_webRtc_VideoData_t wrapperThisHandle,
  uintptr_t buffer,
  binary_size_t size)
{
  auto wrapperThis = wrapper::org_webRtc_VideoData_wrapperFromHandle(wrapperThisHandle);

  auto data = wrapperThis->get_data8bit();
  auto actualSize = wrapperThis->get_size();
  size = size > actualSize ? actualSize : size;

  if (!data)
    return;

  auto ptr = reinterpret_cast<uint8_t *>(buffer);
  if (!ptr)
    return;

  memcpy(ptr, data, sizeof(uint8_t)*size);
}

//------------------------------------------------------------------------------
void ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_VideoData_set_data8bit(
  org_webRtc_VideoData_t wrapperThisHandle,
  uintptr_t buffer,
  binary_size_t size)
{
  auto wrapperThis = wrapper::org_webRtc_VideoData_wrapperFromHandle(wrapperThisHandle);

  auto data = wrapperThis->get_mutableData8bit();
  auto actualSize = wrapperThis->get_size();
  size = size > actualSize ? actualSize : size;

  if (!data)
    return;

  auto ptr = reinterpret_cast<uint8_t *>(buffer);
  if (!ptr)
    return;

  memcpy(data, ptr, sizeof(uint8_t)*size);
}

//------------------------------------------------------------------------------
void ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_VideoData_get_data16bit(
  org_webRtc_VideoData_t wrapperThisHandle,
  uintptr_t buffer,
  binary_size_t size)
{
  auto wrapperThis = wrapper::org_webRtc_VideoData_wrapperFromHandle(wrapperThisHandle);

  auto data = wrapperThis->get_data16bit();
  auto actualSize = wrapperThis->get_size();
  size = size > actualSize ? actualSize : size;

  if (!data)
    return;

  auto ptr = reinterpret_cast<uint16_t *>(buffer);
  if (!ptr)
    return;

  memcpy(ptr, data, sizeof(uint16_t)*size);
}

//------------------------------------------------------------------------------
void ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_VideoData_set_data16bit(
  org_webRtc_VideoData_t wrapperThisHandle,
  uintptr_t buffer,
  binary_size_t size)
{
  auto wrapperThis = wrapper::org_webRtc_VideoData_wrapperFromHandle(wrapperThisHandle);

  auto data = wrapperThis->get_mutableData16bit();
  auto actualSize = wrapperThis->get_size();
  size = size > actualSize ? actualSize : size;

  if (!data)
    return;

  auto ptr = reinterpret_cast<uint16_t *>(buffer);
  if (!ptr)
    return;

  memcpy(data, ptr, sizeof(uint16_t)*size);
}

namespace wrapper
{
  //----------------------------------------------------------------------------
  org_webRtc_VideoData_t org_webRtc_VideoData_wrapperToHandle(wrapper::org::webRtc::VideoDataPtr value)
  {
    typedef org_webRtc_VideoData_t CType;
    typedef wrapper::org::webRtc::VideoDataPtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (!value) return 0;
    return reinterpret_cast<CType>(new WrapperTypePtr(value));
  }

  //----------------------------------------------------------------------------
  wrapper::org::webRtc::VideoDataPtr org_webRtc_VideoData_wrapperFromHandle(org_webRtc_VideoData_t handle)
  {
    typedef wrapper::org::webRtc::VideoDataPtr WrapperTypePtr;
    typedef WrapperTypePtr * WrapperTypePtrRawPtr;
    if (0 == handle) return WrapperTypePtr();
    return (*reinterpret_cast<WrapperTypePtrRawPtr>(handle));
  }


} /* namespace wrapper */

#endif /* ifndef C_USE_GENERATED_ORG_WEBRTC_VIDEODATA */
