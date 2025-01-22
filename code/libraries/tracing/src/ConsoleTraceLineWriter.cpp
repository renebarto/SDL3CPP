//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ConsoleTraceLineWriter.cpp
//
// Namespace   : tracing
//
// Class       : ConsoleTraceLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#include "tracing/ConsoleTraceLineWriter.h"

#include "osal/utilities/Console.h"
#include "tracing/TraceRegistryItem.h"

static osal::Console s_console;

namespace tracing {

static osal::ConsoleColor GetColorForCategory(TraceCategory category)
{
    switch (category)
    {
    case TraceCategory::FunctionEnter:  return osal::ConsoleColor::Yellow;
    case TraceCategory::FunctionLeave:  return osal::ConsoleColor::Yellow;
    case TraceCategory::Debug:          return osal::ConsoleColor::Cyan;
    case TraceCategory::Information:    return osal::ConsoleColor::White;
    case TraceCategory::Warning:        return osal::ConsoleColor::Magenta;
    case TraceCategory::Error:          return osal::ConsoleColor::Red;
    case TraceCategory::Fatal:          return osal::ConsoleColor::Intensity | osal::ConsoleColor::Red;

        default: return osal::ConsoleColor::Default;
    }
}

void ConsoleTraceLineWriter::WriteLine(TraceCategory category, const std::string& line)
{
    s_console << fgcolor(GetColorForCategory(category));
    s_console << line << std::endl;
    s_console << fgcolor(osal::ConsoleColor::Default);
}

} // namespace tracing

DEFINE_TRACE_ENTRY();
