//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : LogWriter.h
//
// Namespace   : tracing
//
// Class       : LogWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "osal/utilities/Clock.h"
#include "tracing/TraceCategory.h"

namespace tracing {

class ILogWriter
{
public:
    virtual ~ILogWriter() {}

    virtual void Log(
        osal::EpochTime timestamp,
        const std::string& msg) = 0;
};

} // namespace tracing
