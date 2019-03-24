
#include <wrapper/generated/c/c_helpers.h>

#include <wrapper/generated/org_webrtc_RTCError.h>

#include <zsLib/types.h>
#include <zsLib/eventing/types.h>
#include <zsLib/SafeInt.h>

namespace wrapper { namespace impl { namespace org { namespace webRtc { ZS_DECLARE_SUBSYSTEM(wrapper_org_webRtc); } } } }

using namespace wrapper;
using namespace wrapper::impl::org::webRtc;


namespace wrapper
{
  //----------------------------------------------------------------------------
  void Throwers::customThrow_set_Exception(exception_handle_t handle, const wrapper::org::webRtc::RTCErrorPtr &error) noexcept
  {
    try {
      if (!error) {
        ZS_THROW_UNEXPECTED_ERROR("No error object provided.");
      }

      String message = error->get_message();

      switch (error->get_type())
      {
        case wrapper::org::webRtc::RTCErrorType::RTCErrorType_none:                 break;
        case wrapper::org::webRtc::RTCErrorType::RTCErrorType_unsupportedOperation: ZS_THROW_NOT_IMPLEMENTED(message);
        case wrapper::org::webRtc::RTCErrorType::RTCErrorType_unsupportedParameter: ZS_THROW_NOT_SUPPORTED(message);
        case wrapper::org::webRtc::RTCErrorType::RTCErrorType_invalidParameter:     ZS_THROW_INVALID_ARGUMENT(message);
        case wrapper::org::webRtc::RTCErrorType::RTCErrorType_invalidRange:         ZS_THROW_RANGE_ERROR(message);
        case wrapper::org::webRtc::RTCErrorType::RTCErrorType_syntaxError:          ZS_THROW_SYNTAX_ERROR(message);
        case wrapper::org::webRtc::RTCErrorType::RTCErrorType_invalidState:         ZS_THROW_BAD_STATE(message);
        case wrapper::org::webRtc::RTCErrorType::RTCErrorType_invalidModification:  ZS_THROW_INVALID_MODIFICATION_ERROR(message);
        case wrapper::org::webRtc::RTCErrorType::RTCErrorType_networkError:         ZS_THROW_NETWORK_ERROR(message);
        case wrapper::org::webRtc::RTCErrorType::RTCErrorType_resourceExhausted:    ZS_THROW_RESOURCE_ERROR(message);
        case wrapper::org::webRtc::RTCErrorType::RTCErrorType_internalError:        ZS_THROW_INTERNAL_ERROR(message);
      }

      ZS_THROW_UNEXPECTED_ERROR(message);

    } catch (const ::zsLib::Exceptions::UnexpectedError &e) {
      exception_set_Exception(handle, std::make_shared<::zsLib::Exceptions::UnexpectedError>(e));
    } catch (const ::zsLib::Exceptions::NotImplemented &e) {
      exception_set_Exception(handle, std::make_shared<::zsLib::Exceptions::NotImplemented>(e));
    } catch (const ::zsLib::Exceptions::NotSupported &e) {
      exception_set_Exception(handle, std::make_shared<::zsLib::Exceptions::NotSupported>(e));
    } catch (const ::zsLib::Exceptions::BadState &e) {
      exception_set_Exception(handle, std::make_shared<::zsLib::Exceptions::BadState>(e));
    } catch (const ::zsLib::Exceptions::InvalidArgument &e) {
      exception_set_Exception(handle, std::make_shared<::zsLib::Exceptions::InvalidArgument>(e));
    } catch (const ::zsLib::Exceptions::RangeError &e) {
      exception_set_Exception(handle, std::make_shared<::zsLib::Exceptions::RangeError>(e));
    } catch (const ::zsLib::Exceptions::SyntaxError &e) {
      exception_set_Exception(handle, std::make_shared<::zsLib::Exceptions::SyntaxError>(e));
    } catch (const ::zsLib::Exceptions::InvalidModification &e) {
      exception_set_Exception(handle, std::make_shared<::zsLib::Exceptions::InvalidModification>(e));
    } catch (const ::zsLib::Exceptions::NetworkError &e) {
      exception_set_Exception(handle, std::make_shared<::zsLib::Exceptions::NetworkError>(e));
    } catch (const ::zsLib::Exceptions::ResourceError &e) {
      exception_set_Exception(handle, std::make_shared<::zsLib::Exceptions::ResourceError>(e));
    } catch (const ::zsLib::Exceptions::InternalError &e) {
      exception_set_Exception(handle, std::make_shared<::zsLib::Exceptions::InternalError>(e));
    }
  }

} /* namespace wrapper */
