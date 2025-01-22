//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceCategoryTest.cpp
//
// Namespace   : tracing
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "tracing/TraceCategory.h"

#include "utility/Serialization.h"

namespace tracing {

TEST(TraceCategoryTest, Serialize)
{
    EXPECT_EQ("Cat80000000", serialization::Serialize(TraceCategory::Cat80000000));
    EXPECT_EQ("Cat40000000", serialization::Serialize(TraceCategory::Cat40000000));
    EXPECT_EQ("Cat20000000", serialization::Serialize(TraceCategory::Cat20000000));
    EXPECT_EQ("Cat10000000", serialization::Serialize(TraceCategory::Cat10000000));
    EXPECT_EQ("Cat08000000", serialization::Serialize(TraceCategory::Cat08000000));
    EXPECT_EQ("Cat04000000", serialization::Serialize(TraceCategory::Cat04000000));
    EXPECT_EQ("Cat02000000", serialization::Serialize(TraceCategory::Cat02000000));
    EXPECT_EQ("Cat01000000", serialization::Serialize(TraceCategory::Cat01000000));
    EXPECT_EQ("Cat00800000", serialization::Serialize(TraceCategory::Cat00800000));
    EXPECT_EQ("Cat00400000", serialization::Serialize(TraceCategory::Cat00400000));
    EXPECT_EQ("Cat00200000", serialization::Serialize(TraceCategory::Cat00200000));
    EXPECT_EQ("Cat00100000", serialization::Serialize(TraceCategory::Cat00100000));
    EXPECT_EQ("Cat00080000", serialization::Serialize(TraceCategory::Cat00080000));
    EXPECT_EQ("Cat00040000", serialization::Serialize(TraceCategory::Cat00040000));
    EXPECT_EQ("Cat00020000", serialization::Serialize(TraceCategory::Cat00020000));
    EXPECT_EQ("Cat00010000", serialization::Serialize(TraceCategory::Cat00010000));
    EXPECT_EQ("Cat00008000", serialization::Serialize(TraceCategory::Cat00008000));
    EXPECT_EQ("Cat00004000", serialization::Serialize(TraceCategory::Cat00004000));
    EXPECT_EQ("Cat00002000", serialization::Serialize(TraceCategory::Cat00002000));
    EXPECT_EQ("Cat00001000", serialization::Serialize(TraceCategory::Cat00001000));
    EXPECT_EQ("Cat00000800", serialization::Serialize(TraceCategory::Cat00000800));
    EXPECT_EQ("Cat00000400", serialization::Serialize(TraceCategory::Cat00000400));
    EXPECT_EQ("Cat00000200", serialization::Serialize(TraceCategory::Cat00000200));
    EXPECT_EQ("Cat00000100", serialization::Serialize(TraceCategory::Cat00000100));
    EXPECT_EQ("Cat00000080", serialization::Serialize(TraceCategory::Cat00000080));
    EXPECT_EQ("Enter",       serialization::Serialize(TraceCategory::FunctionEnter));
    EXPECT_EQ("Leave",       serialization::Serialize(TraceCategory::FunctionLeave));
    EXPECT_EQ("Debug",       serialization::Serialize(TraceCategory::Debug));
    EXPECT_EQ("Information", serialization::Serialize(TraceCategory::Information));
    EXPECT_EQ("Warning",     serialization::Serialize(TraceCategory::Warning));
    EXPECT_EQ("Error",       serialization::Serialize(TraceCategory::Error));
    EXPECT_EQ("Fatal",       serialization::Serialize(TraceCategory::Fatal));
}

TEST(TraceCategoryTest, EnumTraceCategories)
{
    std::vector<TraceCategory> expected = { 
        TraceCategory::Fatal,
        TraceCategory::Error,
        TraceCategory::Warning,
        TraceCategory::Information,
        TraceCategory::Debug,
        TraceCategory::FunctionLeave,
        TraceCategory::FunctionEnter,
        TraceCategory::Cat00000080,
        TraceCategory::Cat00000100,
        TraceCategory::Cat00000200,
        TraceCategory::Cat00000400,
        TraceCategory::Cat00000800,
        TraceCategory::Cat00001000,
        TraceCategory::Cat00002000,
        TraceCategory::Cat00004000,
        TraceCategory::Cat00008000,
        TraceCategory::Cat00010000,
        TraceCategory::Cat00020000,
        TraceCategory::Cat00040000,
        TraceCategory::Cat00080000,
        TraceCategory::Cat00100000,
        TraceCategory::Cat00200000,
        TraceCategory::Cat00400000,
        TraceCategory::Cat00800000,
        TraceCategory::Cat01000000,
        TraceCategory::Cat02000000,
        TraceCategory::Cat04000000,
        TraceCategory::Cat08000000,
        TraceCategory::Cat10000000,
        TraceCategory::Cat20000000,
        TraceCategory::Cat40000000,
        TraceCategory::Cat80000000,
    };
    EXPECT_EQ(expected, EnumTraceCategories());
}

} // namespace tracing
