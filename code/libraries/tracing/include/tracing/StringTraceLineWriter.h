//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : StringTraceLineWriter.h
//
// Namespace   : tracing
//
// Class       : StringTraceLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "tracing/ITraceLineWriter.h"

namespace tracing {

class StringTraceLineWriter
    : public ITraceLineWriter
{
private:
    std::vector<std::string> m_result;

public:
    void WriteLine(TraceCategory category, const std::string& line) override;

    void ResetResult();
    std::vector<std::string> GetResult() const;
};

} // namespace tracing 
