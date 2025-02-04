//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceEntry.h
//
// Namespace   : tracing
//
// Class       : TraceEntry
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "utility/EnumBitSet.h"
#include "tracing/TraceCategory.h"
#include "tracing/TraceHelpers.h"
#include "tracing/TraceRegistry.h"

namespace tracing {

class TraceEntry
{
private:
    utility::EnumBitSet<TraceCategory> m_traceFilter;
    std::string m_compilationUnitFileName;

public:
    TraceEntry(const std::string& compilationUnitFileName, TraceRegistry& traceRegistry);

    const std::string& CompilationUnitFileName() const;
    void SetTraceFilter(const utility::EnumBitSet<TraceCategory>& traceFilter);
    bool IsTraceCategoryEnabled(TraceCategory category) const;
};

} // namespace tracing

#define DEFINE_TRACE_ENTRY(x) static tracing::TraceEntry entry(x, ::GetTraceRegistry())
