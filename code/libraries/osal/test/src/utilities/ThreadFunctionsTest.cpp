//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ThreadFunctionsTest.cpp
//
// Namespace   : osal
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include <sstream>
#include "osal/utilities/ThreadFunctions.h"

namespace osal
{
    
TEST(ThreadTest, ByDefaultNoThreadsMapping)
{
    std::ostringstream stream;
    stream << "Thread #" << std::this_thread::get_id();
    std::string text = stream.str();

    EXPECT_EQ(text, GetThreadNameSelf());
}

TEST(ThreadTest, IfTheMainThreadIsNameItIsInTheMap)
{
    SetThreadNameSelf("Main");

    EXPECT_EQ("Main", GetThreadNameSelf());
}

} // namespace osal

