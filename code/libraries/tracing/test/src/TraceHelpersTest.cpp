//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceHelpersTest.cpp
//
// Namespace   : tracing
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "tracing/TraceHelpers.h"

namespace tracing {

TEST(TraceHelpersTest, ExtractFileNameWindows)
{
    std::string path = "C:\\dir\\file.txt";
    EXPECT_EQ("file.txt", ExtractFileName(path));
}

TEST(TraceHelpersTest, ExtractFileNameLinux)
{
    std::string path = "/dir/file.txt";
    EXPECT_EQ("file.txt", ExtractFileName(path));
}

TEST(TraceHelpersTest, ExtractFileNameEmpty)
{
    std::string path = "";
    EXPECT_EQ("", ExtractFileName(path));
}

} // namespace tracing
