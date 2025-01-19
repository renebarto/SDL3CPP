//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ILineWriter.h
//
// Namespace   : tracing
//
// Class       : ILineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <string>
#include "tracing/TraceCategory.h"

namespace tracing {

class ILineWriter {
public:
    virtual ~ILineWriter() = default;

    virtual void WriteLine(TraceCategory category, const std::string& line) = 0;
};

} // namespace tracing 
