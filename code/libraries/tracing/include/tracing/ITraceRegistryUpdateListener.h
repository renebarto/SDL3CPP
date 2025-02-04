//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ITraceRegistryUpdateListener.h
//
// Namespace   : tracing
//
// Class       : ITraceRegistryUpdateListener
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "utility/EnumBitSet.h"
#include "tracing/TraceCategory.h"

namespace tracing {

class TraceRegistryItem;

class ITraceRegistryUpdateListener
{
public:
    virtual ~ITraceRegistryUpdateListener() = default;

    virtual void UpdateDefaultFilter(const utility::EnumBitSet<TraceCategory>& defaultFilter) = 0;
    virtual void UpdateTraceRegistryItem(const TraceRegistryItem* entry) = 0;
};

} // namespace tracing