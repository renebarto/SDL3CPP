//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TracingTest.cpp
//
// Namespace   : tracing
//
// Class       : TracingTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "MockTraceWriter.h"
#include "osal/utilities/ThreadFunctions.h"
#include "utility/Error.h"
#include "utility/GenericError.h"
#include "osal/regex/Regex.h"
#include "tracing/FatalHandler.h"
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

class TracingTest : public ::testing::Test
{
public:
    int m_exitCode;
    CategorySet<TraceCategory> m_savedTraceFilter;
    StringTraceLineWriter m_lineWriter;
    TraceWriter m_traceWriter;

    TracingTest()
        : m_exitCode()
        , m_savedTraceFilter {}
        , m_lineWriter {}
        , m_traceWriter(m_lineWriter)
    {}

    virtual void SetUp() override
    {
        Tracing::SetTraceWriter(&m_traceWriter);
        m_savedTraceFilter = Tracing::GetDefaultTraceFilter();
        FatalHandler::SetFatalExitFunction([this](int exitCode){ m_exitCode = exitCode; });
        osal::SetThreadNameSelf("TracingTest");
    }
    virtual void TearDown() override
    {
        Tracing::SetTraceWriter(nullptr);
        Tracing::SetDefaultTraceFilter(m_savedTraceFilter);
        FatalHandler::SetFatalExitFunction(nullptr);    
    }
};

TEST_F(TracingTest, IfTracingFunctionsSetButNothingEnabledNothingHappens)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::None);
    Tracing::Trace(TraceCategory::StartupShutdown, "MyFile", 123, "MyFunction", "Hello World");
    CheckMatch({ }, m_lineWriter.GetResult());
}

