//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : ThreadedTraceLineWriter.h
//
// Namespace   : core::tracing
//
// Class       : ThreadedTraceLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <deque>
#include "tracing/ITraceLineWriter.h"
#include "core/threading/ActiveObject.h"

namespace core {
namespace tracing {

struct Entry
{
public:
    ::tracing::TraceCategory m_category;
    std::string m_line;

    Entry(::tracing::TraceCategory category, const std::string& line)
        : m_category{ category }
        , m_line{ line }
    {}
};

class ThreadedTraceLineWriter
    : public ::tracing::ITraceLineWriter
    , public threading::ActiveObject
{
private:
    ::tracing::ITraceLineWriter& m_writer;
    std::deque<Entry> m_buffer;
    std::atomic_bool m_stopThread;

public:
    ThreadedTraceLineWriter(::tracing::ITraceLineWriter& writer);
    ~ThreadedTraceLineWriter();

    void WriteLine(::tracing::TraceCategory category, const std::string & line) override;

protected:
    void InitThread()  override;
    void Run() override;
    void ExitThread()  override;
    void FlushThread() override;
};

} // namespace tracing
} // namespace core
