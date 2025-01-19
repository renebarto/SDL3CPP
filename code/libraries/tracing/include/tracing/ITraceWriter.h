//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ITraceWriter.h
//
// Namespace   : tracing
//
// Class       : ITraceWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "osal/utilities/Clock.h"
#include "tracing/TraceCategory.h"

namespace tracing {

class ITraceWriter
{
public:
    virtual ~ITraceWriter() {}

    virtual void Trace(
        osal::EpochTime timestamp,
        TraceCategory category,
        const std::string& fileName, 
        int line, 
        const std::string& functionName, 
        const std::string& msg) = 0;
};

} // namespace tracing
