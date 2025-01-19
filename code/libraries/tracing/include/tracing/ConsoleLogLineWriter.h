//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ConsoleLogLineWriter.h
//
// Namespace   : tracing
//
// Class       : ConsoleLogLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "tracing/ILogLineWriter.h"

namespace tracing {

class ConsoleLogLineWriter
    : public ILogLineWriter
{
public:
    void WriteLine(const std::string& line) override;
};

} // namespace tracing 
