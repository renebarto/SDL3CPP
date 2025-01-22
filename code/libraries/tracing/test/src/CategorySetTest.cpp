//------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : CategorySetTest.cpp
//
// Namespace   : tracing
//
// Class       : -
//
// Description :
//  CategorySet tests
//
//---------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include <string>
#include "tracing/TraceCategory.h"
#include "tracing/CategorySet.h"

namespace tracing {

TEST(CategorySetTest, ConstructDefault)
{
    CategorySet<TraceCategory> set;
    for (auto const& category : EnumTraceCategories())
    {
        EXPECT_FALSE(set.is_set(category));
    }
}

TEST(CategorySetTest, Construct)
{
    CategorySet<TraceCategory> set(TraceCategory::Information);
    for (auto const& category : EnumTraceCategories())
    {
        if (category != TraceCategory::Information)
            EXPECT_FALSE(set.is_set(category));
        else
            EXPECT_TRUE(set.is_set(category));
    }
}

TEST(CategorySetTest, ConstructMaskNone)
{
    CategorySet<TraceCategory> set(0x0000);
    for (auto const& category : EnumTraceCategories())
    {
        EXPECT_FALSE(set.is_set(category));
    }
}

TEST(CategorySetTest, ConstructMaskAll)
{
    CategorySet<TraceCategory> set(0xFFFFFFFF);
    for (auto const& category : EnumTraceCategories())
    {
        EXPECT_TRUE(set.is_set(category));
    }
}

TEST(CategorySetTest, ConstructMaskOnlyDebug)
{
    CategorySet<TraceCategory> set(0x00000001);
    for (auto const& category : EnumTraceCategories())
    {
        if (category != TraceCategory::Fatal)
            EXPECT_FALSE(set.is_set(category));
        else
            EXPECT_TRUE(set.is_set(category));
    }
}

TEST(CategorySetTest, Set)
{
    CategorySet<TraceCategory> set;
    set.set(TraceCategory::FunctionEnter);
    set.set(TraceCategory::FunctionLeave);
    for (auto const& category : EnumTraceCategories())
    {
        if ((category != TraceCategory::FunctionEnter) && (category != TraceCategory::FunctionLeave))
            EXPECT_FALSE(set.is_set(category));
        else
            EXPECT_TRUE(set.is_set(category));
    }
}

TEST(CategorySetTest, Reset)
{
    CategorySet<TraceCategory> set(0xFFFFFFFF);
    set.reset(TraceCategory::FunctionEnter);
    set.reset(TraceCategory::FunctionLeave);
    for (auto const& category : EnumTraceCategories())
    {
        if ((category != TraceCategory::FunctionEnter) && (category != TraceCategory::FunctionLeave))
            EXPECT_TRUE(set.is_set(category));
        else
            EXPECT_FALSE(set.is_set(category));
    }
}

TEST(CategorySetTest, GetMask)
{
    CategorySet<TraceCategory> set(TraceCategory::FunctionEnter | TraceCategory::FunctionLeave);
    uint32_t actual = set.GetMask();
    uint32_t expected = static_cast<uint32_t>(TraceCategory::FunctionEnter) | static_cast<uint32_t>(TraceCategory::FunctionLeave);
    EXPECT_EQ(expected, actual);
}

TEST(CategorySetTest, ClassOperatorOr)
{
    CategorySet<TraceCategory> set;
    set |= TraceCategory::FunctionEnter;
    set |= TraceCategory::FunctionLeave;
    for (auto const& category : EnumTraceCategories())
    {
        if ((category != TraceCategory::FunctionEnter) && (category != TraceCategory::FunctionLeave))
            EXPECT_FALSE(set.is_set(category));
        else
            EXPECT_TRUE(set.is_set(category));
    }
}

TEST(CategorySetTest, OperatorOrSetCategory)
{
    CategorySet<TraceCategory> set;
    set = set | TraceCategory::FunctionEnter;
    set = set | TraceCategory::FunctionLeave;
    for (auto const& category : EnumTraceCategories())
    {
        if ((category != TraceCategory::FunctionEnter) && (category != TraceCategory::FunctionLeave))
            EXPECT_FALSE(set.is_set(category));
        else
            EXPECT_TRUE(set.is_set(category));
    }
}

TEST(CategorySetTest, OperatorOrCategoryCategory)
{
    CategorySet<TraceCategory> set = TraceCategory::FunctionEnter | TraceCategory::FunctionLeave;
    for (auto const& category : EnumTraceCategories())
    {
        if ((category != TraceCategory::FunctionEnter) && (category != TraceCategory::FunctionLeave))
            EXPECT_FALSE(set.is_set(category));
        else
            EXPECT_TRUE(set.is_set(category));
    }
}

TEST(CategorySetTest, OperatorEqualsSetSet)
{
    CategorySet<TraceCategory> set1 = TraceCategory::FunctionEnter | TraceCategory::FunctionLeave;
    CategorySet<TraceCategory> set2 = TraceCategory::FunctionEnter | TraceCategory::FunctionLeave;
    CategorySet<TraceCategory> set3 = TraceCategory::Information;
    EXPECT_EQ(set1, set2);
    EXPECT_NE(set1, set3);
    EXPECT_NE(set2, set3);
    EXPECT_TRUE(set1 == set2);
    EXPECT_FALSE(set1 == set3);
    EXPECT_FALSE(set2 == set3);
}

TEST(CategorySetTest, OperatorEqualsMaskTypeSet)
{
    CategorySet<TraceCategory> set1 = TraceCategory::FunctionEnter | TraceCategory::FunctionLeave;
    CategorySet<TraceCategory> set2 = TraceCategory::Information;
    uint32_t mask1 = static_cast<uint32_t>(TraceCategory::FunctionEnter) | static_cast<uint32_t>(TraceCategory::FunctionLeave);
    uint32_t mask2 = static_cast<uint32_t>(TraceCategory::Information);
    EXPECT_EQ(set1, mask1);
    EXPECT_NE(set1, mask2);
    EXPECT_NE(set2, mask1);
    EXPECT_EQ(set2, mask2);
    EXPECT_TRUE(set1 == mask1);
    EXPECT_FALSE(set1 == mask2);
    EXPECT_FALSE(set2 == mask1);
    EXPECT_TRUE(set2 == mask2);
}

TEST(CategorySetTest, OperatorEqualsSetMaskType)
{
    CategorySet<TraceCategory> set1 = TraceCategory::FunctionEnter | TraceCategory::FunctionLeave;
    CategorySet<TraceCategory> set2 = TraceCategory::Information;
    uint32_t mask1 = static_cast<uint32_t>(TraceCategory::FunctionEnter) | static_cast<uint32_t>(TraceCategory::FunctionLeave);
    uint32_t mask2 = static_cast<uint32_t>(TraceCategory::Information);
    EXPECT_EQ(mask1, set1);
    EXPECT_NE(mask1, set2);
    EXPECT_NE(mask2, set1);
    EXPECT_EQ(mask2, set2);
    EXPECT_TRUE(mask1 == set1);
    EXPECT_FALSE(mask1 == set2);
    EXPECT_FALSE(mask2 == set1);
    EXPECT_TRUE(mask2 == set2);
}

TEST(CategorySetTest, OperatorNotEqualsSetSet)
{
    CategorySet<TraceCategory> set1 = TraceCategory::FunctionEnter | TraceCategory::FunctionLeave;
    CategorySet<TraceCategory> set2 = TraceCategory::FunctionEnter | TraceCategory::FunctionLeave;
    CategorySet<TraceCategory> set3 = TraceCategory::Information;
    EXPECT_FALSE(set1 != set2);
    EXPECT_TRUE(set1 != set3);
    EXPECT_TRUE(set2 != set3);
}

TEST(CategorySetTest, OperatorNotEqualsMaskTypeSet)
{
    CategorySet<TraceCategory> set1 = TraceCategory::FunctionEnter | TraceCategory::FunctionLeave;
    CategorySet<TraceCategory> set2 = TraceCategory::Information;
    uint32_t mask1 = static_cast<uint32_t>(TraceCategory::FunctionEnter) | static_cast<uint32_t>(TraceCategory::FunctionLeave);
    uint32_t mask2 = static_cast<uint32_t>(TraceCategory::Information);
    EXPECT_FALSE(set1 != mask1);
    EXPECT_TRUE(set1 != mask2);
    EXPECT_TRUE(set2 != mask1);
    EXPECT_FALSE(set2 != mask2);
}

TEST(CategorySetTest, OperatorNotEqualsSetMaskType)
{
    CategorySet<TraceCategory> set1 = TraceCategory::FunctionEnter | TraceCategory::FunctionLeave;
    CategorySet<TraceCategory> set2 = TraceCategory::Information;
    uint32_t mask1 = static_cast<uint32_t>(TraceCategory::FunctionEnter) | static_cast<uint32_t>(TraceCategory::FunctionLeave);
    uint32_t mask2 = static_cast<uint32_t>(TraceCategory::Information);
    EXPECT_FALSE(mask1 != set1);
    EXPECT_TRUE(mask1 != set2);
    EXPECT_TRUE(mask2 != set1);
    EXPECT_FALSE(mask2 != set2);
}

} // namespace tracing
