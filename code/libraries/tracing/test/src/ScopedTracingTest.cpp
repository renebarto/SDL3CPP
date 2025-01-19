//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ScopedTracingTest.cpp
//
// Namespace   : tracing
//
// Class       : ScopedTracingTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "osal/utilities//ThreadFunctions.h"
#include "tracing/ScopedTracing.h"
#include "tracing/StringTraceLineWriter.h"
#include "tracing/TraceWriter.h"
#include "tracing/TraceCategory.h"
#include "osal/regex/Regex.h"

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

class ScopedTracingTest : public ::testing::Test
{
public:
    CategorySet<TraceCategory> m_savedTraceFilter;
    StringTraceLineWriter m_lineWriter;
    TraceWriter m_traceWriter;

    ScopedTracingTest()
        : m_savedTraceFilter {}
        , m_lineWriter {}
        , m_traceWriter(m_lineWriter)
    {}

    virtual void SetUp() override
    {
        tracing::Tracing::SetTraceWriter(&m_traceWriter);
        m_savedTraceFilter = Tracing::GetDefaultTraceFilter();
        osal::SetThreadNameSelf("ScopedTracingTest");
    }
    virtual void TearDown() override
    {
        tracing::Tracing::SetTraceWriter(nullptr);
        Tracing::SetDefaultTraceFilter(m_savedTraceFilter);
    }
};

TEST_F(ScopedTracingTest, IfNothingEnabledNothingHappens)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::None);
    {
        ScopedTracing trace("MyFile", 123, "MyFunction", [](){ return "This is the begin"; }, [](){ return "This is the end"; });
    }
    std::vector<std::string> regexStrings{};
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(ScopedTracingTest, IfEnabledEntryAndExitMessageWritten)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    {
        ScopedTracing trace("MyFile", 123, "MyFunction", [](){ return "This is the begin"; }, [](){ return "This is the end"; });
    }
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Enter\\|MyFile\\:123\\|MyFunction\\|ScopedTracingTest\\|This is the begin",
        TraceRegexTimeStamp + "Leave\\|MyFile\\:123\\|MyFunction\\|ScopedTracingTest\\|This is the end"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(ScopedTracingTest, IfExitFunctionIsNullEmptyStringIsWritten)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    {
        ScopedTracing trace("MyFile", 123, "MyFunction", nullptr, nullptr);
    }
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Enter\\|MyFile\\:123\\|MyFunction\\|ScopedTracingTest\\|",
        TraceRegexTimeStamp + "Leave\\|MyFile\\:123\\|MyFunction\\|ScopedTracingTest\\|"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

} // namespace tracing
