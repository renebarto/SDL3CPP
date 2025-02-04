//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceRegistry.h
//
// Namespace   : tracing
//
// Class       : TraceRegistry
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <map>
#include <mutex>
#include <string>
#include "utility/EnumBitSet.h"
#include "utility/Serialization.h"
#include "tracing/TraceCategory.h"

namespace tracing {

class TraceRegistryItem;
class ITraceRegistryUpdateListener;

class TraceRegistry
{
private:
    utility::EnumBitSet<TraceCategory> m_defaultTraceFilter;
    using RegistryMap = std::map<std::string, TraceRegistryItem*>;
    RegistryMap m_traceEntries;
    using Mutex = std::mutex;
    using Lock = std::lock_guard<Mutex>;
    Mutex m_updateListenerMutex;
    ITraceRegistryUpdateListener* m_updateListener;

public:
    TraceRegistry();

    void SetDefaultTraceFilter(const utility::EnumBitSet<TraceCategory>& traceFilter);
    utility::EnumBitSet<TraceCategory> GetDefaultTraceFilter() const;
    utility::EnumBitSet<TraceCategory> GetTraceFilter(const std::string& compilationUnitName);
    void SetTraceFilter(const std::string& compilationUnitName, const utility::EnumBitSet<TraceCategory>& traceFilter);
    bool IsTraceCategoryEnabled(const std::string& compilationUnitName, TraceCategory category) const;

    void SubscribeUpdateListener(ITraceRegistryUpdateListener* listener);
    void UnsubscribeUpdateListener(ITraceRegistryUpdateListener* listener);

    void AddItem(TraceRegistryItem* entry);
    TraceRegistryItem* FindCompilationUnit(const std::string& compilationUnitName) const;
    RegistryMap GetItems() const;
};

std::ostream& operator << (std::ostream& stream, const TraceRegistry& value);

} // namespace tracing

tracing::TraceRegistry& GetTraceRegistry();

namespace serialization {

template<>
inline std::string Serialize(const tracing::TraceRegistry& value)
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

} // namespace serialization
