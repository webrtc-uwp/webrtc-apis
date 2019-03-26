
#ifndef C_USE_GENERATED_ORG_WEBRTC_MEDIAELEMENTMAKER

#include "c_helpers.h"
#include <zsLib/types.h>
#include <zsLib/eventing/types.h>
#include <zsLib/SafeInt.h>

#include "c_org_webRtc_MediaElementMaker.h"
#include "../org_webRtc_MediaElementMaker.h"
#include "c_org_webRtc_MediaElement.h"

#include <wrapper/impl_org_webRtc_MediaElement.h>


using namespace wrapper;

//------------------------------------------------------------------------------
org_webRtc_MediaElement_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaElementMaker_bind(uintptr_t element)
{
  return wrapper::org_webRtc_MediaElement_wrapperToHandle(wrapper::impl::org::webRtc::MediaElement::toWrapper((HWND)element));
}

//------------------------------------------------------------------------------
uintptr_t ORG_WEBRTC_WRAPPER_C_CALLING_CONVENTION org_webRtc_MediaElementMaker_extract(org_webRtc_MediaElement_t element)
{
  auto result = wrapper::impl::org::webRtc::MediaElement::toNative(wrapper::org_webRtc_MediaElement_wrapperFromHandle(element));
  return ((uintptr_t)result);
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
