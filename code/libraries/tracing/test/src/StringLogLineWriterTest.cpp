//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : StringLogLineWriterTest.cpp
//
// Namespace   : tracing
//
// Class       : StringLogLineWriterTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "tracing/StringLogLineWriter.h"

namespace tracing {

class StringLogLineWriterTest : public ::testing::Test
{
public:
    StringLogLineWriterTest()
    {}

    virtual void SetUp() override
    {
    }
    virtual void TearDown() override
    {
    }

};

TEST_F(StringLogLineWriterTest, WriteLine)
{
    StringLogLineWriter writer;
    std::string text{ "Some text" };
    std::vector<std::string> expected { text };

    EXPECT_TRUE(writer.GetResult().empty());
    writer.WriteLine(text);
    EXPECT_EQ(expected, writer.GetResult());
}

TEST_F(StringLogLineWriterTest, WriteLineMultiple)
{
    StringLogLineWriter writer;
    std::string text1{ "Some text" };
    std::string text2{ "Some more text" };
    std::vector<std::string> expected { text1, text2 };

    EXPECT_TRUE(writer.GetResult().empty());
    writer.WriteLine(text1);
    writer.WriteLine(text2);
    EXPECT_EQ(expected, writer.GetResult());
}

TEST_F(StringLogLineWriterTest, WriteResetResult)
{
    StringLogLineWriter writer;
    std::string text{ "Some text" };

    EXPECT_TRUE(writer.GetResult().empty());
    writer.WriteLine(text);
    EXPECT_FALSE(writer.GetResult().empty());
    writer.ResetResult();
    EXPECT_TRUE(writer.GetResult().empty());
}

} // namespace tracing
