//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceWriter.cpp
//
// Namespace   : tracing
//
// Class       : TraceWriter
//
// Description :
//
//------------------------------------------------------------------------------

#include "tracing/TraceWriter.h"

#include <sstream>

#include "osal/utilities/ThreadFunctions.h"
#include "utility/Serialization.h"
#include "tracing/TraceRegistryItem.h"

namespace tracing {

TraceWriter::TraceWriter(ITraceLineWriter& writer)
    : m_writer(writer)
{
}

void TraceWriter::Trace(
    osal::EpochTime timestamp,
    TraceCategory category,
    const std::string& fileName, 
    int line, 
    const std::string& functionName, 
    const std::string& msg)
{
    std::ostringstream stream;
    stream << osal::Clock::ToString(timestamp) << "|" << category << "|" << fileName << ":" << line << "|" << functionName << "|" << osal::GetThreadNameSelf() << "|" << msg;
    m_writer.WriteLine(category, stream.str());
}

} // namespace tracing

DEFINE_TRACE_ENTRY();
