//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : StringLogLineWriter.cpp
//
// Namespace   : tracing
//
// Class       : StringLogLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#include "tracing/StringLogLineWriter.h"

#include "tracing/TraceRegistryItem.h"

namespace tracing {

void StringLogLineWriter::WriteLine(const std::string& line)
{
    m_result.push_back(line);
}

void StringLogLineWriter::ResetResult()
{
    m_result = {};
}

std::vector<std::string> StringLogLineWriter::GetResult() const
{
    return m_result;
}

} // namespace tracing

DEFINE_TRACE_ENTRY();
