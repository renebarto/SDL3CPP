//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : LoggingTest.cpp
//
// Namespace   : tracing
//
// Class       : LoggingTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "MockLogWriter.h"
#include "osal/utilities/ThreadFunctions.h"
#include "utility/Error.h"
#include "utility/GenericError.h"
#include "osal/regex/Regex.h"
#include "tracing/FatalHandler.h"
#include "tracing/Logging.h"
#include "tracing/LogWriter.h"
#include "tracing/StringLogLineWriter.h"
#include "tracing/StringTraceLineWriter.h"
#include "tracing/TraceWriter.h"
#include "tracing/Tracing.h"

namespace tracing {

static const std::string TraceRegexTimeStamp = "\\d{4}-\\w{3}-\\d{2}\\s\\d{2}:\\d{2}:\\d{2}\\.\\d{6}\\|";

static void CheckMatch(const std::vector<std::string>& regexStrings, const std::vector<std::string>& actual)
{
    EXPECT_EQ(regexStrings.size(), actual.size());
    for (std::size_t i = 0; i < regexStrings.size(); ++i)
    {
        EXPECT_TRUE(osal::VerifyMatch(actual[i], regexStrings[i]));
    }
}

class LoggingTest : public ::testing::Test
{
public:
    int m_exitCode;
    CategorySet<TraceCategory> m_savedTraceFilter;
    StringTraceLineWriter m_traceLineWriter;
    StringLogLineWriter m_logLineWriter;
    TraceWriter m_traceWriter;
    LogWriter m_logWriter;

    LoggingTest()
        : m_exitCode()
        , m_savedTraceFilter {}
        , m_traceLineWriter {}
        , m_logLineWriter{}
        , m_traceWriter(m_traceLineWriter)
        , m_logWriter(m_logLineWriter)
    {}

    virtual void SetUp() override
    {
        Tracing::SetTraceWriter(&m_traceWriter);
        Logging::SetLogWriter(&m_logWriter);
        m_savedTraceFilter = Tracing::GetDefaultTraceFilter();
        FatalHandler::SetFatalExitFunction([this](int exitCode){ m_exitCode = exitCode; });
        osal::SetThreadNameSelf("LoggingTest");
    }
    virtual void TearDown() override
    {
        Tracing::SetTraceWriter(nullptr);
        Logging::SetLogWriter(nullptr);
        Tracing::SetDefaultTraceFilter(m_savedTraceFilter);
        FatalHandler::SetFatalExitFunction(nullptr);    
    }
};

TEST_F(LoggingTest, Log)
{
    Logging::Log("MyFile", 123, "MyFunction", "Hello World");
    CheckMatch(
        { TraceRegexTimeStamp + "Hello World" },
        m_logLineWriter.GetResult());

    CheckMatch(
        { TraceRegexTimeStamp + "Log\\|MyFile\\:123\\|MyFunction\\|LoggingTest\\|Hello World" },
        m_traceLineWriter.GetResult());
}

TEST_F(LoggingTest, LogWithFormat)
{
    Logging::Log("MyFile", 123, "MyFunction", "{0} {1} (C) {2,4:D}", "Hello", "World", 2020);
    CheckMatch(
        { TraceRegexTimeStamp + "Hello World \\(C\\) 2020" },
        m_logLineWriter.GetResult());

    CheckMatch(
        { TraceRegexTimeStamp + "Log\\|MyFile\\:123\\|MyFunction\\|LoggingTest\\|Hello World \\(C\\) 2020" },
        m_traceLineWriter.GetResult());
}

} // namespace tracing
