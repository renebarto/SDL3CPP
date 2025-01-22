//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : MultiSubscriberTraceLineWriterTest.cpp
//
// Namespace   : core::threading
//
// Class       : MultiSubscriberTraceLineWriterTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include <iostream>
#include <thread>
#include "tracing/Tracing.h"
#include "core/tracing/MultiSubscriberTraceLineWriter.h"

namespace core {
namespace tracing {

class MyTraceLineWriterSubscriber
    : public ::tracing::ITraceLineWriter
{
public:
    std::pair<::tracing::TraceCategory, std::string> m_buffer;

    MyTraceLineWriterSubscriber()
        : m_buffer{}
    {
    }
    ~MyTraceLineWriterSubscriber()
    {
    }

    void WriteLine(::tracing::TraceCategory category, const std::string& line) override
    {
        m_buffer = std::pair(category, line);
    }
};

class MultiSubscriberTraceLineWriterTest
    : public ::testing::Test
{
public:
    ::tracing::CategorySet<::tracing::TraceCategory> m_savedTraceFilter;
    MyTraceLineWriterSubscriber m_subscriber1;
    MyTraceLineWriterSubscriber m_subscriber2;

    MultiSubscriberTraceLineWriterTest()
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

TEST_F(MultiSubscriberTraceLineWriterTest, NoSubscriptionNothingIsWritten)
{
    MultiSubscriberTraceLineWriter writer;
    writer.WriteLine(::tracing::TraceCategory::Information, "Hello");

    EXPECT_EQ(::tracing::TraceCategory::None, m_subscriber1.m_buffer.first);
    EXPECT_EQ("", m_subscriber1.m_buffer.second);
    EXPECT_EQ(::tracing::TraceCategory::None, m_subscriber2.m_buffer.first);
    EXPECT_EQ("", m_subscriber2.m_buffer.second);
}

TEST_F(MultiSubscriberTraceLineWriterTest, SingleSubscription)
{
    MultiSubscriberTraceLineWriter writer;
    writer.Subscribe(&m_subscriber1);
    writer.WriteLine(::tracing::TraceCategory::Information, "Hello");

    EXPECT_EQ(::tracing::TraceCategory::Information, m_subscriber1.m_buffer.first);
    EXPECT_EQ("Hello", m_subscriber1.m_buffer.second);
    EXPECT_EQ(::tracing::TraceCategory::None, m_subscriber2.m_buffer.first);
    EXPECT_EQ("", m_subscriber2.m_buffer.second);
}

TEST_F(MultiSubscriberTraceLineWriterTest, MultipleSubscription)
{
    MultiSubscriberTraceLineWriter writer;
    writer.Subscribe(&m_subscriber1);
    writer.Subscribe(&m_subscriber2);
    writer.WriteLine(::tracing::TraceCategory::Information, "Hello");

    EXPECT_EQ(::tracing::TraceCategory::Information, m_subscriber1.m_buffer.first);
    EXPECT_EQ("Hello", m_subscriber1.m_buffer.second);
    EXPECT_EQ(::tracing::TraceCategory::Information, m_subscriber2.m_buffer.first);
    EXPECT_EQ("Hello", m_subscriber2.m_buffer.second);
}

TEST_F(MultiSubscriberTraceLineWriterTest, MultipleSubscriptionSame)
{
    MultiSubscriberTraceLineWriter writer;
    writer.Subscribe(&m_subscriber1);
    writer.Subscribe(&m_subscriber1);
    writer.WriteLine(::tracing::TraceCategory::Information, "Hello");

    EXPECT_EQ(::tracing::TraceCategory::Information, m_subscriber1.m_buffer.first);
    EXPECT_EQ("Hello", m_subscriber1.m_buffer.second);
    EXPECT_EQ(::tracing::TraceCategory::None, m_subscriber2.m_buffer.first);
    EXPECT_EQ("", m_subscriber2.m_buffer.second);
}

} // namespace tracing
} // namespace core
