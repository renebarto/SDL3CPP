//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceWriter.h
//
// Namespace   : tracing
//
// Class       : TraceWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "tracing/ITraceLineWriter.h"
#include "tracing/ITraceWriter.h"

namespace tracing {

class TraceWriter
    : public ITraceWriter
{
private:
    ITraceLineWriter& m_writer;

public:
    TraceWriter(ITraceLineWriter& writer);

    void Trace(
        osal::EpochTime timestamp,
        TraceCategory category,
        const std::string& fileName, 
        int line, 
        const std::string& functionName, 
        const std::string& msg) override;
};

} // namespace tracing
