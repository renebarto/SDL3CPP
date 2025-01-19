//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : EnvironmentTest.cpp
//
// Namespace   : osal
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "osal/utilities/Environment.h"

#include "test-platform/GoogleTest.h"

namespace osal {

TEST(EnvironmentTest, Get)
{
    auto result = Environment::Get("HOME");
    if (result == nullptr)
    {
        result = Environment::Get("HOMEDRIVE");
    }
    EXPECT_NOT_NULL(result);
}

TEST(EnvironmentTest, Set)
{
    const char* variable = "MYDUMMY";
    const char* value1 = "VALUE1";
    const char* value2 = "VALUE2";
    Environment::Set(variable, value1);
    auto result = Environment::Get(variable);
    EXPECT_EQ(std::string(value1), result);
    Environment::Set(variable, value2, false);
    result = Environment::Get(variable);
    EXPECT_EQ(std::string(value1), result);
    Environment::Set(variable, value2, true);
    result = Environment::Get(variable);
    EXPECT_EQ(std::string(value2), result);
}

TEST(EnvironmentTest, Unset)
{
    const char* variable = "MYDUMMY";
    const char* value = "VALUE";
    Environment::Set(variable, value);
    auto result = Environment::Get(variable);
    EXPECT_EQ(std::string(value), result);
    Environment::Unset(variable);
    result = Environment::Get(variable);
    EXPECT_NULL(result);
}

} // namespace osal
