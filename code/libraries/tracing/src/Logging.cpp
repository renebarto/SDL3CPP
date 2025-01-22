//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Logging.cpp
//
// Namespace   : tracing
//
// Class       : Logging
//
// Description :
//
//------------------------------------------------------------------------------

#include "tracing/Logging.h"

#include <iomanip>
#include "osal/utilities/Console.h"
#include "tracing/ConsoleLogLineWriter.h"
#include "utility/Error.h"
#include "tracing/FatalHandler.h"
#include "tracing/Tracing.h"
#include "tracing/TraceRegistryItem.h"
#include "tracing/TraceHelpers.h"
#include "tracing/LogWriter.h"

namespace tracing {

    Logging::Mutex Logging::m_logMutex;
    LogWriter* Logging::m_logWriter = nullptr;

    static ConsoleLogLineWriter s_console;
    static LogWriter s_logWriter(s_console);

    Logging::~Logging() noexcept
    {
    }

    void Logging::SetLogWriter(LogWriter* logWriter)
    {
        m_logWriter = logWriter;
    }

    void Logging::Log(const std::string& path, int line, const std::string& functionName, const std::string& msg)
    {
        Tracing::Trace(TraceCategory::Information, path, line, functionName, msg);
        Lock guard(m_logMutex);
        auto clock = osal::Clock();
        std::string fileName = ExtractFileName(path);
        if (m_logWriter != nullptr)
        {
            m_logWriter->Log(clock.CurrentTime(), msg);
        }
        else
        {
            s_logWriter.Log(clock.CurrentTime(), msg);
        }
    }

    void Logging::Error(const std::string& path, int line, const std::string& functionName, const utility::Error& error)
    {
        auto errorCode = error.ErrorCode();
        if (errorCode != -1)
        {
            Log(path, line, functionName, "Error code: {}", serialization::Serialize(error));
        }
        else
        {
            Log(path, line, functionName, "Error code: Unknown: {}", error.Message());
        }
    }
    
    void Logging::Error(const std::string& path, int line, const std::string& functionName, const utility::GenericError& error)
    {
        Log(path, line, functionName, serialization::Serialize(error));
    }
    
    void Logging::Fatal(const std::string& path, int line, const std::string& functionName, const utility::Error& error)
    {
        auto errorCode = error.ErrorCode();
        if (errorCode != -1)
        {
            Log(path, line, functionName, "Error code: {}", serialization::Serialize(error));
        }
        else
        {
            Log(path, line, functionName, "Error code: Unknown: {}", error.Message());
        }
        FatalHandler::FatalExit(error.ErrorCode());
    }
    
    void Logging::Fatal(const std::string& path, int line, const std::string& functionName, const utility::GenericError& error)
    {
        Log(path, line, functionName, serialization::Serialize(error));
        FatalHandler::FatalExit(1);
    }

} // namespace tracing

DEFINE_TRACE_ENTRY();