TEST_F(TracingTest, IfTracingFunctionsSetAndCategoryEnabledTraceIsWritten)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    Tracing::Trace(TraceCategory::StartupShutdown, "MyFile", 123, "MyFunction", "Hello World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "StartupShutdown\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TracingOnlyForEnabledCategory)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::StartupShutdown);
    Tracing::Trace(TraceCategory::StartupShutdown, "MyFile", 123, "MyFunction", "Hello World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "StartupShutdown\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, IfNoTracingEnableFunctionSetOnlyDefaultCategoriesAreEnabled)
{
    // Assumption: default only StartupShutdown enabled
    Tracing::Trace(TraceCategory::StartupShutdown, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Data, "MyFile", 123, "MyFunction", "Hello World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "StartupShutdown\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, IfDefaultFilterIsChangedOnlySpecifiedCategoriesAreEnabled)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::StartupShutdown);
    Tracing::Trace(TraceCategory::StartupShutdown, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Data, "MyFile", 123, "MyFunction", "Hello World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "StartupShutdown\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TracingCategories)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    Tracing::Trace(TraceCategory::SscfBegin, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::SscfEnd, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::SscfEvent, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::SscfLib, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::DriverLayer, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Physical, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::ApplicationLayer, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::ControlLayer, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::PipelineIn, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::FunctionEnter, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::FunctionLeave, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::CanNmtDbt, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Information, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Log, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Interrupt, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::BistPostInfo, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::SscfCan, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::BitfieldDriver, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::StartupShutdown, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Cat00001000, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::ResultFlow, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Cat00000400, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Cat00000200, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Cat00000100, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Cat00000080, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Cat00000040, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Cat00000020, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Cat00000010, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Cat00000008, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Data, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Flow, "MyFile", 123, "MyFunction", "Hello World");
    Tracing::Trace(TraceCategory::Debug, "MyFile", 123, "MyFunction", "Hello World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "SscfBeg\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "SscfEnd\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "SscfEv\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "SscfLib\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Drvr\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Phys\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Appl\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Ctrl\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "PlIn\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Enter\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Leave\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "NmtDbt\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Info\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Log\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Interrupt\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "BistPostInfo\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "SscfCan\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "BitfieldDriver\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "StartupShutdown\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Cat00001000\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "ResultFlow\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Cat00000400\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Cat00000200\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Cat00000100\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Cat00000080\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Cat00000040\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Cat00000020\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Cat00000010\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Cat00000008\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Data\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Flow\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World",
        TraceRegexTimeStamp + "Debug\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TracingWithFormat)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::Information);
    Tracing::Trace(TraceCategory::Information, "MyFile", 123, "MyFunction", "{0} {1} (C) {2,4:D}", "Hello", "World", 2020);
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World \\(C\\) 2020"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, Error)
{
    utility::Error error(2, strerror(2), "Fake error");
    Tracing::Error("MyFile", 123, "MyFunction", error);
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Error code\\: 2 \\(02\\)\\: No such file or directory Fake error"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
    EXPECT_EQ(0, m_exitCode);
}

TEST_F(TracingTest, ErrorUnknownError)
{
    utility::Error error(-1, "", "Fake error");
    Tracing::Error("MyFile", 123, "MyFunction", error);
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Error code\\: Unknown\\: Fake error"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
    EXPECT_EQ(0, m_exitCode);
}

TEST_F(TracingTest, Fatal)
{
    utility::Error error(2, strerror(2), "Fake error");
    EXPECT_EQ(0, m_exitCode);
    Tracing::Fatal("MyFile", 123, "MyFunction", error);
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Error code\\: 2 \\(02\\)\\: No such file or directory Fake error"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
    EXPECT_EQ(2, m_exitCode);
}

TEST_F(TracingTest, FatalUnknownError)
{
    utility::Error error(-1, "", "Fake error");
    EXPECT_EQ(0, m_exitCode);
    Tracing::Fatal("MyFile", 123, "MyFunction", error);
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Error code\\: Unknown\\: Fake error"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
    EXPECT_EQ(-1, m_exitCode);
}

TEST_F(TracingTest, FatalGenericError)
{
    utility::GenericError error("Fake error");
    EXPECT_EQ(0, m_exitCode);
    Tracing::Fatal("MyFile", 123, "MyFunction", error);
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Fake error"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
    EXPECT_EQ(1, m_exitCode);
}

TEST_F(TracingTest, ThrowError)
{
    utility::Error error(2, strerror(2), "Fake error");

    std::string result;
    try
    {
        Tracing::Throw("MyFile", 123, "MyFunction", error);
    }
    catch (std::exception& e)
    {
        result = e.what();
    }
    EXPECT_TRUE(osal::VerifyMatch(result,
        TraceRegexTimeStamp + "Info MyFile\\:123 \\(MyFunction\\)\\: Fake error\\: Error code\\: 2 \\(02\\)\\: No such file or directory"));
    EXPECT_EQ(0, m_exitCode);
}

TEST_F(TracingTest, ThrowGenericError)
{
    utility::GenericError error("Fake error");

    std::string result;
    try
    {
        Tracing::Throw("MyFile", 123, "MyFunction", error);
    }
    catch (std::exception& e)
    {
        result = e.what();
    }
    EXPECT_TRUE(osal::VerifyMatch(result, 
        TraceRegexTimeStamp + "Info MyFile\\:123 \\(MyFunction\\)\\: Fake error"));
    EXPECT_EQ(0, m_exitCode);
}

TEST_F(TracingTest, TraceFuncEnterString)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceFuncEnter("MyFile", 123, "MyFunction", "Hello World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Enter\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TraceFuncEnterFormatted)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceFuncEnter("MyFile", 123, "MyFunction", "{0} {1}", "Hello", "World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Enter\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TraceFuncLeaveString)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceFuncLeave("MyFile", 123, "MyFunction", "Hello World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Leave\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TraceFuncLeaveFormatted)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceFuncLeave("MyFile", 123, "MyFunction", "{0} {1}", "Hello", "World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Leave\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TraceStartup)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceStartup("MyFile", 123, "MyFunction", "Hello World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "StartupShutdown\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TraceShutdown)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceShutdown("MyFile", 123, "MyFunction", "Hello World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "StartupShutdown\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TraceInfoString)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceInfo("MyFile", 123, "MyFunction", "Hello World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TraceInfoFormatted)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceInfo("MyFile", 123, "MyFunction", "{0} {1}", "Hello", "World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TraceDataString)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceData("MyFile", 123, "MyFunction", "Hello World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Data\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TraceDataFormatted)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceData("MyFile", 123, "MyFunction", "{0} {1}", "Hello", "World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Data\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TraceDebugString)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceDebug("MyFile", 123, "MyFunction", "Hello World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Debug\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, TraceDebugFormatted)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceDebug("MyFile", 123, "MyFunction", "{0} {1}", "Hello", "World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Debug\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, FatalCheckPassString)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceFatalCheck(true, "MyFile", 123, "MyFunction", "Hello World");
    EXPECT_TRUE(m_lineWriter.GetResult().empty());
    EXPECT_EQ(0, m_exitCode);
}

