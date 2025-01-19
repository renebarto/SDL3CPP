//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ILogLineWriter.h
//
// Namespace   : tracing
//
// Class       : ILogLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <string>

namespace tracing {

class ILogLineWriter {
public:
    virtual ~ILogLineWriter() = default;

    virtual void WriteLine(const std::string& line) = 0;
};

} // namespace tracing 
