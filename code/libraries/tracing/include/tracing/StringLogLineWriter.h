//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : StringLogLineWriter.h
//
// Namespace   : tracing
//
// Class       : StringLogLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <vector>
#include "tracing/ILogLineWriter.h"

namespace tracing {

class StringLogLineWriter
    : public ILogLineWriter
{
private:
    std::vector<std::string> m_result;

public:
    void WriteLine(const std::string& line) override;

    void ResetResult();
    std::vector<std::string> GetResult() const;
};

} // namespace tracing 
