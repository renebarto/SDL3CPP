//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceCategory.cpp
//
// Namespace   : tracing
//
// Class       : -
//
// Description : TraceCategory serialization and helper functions
//
//------------------------------------------------------------------------------

#include "tracing/TraceCategory.h"

#include "serialization/EnumSerialization.h"
#include "tracing/TraceRegistryItem.h"

namespace serialization {

template<>
const BidirectionalMap<tracing::TraceCategory, std::string> EnumSerializationMap<tracing::TraceCategory>::ConversionMap = {
    { tracing::TraceCategory::Cat80000000, "Cat80000000"},
    { tracing::TraceCategory::Cat40000000, "Cat40000000"},
    { tracing::TraceCategory::Cat20000000, "Cat20000000"},
    { tracing::TraceCategory::Cat10000000, "Cat10000000"},
    { tracing::TraceCategory::Cat08000000, "Cat08000000"},
    { tracing::TraceCategory::Cat04000000, "Cat04000000"},
    { tracing::TraceCategory::Cat02000000, "Cat02000000"},
    { tracing::TraceCategory::Cat01000000, "Cat01000000"},
    { tracing::TraceCategory::Cat00800000, "Cat00800000"},
    { tracing::TraceCategory::Cat00400000, "Cat00400000"},
    { tracing::TraceCategory::Cat00200000, "Cat00200000"},
    { tracing::TraceCategory::Cat00100000, "Cat00100000"},
    { tracing::TraceCategory::Cat00080000, "Cat00080000"},
    { tracing::TraceCategory::Cat00040000, "Cat00040000"},
    { tracing::TraceCategory::Cat00020000, "Cat00020000"},
    { tracing::TraceCategory::Cat00010000, "Cat00010000"},
    { tracing::TraceCategory::Cat00008000, "Cat00008000"},
    { tracing::TraceCategory::Cat00004000, "Cat00004000"},
    { tracing::TraceCategory::Cat00002000, "Cat00002000"},
    { tracing::TraceCategory::Cat00001000, "Cat00001000"},
    { tracing::TraceCategory::Cat00000800, "Cat00000800"},
    { tracing::TraceCategory::Cat00000400, "Cat00000400"},
    { tracing::TraceCategory::Cat00000200, "Cat00000200"},
    { tracing::TraceCategory::Cat00000100, "Cat00000100"},
    { tracing::TraceCategory::Cat00000080, "Cat00000080"},
    { tracing::TraceCategory::FunctionEnter, "Enter"},
    { tracing::TraceCategory::FunctionLeave, "Leave"},
    { tracing::TraceCategory::Debug, "Debug"},
    { tracing::TraceCategory::Information, "Information"},
    { tracing::TraceCategory::Warning, "Warning"},
    { tracing::TraceCategory::Error, "Error"},
    { tracing::TraceCategory::Fatal, "Fatal"},
};

} // namespace serialization

namespace tracing {

std::ostream& operator << (std::ostream& stream, const TraceCategory& value)
{
    return stream << serialization::Serialize(value, "????");
}

std::vector<TraceCategory> EnumTraceCategories()
{
    return serialization::EnumSerializationMap<TraceCategory>::GetKeys();
}

} // namespace tracing

DEFINE_TRACE_ENTRY();
