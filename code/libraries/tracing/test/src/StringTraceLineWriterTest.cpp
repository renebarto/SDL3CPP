//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : StringTraceLineWriterTest.cpp
//
// Namespace   : tracing
//
// Class       : StringTraceLineWriterTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "tracing/StringTraceLineWriter.h"

namespace tracing {

TEST(StringTraceLineWriterTest, WriteLine)
{
    StringTraceLineWriter writer;
    std::string text{ "Some text" };
    std::vector<std::string> expected { text };

    EXPECT_TRUE(writer.GetResult().empty());
    writer.WriteLine(TraceCategory::None, text);
    EXPECT_EQ(expected, writer.GetResult());
}

TEST(StringTraceLineWriterTest, WriteLineMultiple)
{
    StringTraceLineWriter writer;
    std::string text1{ "Some text" };
    std::string text2{ "Some more text" };
    std::vector<std::string> expected { text1, text2 };

    EXPECT_TRUE(writer.GetResult().empty());
    writer.WriteLine(TraceCategory::None, text1);
    writer.WriteLine(TraceCategory::None, text2);
    EXPECT_EQ(expected, writer.GetResult());
}

TEST(StringTraceLineWriterTest, WriteResetResult)
{
    StringTraceLineWriter writer;
    std::string text{ "Some text" };

    EXPECT_TRUE(writer.GetResult().empty());
    writer.WriteLine(TraceCategory::None, text);
    EXPECT_FALSE(writer.GetResult().empty());
    writer.ResetResult();
    EXPECT_TRUE(writer.GetResult().empty());
}

} // namespace tracing
