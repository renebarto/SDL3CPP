//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Tracing.h
//
// Namespace   : tracing
//
// Class       : Tracing
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
#include "utility/EnumBitSet.h"
#include "tracing/TraceCategory.h"

namespace utility {

class Error;
class GenericError;

}

namespace tracing {

class ITraceWriter;

using IsTraceCategoryEnabledFunction = std::function<bool(TraceCategory category)>;

class Tracing
{
private:
    // We might want to remove this over time, and use only the TraceFilter
    static IsTraceCategoryEnabledFunction m_isTraceCategoryEnabledFunc;

    static ITraceWriter* m_traceWriter;
    static utility::EnumBitSet<TraceCategory> m_defaultTraceFilter;

    typedef std::recursive_mutex Mutex;
    typedef std::lock_guard<Mutex> Lock;
    static Mutex m_traceMutex;

public:
    Tracing() = default;
    virtual ~Tracing() noexcept;
    
    static void SetDefaultTraceFilter(const utility::EnumBitSet<TraceCategory>& defaultFilter);
    static utility::EnumBitSet<TraceCategory> GetDefaultTraceFilter();

    static void SetTracingEnabledFunction(IsTraceCategoryEnabledFunction enabledFunc);
    
    static void SetTraceWriter(ITraceWriter* traceWriter);

    static bool IsTraceCategoryEnabled(TraceCategory category);
    static void Trace(TraceCategory category, const std::string& path, int line, const std::string& functionName, const std::string& message);
    template <typename ... Args>
    static void Trace(TraceCategory category, const std::string& path, int line, const std::string& functionName, const std::string& format, Args const& ... args) noexcept
    {
        if (IsTraceCategoryEnabled(category))
        {
            std::string str;
            utility::Format(str, format, args ...);
            Trace(category, path, line, functionName, str);
        }
    }

    static void Error(const std::string& path, int line, const std::string& functionName, const utility::Error& error);
    static void Error(const std::string& path, int line, const std::string& functionName, const utility::GenericError& error);
    static void Fatal(const std::string& path, int line, const std::string& functionName, const utility::Error& error);
    static void Fatal(const std::string& path, int line, const std::string& functionName, const utility::GenericError& error);
    static void Throw(const std::string& path, int line, const std::string& functionName, const utility::Error& error);
    static void Throw(const std::string& path, int line, const std::string& functionName, const utility::GenericError& error);
};

} // namespace tracing

inline void TraceFuncEnter(const std::string& path, int line, const std::string& functionName, const std::string& message)
{
    tracing::Tracing::Trace(tracing::TraceCategory::FunctionEnter, path, line, functionName, message);
}
template <typename ... Args>
inline void TraceFuncEnter(const std::string& path, int line, const std::string& functionName, const std::string& format, Args const& ... args) noexcept
{
    tracing::Tracing::Trace(tracing::TraceCategory::FunctionEnter, path, line, functionName, format, args ...);
}

inline void TraceFuncLeave(const std::string& path, int line, const std::string& functionName, const std::string& message)
{
    tracing::Tracing::Trace(tracing::TraceCategory::FunctionLeave, path, line, functionName, message);
}
template <typename ... Args>
inline void TraceFuncLeave(const std::string& path, int line, const std::string& functionName, const std::string& format, Args const& ... args) noexcept
{
    tracing::Tracing::Trace(tracing::TraceCategory::FunctionLeave, path, line, functionName, format, args ...);
}

inline void TraceDebug(const std::string& path, int line, const std::string& functionName, const std::string& message)
{
    tracing::Tracing::Trace(tracing::TraceCategory::Debug, path, line, functionName, message);
}
template <typename ... Args>
inline void TraceDebug(const std::string& path, int line, const std::string& functionName, const std::string& format, Args const& ... args) noexcept
{
    tracing::Tracing::Trace(tracing::TraceCategory::Debug, path, line, functionName, format, args ...);
}

