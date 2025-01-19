//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : FatalHandlerTest.cpp
//
// Namespace   : tracing
//
// Class       : FatalHandlerTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "tracing/FatalHandler.h"

namespace tracing {

class FatalHandlerTest : public ::testing::Test
{
public:
    int m_exitCode;

    FatalHandlerTest()
        : m_exitCode()
    {}

    virtual void SetUp() override
    {
        FatalHandler::SetFatalExitFunction([this](int exitCode){ m_exitCode = exitCode; });
    }
    virtual void TearDown() override
    {
        FatalHandler::SetFatalExitFunction(nullptr);    
    }
};

TEST_F(FatalHandlerTest, FatalExitNonZero)
{
    FatalHandler::FatalExit(1);
    EXPECT_EQ(1, m_exitCode);
}

} // namespace tracing
