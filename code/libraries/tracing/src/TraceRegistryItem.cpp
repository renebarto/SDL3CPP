//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceRegistryItem.cpp
//
// Namespace   : tracing
//
// Class       : TraceRegistryItem
//
// Description :
//
//------------------------------------------------------------------------------

#include "tracing/TraceRegistryItem.h"

#include <algorithm>
#include "filesystem/PathFunctions.h"

namespace tracing {

static const char ForwardSlashChar = '/';
static const char BackSlashChar = '\\';

static std::string RelativePath(const std::string& path)
{
    std::string result = path;
    auto start = path.find("code");
    if (start != std::string::npos)
    {
        result = result.substr(start);
    }
    std::replace(result.begin(), result.end(), BackSlashChar, ForwardSlashChar);
    return result;
}

TraceRegistryItem::TraceRegistryItem(const std::string& compilationUnitFileName, TraceRegistry& traceRegistry)
    : m_traceFilter(traceRegistry.GetDefaultTraceFilter())
    , m_compilationUnitFileName(RelativePath(compilationUnitFileName))
{
    traceRegistry.AddItem(this);
}

const std::string& TraceRegistryItem::CompilationUnitFileName() const
{
    return m_compilationUnitFileName;
}

void TraceRegistryItem::SetTraceFilter(const CategorySet<TraceCategory>& traceFilter)
{
    m_traceFilter = traceFilter;
}

CategorySet<TraceCategory> TraceRegistryItem::GetTraceFilter() const
{
    return m_traceFilter;
}

bool TraceRegistryItem::IsTraceCategoryEnabled(TraceCategory category) const
{
    return m_traceFilter.is_set(category);
}

std::ostream& operator << (std::ostream& stream, const tracing::TraceRegistryItem& value)
{
    stream << serialization::Serialize(value.GetTraceFilter());
    return stream;
}

} // namespace tracing

DEFINE_TRACE_ENTRY();
