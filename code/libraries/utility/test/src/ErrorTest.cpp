//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ErrorTest.cpp
//
// Namespace   : utility
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "utility/Error.h"

namespace utility {

TEST(ErrorTest, Construct)
{
    std::string errorString{ "File not found" };
    std::string message{ "Could not open file" };
    Error error(2, errorString, message);
    EXPECT_EQ(2, error.ErrorCode());
    EXPECT_EQ(errorString, error.ErrorString());
    EXPECT_EQ(message, error.Message());
}

TEST(ErrorTest, ConstructFormat)
{
    std::string errorString{ "File not found" };
    std::string formatString{ "Could not open file {}: {}" };
    std::string arg1{ "file.txt" };
    std::string arg2{ "Failed" };
    std::string message{ "Could not open file file.txt: Failed" };
    Error error(2, errorString, formatString, arg1, arg2);
    EXPECT_EQ(2, error.ErrorCode());
    EXPECT_EQ(errorString, error.ErrorString());
    EXPECT_EQ(message, error.Message());
}

TEST(ErrorTest, InsertionOperator)
{
    std::string errorString{ "File not found" };
    std::string arg{ "Could not open file: " };
    std::string argAdditional{ "file.txt" };
    std::string message{ "Could not open file: file.txt" };
    Error error(2, errorString, arg);
    error << argAdditional;
    EXPECT_EQ(2, error.ErrorCode());
    EXPECT_EQ(errorString, error.ErrorString());
    EXPECT_EQ(message, error.Message());
}

TEST(ErrorTest, StreamInsertion)
{
    std::string errorString{ "File not found" };
    std::string message{ "Could not open file" };
    std::string text{ "2 (02): File not found Could not open file" };
    Error error(2, errorString, message);
    std::ostringstream stream;
    stream << error;
    EXPECT_EQ(text, stream.str());
}

TEST(ErrorTest, Serialize)
{
    std::string errorString{ "File not found" };
    std::string message{ "Could not open file" };
    std::string text{ "2 (02): File not found Could not open file" };
    Error error(2, errorString, message);
    EXPECT_EQ(text, serialization::Serialize(error));
}

} // namespace utility
