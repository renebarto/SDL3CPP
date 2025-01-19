//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ConsoleLogLineWriter.cpp
//
// Namespace   : tracing
//
// Class       : ConsoleLogLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#include "tracing/ConsoleLogLineWriter.h"

#include "osal/utilities/Console.h"
#include "tracing/TraceRegistryItem.h"

static osal::Console s_console;

namespace tracing {

void ConsoleLogLineWriter::WriteLine(const std::string& line)
{
    s_console << fgcolor(osal::ConsoleColor::Magenta);
    s_console << line << std::endl;
    s_console << fgcolor(osal::ConsoleColor::Default);
}

} // namespace tracing

DEFINE_TRACE_ENTRY();
