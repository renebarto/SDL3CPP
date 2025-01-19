//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceRegistry.cpp
//
// Namespace   : tracing
//
// Class       : TraceRegistry
//
// Description :
//
//------------------------------------------------------------------------------

#include "tracing/TraceRegistry.h"

#include <iostream>
#include "utility/Serialization.h"
#include "tracing/TraceRegistryItem.h"
#include "tracing/ITraceRegistryUpdateListener.h"

namespace tracing {

TraceRegistry::TraceRegistry()
    : m_defaultTraceFilter(
        (TraceCategory::SscfBegin | TraceCategory::SscfEnd | TraceCategory::SscfEvent |
        TraceCategory::SscfLib | TraceCategory::ControlLayer | TraceCategory::CanNmtDbt |
        TraceCategory::Information | TraceCategory::Log | TraceCategory::BistPostInfo |
        TraceCategory::StartupShutdown | TraceCategory::ResultFlow))
    , m_traceEntries()
    , m_updateListenerMutex()
    , m_updateListener()
{

}

void TraceRegistry::SetDefaultTraceFilter(const CategorySet<TraceCategory>& traceFilter)
{
    m_defaultTraceFilter = traceFilter;
    Lock lock(m_updateListenerMutex);
    if (m_updateListener)
    {
        m_updateListener->UpdateDefaultFilter(traceFilter);
    }
}

CategorySet<TraceCategory> TraceRegistry::GetDefaultTraceFilter() const
{
    return m_defaultTraceFilter;
}

CategorySet<TraceCategory> TraceRegistry::GetTraceFilter(const std::string& compilationUnitName)
{
    auto entry = FindCompilationUnit(compilationUnitName);
    if (entry != nullptr)
        return entry->GetTraceFilter();
    return {};
}

void TraceRegistry::SetTraceFilter(const std::string& compilationUnitName, const CategorySet<TraceCategory>& traceFilter)
{
    auto entry = FindCompilationUnit(compilationUnitName);
    if (entry != nullptr)
        entry->SetTraceFilter(traceFilter);
    Lock lock(m_updateListenerMutex);
    if (m_updateListener)
    {
        m_updateListener->UpdateTraceRegistryItem(entry);
    }
}

bool TraceRegistry::IsTraceCategoryEnabled(const std::string& compilationUnitName, TraceCategory category) const
{
    auto entry = FindCompilationUnit(compilationUnitName);
    if (entry != nullptr)
        return entry->IsTraceCategoryEnabled(category);
    return m_defaultTraceFilter.is_set(category);
}

void TraceRegistry::SubscribeUpdateListener(ITraceRegistryUpdateListener* listener)
{
    Lock lock(m_updateListenerMutex);
    m_updateListener = listener;
}

void TraceRegistry::UnsubscribeUpdateListener(ITraceRegistryUpdateListener* /*listener*/)
{
    Lock lock(m_updateListenerMutex);
    m_updateListener = nullptr;
}

void TraceRegistry::AddItem(TraceRegistryItem* entry)
{
    auto it = m_traceEntries.find(entry->CompilationUnitFileName());
    if (it == m_traceEntries.end())
    {
        entry->SetTraceFilter(m_defaultTraceFilter);
        m_traceEntries.insert(std::make_pair(entry->CompilationUnitFileName(), entry));
    }
    else
    {
        it->second = entry;
    }
    Lock lock(m_updateListenerMutex);
    if (m_updateListener)
    {
        m_updateListener->UpdateTraceRegistryItem(entry);
    }
}

TraceRegistryItem* TraceRegistry::FindCompilationUnit(const std::string& compilationUnitName) const
{
    auto it = m_traceEntries.find(compilationUnitName);
    if (it != m_traceEntries.end())
    {
        return it->second;
    }
    return nullptr;
}

TraceRegistry::RegistryMap TraceRegistry::GetItems() const
{
    return m_traceEntries;
}

std::ostream& operator << (std::ostream& stream, const tracing::TraceRegistry& value)
{
    auto map = value.GetItems();
    for (auto item : map)
    {
        stream << item.first << ":" << *(item.second) << std::endl;
    }
    return stream;
}

} // namespace tracing

tracing::TraceRegistry& GetTraceRegistry()
{
    static tracing::TraceRegistry theRegistry;
    return theRegistry;
}

DEFINE_TRACE_ENTRY();
