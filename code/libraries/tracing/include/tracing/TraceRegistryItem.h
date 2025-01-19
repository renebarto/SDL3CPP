//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceRegistryItem.h
//
// Namespace   : tracing
//
// Class       : TraceRegistryItem
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "utility/Serialization.h"
#include "tracing/CategorySet.h"
#include "tracing/TraceCategory.h"
#include "tracing/TraceHelpers.h"
#include "tracing/TraceRegistry.h"

namespace tracing {

class TraceRegistryItem
{
private:
    CategorySet<TraceCategory> m_traceFilter;
    std::string m_compilationUnitFileName;

public:
    TraceRegistryItem(const std::string& compilationUnitFileName, TraceRegistry& traceRegistry);

    const std::string& CompilationUnitFileName() const;
    void SetTraceFilter(const CategorySet<TraceCategory>& traceFilter);
    CategorySet<TraceCategory> GetTraceFilter() const;
    bool IsTraceCategoryEnabled(TraceCategory category) const;
};

std::ostream& operator << (std::ostream& stream, const TraceRegistryItem& value);

} // namespace tracing

#define DEFINE_TRACE_ENTRY() static tracing::TraceRegistryItem entry(__BASE_FILE__, ::GetTraceRegistry())

namespace serialization {

template<>
inline std::string Serialize(const tracing::TraceRegistryItem& value)
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

} // namespace serialization
