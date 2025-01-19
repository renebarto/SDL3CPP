//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ErrorCodeTest.cpp
//
// Namespace   : osal
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "osal/utilities/ErrorCode.h"

#include "test-platform/GoogleTest.h"

namespace osal {

//TEST(ErrorCodeTest, ConstructDefault)
//{
//    ErrorCode errorCode;
//    EXPECT_TRUE(static_cast<bool>(errorCode));
//    EXPECT_EQ(0, errorCode.Code());
//    std::string errorString = "Success";
//
//    EXPECT_EQ(errorString, errorCode.Description());
//}

//TEST(ErrorCodeTest, ConstructNoError)
//{
//    ErrorCode errorCode(0);
//    EXPECT_TRUE(static_cast<bool>(errorCode));
//    EXPECT_EQ(0, errorCode.Code());
//}
//
//TEST(ErrorCodeTest, ConstructError)
//{
//    ErrorCode errorCode(2); // File not found
//    EXPECT_FALSE(static_cast<bool>(errorCode));
//    EXPECT_EQ(2, errorCode.Code());
//
//#if defined(PLATFORM_WINDOWS)
//    std::string errorString = "The system cannot find the file specified.\r\n";
//#else
//    std::string errorString = "No such file or directory";
//#endif
//    EXPECT_EQ(errorString, errorCode.Description());
//}
//
} // namespace osal
