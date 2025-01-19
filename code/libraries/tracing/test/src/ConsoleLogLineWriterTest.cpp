//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ConsoleLogLineWriterTest.cpp
//
// Namespace   : tracing
//
// Class       : ConsoleLogLineWriterTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "tracing/ConsoleLogLineWriter.h"

namespace tracing {

class ConsoleLogLineWriterTest : public ::testing::Test
{
public:
    ConsoleLogLineWriterTest()
    {}

    virtual void SetUp() override
    {
    }
    virtual void TearDown() override
    {
    }

};

TEST_F(ConsoleLogLineWriterTest, WriteLine)
{
    ConsoleLogLineWriter writer;
    std::string text{ "Some text" };

    // Should print line "Some text" in Magenta
    writer.WriteLine(text);
}

} // namespace tracing
