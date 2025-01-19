//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : LogEntry.h
//
// Namespace   : tracing
//
// Class       : LogEntry
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "serialization/EnumSerialization.h"
#include "tracing/TraceChannel.h"

namespace tracing {

enum class LoggingSeverity
{
    Info,
    Warning,
    Error,
    Fatal
};

enum class LogEntryType
{
    Trace,
    Development,
    Service,
    Utilization
};

inline std::ostream& operator << (std::ostream& stream, LoggingSeverity value)
{
    return stream << serialization::Serialize(value);
}

inline std::ostream& operator << (std::ostream& stream, LogEntryType value)
{
    return stream << serialization::Serialize(value);
}

class LogEntry
{
private:
    unsigned int m_entryID;
    std::string m_stringId;
    std::string m_description;
    std::string m_freeText;
    LoggingSeverity m_severity;
    LogEntryType m_logEntryType;
    int m_lineNumber;
    std::string m_sourceFileName;
    std::string m_className;
    TraceChannel m_channel;
    bool m_externalResponsibility;
    bool m_collateral;
    unsigned int m_ignore;

public:
};

} // namespace tracing
