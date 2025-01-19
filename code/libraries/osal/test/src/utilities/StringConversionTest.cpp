//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : StringConversionTest.cpp
//
// Namespace   : osal
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

namespace osal {

TEST(StringFunctionsTest, ConvertString)
{
    EXPECT_EQ("ABCDEF", Convert("ABCDEF"));
}

TEST(StringFunctionsTest, ConvertToString)
{
    EXPECT_EQ("ABCDEF", ConvertToString("ABCDEF"));
}

} // namespace osal
