//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : SerializationTest.cpp
//
// Namespace   : serialization
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "serialization/Serialization.h"

namespace serialization {

TEST(StringFunctionsTest, AlignLeft)
{
    auto expected = "ABCD    ";
    auto actual = Align("ABCD", -8);
    EXPECT_EQ(expected, actual);
}

TEST(StringFunctionsTest, AlignRight)
{
    auto expected = "    ABCD";
    auto actual = Align("ABCD", 8);
    EXPECT_EQ(expected, actual);
}

} // namespace serialization
