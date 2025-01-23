//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : ThreadedLogLineWriter.cpp
//
// Namespace   : core::tracing
//
// Class       : ThreadedLogLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#include <thread>
#include "core/tracing/ThreadedLogLineWriter.h"

using namespace std::chrono_literals;

namespace core {
namespace tracing {

ThreadedLogLineWriter::ThreadedLogLineWriter(::tracing::ILogLineWriter& writer)
    : threading::ActiveObject{"LogLineWriter"}
    , m_writer{ writer }
    , m_buffer{}
    , m_stopThread{}
{
}

ThreadedLogLineWriter::~ThreadedLogLineWriter()
{
}

void ThreadedLogLineWriter::WriteLine(const std::string & line)
{
    m_buffer.emplace_back(line);
}

void ThreadedLogLineWriter::InitThread()
{
}

void ThreadedLogLineWriter::Run()
{
    while (!m_stopThread)
    {
        while (!m_buffer.empty())
        {
            m_writer.WriteLine(m_buffer.front());
            m_buffer.pop_front();
        }
        std::this_thread::sleep_for(100ms);
    }
}

void ThreadedLogLineWriter::ExitThread()
{
    while (!m_buffer.empty())
    {
        m_writer.WriteLine(m_buffer.front());
        m_buffer.pop_front();
    }
}

void ThreadedLogLineWriter::FlushThread()
{
    m_stopThread = true;
}

} // namespace tracing
} // namespace core