inline void TraceInfo(const std::string& path, int line, const std::string& functionName, const std::string& message)
{
    tracing::Tracing::Trace(tracing::TraceCategory::Information, path, line, functionName, message);
}
template <typename ... Args>
inline void TraceInfo(const std::string& path, int line, const std::string& functionName, const std::string& format, Args const& ... args) noexcept
{
    tracing::Tracing::Trace(tracing::TraceCategory::Information, path, line, functionName, format, args ...);
}

inline void TraceWarning(const std::string& path, int line, const std::string& functionName, const std::string& message)
{
    tracing::Tracing::Trace(tracing::TraceCategory::Warning, path, line, functionName, message);
}
template <typename ... Args>
inline void TraceWarning(const std::string& path, int line, const std::string& functionName, const std::string& format, Args const& ... args) noexcept
{
    tracing::Tracing::Trace(tracing::TraceCategory::Warning, path, line, functionName, format, args ...);
}

inline void TraceError(const std::string& path, int line, const std::string& functionName, const std::string& message)
{
    tracing::Tracing::Trace(tracing::TraceCategory::Error, path, line, functionName, message);
}
template <typename ... Args>
inline void TraceError(const std::string& path, int line, const std::string& functionName, const std::string& format, Args const& ... args) noexcept
{
    tracing::Tracing::Trace(tracing::TraceCategory::Error, path, line, functionName, format, args ...);
}

inline void TraceFatal(const std::string& path, int line, const std::string& functionName, const std::string& message)
{
    tracing::Tracing::Trace(tracing::TraceCategory::Fatal, path, line, functionName, message);
}
template <typename ... Args>
inline void TraceFatal(const std::string& path, int line, const std::string& functionName, const std::string& format, Args const& ... args) noexcept
{
    tracing::Tracing::Trace(tracing::TraceCategory::Fatal, path, line, functionName, format, args ...);
}

inline void TraceFatalCheck(bool condition, const std::string& path, int line, const std::string& functionName, const std::string& message)
{
    if (!condition)
    {
        tracing::Tracing::Fatal(path, line, functionName, utility::GenericError(message));
    }
}

template <typename ... Args>
inline void TraceFatalCheck(bool condition, const std::string& path, int line, const std::string& functionName, const std::string& format, Args const& ... args) noexcept
{
    if (!condition)
    {
        tracing::Tracing::Fatal(path, line, functionName, utility::GenericError(format, args ...));
    }
}

#define TRACE_INFRA(category, message, ...) tracing::Tracing::Trace(category, __FILE__, __LINE__, __func__, std::string(message), ## __VA_ARGS__)

#define FATAL(object) tracing::Tracing::Fatal(__FILE__, __LINE__, __func__, object)
#define ERROR(object) tracing::Tracing::Error(__FILE__, __LINE__, __func__, object)
#define TRACE_FATAL(message, ...) tracing::Tracing::Trace(tracing::TraceCategory::Fatal, __FILE__, __LINE__, __func__, std::string(message), ## __VA_ARGS__)
#define TRACE_ERROR(message, ...) tracing::Tracing::Trace(tracing::TraceCategory::Error, __FILE__, __LINE__, __func__, std::string(message), ## __VA_ARGS__)
#define TRACE_WARNING(message, ...) tracing::Tracing::Trace(tracing::TraceCategory::Warning, __FILE__, __LINE__, __func__, std::string(message), ## __VA_ARGS__)
#define TRACE_THROW(object) tracing::Tracing::Throw(__FILE__, __LINE__, __func__, object)

#define TRACE_INFO(message, ...) tracing::Tracing::Trace(tracing::TraceCategory::Information, __FILE__, __LINE__, __func__, std::string(message), ## __VA_ARGS__)
#define TRACE_DEBUG(message, ...) tracing::Tracing::Trace(tracing::TraceCategory::Debug, __FILE__, __LINE__, __func__, std::string(message), ## __VA_ARGS__)

#define TRACE_FATALCHECK(condition, message, ...) TraceFatalCheck(condition, __FILE__, __LINE__, __func__, std::string(message), ## __VA_ARGS__)
