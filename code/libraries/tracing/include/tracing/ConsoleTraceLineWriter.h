//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ConsoleTraceLineWriter.h
//
// Namespace   : tracing
//
// Class       : ConsoleTraceLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "tracing/ITraceLineWriter.h"

namespace tracing {

class ConsoleTraceLineWriter
    : public ITraceLineWriter
{
public:
    void WriteLine(TraceCategory category, const std::string& line) override;
};

} // namespace tracing 
