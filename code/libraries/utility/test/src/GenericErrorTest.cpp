//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : GenericErrorTest.cpp
//
// Namespace   : utility
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "utility/GenericError.h"

namespace utility {

TEST(GenericErrorTest, Construct)
{
    std::string message{ "Could not open file" };
    GenericError error(message);
    EXPECT_EQ(message, error.Message());
}

TEST(GenericErrorTest, ConstructFormat)
{
    std::string formatString{ "Could not open file {}: {}" };
    std::string arg1{ "file.txt" };
    std::string arg2{ "Failed" };
    std::string message{ "Could not open file file.txt: Failed" };
    GenericError error(formatString, arg1, arg2);
    EXPECT_EQ(message, error.Message());
}

TEST(GenericErrorTest, InsertionOperator)
{
    std::string arg{ "Could not open file: " };
    std::string argAdditional{ "file.txt" };
    std::string message{ "Could not open file: file.txt" };
    GenericError error(arg);
    error << argAdditional;
    EXPECT_EQ(message, error.Message());
}

TEST(GenericErrorTest, StreamInsertion)
{
    std::string message{ "Could not open file" };
    std::string text{ "Could not open file" };
    GenericError error(message);
    std::ostringstream stream;
    stream << error;
    EXPECT_EQ(text, stream.str());
}

TEST(GenericErrorTest, Serialize)
{
    std::string message{ "Could not open file" };
    std::string text{ "Could not open file" };
    GenericError error(message);
    EXPECT_EQ(text, serialization::Serialize(error));
}

} // namespace utility
