//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 René Barto
//
// File        : SizeTest.cpp
//
// Namespace   : SDL3CPP
//
// Class       : -
//
// Description : 
//  Test for SDL3CPP Size class
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "SDL3CPP/Size.h"
#include "SDL3CPP/Rect.h"

namespace SDL3CPP {

TEST(SizeTest, ConstructDefault)
{
    Size size;

    EXPECT_EQ(0, size.x);
    EXPECT_EQ(0, size.y);
    EXPECT_EQ(0, size.GetWidth());
    EXPECT_EQ(0, size.GetHeight());
}

TEST(SizeTest, ConstructFromSDL_Point)
{
    Size size{SDL_Point{ 1, 2 }};

    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(1, size.GetWidth());
    EXPECT_EQ(2, size.GetHeight());
}

TEST(SizeTest, ConstructFromValues)
{
    Size size{ 1, 2 };

    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(1, size.GetWidth());
    EXPECT_EQ(2, size.GetHeight());
}

TEST(SizeTest, ConstructCopy)
{
    Size size{ 1, 2 };
    Size target{ size };

    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
    EXPECT_EQ(1, target.GetWidth());
    EXPECT_EQ(2, target.GetHeight());
}

TEST(SizeTest, ConstructMove)
{
    Size size{ 1, 2 };
    Size target{ std::move(size) };

    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
    EXPECT_EQ(1, target.GetWidth());
    EXPECT_EQ(2, target.GetHeight());
}

TEST(SizeTest, Assign)
{
    Size size{ 1, 2 };
    Size target;
    
    target = size;

    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
    EXPECT_EQ(1, target.GetWidth());
    EXPECT_EQ(2, target.GetHeight());
}

TEST(SizeTest, AssignMove)
{
    Size size{ 1, 2 };
    Size target;
    
    target = std::move(size);

    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
    EXPECT_EQ(1, target.GetWidth());
    EXPECT_EQ(2, target.GetHeight());
}

TEST(SizeTest, GetWidthY)
{
    Size size{ 1, 2 };
    
    EXPECT_EQ(1, size.GetWidth());
    EXPECT_EQ(2, size.GetHeight());
}

TEST(SizeTest, SetWidthY)
{
    Size size;
    
    EXPECT_EQ(0, size.GetWidth());
    EXPECT_EQ(0, size.GetHeight());
    size.SetWidth(1);
    size.SetHeight(2);
    EXPECT_EQ(1, size.GetWidth());
    EXPECT_EQ(2, size.GetHeight());
}

TEST(SizeTest, Negation)
{
    Size size{ 1, 2 };
    Size target = -size;
    
    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(-1, target.x);
    EXPECT_EQ(-2, target.y);
}

TEST(SizeTest, Addition)
{
    Size size1{ 1, 2 };
    Size size2{ 3, 4 };
    Size target = size1 + size2;
    
    EXPECT_EQ(1, size1.x);
    EXPECT_EQ(2, size1.y);
    EXPECT_EQ(3, size2.x);
    EXPECT_EQ(4, size2.y);
    EXPECT_EQ(4, target.x);
    EXPECT_EQ(6, target.y);
}

TEST(SizeTest, Subtraction)
{
    Size size1{ 1, 2 };
    Size size2{ 3, 4 };
    Size target = size2 - size1;
    
    EXPECT_EQ(1, size1.x);
    EXPECT_EQ(2, size1.y);
    EXPECT_EQ(3, size2.x);
    EXPECT_EQ(4, size2.y);
    EXPECT_EQ(2, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(SizeTest, DivisionByValue)
{
    Size size{ 50, 101 };
    Size target = size / 2;
    
    EXPECT_EQ(50, size.x);
    EXPECT_EQ(101, size.y);
    EXPECT_EQ(25, target.x);
    EXPECT_EQ(50, target.y);
}

TEST(SizeTest, Division)
{
    Size size1{ 1, 2 };
    Size size2{ 3, 4 };
    Size target = size2 / size1;
    
    EXPECT_EQ(1, size1.x);
    EXPECT_EQ(2, size1.y);
    EXPECT_EQ(3, size2.x);
    EXPECT_EQ(4, size2.y);
    EXPECT_EQ(3, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(SizeTest, RemainderByValue)
{
    Size size{ 50, 101 };
    Size target = size % 2;
    
    EXPECT_EQ(50, size.x);
    EXPECT_EQ(101, size.y);
    EXPECT_EQ(0, target.x);
    EXPECT_EQ(1, target.y);
}

TEST(SizeTest, Remainder)
{
    Size size1{ 2, 4 };
    Size size2{ 50, 101 };
    Size target = size2 % size1;
    
    EXPECT_EQ(2, size1.x);
    EXPECT_EQ(4, size1.y);
    EXPECT_EQ(50, size2.x);
    EXPECT_EQ(101, size2.y);
    EXPECT_EQ(0, target.x);
    EXPECT_EQ(1, target.y);
}

TEST(SizeTest, MultiplicationByValue)
{
    Size size{ 10, 25 };
    Size target = size * 2;
    
    EXPECT_EQ(10, size.x);
    EXPECT_EQ(25, size.y);
    EXPECT_EQ(20, target.x);
    EXPECT_EQ(50, target.y);
}

TEST(SizeTest, Multiplication)
{
    Size size1{ 1, 2 };
    Size size2{ 3, 4 };
    Size target = size2 * size1;
    
    EXPECT_EQ(1, size1.x);
    EXPECT_EQ(2, size1.y);
    EXPECT_EQ(3, size2.x);
    EXPECT_EQ(4, size2.y);
    EXPECT_EQ(3, target.x);
    EXPECT_EQ(8, target.y);
}

TEST(SizeTest, AdditionAssignment)
{
    Size size{ 1, 2 };
    Size target{ 3, 4 };
    target += size;
    
    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(4, target.x);
    EXPECT_EQ(6, target.y);
}

TEST(SizeTest, SubtractionAssignment)
{
    Size size{ 1, 2 };
    Size target{ 3, 4 };
    target -= size;
    
    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(2, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(SizeTest, DivisionAssignmentByValue)
{
    Size target{ 50, 101 };
    target /= 2;
    
    EXPECT_EQ(25, target.x);
    EXPECT_EQ(50, target.y);
}

TEST(SizeTest, DivisionAssignment)
{
    Size size{ 1, 2 };
    Size target{ 3, 4 };
    target /= size;
    
    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(3, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(SizeTest, RemainderAssignmentByValue)
{
    Size target{ 50, 101 };
    target %= 2;
    
    EXPECT_EQ(0, target.x);
    EXPECT_EQ(1, target.y);
}

TEST(SizeTest, RemainderAssignment)
{
    Size size{ 2, 4 };
    Size target{ 50, 101 };
    target %= size;
    
    EXPECT_EQ(2, size.x);
    EXPECT_EQ(4, size.y);
    EXPECT_EQ(0, target.x);
    EXPECT_EQ(1, target.y);
}

TEST(SizeTest, MultiplicationAssignmentByValue)
{
    Size target{ 10, 25 };
    target *= 2;
    
    EXPECT_EQ(20, target.x);
    EXPECT_EQ(50, target.y);
}

TEST(SizeTest, MultiplicationAssignment)
{
    Size size{ 1, 2 };
    Size target{ 3, 4 };
    target *= size;
    
    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(3, target.x);
    EXPECT_EQ(8, target.y);
}

TEST(SizeTest, GetClampedInside)
{
    Rect rect{ 0, 0, 10, 10 };
    Size size{ 1, 2 };
    Size target{ size.GetClamped(rect) };
    
    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(SizeTest, GetClampedOutside)
{
    Rect rect{ 0, 0, 10, 10 };
    Size size{ 11, 12 };
    Size target{ size.GetClamped(rect) };
    
    EXPECT_EQ(11, size.x);
    EXPECT_EQ(12, size.y);
    EXPECT_EQ(10, target.x);
    EXPECT_EQ(10, target.y);
}

TEST(SizeTest, ClampInside)
{
    Rect rect{ 0, 0, 10, 10 };
    Size size{ 1, 2 };
    Size target = size.Clamp(rect);
    
    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(SizeTest, ClampOutside)
{
    Rect rect{ 0, 0, 10, 10 };
    Size size{ 11, 12 };
    Size target = size.Clamp(rect);
    
    EXPECT_EQ(10, size.x);
    EXPECT_EQ(10, size.y);
    EXPECT_EQ(10, target.x);
    EXPECT_EQ(10, target.y);
}

TEST(SizeTest, GetWrappedInside)
{
    Rect rect{ 0, 0, 10, 10 };
    Size size{ 1, 2 };
    Size target{ size.GetWrapped(rect) };
    
    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(SizeTest, GetWrappedOutside)
{
    Rect rect{ 0, 0, 10, 10 };
    Size size{ 11, 12 };
    Size target{ size.GetWrapped(rect) };
    
    EXPECT_EQ(11, size.x);
    EXPECT_EQ(12, size.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(SizeTest, WrapInside)
{
    Rect rect{ 0, 0, 10, 10 };
    Size size{ 1, 2 };
    Size target = size.Wrap(rect);
    
    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(SizeTest, WrapOutside)
{
    Rect rect{ 0, 0, 10, 10 };
    Size size{ 11, 12 };
    Size target = size.Wrap(rect);
    
    EXPECT_EQ(1, size.x);
    EXPECT_EQ(2, size.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(SizeTest, ComparisonEqual)
{
    Size size{ 11, 12 };
    Size size1;
    Size size2{ 1, 2 };
    Size size3{ 11, 12 };
    
    EXPECT_TRUE(size == size);
    EXPECT_FALSE(size == size1);
    EXPECT_FALSE(size == size2);
    EXPECT_TRUE(size == size3);
}

TEST(SizeTest, ComparisonNotEqual)
{
    Size size{ 11, 12 };
    Size size1;
    Size size2{ 1, 2 };
    Size size3{ 11, 12 };
    
    EXPECT_FALSE(size != size);
    EXPECT_TRUE(size != size1);
    EXPECT_TRUE(size != size2);
    EXPECT_FALSE(size != size3);
}

TEST(SizeTest, StreamInsertion)
{
    Size size{ 1, 2 };
    std::string expected{ "[w:1,h:2]" };
    std::ostringstream stream;
    stream << size;
    EXPECT_EQ(expected, stream.str());
}

TEST(SizeTest, Hash)
{
    Size size{ 11, 12 };
    Size size1;
    Size size2{ 1, 2 };
    Size size3{ 11, 12 };
    
    EXPECT_TRUE(std::hash<Size>{}(size) == std::hash<Size>{}(size));
    EXPECT_FALSE(std::hash<Size>{}(size) == std::hash<Size>{}(size1));
    EXPECT_FALSE(std::hash<Size>{}(size) == std::hash<Size>{}(size2));
    EXPECT_TRUE(std::hash<Size>{}(size) == std::hash<Size>{}(size3));
}

} // namespace SDL3CPP
