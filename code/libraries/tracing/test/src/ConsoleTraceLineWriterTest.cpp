//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ConsoleTraceLineWriterTest.cpp
//
// Namespace   : tracing
//
// Class       : ConsoleTraceLineWriterTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "tracing/ConsoleTraceLineWriter.h"

namespace tracing {

    class ConsoleTraceLineWriterTest : public ::testing::Test
    {
    public:
        ConsoleTraceLineWriterTest()
        {}

        virtual void SetUp() override
        {
        }
        virtual void TearDown() override
        {
        }

    };

    TEST_F(ConsoleTraceLineWriterTest, WriteLine)
    {
        ConsoleTraceLineWriter writer;
        std::string text{ "Some text" };

        // Should print line "Some text" in Yellow
        writer.WriteLine(TraceCategory::FunctionEnter, text);
        // Should print line "Some text" in Yellow
        writer.WriteLine(TraceCategory::FunctionLeave, text);
        // Should print line "Some text" in Green
        writer.WriteLine(TraceCategory::Debug, text);
        // Should print line "Some text" in White
        writer.WriteLine(TraceCategory::Information, text);
        // Should print line "Some text" in Magenta
        writer.WriteLine(TraceCategory::Warning, text);
        // Should print line "Some text" in Red
        writer.WriteLine(TraceCategory::Error, text);
        // Should print line "Some text" in Bright red
        writer.WriteLine(TraceCategory::Fatal, text);
    }

} // namespace tracing
