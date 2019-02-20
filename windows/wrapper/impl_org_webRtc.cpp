
#include <zsLib/Log.h>

#include "Org.WebRtc.Glue.events.h"
#include "Org.WebRtc.Glue.events.jman.h"

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_IMPLEMENT_SUBSYSTEM(wrapper_org_webRtc); } } } }

ZS_EVENTING_SUBSYSTEM_DEFAULT_LEVEL(wrapper_org_webRtc, Debug)

namespace wrapper {
namespace impl {
namespace org {
namespace webRtc {

void initSubsystems() noexcept
{
  ZS_GET_SUBSYSTEM_LOG_LEVEL(ZS_GET_OTHER_SUBSYSTEM(wrapper::impl::org::webRtc, wrapper_org_webRtc));
  ZS_EVENTING_REGISTER(Org_WebRtc_Glue);
}

} // namespace webRtc
} // namespace impl
} // namespace org
} // namespace webRtc
