//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : MultiSubscriberLogLineWriterTest.cpp
//
// Namespace   : core::threading
//
// Class       : MultiSubscriberLogLineWriterTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include <iostream>
#include <thread>
#include "tracing/Tracing.h"
#include "core/tracing/MultiSubscriberLogLineWriter.h"

namespace core {
namespace tracing {

class MyLogLineWriterSubscriber
    : public ::tracing::ILogLineWriter
{
public:
    std::string m_buffer;

    MyLogLineWriterSubscriber()
        : m_buffer{}
    {
    }
    ~MyLogLineWriterSubscriber()
    {
    }

    void WriteLine(const std::string& line) override
    {
        m_buffer += line;
        m_buffer += '\n';
    }
};

class MultiSubscriberLogLineWriterTest
    : public ::testing::Test
{
public:
    ::utility::EnumBitSet<::tracing::TraceCategory> m_savedTraceFilter;
    MyLogLineWriterSubscriber m_subscriber1;
    MyLogLineWriterSubscriber m_subscriber2;

    MultiSubscriberLogLineWriterTest()
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

TEST_F(MultiSubscriberLogLineWriterTest, NoSubscriptionNothingIsWritten)
{
    MultiSubscriberLogLineWriter writer;
    writer.WriteLine("Hello");

    EXPECT_EQ("", m_subscriber1.m_buffer);
    EXPECT_EQ("", m_subscriber2.m_buffer);
}

TEST_F(MultiSubscriberLogLineWriterTest, SingleSubscription)
{
    MultiSubscriberLogLineWriter writer;
    writer.Subscribe(&m_subscriber1);
    writer.WriteLine("Hello");

    EXPECT_EQ("Hello\n", m_subscriber1.m_buffer);
    EXPECT_EQ("", m_subscriber2.m_buffer);
}

TEST_F(MultiSubscriberLogLineWriterTest, MultipleSubscription)
{
    MultiSubscriberLogLineWriter writer;
    writer.Subscribe(&m_subscriber1);
    writer.Subscribe(&m_subscriber2);
    writer.WriteLine("Hello");

    EXPECT_EQ("Hello\n", m_subscriber1.m_buffer);
    EXPECT_EQ("Hello\n", m_subscriber2.m_buffer);
}

TEST_F(MultiSubscriberLogLineWriterTest, MultipleSubscriptionSame)
{
    MultiSubscriberLogLineWriter writer;
    writer.Subscribe(&m_subscriber1);
    writer.Subscribe(&m_subscriber1);
    writer.WriteLine("Hello");

    EXPECT_EQ("Hello\n", m_subscriber1.m_buffer);
    EXPECT_EQ("", m_subscriber2.m_buffer);
}

} // namespace tracing
} // namespace core
