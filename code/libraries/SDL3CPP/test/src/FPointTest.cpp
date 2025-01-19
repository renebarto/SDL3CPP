//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 René Barto
//
// File        : FPointTest.cpp
//
// Namespace   : SDL2
//
// Class       : -
//
// Description : 
//  Test for SDL2 FPoint class
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "SDL3CPP/FPoint.h"
#include "SDL3CPP/FRect.h"

namespace SDL3CPP {

TEST(FPointTest, ConstructDefault)
{
    FPoint point;

    EXPECT_EQ(0.0F, point.x);
    EXPECT_EQ(0.0F, point.y);
}

TEST(FPointTest, ConstructFromSDL_FPoint)
{
    FPoint point{SDL_FPoint{ 1.0F, 2.0F }};

    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
}

TEST(FPointTest, ConstructFromValues)
{
    FPoint point{ 1.0F, 2.0F };

    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
}

TEST(FPointTest, ConstructCopy)
{
    FPoint point{ 1.0F, 2.0F };
    FPoint target{ point };

    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, ConstructMove)
{
    FPoint point{ 1.0F, 2.0F };
    FPoint target{ std::move(point) };

    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, Assign)
{
    FPoint point{ 1.0F, 2.0F };
    FPoint target;
    
    target = point;

    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, AssignMove)
{
    FPoint point{ 1.0F, 2.0F };
    FPoint target;
    
    target = std::move(point);

    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, GetXY)
{
    FPoint point{ 1.0F, 2.0F };
    
    EXPECT_EQ(1.0F, point.GetX());
    EXPECT_EQ(2.0F, point.GetY());
}

TEST(FPointTest, SetXY)
{
    FPoint point;
    
    EXPECT_EQ(0.0F, point.GetX());
    EXPECT_EQ(0.0F, point.GetY());
    point.SetX(1.0F);
    point.SetY(2.0F);
    EXPECT_EQ(1.0F, point.GetX());
    EXPECT_EQ(2.0F, point.GetY());
}

TEST(FPointTest, Negation)
{
    FPoint point{ 1.0F, 2.0F };
    FPoint target = -point;
    
    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(-1.0F, target.x);
    EXPECT_EQ(-2.0F, target.y);
}

TEST(FPointTest, Addition)
{
    FPoint point1{ 1.0F, 2.0F };
    FPoint point2{ 3.0F, 4.0F };
    FPoint target = point1 + point2;
    
    EXPECT_EQ(1.0F, point1.x);
    EXPECT_EQ(2.0F, point1.y);
    EXPECT_EQ(3.0F, point2.x);
    EXPECT_EQ(4.0F, point2.y);
    EXPECT_EQ(4.0F, target.x);
    EXPECT_EQ(6.0F, target.y);
}

TEST(FPointTest, Subtraction)
{
    FPoint point1{ 1.0F, 2.0F };
    FPoint point2{ 3.0F, 4.0F };
    FPoint target = point2 - point1;
    
    EXPECT_EQ(1.0F, point1.x);
    EXPECT_EQ(2.0F, point1.y);
    EXPECT_EQ(3.0F, point2.x);
    EXPECT_EQ(4.0F, point2.y);
    EXPECT_EQ(2.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, DivisionByValue)
{
    FPoint point{ 50.0F, 101.0F };
    FPoint target = point / 2.0F;
    
    EXPECT_EQ(50.0F, point.x);
    EXPECT_EQ(101.0F, point.y);
    EXPECT_EQ(25.0F, target.x);
    EXPECT_EQ(50.5F, target.y);
}

TEST(FPointTest, Division)
{
    FPoint point1{ 1.0F, 2.0F };
    FPoint point2{ 3.0F, 4.0F };
    FPoint target = point2 / point1;
    
    EXPECT_EQ(1.0F, point1.x);
    EXPECT_EQ(2.0F, point1.y);
    EXPECT_EQ(3.0F, point2.x);
    EXPECT_EQ(4.0F, point2.y);
    EXPECT_EQ(3.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, RemainderByValue)
{
    FPoint point{ 50.0F, 101.0F };
    FPoint target = point % 2.0F;
    
    EXPECT_EQ(50.0F, point.x);
    EXPECT_EQ(101.0F, point.y);
    EXPECT_EQ(0.0F, target.x);
    EXPECT_EQ(1.0F, target.y);
}

TEST(FPointTest, Remainder)
{
    FPoint point1{ 2.0F, 4.0F };
    FPoint point2{ 50.0F, 101.0F };
    FPoint target = point2 % point1;
    
    EXPECT_EQ(2.0F, point1.x);
    EXPECT_EQ(4.0F, point1.y);
    EXPECT_EQ(50.0F, point2.x);
    EXPECT_EQ(101.0F, point2.y);
    EXPECT_EQ(0.0F, target.x);
    EXPECT_EQ(1.0F, target.y);
}

TEST(FPointTest, MultiplicationByValue)
{
    FPoint point{ 10.0F, 25.0F };
    FPoint target = point * 2.0F;
    
    EXPECT_EQ(10.0F, point.x);
    EXPECT_EQ(25.0F, point.y);
    EXPECT_EQ(20.0F, target.x);
    EXPECT_EQ(50.0F, target.y);
}

TEST(FPointTest, Multiplication)
{
    FPoint point1{ 1.0F, 2.0F };
    FPoint point2{ 3.0F, 4.0F };
    FPoint target = point2 * point1;
    
    EXPECT_EQ(1.0F, point1.x);
    EXPECT_EQ(2.0F, point1.y);
    EXPECT_EQ(3.0F, point2.x);
    EXPECT_EQ(4.0F, point2.y);
    EXPECT_EQ(3.0F, target.x);
    EXPECT_EQ(8.0F, target.y);
}

TEST(FPointTest, AdditionAssignment)
{
    FPoint point{ 1.0F, 2.0F };
    FPoint target{ 3.0F, 4.0F };
    target += point;
    
    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(4.0F, target.x);
    EXPECT_EQ(6.0F, target.y);
}

TEST(FPointTest, SubtractionAssignment)
{
    FPoint point{ 1.0F, 2.0F };
    FPoint target{ 3.0F, 4.0F };
    target -= point;
    
    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(2.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, DivisionAssignmentByValue)
{
    FPoint target{ 50.0F, 101.0F };
    target /= 2.0F;
    
    EXPECT_EQ(25.0F, target.x);
    EXPECT_EQ(50.5F, target.y);
}

TEST(FPointTest, DivisionAssignment)
{
    FPoint point{ 1.0F, 2.0F };
    FPoint target{ 3.0F, 4.0F };
    target /= point;
    
    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(3.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, RemainderAssignmentByValue)
{
    FPoint target{ 50.0F, 101.0F };
    target %= 2.0F;
    
    EXPECT_EQ(0.0F, target.x);
    EXPECT_EQ(1.0F, target.y);
}

TEST(FPointTest, RemainderAssignment)
{
    FPoint point{ 2.0F, 4.0F };
    FPoint target{ 50.0F, 101.0F };
    target %= point;
    
    EXPECT_EQ(2.0F, point.x);
    EXPECT_EQ(4.0F, point.y);
    EXPECT_EQ(0.0F, target.x);
    EXPECT_EQ(1.0F, target.y);
}

TEST(FPointTest, MultiplicationAssignmentByValue)
{
    FPoint target{ 10.0F, 25.0F };
    target *= 2.0F;
    
    EXPECT_EQ(20.0F, target.x);
    EXPECT_EQ(50.0F, target.y);
}

TEST(FPointTest, MultiplicationAssignment)
{
    FPoint point{ 1.0F, 2.0F };
    FPoint target{ 3.0F, 4.0F };
    target *= point;
    
    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(3.0F, target.x);
    EXPECT_EQ(8.0F, target.y);
}

TEST(FPointTest, GetClampedInside)
{
    FRect rect{ 0.0F, 0.0F, 10.0F, 10.0F };
    FPoint point{ 1.0F, 2.0F };
    FPoint target{ point.GetClamped(rect) };
    
    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, GetClampedOutside)
{
    FRect rect{ 0.0F, 0.0F, 10.0F, 10.0F };
    FPoint point{ 11.0F, 12.0F };
    FPoint target{ point.GetClamped(rect) };
    
    EXPECT_EQ(11.0F, point.x);
    EXPECT_EQ(12.0F, point.y);
    EXPECT_EQ(9.0F, target.x);
    EXPECT_EQ(9.0F, target.y);
}

TEST(FPointTest, ClampInside)
{
    FRect rect{ 0.0F, 0.0F, 10.0F, 10.0F };
    FPoint point{ 1.0F, 2.0F };
    FPoint target = point.Clamp(rect);
    
    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, ClampOutside)
{
    FRect rect{ 0.0F, 0.0F, 10.0F, 10.0F };
    FPoint point{ 11.0F, 12.0F };
    FPoint target = point.Clamp(rect);
    
    EXPECT_EQ(9.0F, point.x);
    EXPECT_EQ(9.0F, point.y);
    EXPECT_EQ(9.0F, target.x);
    EXPECT_EQ(9.0F, target.y);
}

TEST(FPointTest, GetWrappedInside)
{
    FRect rect{ 0.0F, 0.0F, 10.0F, 10.0F };
    FPoint point{ 1.0F, 2.0F };
    FPoint target{ point.GetWrapped(rect) };
    
    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, GetWrappedOutside)
{
    FRect rect{ 0.0F, 0.0F, 10.0F, 10.0F };
    FPoint point{ 11.0F, 12.0F };
    FPoint target{ point.GetWrapped(rect) };
    
    EXPECT_EQ(11.0F, point.x);
    EXPECT_EQ(12.0F, point.y);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, WrapInside)
{
    FRect rect{ 0.0F, 0.0F, 10.0F, 10.0F };
    FPoint point{ 1.0F, 2.0F };
    FPoint target = point.Wrap(rect);
    
    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, WrapOutside)
{
    FRect rect{ 0.0F, 0.0F, 10.0F, 10.0F };
    FPoint point{ 11.0F, 12.0F };
    FPoint target = point.Wrap(rect);
    
    EXPECT_EQ(1.0F, point.x);
    EXPECT_EQ(2.0F, point.y);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
}

TEST(FPointTest, ComparisonEqual)
{
    FPoint point{ 11.0F, 12.0F };
    FPoint point1;
    FPoint point2{ 1.0F, 2.0F };
    FPoint point3{ 11.0F, 12.0F };
    
    EXPECT_TRUE(point == point);
    EXPECT_FALSE(point == point1);
    EXPECT_FALSE(point == point2);
    EXPECT_TRUE(point == point3);
}

TEST(FPointTest, ComparisonNotEqual)
{
    FPoint point{ 11.0F, 12.0F };
    FPoint point1;
    FPoint point2{ 1.0F, 2.0F };
    FPoint point3{ 11.0F, 12.0F };
    
    EXPECT_FALSE(point != point);
    EXPECT_TRUE(point != point1);
    EXPECT_TRUE(point != point2);
    EXPECT_FALSE(point != point3);
}

TEST(FPointTest, StreamInsertion)
{
    FPoint point{ 1.0F, 2.0F };
    std::string expected{ "[x:1,y:2]" };
    std::ostringstream stream;
    stream << point;
    EXPECT_EQ(expected, stream.str());
}

TEST(FPointTest, Hash)
{
    FPoint point{ 11.0F, 12.0F };
    FPoint point1;
    FPoint point2{ 1.0F, 2.0F };
    FPoint point3{ 11.0F, 12.0F };
    
    EXPECT_TRUE(std::hash<FPoint>{}(point) == std::hash<FPoint>{}(point));
    EXPECT_FALSE(std::hash<FPoint>{}(point) == std::hash<FPoint>{}(point1));
    EXPECT_FALSE(std::hash<FPoint>{}(point) == std::hash<FPoint>{}(point2));
    EXPECT_TRUE(std::hash<FPoint>{}(point) == std::hash<FPoint>{}(point3));
}

} // namespace SDL3CPP
