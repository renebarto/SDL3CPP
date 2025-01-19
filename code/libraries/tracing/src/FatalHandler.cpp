//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : FatalHandler.cpp
//
// Namespace   : tracing
//
// Class       : FatalHandler
//
// Description :
//
//------------------------------------------------------------------------------

#include "tracing/FatalHandler.h"

#include "tracing/TraceRegistryItem.h"

namespace tracing {

FatalExitFunction FatalHandler::m_fatalExitFunc = nullptr;

FatalHandler::~FatalHandler() noexcept
{
}

void FatalHandler::SetFatalExitFunction(FatalExitFunction function)
{
    FatalHandler::m_fatalExitFunc = function;
}

void FatalHandler::FatalExit(int errorCode)
{
    if (m_fatalExitFunc != nullptr)
    {
        return m_fatalExitFunc(errorCode);
    }
    else
    {
        exit(errorCode);
    }
}

} // namespace tracing

DEFINE_TRACE_ENTRY();
