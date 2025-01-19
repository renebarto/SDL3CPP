//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 René Barto
//
// File        : OptionalTest.cpp
//
// Namespace   : SDL2
//
// Class       : -
//
// Description : 
//  Test for SDL2 Optional template
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "SDL3CPP/Optional.h"
#include "SDL3CPP/Point.h"

namespace SDL3CPP {

TEST(OptionalTest, Default)
{
    Optional<Point> optional{};

    EXPECT_FALSE(optional.has_value());
    EXPECT_FALSE(optional.operator bool());
#ifdef PLATFORM_WINDOWS
#pragma warning(disable: 4834)
#endif
    EXPECT_THROW(optional.value(), std::bad_optional_access);
#ifdef PLATFORM_WINDOWS
#pragma warning(default: 4834)
#endif
}

TEST(OptionalTest, NullOpt)
{
    Optional<Point> optional{ NullOpt };

    EXPECT_FALSE(optional.has_value());
    EXPECT_FALSE(optional.operator bool());
#ifdef PLATFORM_WINDOWS
#pragma warning(disable: 4834)
#endif
    EXPECT_THROW(optional.value(), std::bad_optional_access);
#ifdef PLATFORM_WINDOWS
#pragma warning(default: 4834)
#endif
}

TEST(OptionalTest, Value)
{
    Optional<Point> optional{ Point{1, 2} };
    Point expected{1, 2};

    EXPECT_TRUE(optional.has_value());
    EXPECT_TRUE(optional.operator bool());
    EXPECT_EQ(expected, optional.value());
}

TEST(OptionalTest, StreamInsertionNull)
{
    Optional<Point> optional{ NullOpt };
    std::string expected{ "null" };
    std::ostringstream stream;
    stream << optional;
    EXPECT_EQ(expected, stream.str());
}

TEST(OptionalTest, StreamInsertionValue)
{
    Optional<Point> optional{ Point{ 1, 2} };
    std::string expected{ "[x:1,y:2]" };
    std::ostringstream stream;
    stream << optional;
    EXPECT_EQ(expected, stream.str());
}

} // namespace SDL3CPP
