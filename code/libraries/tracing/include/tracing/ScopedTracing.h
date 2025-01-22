//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : ScopedTracing.h
//
// Namespace   : tracing
//
// Class       : ScopedTracing
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "tracing/TraceCategory.h"
#include "tracing/Tracing.h"

namespace tracing {

using EntryFunction = std::function<std::string()>;
using ExitFunction = std::function<std::string()>;

template<TraceCategory EntryCategory, TraceCategory ExitCategory>
class ScopedTracingGeneric
{
public:
    ScopedTracingGeneric(const std::string& path, int line, const std::string& functionName, EntryFunction entryFunction, ExitFunction exitFunction)
        : m_path(path)
        , m_line(line)
        , m_functionName(functionName)
        , m_exitFunction(exitFunction)
    {
        if (Tracing::IsTraceCategoryEnabled(EntryCategory) && Tracing::IsTraceCategoryEnabled(ExitCategory))
            Tracing::Trace(EntryCategory, path, line, functionName, entryFunction ? entryFunction() : "");
    }

    ~ScopedTracingGeneric() noexcept
    {
        if (Tracing::IsTraceCategoryEnabled(EntryCategory) && Tracing::IsTraceCategoryEnabled(ExitCategory))
            Tracing::Trace(ExitCategory, m_path, m_line, m_functionName, m_exitFunction ? m_exitFunction() : "");
    }

private:
    std::string m_path;
    int m_line;
    std::string m_functionName;
    ExitFunction m_exitFunction;
};

using ScopedTracing = ScopedTracingGeneric<TraceCategory::FunctionEnter, TraceCategory::FunctionLeave>;

#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
#define SCOPEDTRACE(entryFunction, exitFunction) ::tracing::ScopedTracing TOKENPASTE2(_trace, __LINE__)(__FILE__, __LINE__, __func__, entryFunction, exitFunction)

} // namespace tracing
