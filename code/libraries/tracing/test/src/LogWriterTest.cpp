//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : LogWriterTest.cpp
//
// Namespace   : tracing
//
// Class       : LogWriterTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "osal/utilities/ThreadFunctions.h"
#include "osal/regex/Regex.h"
#include "tracing/LogWriter.h"
#include "MockLogLineWriter.h"

using testing::_;

namespace tracing {

static const std::string LogRegexTimeStamp = "\\d{4}-\\w{3}-\\d{2}\\s\\d{2}:\\d{2}:\\d{2}\\.\\d{6}\\|";

class LogWriterTest : public ::testing::Test
{
public:
    LogWriterTest()
    {}

    virtual void SetUp() override
    {
        osal::SetThreadNameSelf("LogWriterTest");
    }
    virtual void TearDown() override
    {
    }

};

TEST_F(LogWriterTest, Log)
{
    MockLogLineWriter lineWriter;
    LogWriter traceWriter(lineWriter);
    std::string text;

    EXPECT_CALL(lineWriter, WriteLine(_)).Times(1).WillRepeatedly(testing::SaveArg<0>(&text));

    traceWriter.Log(osal::Clock().CurrentTime(), "TEXT");
    // std::cout << text << std::endl;
    EXPECT_TRUE(osal::VerifyMatch(text, LogRegexTimeStamp + "TEXT"));
}

} // namespace tracing
