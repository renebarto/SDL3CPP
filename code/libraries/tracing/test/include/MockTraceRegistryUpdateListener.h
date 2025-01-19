//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : MockTraceRegistryUpdateListener.cpp
//
// Namespace   : tracing
//
// Class       : MockTraceRegistryUpdateListener
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "tracing/ITraceRegistryUpdateListener.h"

#include "test-platform/GoogleMock.h"

namespace tracing {

class MockTraceRegistryUpdateListener
    : public ITraceRegistryUpdateListener
{
public:
    virtual ~MockTraceRegistryUpdateListener() = default;

    MOCK_METHOD(void, UpdateDefaultFilter, (const CategorySet<TraceCategory>& defaultFilter), (override));
    MOCK_METHOD(void, UpdateTraceRegistryItem, (const TraceRegistryItem* entry), (override));
};

} // namespace tracing
