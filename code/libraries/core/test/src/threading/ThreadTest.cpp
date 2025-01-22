//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : ThreadTest.cpp
//
// Namespace   : core::threading
//
// Class       : ThreadTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "osal/utilities/ThreadFunctions.h"
#include "core/threading/Thread.h"
#include "tracing/ITraceLineWriter.h"
#include "tracing/Tracing.h"

namespace core {
namespace threading {

static const auto SLEEP = std::chrono::milliseconds(50);
static const StringType ThreadName = TX("MyThread");

class ThreadTest : public ::testing::Test
{
public:
    ::utility::EnumBitSet<tracing::TraceCategory> m_savedTraceFilter;

    ThreadTest()
        : m_savedTraceFilter()
    {}

    virtual void SetUp() override
    {
        m_savedTraceFilter = ::tracing::Tracing::GetDefaultTraceFilter();
    }
    virtual void TearDown() override 
    {
        ::tracing::Tracing::SetDefaultTraceFilter(m_savedTraceFilter);
    }

    static void TestThread()
    {
        std::this_thread::sleep_for(SLEEP);
    }
    static void CrashingThread()
    {
        std::this_thread::sleep_for(SLEEP);
        throw std::runtime_error("Crash");
    }
};

TEST_F(ThreadTest, Construction)
{
    Thread thread;
    EXPECT_FALSE(thread.IsAlive());
    EXPECT_FALSE(thread.IsRunning());
    EXPECT_FALSE(thread.IsFinished());
    EXPECT_EQ(TX(""), thread.GetName());
    thread.WaitForDeath();
    EXPECT_FALSE(thread.IsAlive());
    EXPECT_FALSE(thread.IsRunning());
    EXPECT_FALSE(thread.IsFinished());
    EXPECT_FALSE(thread.HasDied());
    EXPECT_FALSE(thread.HaveResult());
    EXPECT_THROW(thread.GetResult(), std::future_error);
}

TEST_F(ThreadTest, ConstructionName)
{
    Thread thread(ThreadName);
    EXPECT_FALSE(thread.IsAlive());
    EXPECT_FALSE(thread.IsRunning());
    EXPECT_FALSE(thread.IsFinished());
    EXPECT_EQ(ThreadName, thread.GetName());
    thread.WaitForDeath();
    EXPECT_FALSE(thread.IsAlive());
    EXPECT_FALSE(thread.IsRunning());
    EXPECT_FALSE(thread.IsFinished());
    EXPECT_FALSE(thread.HasDied());
    EXPECT_FALSE(thread.HaveResult());
    EXPECT_THROW(thread.GetResult(), std::future_error);
}

TEST_F(ThreadTest, ConstructionFunction)
{
    Thread thread(TestThread);
    EXPECT_TRUE(thread.IsAlive());
    EXPECT_TRUE(thread.IsRunning());
    EXPECT_FALSE(thread.IsFinished());
    EXPECT_EQ(TX(""), thread.GetName());
    std::this_thread::sleep_for(SLEEP);
    thread.WaitForDeath();
    EXPECT_FALSE(thread.IsAlive());
    EXPECT_FALSE(thread.IsRunning());
    EXPECT_TRUE(thread.IsFinished());
    EXPECT_TRUE(thread.HasDied());
    EXPECT_EQ(TX(""), thread.GetName());
    EXPECT_TRUE(thread.HaveResult());
    EXPECT_NO_THROW(thread.GetResult());
}

TEST_F(ThreadTest, ConstructionFunctionName)
{
    Thread thread(TestThread, ThreadName);
    EXPECT_TRUE(thread.IsAlive());
    EXPECT_TRUE(thread.IsRunning());
    EXPECT_FALSE(thread.IsFinished());
    EXPECT_EQ(ThreadName, thread.GetName());
    std::this_thread::sleep_for(SLEEP);
    thread.WaitForDeath();
    EXPECT_FALSE(thread.IsAlive());
    EXPECT_FALSE(thread.IsRunning());
    EXPECT_TRUE(thread.IsFinished());
    EXPECT_TRUE(thread.HasDied());
    EXPECT_EQ(ThreadName, thread.GetName());
    EXPECT_TRUE(thread.HaveResult());
    EXPECT_NO_THROW(thread.GetResult());
}

TEST_F(ThreadTest, GetSetName)
{
    const StringType AltName = TX("Thread");
    Thread thread(ThreadName);
    EXPECT_EQ(ThreadName, thread.GetName());
    thread.Create(TestThread);
    thread.SetName(AltName);
    EXPECT_EQ(AltName, thread.GetName());
    EXPECT_TRUE(thread.HaveResult());
    EXPECT_NO_THROW(thread.GetResult());
}

TEST_F(ThreadTest, Create)
{
    Thread thread(ThreadName);
    EXPECT_FALSE(thread.IsAlive());
    EXPECT_FALSE(thread.IsRunning());
    EXPECT_FALSE(thread.IsFinished());
    EXPECT_EQ(ThreadName, thread.GetName());
    thread.Create(TestThread);
    EXPECT_TRUE(thread.IsAlive());
    EXPECT_TRUE(thread.IsRunning());
    EXPECT_FALSE(thread.IsFinished());
    EXPECT_EQ(ThreadName, thread.GetName());
    std::this_thread::sleep_for(SLEEP);
    thread.WaitForDeath();
    EXPECT_FALSE(thread.IsAlive());
    EXPECT_FALSE(thread.IsRunning());
    EXPECT_TRUE(thread.IsFinished());
    EXPECT_TRUE(thread.HasDied());
    EXPECT_EQ(ThreadName, thread.GetName());
    EXPECT_TRUE(thread.HaveResult());
    EXPECT_NO_THROW(thread.GetResult());
}

TEST_F(ThreadTest, Destroy)
{
    Thread thread(TestThread, ThreadName);
    EXPECT_TRUE(thread.IsAlive());
    EXPECT_TRUE(thread.IsRunning());
    EXPECT_FALSE(thread.IsFinished());
    EXPECT_EQ(ThreadName, thread.GetName());
    std::this_thread::sleep_for(SLEEP);
    thread.Destroy();
    EXPECT_FALSE(thread.IsAlive());
    EXPECT_FALSE(thread.IsRunning());
    EXPECT_FALSE(thread.IsFinished());
    EXPECT_TRUE(thread.HasDied());
    EXPECT_EQ(ThreadName, thread.GetName());
    EXPECT_TRUE(thread.HaveResult());
    EXPECT_NO_THROW(thread.GetResult());
}

TEST_F(ThreadTest, CrashingThread)
{
    Thread thread(CrashingThread, ThreadName);
    EXPECT_TRUE(thread.IsAlive());
    EXPECT_TRUE(thread.IsRunning());
    EXPECT_FALSE(thread.IsFinished());
    EXPECT_EQ(ThreadName, thread.GetName());
    std::this_thread::sleep_for(SLEEP);
    thread.Destroy();
    EXPECT_FALSE(thread.IsAlive());
    EXPECT_FALSE(thread.IsRunning());
    EXPECT_FALSE(thread.IsFinished());
    EXPECT_TRUE(thread.HasDied());
    EXPECT_EQ(ThreadName, thread.GetName());
    EXPECT_TRUE(thread.HaveResult());
    EXPECT_THROW(thread.GetResult(), std::runtime_error);
}

StringType HelperThread()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return osal::GetThreadNameSelf();
}
TEST_F(ThreadTest, GetNamesOfMultipleThreads)
{
    osal::SetThreadNameSelf(TX("Main"));

    const StringType helperThreadName = TX("HelperThread");
    core::threading::TypedReturnThread<StringType> helperThread(HelperThread, helperThreadName);
    EXPECT_EQ(helperThreadName, helperThread.GetName());

    helperThread.WaitForDeath();
    auto result = helperThread.GetResult();
   
    EXPECT_EQ(helperThreadName, result);
    EXPECT_EQ(TX("Main"), osal::GetThreadNameSelf());
}

} // namespace threading
} // namespace core
