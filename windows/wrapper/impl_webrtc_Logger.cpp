

#include "impl_webrtc_Logger.h"
#include "Org.WebRtc.Glue.events.h"

#include "impl_org_webRtc_pre_include.h"
#include "rtc_base/logging.h"
#include "impl_org_webRtc_post_include.h"

#include <zsLib/Log.h>

#include <memory>

using std::make_shared;
using zsLib::Lock;
using zsLib::AutoLock;
using zsLib::RecursiveLock;
using zsLib::AutoRecursiveLock;

namespace webrtc { namespace log { ZS_DECLARE_SUBSYSTEM(webrtc); } }

namespace webrtc
{
  namespace log
  {
    ZS_DECLARE_CLASS_PTR(Logger);

    class Logger : public ::rtc::LogSink,
                   public zsLib::ILogSubsystemDelegate
    {
      struct make_private {};

    protected:
      //-----------------------------------------------------------------------
      void init()
      {
      }

    public:
      //-----------------------------------------------------------------------
      Logger(const make_private &)
      {}

      //-----------------------------------------------------------------------
      ~Logger()
      {
        currentSeverity_ = rtc::LoggingSeverity::LS_NONE;
        currentLoggingCount_ = 0;
        currentEventingCount_ = 0;
        setupLoggingIfNeeded();
      }

      //-----------------------------------------------------------------------
      static LoggerPtr create()
      {
        auto pThis = make_shared<Logger>(make_private{});
        pThis->thisWeak_ = pThis;
        pThis->init();
        return pThis;
      }

      //-----------------------------------------------------------------------
      static void setup()
      {
        zsLib::Log::addSubsystemDelegate(create());
      }

    protected:
      // rtc::LogSink

      //-----------------------------------------------------------------------
      void OnLogMessage(
        const std::string& msg,
        ::rtc::LoggingSeverity severity,
        const char* tag) override
      {
        switch (severity)
        {
          case rtc::LoggingSeverity::LS_SENSITIVE:
          case rtc::LoggingSeverity::LS_VERBOSE:
          case rtc::LoggingSeverity::LS_INFO:
          case rtc::LoggingSeverity::LS_NONE:
          {
            ZS_EVENTING_3(
              x, i, Basic, OnLogMessageInfo, webrtc, Logging, Info,
              string, severity, toString(severity),
              string, message, msg.c_str(),
              string, tag, tag);
            break;
          }
          case rtc::LoggingSeverity::LS_ERROR:
          {
            ZS_EVENTING_3(
              x, e, Basic, OnLogMessageError, webrtc, Logging, Info,
              string, severity, toString(severity),
              string, message, msg.c_str(),
              string, tag, tag);
            break;
          }
          case rtc::LoggingSeverity::LS_WARNING:
          {
            ZS_EVENTING_3(
              x, w, Basic, OnLogMessageWarning, webrtc, Logging, Info,
              string, severity, toString(severity),
              string, message, msg.c_str(),
              string, tag, tag);
            break;
          }
        }
      }

      //-----------------------------------------------------------------------
      void OnLogMessage(const std::string& message) override
      {
        ZS_EVENTING_3(
          x, i, Basic, OnLogMessageInfo, webrtc, Logging, Info,
          string, severity, toString(rtc::LoggingSeverity::LS_INFO),
          string, message, message.c_str(),
          string, tag, "");
      }

      //ILogSubsystemDelegate
      //-----------------------------------------------------------------------
      void notifySubsystemLevelChange(ZS_MAYBE_USED() zsLib::Subsystem &inSubsystem) noexcept override
      {
        if ((&(ZS_GET_SUBSYSTEM())) != (&inSubsystem))
          return;

        AutoRecursiveLock lock(lock_);
        auto levelEventing = toNative(inSubsystem.getEventingLevel());
        currentSeverity_ = toNative(inSubsystem.getEventingLevel());
        setupLoggingIfNeeded();
      }

      //-----------------------------------------------------------------------
      void notifyLogSubscriberTotalChanged(size_t count) noexcept override
      {
        AutoRecursiveLock lock(lock_);
        currentLoggingCount_ = count;
        setupLoggingIfNeeded();
      }

      //-----------------------------------------------------------------------
      void notifyEventingSubscriberTotalChanged(size_t count) noexcept override
      {
        AutoRecursiveLock lock(lock_);
        currentEventingCount_ = count;
        setupLoggingIfNeeded();
      }

      //-----------------------------------------------------------------------
      static rtc::LoggingSeverity toNative(zsLib::Log::Level level)
      {
        switch (level)
        {
          case zsLib::Log::Level::None:     return rtc::LoggingSeverity::LS_NONE;
          case zsLib::Log::Level::Basic:    return rtc::LoggingSeverity::LS_ERROR;
          case zsLib::Log::Level::Detail:   return rtc::LoggingSeverity::LS_WARNING;
          case zsLib::Log::Level::Debug:    return rtc::LoggingSeverity::LS_INFO;
          case zsLib::Log::Level::Trace:    return rtc::LoggingSeverity::LS_VERBOSE;
          case zsLib::Log::Level::Insane:   return rtc::LoggingSeverity::LS_SENSITIVE;
        }
        return rtc::LoggingSeverity::LS_NONE;
      }

      //-----------------------------------------------------------------------
      static const char *toString(rtc::LoggingSeverity severity)
      {
        switch (severity)
        {
          case rtc::LoggingSeverity::LS_NONE:       return "none";
          case rtc::LoggingSeverity::LS_ERROR:      return "error";
          case rtc::LoggingSeverity::LS_WARNING:    return "warning";
          case rtc::LoggingSeverity::LS_INFO:       return "info";;
          case rtc::LoggingSeverity::LS_VERBOSE:    return "verbose";
          case rtc::LoggingSeverity::LS_SENSITIVE:  return "sensitive";
        }
        return "unknown";
      }

      //-----------------------------------------------------------------------
      void setupLoggingIfNeeded()
      {
        // WARNING: must be called within a lock
        bool severityChanged = lastSeverity_ != currentSeverity_;
        bool needsLogging = ((currentEventingCount_ + currentLoggingCount_) > 0) && (rtc::LoggingSeverity::LS_NONE != currentSeverity_);
        bool hasLogging = (lastSeverity_ > 0) && (rtc::LoggingSeverity::LS_NONE != lastCount_);

        lastSeverity_ = currentSeverity_;
        lastCount_ = currentEventingCount_ + currentLoggingCount_;

        rtc::LoggingSeverity level{ rtc::LoggingSeverity::LS_NONE };

        if (needsLogging) {
          if (!severityChanged)
            return;

          if (hasLogging) {
            rtc::LogMessage::RemoveLogToStream(this);
          }
          rtc::LogMessage::AddLogToStream(this, level);
          return;
        }

        if (!hasLogging)
          return;

        rtc::LogMessage::RemoveLogToStream(this);
      }

    private:
      LoggerWeakPtr thisWeak_;

      mutable RecursiveLock lock_;

      size_t currentLoggingCount_{};
      size_t currentEventingCount_{};
      rtc::LoggingSeverity currentSeverity_ { rtc::LoggingSeverity::LS_NONE };

      size_t lastCount_ {};
      rtc::LoggingSeverity lastSeverity_ {rtc::LoggingSeverity::LS_NONE};
    };
  }
} // namespace webrtc

//-----------------------------------------------------------------------------
void webrtc::log::ILogger::setup()
{
  webrtc::log::Logger::setup();
}
