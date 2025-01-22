//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : ThreadedTraceLineWriterTest.cpp
//
// Namespace   : core::threading
//
// Class       : ThreadedTraceLineWriterTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include <iostream>
#include <thread>
#include "tracing/Tracing.h"
#include "core/tracing/ThreadedTraceLineWriter.h"

namespace core {
namespace tracing {

class MyTraceLineWriter
    : public ::tracing::ITraceLineWriter
{
public:
    std::pair<::tracing::TraceCategory, StringType> m_buffer;

    MyTraceLineWriter()
        : m_buffer{}
    {
    }
    ~MyTraceLineWriter()
    {
    }

    void WriteLine(::tracing::TraceCategory category, const StringType& line) override
    {
        m_buffer = std::pair(category, line);
    }
};

class ThreadedTraceLineWriterTest
    : public ::testing::Test
{
public:
    ::utility::EnumBitSet<::tracing::TraceCategory> m_savedTraceFilter;
    MyTraceLineWriter m_writer;

    ThreadedTraceLineWriterTest()
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

TEST_F(ThreadedTraceLineWriterTest, WriteThreadNotRunning)
{
    ThreadedTraceLineWriter writer(m_writer);
    writer.WriteLine(::tracing::TraceCategory::Information, TX("Hello"));

    EXPECT_EQ(::tracing::TraceCategory::None, m_writer.m_buffer.first);
    EXPECT_EQ(TX(""), m_writer.m_buffer.second);
}

TEST_F(ThreadedTraceLineWriterTest, WriteThreadRunning)
{
    ThreadedTraceLineWriter writer(m_writer);
    writer.Create();
    writer.WriteLine(::tracing::TraceCategory::Information, TX("Hello"));
    writer.Kill();

    EXPECT_EQ(::tracing::TraceCategory::Information, m_writer.m_buffer.first);
    EXPECT_EQ(TX("Hello"), m_writer.m_buffer.second);
}

} // namespace tracing
} // namespace core
