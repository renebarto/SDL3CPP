//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : MockLogWriter.cpp
//
// Namespace   : tracing
//
// Class       : MockLogWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "tracing/ILogWriter.h"

#include "test-platform/GoogleMock.h"
#include "osal/utilities/Clock.h"

namespace tracing {

class MockLogWriter
    : public ILogWriter
{
public:
    virtual ~MockLogWriter() = default;

    MOCK_METHOD(void, Log, (osal::EpochTime timestamp, const std::string &), (override));
};

} // namespace tracing
