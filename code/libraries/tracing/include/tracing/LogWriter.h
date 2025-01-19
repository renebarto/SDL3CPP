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

#include "tracing/ILogLineWriter.h"
#include "tracing/ILogWriter.h"

namespace tracing {

class LogWriter
    : public ILogWriter
{
private:
    ILogLineWriter& m_writer;

public:
    LogWriter(ILogLineWriter& writer);

    void Log(
        osal::EpochTime timestamp,
        const std::string& msg) override;
};

} // namespace tracing
