//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : ThreadedTraceLineWriter.cpp
//
// Namespace   : core::tracing
//
// Class       : ThreadedTraceLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#include <thread>
#include "core/tracing/ThreadedTraceLineWriter.h"

using namespace std::chrono_literals;

namespace core {
namespace tracing {

ThreadedTraceLineWriter::ThreadedTraceLineWriter(::tracing::ITraceLineWriter& writer)
    : threading::ActiveObject{"TraceLineWriter"}
    , m_writer{ writer }
    , m_buffer{}
    , m_stopThread{}
{
}

ThreadedTraceLineWriter::~ThreadedTraceLineWriter()
{
}

void ThreadedTraceLineWriter::WriteLine(::tracing::TraceCategory category, const std::string & line)
{
    m_buffer.emplace_back(category, line);
}

void ThreadedTraceLineWriter::InitThread()
{
}

void ThreadedTraceLineWriter::Run()
{
    while (!m_stopThread)
    {
        while (!m_buffer.empty())
        {
            m_writer.WriteLine(m_buffer.front().m_category, m_buffer.front().m_line);
            m_buffer.pop_front();
        }
        std::this_thread::sleep_for(100ms);
    }
}

void ThreadedTraceLineWriter::ExitThread()
{
    while (!m_buffer.empty())
    {
        m_writer.WriteLine(m_buffer.front().m_category, m_buffer.front().m_line);
        m_buffer.pop_front();
    }
}

void ThreadedTraceLineWriter::FlushThread()
{
    m_stopThread = true;
}

} // namespace tracing
} // namespace core