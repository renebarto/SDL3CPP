//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : StringTraceLineWriter.cpp
//
// Namespace   : tracing
//
// Class       : StringTraceLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#include "tracing/StringTraceLineWriter.h"

#include "tracing/TraceRegistryItem.h"

namespace tracing {

void StringTraceLineWriter::WriteLine(TraceCategory /*category*/, const std::string& line)
{
    m_result.push_back(line);
}

void StringTraceLineWriter::ResetResult()
{
    m_result = {};
}

std::vector<std::string> StringTraceLineWriter::GetResult() const
{
    return m_result;
}

} // namespace tracing

DEFINE_TRACE_ENTRY();
