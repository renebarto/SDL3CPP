//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Logging.h
//
// Namespace   : tracing
//
// Class       : Logging
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <functional>
#include <mutex>
#include <string>
#include "osal/utilities/Clock.h"
#include "utility/Format.h"
#include "utility/GenericError.h"
#include "tracing/LogEntry.h"

namespace utility {

class Error;
class GenericError;

}

namespace tracing {

class LogWriter;

using LogFunction = std::function<
    void (osal::EpochTime timestamp,
          const LogEntry&)>;

class Logging
{
private:
    static LogWriter* m_logWriter;

    typedef std::recursive_mutex Mutex;
    typedef std::lock_guard<Mutex> Lock;
    static Mutex m_logMutex;

public:
    Logging() = default;
    virtual ~Logging() noexcept;
        
    static void SetLogWriter(LogWriter* logWriter);

    static void Log(const std::string& path, int line, const std::string& functionName, const std::string& message);
    template <typename ... Args>
    static void Log(const std::string& path, int line, const std::string& functionName, const std::string& format, Args const& ... args) noexcept
    {
        std::string str;
        utility::Format(str, format, args ...);
        Log(path, line, functionName, str);
    }
    static void Error(const std::string& path, int line, const std::string& functionName, const utility::Error& error);
    static void Error(const std::string& path, int line, const std::string& functionName, const utility::GenericError& error);
    static void Fatal(const std::string& path, int line, const std::string& functionName, const utility::Error& error);
    static void Fatal(const std::string& path, int line, const std::string& functionName, const utility::GenericError& error);
};

} // namespace tracing

inline void LogError(const std::string& path, int line, const std::string& functionName, const std::string& message)
{
    tracing::Logging::Log(path, line, functionName, message);
}
template <typename ... Args>
static void LogError(const std::string& path, int line, const std::string& functionName, const std::string& format, Args const& ... args) noexcept
{
    tracing::Logging::Log(path, line, functionName, format, args ...);
}

inline void LogFatal(const std::string& path, int line, const std::string& functionName, const std::string& message)
{
    tracing::Logging::Fatal(path, line, functionName, utility::GenericError(message));
}

template <typename ... Args>
static void LogFatal(const std::string& path, int line, const std::string& functionName, const std::string& format, Args const& ... args) noexcept
{
    tracing::Logging::Fatal(path, line, functionName, utility::GenericError(format, args ...));
}

inline void LogFatalCheck(bool condition, const std::string& path, int line, const std::string& functionName, const std::string& message)
{
    if (!condition)
    {
        tracing::Logging::Fatal(path, line, functionName, utility::GenericError(message));
    }
}

template <typename ... Args>
inline void LogFatalCheck(bool condition, const std::string& path, int line, const std::string& functionName, const std::string& format, Args const& ... args) noexcept
{
    if (!condition)
    {
        tracing::Logging::Fatal(path, line, functionName, utility::GenericError(format, args ...));
    }
}

// TODO: Need to remove INFRA_ after merging tracing with common, operator-controls
#define LOG_INFRA(message, ...) tracing::Logging::Log(__FILE__, __LINE__, __func__, std::string(message), ## __VA_ARGS__)

#define LOG_ERROR(object) tracing::Logging::Error(__FILE__, __LINE__, __func__, object)
#define LOG_FATAL(object) tracing::Logging::Fatal(__FILE__, __LINE__, __func__, object)

#define LOG_FATALCHECK(condition, message, ...) LogFatalCheck(condition, __FILE__, __LINE__, __func__, std::string(message), ## __VA_ARGS__)
