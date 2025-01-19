//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : LogWriter.cpp
//
// Namespace   : tracing
//
// Class       : LogWriter
//
// Description :
//
//------------------------------------------------------------------------------

#include "tracing/LogWriter.h"

#include <sstream>

#include "osal/utilities/ThreadFunctions.h"
#include "tracing/TraceCategory.h"
#include "utility/Serialization.h"
#include "tracing/TraceRegistryItem.h"

namespace tracing {

LogWriter::LogWriter(ILogLineWriter& writer)
    : m_writer(writer)
{
}

void LogWriter::Log(
    osal::EpochTime timestamp,
    const std::string& msg)
{
    std::ostringstream stream;
    stream << osal::Clock::ToString(timestamp) << "|" << msg;
    m_writer.WriteLine(stream.str());
}

} // namespace tracing

DEFINE_TRACE_ENTRY();
