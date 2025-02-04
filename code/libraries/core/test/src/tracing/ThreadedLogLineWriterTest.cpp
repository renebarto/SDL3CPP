//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : ThreadedLogLineWriterTest.cpp
//
// Namespace   : core::threading
//
// Class       : ThreadedLogLineWriterTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include <iostream>
#include <thread>
#include "tracing/Tracing.h"
#include "core/tracing/ThreadedLogLineWriter.h"

namespace core {
namespace tracing {

class MyLogLineWriter
    : public ::tracing::ILogLineWriter
{
public:
    std::string m_buffer;

    MyLogLineWriter()
        : m_buffer{}
    {
    }
    ~MyLogLineWriter()
    {
    }

    void WriteLine(const std::string& line) override
    {
        m_buffer += line;
        m_buffer += '\n';
    }
};

class ThreadedLogLineWriterTest
    : public ::testing::Test
{
public:
    ::utility::EnumBitSet<::tracing::TraceCategory> m_savedTraceFilter;
    MyLogLineWriter m_writer;

    ThreadedLogLineWriterTest()
        : m_savedTraceFilter()
    {}

    void SetUp() override
    {
        m_savedTraceFilter = ::tracing::Tracing::GetDefaultTraceFilter();
        ::tracing::Tracing::SetDefaultTraceFilter(::tracing::TraceCategory::Information);
    }
    void TearDown() override
    {
        ::tracing::Tracing::SetDefaultTraceFilter(m_savedTraceFilter);
    }
};

TEST_F(ThreadedLogLineWriterTest, WriteThreadNotRunning)
{
    ThreadedLogLineWriter writer(m_writer);
    writer.WriteLine("Hello");

    EXPECT_EQ("", m_writer.m_buffer);
}

TEST_F(ThreadedLogLineWriterTest, WriteThreadRunning)
{
    ThreadedLogLineWriter writer(m_writer);
    writer.Create();
    writer.WriteLine("Hello");
    writer.Kill();

    EXPECT_EQ("Hello\n", m_writer.m_buffer);
}

} // namespace tracing
} // namespace core
