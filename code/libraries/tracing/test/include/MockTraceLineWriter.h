//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : MockTraceLineWriter.cpp
//
// Namespace   : tracing
//
// Class       : MockTraceLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "tracing/ITraceLineWriter.h"

#include "test-platform/GoogleMock.h"

namespace tracing {

class MockTraceLineWriter
    : public ITraceLineWriter
{
public:
    virtual ~MockTraceLineWriter() = default;

    MOCK_METHOD(void, WriteLine, (TraceCategory, const std::string &), (override));
};

} // namespace tracing
