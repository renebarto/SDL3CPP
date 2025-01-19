//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : MockLogLineWriter.cpp
//
// Namespace   : tracing
//
// Class       : MockLogLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "tracing/ILogLineWriter.h"

#include "test-platform/GoogleMock.h"

namespace tracing {

class MockLogLineWriter
    : public ILogLineWriter
{
public:
    virtual ~MockLogLineWriter() = default;

    MOCK_METHOD(void, WriteLine, (const std::string &), (override));
};

} // namespace tracing
