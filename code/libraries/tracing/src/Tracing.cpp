//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Tracing.cpp
//
// Namespace   : tracing
//
// Class       : Tracing
//
// Description :
//
//------------------------------------------------------------------------------

#include "tracing/Tracing.h"

#include <iomanip>
#include "osal/utilities/Console.h"
#include "osal/utilities/ThreadFunctions.h"
#include "tracing/ConsoleTraceLineWriter.h"
#include "tracing/FatalHandler.h"
#include "utility/Error.h"
#include "tracing/LogWriter.h"
#include "tracing/TraceRegistryItem.h"
#include "tracing/TraceHelpers.h"
#include "tracing/TraceWriter.h"

using namespace utility;

namespace tracing {

IsTraceCategoryEnabledFunction Tracing::m_isTraceCategoryEnabledFunc = nullptr;
utility::EnumBitSet<TraceCategory> Tracing::m_defaultTraceFilter = 
    (TraceCategory::Fatal | TraceCategory::Error | TraceCategory::Information);
Tracing::Mutex Tracing::m_traceMutex;
ITraceWriter* Tracing::m_traceWriter = nullptr;

static ConsoleTraceLineWriter s_console;
static TraceWriter s_traceWriter(s_console);

Tracing::~Tracing() noexcept
{
}

void Tracing::SetTracingEnabledFunction(IsTraceCategoryEnabledFunction enabledFunc)
{
    m_isTraceCategoryEnabledFunc = enabledFunc;
}

void Tracing::SetDefaultTraceFilter(const utility::EnumBitSet<TraceCategory>& defaultFilter)
{
    Tracing::m_defaultTraceFilter = defaultFilter;
}

utility::EnumBitSet<TraceCategory> Tracing::GetDefaultTraceFilter()
{
    return Tracing::m_defaultTraceFilter;
}

void Tracing::SetTraceWriter(ITraceWriter* traceWriter)
{
    m_traceWriter = traceWriter;
}

bool Tracing::IsTraceCategoryEnabled(TraceCategory category)
{
    if (m_isTraceCategoryEnabledFunc != nullptr)
    {
        return m_isTraceCategoryEnabledFunc(category);
    }
    else
    {
        return m_defaultTraceFilter.IsSet(category);
    }
}

void Tracing::Trace(TraceCategory category, const std::string& path, int line, const std::string& functionName, const std::string& msg)
{
    if (!IsTraceCategoryEnabled(category))
        return;
    Lock guard(m_traceMutex);
    auto clock = osal::Clock();
    std::string fileName = ExtractFileName(path);
    if (m_traceWriter != nullptr)
    {
        m_traceWriter->Trace(clock.CurrentTime(), category, fileName, line, functionName, msg);
    }
    // Else do nothing
}

void Tracing::Error(const std::string& path, int line, const std::string& functionName, const utility::Error& error)
{
    auto errorCode = error.ErrorCode();
    if (errorCode != -1)
    {
        Trace(TraceCategory::Error, path, line, functionName, "Error code: {}", serialization::Serialize(error));
    }
    else
    {
        Trace(TraceCategory::Error, path, line, functionName, "Error code: Unknown: {}", error.Message());
    }
}

void Tracing::Error(const std::string& path, int line, const std::string& functionName, const utility::GenericError& error)
{
    Trace(TraceCategory::Error, path, line, functionName, serialization::Serialize(error));
}

void Tracing::Fatal(const std::string& path, int line, const std::string& functionName, const utility::Error& error)
{
    auto errorCode = error.ErrorCode();
    if (errorCode != -1)
    {
        Trace(TraceCategory::Fatal, path, line, functionName, "Error code: {}", serialization::Serialize(error));
    }
    else
    {
        Trace(TraceCategory::Fatal, path, line, functionName, "Error code: Unknown: {}", error.Message());
    }
    FatalHandler::FatalExit(error.ErrorCode());
}

void Tracing::Fatal(const std::string& path, int line, const std::string& functionName, const utility::GenericError& error)
{
    Trace(TraceCategory::Fatal, path, line, functionName, serialization::Serialize(error));
    FatalHandler::FatalExit(1);
}

void Tracing::Throw(const std::string& path, int line, const std::string& functionName, const utility::Error& error)
{
    std::ostringstream stream;
    stream 
        << osal::Clock() << "|" << TraceCategory::Information << " " << ExtractFileName(path) << ":" << line << " (" << functionName << "): " << error.Message() << ": Error code: "
        << std::dec << error.ErrorCode() << " (" << std::hex << std::setw(2) << std::setfill('0') << error.ErrorCode() << "): "
        << error.ErrorString();
    throw std::runtime_error(stream.str());
}

void Tracing::Throw(const std::string& path, int line, const std::string& functionName, const utility::GenericError& error)
{
    std::ostringstream stream;
    stream << osal::Clock() << "|" << TraceCategory::Information << " " << ExtractFileName(path) << ":" << line << " (" << functionName << "): " << error;
    throw std::runtime_error(stream.str());
}

} // namespace tracing

DEFINE_TRACE_ENTRY();
