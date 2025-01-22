//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceRegistryTest.cpp
//
// Namespace   : tracing
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "tracing/TraceRegistry.h"

#include "osal/utilities/Console.h"
#include "tracing/TraceRegistryItem.h"

#include "MockTraceRegistryUpdateListener.h"

using ::testing::_;

namespace tracing {

TEST(TraceRegistryTest, FindCompilationUnit)
{
    auto& registry = ::GetTraceRegistry();
    auto entry = registry.FindCompilationUnit("code/libraries/tracing/src/TraceRegistry.cpp");
    EXPECT_NOT_NULL(entry);
}

TEST(TraceRegistryTest, TraceCategoryIsEnabledForRegisteredCompilationUnitWithOverruledTraceFilter)
{
    auto& registry = ::GetTraceRegistry();
    auto filter = registry.GetTraceFilter("code/libraries/tracing/src/TraceRegistry.cpp");
    registry.SetTraceFilter("code/libraries/tracing/src/TraceRegistry.cpp", TraceCategory::FunctionEnter | TraceCategory::FunctionLeave);
    EXPECT_TRUE(registry.IsTraceCategoryEnabled("code/libraries/tracing/src/TraceRegistry.cpp", TraceCategory::FunctionEnter));
    registry.SetTraceFilter("code/libraries/tracing/src/TraceRegistry.cpp", TraceCategory::None);
    EXPECT_FALSE(registry.IsTraceCategoryEnabled("code/libraries/tracing/src/TraceRegistry.cpp", TraceCategory::FunctionEnter));
    registry.SetTraceFilter("code/libraries/tracing/src/TraceRegistry.cpp", filter);
}

TEST(TraceRegistryTest, TraceCategoryNotEnabledForRegisteredCompilationUnitWithDefaultTraceFilter)
{
    auto& registry = ::GetTraceRegistry();
    EXPECT_FALSE(registry.IsTraceCategoryEnabled("code/libraries/tracing/src/TraceRegistry.cpp", TraceCategory::FunctionEnter));
}

TEST(TraceRegistryTest, TraceCategoryNotEnabledForUnregisteredCompilationUnit)
{
    auto& registry = ::GetTraceRegistry();
    
    EXPECT_FALSE(registry.IsTraceCategoryEnabled("code/libraries/tracing/src/MyNonExistingFile.cpp", TraceCategory::FunctionEnter));
}

TEST(TraceRegistryTest, TraceCategoryIsEnabledForUnregisteredCompilationUnitWhenDefaultEnables)
{
    auto& registry = ::GetTraceRegistry();
    
    registry.SetDefaultTraceFilter(TraceCategory::FunctionEnter | TraceCategory::FunctionLeave);
    EXPECT_TRUE(registry.IsTraceCategoryEnabled("code/libraries/tracing/src/MyNonExistingFile.cpp", TraceCategory::FunctionEnter));
    registry.SetDefaultTraceFilter(TraceCategory::None);
}

TEST(TraceRegistryTest, TraceRegistryUpdateListenerIsNotCalledIfNotSubscribed)
{
    TraceRegistry registry;

    MockTraceRegistryUpdateListener listener;

    CategorySet<TraceCategory> defaultFilter = TraceCategory::FunctionEnter | TraceCategory::FunctionLeave;
    EXPECT_CALL(listener, UpdateDefaultFilter(defaultFilter)).Times(0);

    registry.SetDefaultTraceFilter(defaultFilter);
}

TEST(TraceRegistryTest, TraceRegistryUpdateListenerIsCalledWhenDefaultTraceFilterIsChanged)
{
    TraceRegistry registry;

    MockTraceRegistryUpdateListener listener;
    registry.SubscribeUpdateListener(&listener);

    CategorySet<TraceCategory> defaultFilter = TraceCategory::FunctionEnter | TraceCategory::FunctionLeave;
    EXPECT_CALL(listener, UpdateDefaultFilter(defaultFilter)).Times(1);

    registry.SetDefaultTraceFilter(defaultFilter);
}

TEST(TraceRegistryTest, TraceRegistryUpdateListenerIsCalledWhenEntryIsAdded)
{
    TraceRegistry registry;

    MockTraceRegistryUpdateListener listener;
    registry.SubscribeUpdateListener(&listener);

    EXPECT_CALL(listener, UpdateTraceRegistryItem(_)).Times(1);

    TraceRegistryItem traceEntry("dummy", registry);
}

TEST(TraceRegistryTest, TraceRegistryUpdateListenerIsCalledWhenEntryIsUpdated)
{
    TraceRegistry registry;
    TraceRegistryItem traceEntry("dummy", registry);

    MockTraceRegistryUpdateListener listener;
    registry.SubscribeUpdateListener(&listener);

    EXPECT_CALL(listener, UpdateTraceRegistryItem(_)).Times(1);

    TraceRegistryItem traceEntry2("dummy", registry);
}

TEST(TraceRegistryTest, TraceRegistryUpdateListenerIsRemovedWhenUnsubscribed)
{
    TraceRegistry registry;

    MockTraceRegistryUpdateListener listener;
    registry.SubscribeUpdateListener(&listener);

    EXPECT_CALL(listener, UpdateTraceRegistryItem(_)).Times(1);

    TraceRegistryItem traceEntry("dummy", registry);

    registry.UnsubscribeUpdateListener(&listener);

    TraceRegistryItem traceEntry2("dummy", registry);
}

TEST(TraceRegistryTest, GetItems)
{
    TraceRegistry registry;

    TraceRegistryItem traceEntry("dummy", registry);
    TraceRegistryItem traceEntry2("dummy2", registry);

    auto items = registry.GetItems();
    try {
        auto entry1 = items["dummy"];
        EXPECT_EQ("dummy", entry1->CompilationUnitFileName());
        EXPECT_EQ(uint32_t{ 0x0000000F }, entry1->GetTraceFilter().GetMask());
        auto entry2 = items["dummy2"];
        EXPECT_EQ("dummy2", entry2->CompilationUnitFileName());
        EXPECT_EQ(uint32_t{ 0x0000000F }, entry2->GetTraceFilter().GetMask());
    }
    catch(...)
    {
        FAIL();
    }

}

TEST(TraceRegistryTest, Serialize)
{
    TraceRegistry registry;

    TraceRegistryItem traceEntry("dummy", registry);
    TraceRegistryItem traceEntry2("dummy2", registry);

    std::ostringstream stream;
    stream << registry;
    EXPECT_EQ("dummy:0x0000000F\ndummy2:0x0000000F\n", stream.str());
}

TEST(TraceRegistryTest, SerializeActual)
{
    osal::Console console;
    console << GetTraceRegistry();
}

} // namespace tracing