TEST_F(TracingTest, FatalCheckFailureString)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceFatalCheck(false, "MyFile", 123, "MyFunction", "Hello World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
    EXPECT_EQ(1, m_exitCode);
}

TEST_F(TracingTest, FatalCheckPassFormatted)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceFatalCheck(true, "MyFile", 123, "MyFunction", "{0} {1}", "Hello", "World");
    EXPECT_TRUE(m_lineWriter.GetResult().empty());
    EXPECT_EQ(0, m_exitCode);
}

TEST_F(TracingTest, FatalCheckFailureFormatted)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceFatalCheck(false, "MyFile", 123, "MyFunction", "{0} {1}", "Hello", "World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|MyFile\\:123\\|MyFunction\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
    EXPECT_EQ(1, m_exitCode);
}

TEST_F(TracingTest, TraceMacro)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::Information);
    TRACE_INFRA(TraceCategory::Information, "{0} {1} (C) {2,4:D}", "Hello", "World", 2020);
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|\\w+.cpp\\:\\d+\\|\\w+\\|TracingTest\\|Hello World \\(C\\) 2020"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, ErrorMacro)
{
    utility::Error error(-1, "", "Fake error");
    TRACE_ERROR(error);
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|\\w+.cpp\\:\\d+\\|\\w+\\|TracingTest\\|Error code\\: Unknown\\: Fake error"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
    EXPECT_EQ(0, m_exitCode);
}

TEST_F(TracingTest, FatalMacro)
{
    utility::Error error(-1, "", "Fake error");
    EXPECT_EQ(0, m_exitCode);
    TRACE_FATAL(error);
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|\\w+.cpp\\:\\d+\\|\\w+\\|TracingTest\\|Error code\\: Unknown\\: Fake error"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
    EXPECT_EQ(-1, m_exitCode);
}

TEST_F(TracingTest, ThrowMacro)
{
    utility::GenericError error("Fake error");

    std::string result;
    try
    {
        TRACE_THROW(error);
    }
    catch (std::exception& e)
    {
        result = e.what();
    }
    EXPECT_TRUE(osal::VerifyMatch(result,
        TraceRegexTimeStamp + "Info \\w+.cpp\\:\\d+ \\(\\w+\\)\\: Fake error"));
    EXPECT_EQ(0, m_exitCode);
}

TEST_F(TracingTest, TraceInfoMacro)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TRACE_INFO("{0} {1}", "Hello", "World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|\\w+.cpp\\:\\d+\\|\\w+\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
}

TEST_F(TracingTest, FatalCheckMacroSuccess)
{
    TRACE_FATALCHECK(true, "{0} {1}", "Hello", "World");
    EXPECT_TRUE(m_lineWriter.GetResult().empty());
    EXPECT_EQ(0, m_exitCode);
}

TEST_F(TracingTest, FatalCheckMacroFailure)
{
    TRACE_FATALCHECK(false, "{0} {1}", "Hello", "World");
    std::vector<std::string> regexStrings{
        TraceRegexTimeStamp + "Info\\|\\w+.cpp\\:\\d+\\|\\w+\\|TracingTest\\|Hello World"
    };
    CheckMatch(regexStrings, m_lineWriter.GetResult());
    EXPECT_EQ(1, m_exitCode);
}

TEST_F(TracingTest, TraceToConsole)
{
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TraceStartup("MyFile", 123, "MyFunction", "Starting");
    TraceShutdown("MyFile", 123, "MyFunction", "Stopping");
}

} // namespace tracing
