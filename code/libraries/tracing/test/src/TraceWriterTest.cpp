//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceWriterTest.cpp
//
// Namespace   : tracing
//
// Class       : TraceWriterTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "osal/utilities/ThreadFunctions.h"
#include "osal/regex/Regex.h"
#include "tracing/TraceWriter.h"
#include "MockTraceLineWriter.h"

using testing::_;

namespace tracing {

static const std::string TraceRegexTimeStamp = "\\d{4}-\\w{3}-\\d{2}\\s\\d{2}:\\d{2}:\\d{2}\\.\\d{6}\\|";

class TraceWriterTest : public ::testing::Test
{
public:
    TraceWriterTest()
    {}

    virtual void SetUp() override
    {
        osal::SetThreadNameSelf("TraceChannelTest");
    }
    virtual void TearDown() override
    {
    }

};

TEST_F(TraceWriterTest, Trace)
{
    MockTraceLineWriter lineWriter;
    TraceWriter traceWriter(lineWriter);
    std::string text;

    EXPECT_CALL(lineWriter, WriteLine(TraceCategory::Information, _)).Times(1).WillRepeatedly(testing::SaveArg<1>(&text));

    traceWriter.Trace(osal::Clock().CurrentTime(), TraceCategory::Information, "FILE", 123, "FUNCTION", "TEXT");
    // std::cout << text << std::endl;
    EXPECT_TRUE(osal::VerifyMatch(text, TraceRegexTimeStamp + "Information\\|FILE\\:123\\|FUNCTION\\|TraceChannelTest\\|TEXT"));
}

} // namespace tracing
