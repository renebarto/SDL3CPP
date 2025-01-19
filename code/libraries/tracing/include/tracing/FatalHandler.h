//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : FatalHandler.h
//
// Namespace   : tracing
//
// Class       : FatalHandler
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <functional>

namespace tracing {

using FatalExitFunction = std::function<void(int errorCode)>;

class FatalHandler
{
private:
    static FatalExitFunction m_fatalExitFunc;

public:
    FatalHandler() = default;
    virtual ~FatalHandler() noexcept;
    
    static void SetFatalExitFunction(FatalExitFunction function);
    static void FatalExit(int errorCode);
};

} // namespace tracing
