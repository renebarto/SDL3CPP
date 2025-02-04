//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 René Barto
//
// File        : PointTest.cpp
//
// Namespace   : SDL3CPP
//
// Class       : -
//
// Description : 
//  Test for SDL3CPP Point class
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "SDL3CPP/Point.h"
#include "SDL3CPP/Rect.h"

namespace SDL3CPP {

TEST(PointTest, ConstructDefault)
{
    Point point;

    EXPECT_EQ(0, point.x);
    EXPECT_EQ(0, point.y);
}

TEST(PointTest, ConstructFromSDL_Point)
{
    Point point{SDL_Point{ 1, 2 }};

    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
}

TEST(PointTest, ConstructFromValues)
{
    Point point{ 1, 2 };

    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
}

TEST(PointTest, ConstructCopy)
{
    Point point{ 1, 2 };
    Point target{ point };

    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, ConstructMove)
{
    Point point{ 1, 2 };
    Point target{ std::move(point) };

    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, Assign)
{
    Point point{ 1, 2 };
    Point target;
    
    target = point;

    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, AssignMove)
{
    Point point{ 1, 2 };
    Point target;
    
    target = std::move(point);

    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, GetXY)
{
    Point point{ 1, 2 };
    
    EXPECT_EQ(1, point.GetX());
    EXPECT_EQ(2, point.GetY());
}

TEST(PointTest, SetXY)
{
    Point point;
    
    EXPECT_EQ(0, point.GetX());
    EXPECT_EQ(0, point.GetY());
    point.SetX(1);
    point.SetY(2);
    EXPECT_EQ(1, point.GetX());
    EXPECT_EQ(2, point.GetY());
}

TEST(PointTest, Negation)
{
    Point point{ 1, 2 };
    Point target = -point;
    
    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(-1, target.x);
    EXPECT_EQ(-2, target.y);
}

TEST(PointTest, Addition)
{
    Point point1{ 1, 2 };
    Point point2{ 3, 4 };
    Point target = point1 + point2;
    
    EXPECT_EQ(1, point1.x);
    EXPECT_EQ(2, point1.y);
    EXPECT_EQ(3, point2.x);
    EXPECT_EQ(4, point2.y);
    EXPECT_EQ(4, target.x);
    EXPECT_EQ(6, target.y);
}

TEST(PointTest, Subtraction)
{
    Point point1{ 1, 2 };
    Point point2{ 3, 4 };
    Point target = point2 - point1;
    
    EXPECT_EQ(1, point1.x);
    EXPECT_EQ(2, point1.y);
    EXPECT_EQ(3, point2.x);
    EXPECT_EQ(4, point2.y);
    EXPECT_EQ(2, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, DivisionByValue)
{
    Point point{ 50, 101 };
    Point target = point / 2;
    
    EXPECT_EQ(50, point.x);
    EXPECT_EQ(101, point.y);
    EXPECT_EQ(25, target.x);
    EXPECT_EQ(50, target.y);
}

TEST(PointTest, Division)
{
    Point point1{ 1, 2 };
    Point point2{ 3, 4 };
    Point target = point2 / point1;
    
    EXPECT_EQ(1, point1.x);
    EXPECT_EQ(2, point1.y);
    EXPECT_EQ(3, point2.x);
    EXPECT_EQ(4, point2.y);
    EXPECT_EQ(3, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, RemainderByValue)
{
    Point point{ 50, 101 };
    Point target = point % 2;
    
    EXPECT_EQ(50, point.x);
    EXPECT_EQ(101, point.y);
    EXPECT_EQ(0, target.x);
    EXPECT_EQ(1, target.y);
}

TEST(PointTest, Remainder)
{
    Point point1{ 2, 4 };
    Point point2{ 50, 101 };
    Point target = point2 % point1;
    
    EXPECT_EQ(2, point1.x);
    EXPECT_EQ(4, point1.y);
    EXPECT_EQ(50, point2.x);
    EXPECT_EQ(101, point2.y);
    EXPECT_EQ(0, target.x);
    EXPECT_EQ(1, target.y);
}

TEST(PointTest, MultiplicationByValue)
{
    Point point{ 10, 25 };
    Point target = point * 2;
    
    EXPECT_EQ(10, point.x);
    EXPECT_EQ(25, point.y);
    EXPECT_EQ(20, target.x);
    EXPECT_EQ(50, target.y);
}

TEST(PointTest, Multiplication)
{
    Point point1{ 1, 2 };
    Point point2{ 3, 4 };
    Point target = point2 * point1;
    
    EXPECT_EQ(1, point1.x);
    EXPECT_EQ(2, point1.y);
    EXPECT_EQ(3, point2.x);
    EXPECT_EQ(4, point2.y);
    EXPECT_EQ(3, target.x);
    EXPECT_EQ(8, target.y);
}

TEST(PointTest, AdditionAssignment)
{
    Point point{ 1, 2 };
    Point target{ 3, 4 };
    target += point;
    
    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(4, target.x);
    EXPECT_EQ(6, target.y);
}

TEST(PointTest, SubtractionAssignment)
{
    Point point{ 1, 2 };
    Point target{ 3, 4 };
    target -= point;
    
    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(2, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, DivisionAssignmentByValue)
{
    Point target{ 50, 101 };
    target /= 2;
    
    EXPECT_EQ(25, target.x);
    EXPECT_EQ(50, target.y);
}

TEST(PointTest, DivisionAssignment)
{
    Point point{ 1, 2 };
    Point target{ 3, 4 };
    target /= point;
    
    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(3, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, RemainderAssignmentByValue)
{
    Point target{ 50, 101 };
    target %= 2;
    
    EXPECT_EQ(0, target.x);
    EXPECT_EQ(1, target.y);
}

TEST(PointTest, RemainderAssignment)
{
    Point point{ 2, 4 };
    Point target{ 50, 101 };
    target %= point;
    
    EXPECT_EQ(2, point.x);
    EXPECT_EQ(4, point.y);
    EXPECT_EQ(0, target.x);
    EXPECT_EQ(1, target.y);
}

TEST(PointTest, MultiplicationAssignmentByValue)
{
    Point target{ 10, 25 };
    target *= 2;
    
    EXPECT_EQ(20, target.x);
    EXPECT_EQ(50, target.y);
}

TEST(PointTest, MultiplicationAssignment)
{
    Point point{ 1, 2 };
    Point target{ 3, 4 };
    target *= point;
    
    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(3, target.x);
    EXPECT_EQ(8, target.y);
}

TEST(PointTest, GetClampedInside)
{
    Rect rect{ 0, 0, 10, 10 };
    Point point{ 1, 2 };
    Point target{ point.GetClamped(rect) };
    
    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, GetClampedOutside)
{
    Rect rect{ 0, 0, 10, 10 };
    Point point{ 11, 12 };
    Point target{ point.GetClamped(rect) };
    
    EXPECT_EQ(11, point.x);
    EXPECT_EQ(12, point.y);
    EXPECT_EQ(9, target.x);
    EXPECT_EQ(9, target.y);
}

TEST(PointTest, ClampInside)
{
    Rect rect{ 0, 0, 10, 10 };
    Point point{ 1, 2 };
    Point target = point.Clamp(rect);
    
    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, ClampOutside)
{
    Rect rect{ 0, 0, 10, 10 };
    Point point{ 11, 12 };
    Point target = point.Clamp(rect);
    
    EXPECT_EQ(9, point.x);
    EXPECT_EQ(9, point.y);
    EXPECT_EQ(9, target.x);
    EXPECT_EQ(9, target.y);
}

TEST(PointTest, GetWrappedInside)
{
    Rect rect{ 0, 0, 10, 10 };
    Point point{ 1, 2 };
    Point target{ point.GetWrapped(rect) };
    
    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, GetWrappedOutside)
{
    Rect rect{ 0, 0, 10, 10 };
    Point point{ 11, 12 };
    Point target{ point.GetWrapped(rect) };
    
    EXPECT_EQ(11, point.x);
    EXPECT_EQ(12, point.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, WrapInside)
{
    Rect rect{ 0, 0, 10, 10 };
    Point point{ 1, 2 };
    Point target = point.Wrap(rect);
    
    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, WrapOutside)
{
    Rect rect{ 0, 0, 10, 10 };
    Point point{ 11, 12 };
    Point target = point.Wrap(rect);
    
    EXPECT_EQ(1, point.x);
    EXPECT_EQ(2, point.y);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
}

TEST(PointTest, ComparisonEqual)
{
    Point point{ 11, 12 };
    Point point1;
    Point point2{ 1, 2 };
    Point point3{ 11, 12 };
    
    EXPECT_TRUE(point == point);
    EXPECT_FALSE(point == point1);
    EXPECT_FALSE(point == point2);
    EXPECT_TRUE(point == point3);
}

TEST(PointTest, ComparisonNotEqual)
{
    Point point{ 11, 12 };
    Point point1;
    Point point2{ 1, 2 };
    Point point3{ 11, 12 };
    
    EXPECT_FALSE(point != point);
    EXPECT_TRUE(point != point1);
    EXPECT_TRUE(point != point2);
    EXPECT_FALSE(point != point3);
}

TEST(PointTest, StreamInsertion)
{
    Point point{ 1, 2 };
    std::string expected{ "[x:1,y:2]" };
    std::ostringstream stream;
    stream << point;
    EXPECT_EQ(expected, stream.str());
}

TEST(PointTest, Hash)
{
    Point point{ 11, 12 };
    Point point1;
    Point point2{ 1, 2 };
    Point point3{ 11, 12 };
    
    EXPECT_TRUE(std::hash<Point>{}(point) == std::hash<Point>{}(point));
    EXPECT_FALSE(std::hash<Point>{}(point) == std::hash<Point>{}(point1));
    EXPECT_FALSE(std::hash<Point>{}(point) == std::hash<Point>{}(point2));
    EXPECT_TRUE(std::hash<Point>{}(point) == std::hash<Point>{}(point3));
}

} // namespace SDL3CPP
