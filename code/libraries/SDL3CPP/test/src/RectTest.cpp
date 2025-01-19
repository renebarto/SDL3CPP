//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 René Barto
//
// File        : RectTest.cpp
//
// Namespace   : SDL2
//
// Class       : -
//
// Description : 
//  Test for SDL2 Rect class
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "SDL3CPP/Rect.h"

namespace SDL3CPP {

TEST(RectTest, ConstructDefault)
{
    Rect rect;

    EXPECT_EQ(0, rect.x);
    EXPECT_EQ(0, rect.y);
    EXPECT_EQ(0, rect.w);
    EXPECT_EQ(0, rect.h);
}

TEST(RectTest, ConstructFromSDL_Rect)
{
    Rect rect{SDL_Rect{ 1, 2, 3, 4 }};

    EXPECT_EQ(1, rect.x);
    EXPECT_EQ(2, rect.y);
    EXPECT_EQ(3, rect.w);
    EXPECT_EQ(4, rect.h);
}

TEST(RectTest, ConstructFromPoints)
{
    Point topLeft{ 1, 2 };
    Point size {3, 4};
    Rect rect{ topLeft, size };

    EXPECT_EQ(1, rect.x);
    EXPECT_EQ(2, rect.y);
    EXPECT_EQ(3, rect.w);
    EXPECT_EQ(4, rect.h);
}

TEST(RectTest, ConstructFromValues)
{
    Rect rect{ 1, 2, 3, 4 };

    EXPECT_EQ(1, rect.x);
    EXPECT_EQ(2, rect.y);
    EXPECT_EQ(3, rect.w);
    EXPECT_EQ(4, rect.h);
}

TEST(RectTest, ConstructCopy)
{
    Rect rect{ 1, 2, 3, 4 };
    Rect target{ rect };

    EXPECT_EQ(1, rect.x);
    EXPECT_EQ(2, rect.y);
    EXPECT_EQ(3, rect.w);
    EXPECT_EQ(4, rect.h);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
    EXPECT_EQ(3, target.w);
    EXPECT_EQ(4, target.h);
}

TEST(RectTest, ConstructMove)
{
    Rect rect{ 1, 2, 3, 4 };
    Rect target{ std::move(rect) };

    EXPECT_EQ(1, rect.x);
    EXPECT_EQ(2, rect.y);
    EXPECT_EQ(3, rect.w);
    EXPECT_EQ(4, rect.h);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
    EXPECT_EQ(3, target.w);
    EXPECT_EQ(4, target.h);
}

TEST(RectTest, FromCenterValues)
{
    Rect rect{ Rect::FromCenter(5, 5, 3, 4) };

    EXPECT_EQ(4, rect.x); // 5 - 3/2
    EXPECT_EQ(3, rect.y); // 5 - 4/2
    EXPECT_EQ(3, rect.w);
    EXPECT_EQ(4, rect.h);
}

TEST(RectTest, FromCenterPoints)
{
    Point topLeft{ 5, 5 };
    Point size {3, 4};
    Rect rect{ Rect::FromCenter(topLeft, size) };

    EXPECT_EQ(4, rect.x); // 5 - 3/2
    EXPECT_EQ(3, rect.y); // 5 - 4/2
    EXPECT_EQ(3, rect.w);
    EXPECT_EQ(4, rect.h);
}

TEST(RectTest, FromCornersValues)
{
    Rect rect{ Rect::FromCorners(1, 2, 3, 4) };

    EXPECT_EQ(1, rect.x);
    EXPECT_EQ(2, rect.y);
    EXPECT_EQ(3, rect.w); // 3 - 1 + 1
    EXPECT_EQ(3, rect.h); // 4 - 2 + 1
}

TEST(RectTest, FromCornersPoints)
{
    Point topLeft{ 1, 2 };
    Point bottomRight {3, 4};
    Rect rect{ Rect::FromCorners(topLeft, bottomRight) };

    EXPECT_EQ(1, rect.x);
    EXPECT_EQ(2, rect.y);
    EXPECT_EQ(3, rect.w); // 3 - 1 + 1
    EXPECT_EQ(3, rect.h); // 4 - 2 + 1
}

TEST(RectTest, Assign)
{
    Rect rect{ 1, 2, 3, 4 };
    Rect target;
    
    target = rect;

    EXPECT_EQ(1, rect.x);
    EXPECT_EQ(2, rect.y);
    EXPECT_EQ(3, rect.w);
    EXPECT_EQ(4, rect.h);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
    EXPECT_EQ(3, target.w);
    EXPECT_EQ(4, target.h);
}

TEST(RectTest, AssignMove)
{
    Rect rect{ 1, 2, 3, 4 };
    Rect target;
    
    target = std::move(rect);

    EXPECT_EQ(1, rect.x);
    EXPECT_EQ(2, rect.y);
    EXPECT_EQ(3, rect.w);
    EXPECT_EQ(4, rect.h);
    EXPECT_EQ(1, target.x);
    EXPECT_EQ(2, target.y);
    EXPECT_EQ(3, target.w);
    EXPECT_EQ(4, target.h);
}

TEST(RectTest, GetXYWH)
{
    Rect rect{ 1, 2, 3, 4 };
    
    EXPECT_EQ(1, rect.GetX());
    EXPECT_EQ(2, rect.GetY());
    EXPECT_EQ(3, rect.GetW());
    EXPECT_EQ(4, rect.GetH());
}

TEST(RectTest, SetXYWH)
{
    Rect rect;
    
    EXPECT_EQ(0, rect.GetX());
    EXPECT_EQ(0, rect.GetY());
    EXPECT_EQ(0, rect.GetW());
    EXPECT_EQ(0, rect.GetH());
    rect.SetX(1);
    rect.SetY(2);
    EXPECT_EQ(1, rect.GetX());
    EXPECT_EQ(2, rect.GetY());
    EXPECT_EQ(0, rect.GetW());
    EXPECT_EQ(0, rect.GetH());
    rect.SetW(3);
    rect.SetH(4);
    EXPECT_EQ(1, rect.GetX());
    EXPECT_EQ(2, rect.GetY());
    EXPECT_EQ(3, rect.GetW());
    EXPECT_EQ(4, rect.GetH());
}

TEST(RectTest, GetX2Y2)
{
    Rect rect{ 1, 2, 3, 4 };
    
    EXPECT_EQ(1, rect.GetX());
    EXPECT_EQ(2, rect.GetY());
    EXPECT_EQ(3, rect.GetW());
    EXPECT_EQ(4, rect.GetH());
    EXPECT_EQ(3, rect.GetX2());
    EXPECT_EQ(5, rect.GetY2());
}

TEST(RectTest, SetX2Y2)
{
    Rect rect;
    
    EXPECT_EQ(0, rect.GetX());
    EXPECT_EQ(0, rect.GetY());
    EXPECT_EQ(0, rect.GetW());
    EXPECT_EQ(0, rect.GetH());
    EXPECT_EQ(-1, rect.GetX2()); // X + W - 1
    EXPECT_EQ(-1, rect.GetY2()); // Y + H - 1
    rect.SetX(1);
    rect.SetY(2);
    EXPECT_EQ(1, rect.GetX());
    EXPECT_EQ(2, rect.GetY());
    EXPECT_EQ(0, rect.GetW());
    EXPECT_EQ(0, rect.GetH());
    EXPECT_EQ(0, rect.GetX2()); // X + W - 1
    EXPECT_EQ(1, rect.GetY2()); // Y + H - 1
    rect.SetX2(3);
    rect.SetY2(5);
    EXPECT_EQ(1, rect.GetX());
    EXPECT_EQ(2, rect.GetY());
    EXPECT_EQ(3, rect.GetW()); // X2 - X + 1
    EXPECT_EQ(4, rect.GetH()); // Y2 - Y + 1
    EXPECT_EQ(3, rect.GetX2());
    EXPECT_EQ(5, rect.GetY2());
}

TEST(RectTest, GetCorners)
{
    Rect rect{ 1, 2, 3, 4 };
    
    EXPECT_EQ(1, rect.GetTopLeft().x);
    EXPECT_EQ(2, rect.GetTopLeft().y);
    EXPECT_EQ(3, rect.GetTopRight().x); // X + W - 1
    EXPECT_EQ(2, rect.GetTopRight().y);
    EXPECT_EQ(1, rect.GetBottomLeft().x);
    EXPECT_EQ(5, rect.GetBottomLeft().y); // Y + H - 1
    EXPECT_EQ(3, rect.GetBottomRight().x); // X + W - 1
    EXPECT_EQ(5, rect.GetBottomRight().y); // Y + H - 1
}

TEST(RectTest, GetSize)
{
    Rect rect{ 1, 2, 3, 4 };
    
    EXPECT_EQ(3, rect.GetSize().x);
    EXPECT_EQ(4, rect.GetSize().y);
}

TEST(RectTest, GetCentroid)
{
    Rect rect{ 1, 2, 3, 4 };
    
    EXPECT_EQ(2, rect.GetCentroid().x); // X + W/2
    EXPECT_EQ(4, rect.GetCentroid().y); // Y + H/2
}

TEST(RectTest, ContainsValue)
{
    Rect rect{ 1, 2, 3, 4 };
    
    EXPECT_FALSE(rect.Contains(0, 0));
    EXPECT_FALSE(rect.Contains(1, 0));
    EXPECT_FALSE(rect.Contains(0, 2));
    EXPECT_TRUE(rect.Contains(1, 2));
    EXPECT_TRUE(rect.Contains(3, 5));
    EXPECT_FALSE(rect.Contains(4, 5));
    EXPECT_FALSE(rect.Contains(3, 6));
}

TEST(RectTest, ContainsPoint)
{
    Rect rect{ 1, 2, 3, 4 };
    
    EXPECT_FALSE(rect.Contains(Point{ 0, 0 }));
    EXPECT_FALSE(rect.Contains(Point{ 1, 0 }));
    EXPECT_FALSE(rect.Contains(Point{ 0, 2 }));
    EXPECT_TRUE(rect.Contains(Point{ 1, 2 }));
    EXPECT_TRUE(rect.Contains(Point{ 3, 5 }));
    EXPECT_FALSE(rect.Contains(Point{ 4, 5 }));
    EXPECT_FALSE(rect.Contains(Point{ 3, 6 }));
    EXPECT_TRUE(rect.Contains(rect.GetTopLeft()));
    EXPECT_TRUE(rect.Contains(rect.GetTopRight()));
    EXPECT_TRUE(rect.Contains(rect.GetBottomLeft()));
    EXPECT_TRUE(rect.Contains(rect.GetBottomLeft()));
    EXPECT_TRUE(rect.Contains(rect.GetCentroid()));
}

TEST(RectTest, ContainsRect)
{
    Rect rect{ 1, 2, 3, 4 };
    
    EXPECT_TRUE(rect.Contains(rect));
    EXPECT_FALSE(rect.Contains(Rect::FromCorners(1, 0, 3, 5)));
    EXPECT_FALSE(rect.Contains(Rect::FromCorners(0, 2, 3, 5)));
    EXPECT_TRUE(rect.Contains(Rect::FromCorners(1, 2, 3, 5)));
    EXPECT_TRUE(rect.Contains(Rect::FromCorners(2, 2, 3, 5)));
    EXPECT_TRUE(rect.Contains(Rect::FromCorners(1, 3, 3, 5)));
    EXPECT_FALSE(rect.Contains(Rect::FromCorners(2, 3, 4, 5)));
    EXPECT_FALSE(rect.Contains(Rect::FromCorners(2, 3, 3, 6)));
    EXPECT_TRUE(rect.Contains(Rect::FromCorners(rect.GetTopLeft(), rect.GetBottomRight())));
}

TEST(RectTest, Intersects)
{
    Rect rect{ Rect::FromCorners(1, 2, 3, 5) };
    Rect rectNonIntersecting{ Rect::FromCorners(5, 5, 8, 8) };
    Rect rectContaining{ Rect::FromCorners(0, 0, 5, 5) };
    Rect rectIntersecting{ Rect::FromCorners(3, 3, 5, 5) };
    Rect rectTouchingBottomLeft{ Rect::FromCorners(0, 0, 1, 2) };
    Rect rectTouchingTopRight{ Rect::FromCorners(3, 5, 8, 8) };
    
    EXPECT_TRUE(rect.Intersects(rect));
    EXPECT_FALSE(rect.Intersects(rectNonIntersecting));
    EXPECT_TRUE(rect.Intersects(rectContaining));
    EXPECT_TRUE(rect.Intersects(rectIntersecting));
    EXPECT_TRUE(rect.Intersects(rectTouchingBottomLeft));
    EXPECT_TRUE(rect.Intersects(rectTouchingTopRight));
}

TEST(RectTest, GetUnion)
{
    Rect rect{ Rect::FromCorners(0, 0, 5, 5) };
    Rect rectNonOverlapping{ Rect::FromCorners(10, 10, 15, 15) };
    Rect rectContaining{ Rect::FromCorners(0, 0, 10, 10) };
    Rect rectIntersecting{ Rect::FromCorners(3, 3, 10, 10) };
    Rect unionIdentity = rect.GetUnion(rect);
    Rect unionNonOverlapping = rect.GetUnion(rectNonOverlapping);
    Rect unionContaining = rect.GetUnion(rectContaining);
    Rect unionIntersecting = rect.GetUnion(rectIntersecting);
    
    EXPECT_EQ(Rect::FromCorners(0, 0, 5, 5), unionIdentity);
    EXPECT_EQ(Rect::FromCorners(0, 0, 15, 15), unionNonOverlapping);
    EXPECT_EQ(Rect::FromCorners(0, 0, 10, 10), unionContaining);
    EXPECT_EQ(Rect::FromCorners(0, 0, 10, 10), unionIntersecting);
}

TEST(RectTest, Union)
{
    Rect rect{ Rect::FromCorners(0, 0, 5, 5) };
    Rect rectIdentity{ rect };
    Rect rectNonOverlapping{ Rect::FromCorners(10, 10, 15, 15) };
    Rect rectContaining{ Rect::FromCorners(0, 0, 10, 10) };
    Rect rectIntersecting{ Rect::FromCorners(3, 3, 10, 10) };
    rectIdentity.Union(rect);
    rectNonOverlapping.Union(rect);
    rectContaining.Union(rect);
    rectIntersecting.Union(rect);
    
    EXPECT_EQ(Rect::FromCorners(0, 0, 5, 5), rectIdentity);
    EXPECT_EQ(Rect::FromCorners(0, 0, 15, 15), rectNonOverlapping);
    EXPECT_EQ(Rect::FromCorners(0, 0, 10, 10), rectContaining);
    EXPECT_EQ(Rect::FromCorners(0, 0, 10, 10), rectIntersecting);
}

TEST(RectTest, GetExtensionSingleAmount)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    Rect rectExtended{ rect.GetExtension(5) };
    
    EXPECT_EQ(Rect::FromCorners(5, 5, 25, 25), rectExtended);
}

TEST(RectTest, GetExtensionXYAmount)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    Rect rectExtended{ rect.GetExtension(2, 3) };
    
    EXPECT_EQ(Rect::FromCorners(8, 7, 22, 23), rectExtended);
}

TEST(RectTest, ExtendSingleAmount)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    rect.Extend(5);
    
    EXPECT_EQ(Rect::FromCorners(5, 5, 25, 25), rect);
}

TEST(RectTest, ExtendXYAmount)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    rect.Extend(2, 3);
    
    EXPECT_EQ(Rect::FromCorners(8, 7, 22, 23), rect);
}

TEST(RectTest, GetIntersection)
{
    Rect rect{ Rect::FromCorners(1, 2, 3, 5) };
    Rect rectIdentity{ rect };
    Rect rectNonIntersecting{ Rect::FromCorners(5, 5, 8, 8) };
    Rect rectContaining{ Rect::FromCorners(0, 0, 5, 5) };
    Rect rectIntersecting{ Rect::FromCorners(3, 3, 5, 5) };
    Rect rectTouchingBottomLeft{ Rect::FromCorners(0, 0, 1, 2) };
    Rect rectTouchingTopRight{ Rect::FromCorners(3, 5, 8, 8) };
    
    EXPECT_EQ(Rect::FromCorners(1, 2, 3, 5), rect.GetIntersection(rectIdentity));
    EXPECT_EQ(NullOpt, rect.GetIntersection(rectNonIntersecting));
    EXPECT_EQ(Rect::FromCorners(1, 2, 3, 5), rect.GetIntersection(rectContaining));
    EXPECT_EQ(Rect::FromCorners(3, 3, 3, 5), rect.GetIntersection(rectIntersecting));
    EXPECT_EQ(Rect::FromCorners(1, 2, 1, 2), rect.GetIntersection(rectTouchingBottomLeft));
    EXPECT_EQ(Rect::FromCorners(3, 5, 3, 5), rect.GetIntersection(rectTouchingTopRight));
}

TEST(RectTest, IntersectLineValuesFullyInside)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    
    int x1 = 10;
    int y1 = 10;
    int x2 = 20;
    int y2 = 20;
    EXPECT_TRUE(rect.IntersectLine(x1, y1, x2, y2));
    EXPECT_EQ(10, x1);
    EXPECT_EQ(10, y1);
    EXPECT_EQ(20, x2);
    EXPECT_EQ(20, y2);
}

TEST(RectTest, IntersectLineValuesFullyOutside)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    
    int x1 = 10;
    int y1 = 5;
    int x2 = 20;
    int y2 = 5;
    EXPECT_FALSE(rect.IntersectLine(x1, y1, x2, y2));
    EXPECT_EQ(10, x1);
    EXPECT_EQ(5, y1);
    EXPECT_EQ(20, x2);
    EXPECT_EQ(5, y2);
}

TEST(RectTest, IntersectLineValuesPartlyInside)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    
    int x1 = 00;
    int y1 = 00;
    int x2 = 30;
    int y2 = 30;
    EXPECT_TRUE(rect.IntersectLine(x1, y1, x2, y2));
    EXPECT_EQ(10, x1);
    EXPECT_EQ(10, y1);
    EXPECT_EQ(20, x2);
    EXPECT_EQ(20, y2);
}

TEST(RectTest, IntersectLinePointsFullyInside)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    
    Point point1{ 10, 10 };
    Point point2{ 20, 20};
    EXPECT_TRUE(rect.IntersectLine(point1, point2));
    EXPECT_EQ(10, point1.x);
    EXPECT_EQ(10, point1.y);
    EXPECT_EQ(20, point2.x);
    EXPECT_EQ(20, point2.y);
}

TEST(RectTest, IntersectLinePointsFullyOutside)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    
    Point point1{ 10, 5 };
    Point point2{ 20, 5};
    EXPECT_FALSE(rect.IntersectLine(point1, point2));
    EXPECT_EQ(10, point1.x);
    EXPECT_EQ(5, point1.y);
    EXPECT_EQ(20, point2.x);
    EXPECT_EQ(5, point2.y);
}

TEST(RectTest, IntersectLinePointsPartlyInside)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    
    Point point1{ 0, 0 };
    Point point2{ 30, 30};
    EXPECT_TRUE(rect.IntersectLine(point1, point2));
    EXPECT_EQ(10, point1.x);
    EXPECT_EQ(10, point1.y);
    EXPECT_EQ(20, point2.x);
    EXPECT_EQ(20, point2.y);
}

TEST(RectTest, Add)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    
    Point offset{ 5, 5 };
    Rect rectMoved = rect + offset;
    EXPECT_EQ(Rect::FromCorners(15, 15, 25, 25), rectMoved);
}

TEST(RectTest, Subtract)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    
    Point offset{ 5, 5 };
    Rect rectMoved = rect - offset;
    EXPECT_EQ(Rect::FromCorners(5, 5, 15, 15), rectMoved);
}

TEST(RectTest, AddAssign)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    
    Point offset{ 5, 5 };
    rect += offset;
    EXPECT_EQ(Rect::FromCorners(15, 15, 25, 25), rect);
}

TEST(RectTest, SubtractAssign)
{
    Rect rect{ Rect::FromCorners(10, 10, 20, 20) };
    
    Point offset{ 5, 5 };
    rect -= offset;
    EXPECT_EQ(Rect::FromCorners(5, 5, 15, 15), rect);
}

TEST(RectTest, Comparison)
{
    Rect rect{ 10, 10, 20, 20 };
    Rect rectEmpty;
    Rect rectEqual{ 10, 10, 20, 20 };
    Rect rectBottomLess{ 10, 10, 20, 19 };
    Rect rectRightLess{ 10, 10, 19, 20 };
    Rect rectTopLess{ 10, 9, 20, 20 };
    Rect rectLeftLess{ 9, 10, 20, 20 };
    Rect rectBottomMore{ 10, 10, 20, 21 };
    Rect rectRightMore{ 10, 10, 21, 20 };
    Rect rectTopMore{ 10, 11, 20, 20 };
    Rect rectLeftMore{ 11, 10, 20, 20 };
    
    EXPECT_FALSE(rect == rectEmpty);
    EXPECT_TRUE(rect != rectEmpty);
    EXPECT_FALSE(rect < rectEmpty);
    EXPECT_FALSE(rect <= rectEmpty);
    EXPECT_TRUE(rect > rectEmpty);
    EXPECT_TRUE(rect >= rectEmpty);

    EXPECT_TRUE(rect == rectEqual);
    EXPECT_FALSE(rect != rectEqual);
    EXPECT_FALSE(rect < rectEqual);
    EXPECT_TRUE(rect <= rectEqual);
    EXPECT_FALSE(rect > rectEqual);
    EXPECT_TRUE(rect >= rectEqual);

    EXPECT_FALSE(rect == rectBottomLess);
    EXPECT_TRUE(rect != rectBottomLess);
    EXPECT_FALSE(rect < rectBottomLess);
    EXPECT_FALSE(rect <= rectBottomLess);
    EXPECT_TRUE(rect > rectBottomLess);
    EXPECT_TRUE(rect >= rectBottomLess);

    EXPECT_FALSE(rect == rectRightLess);
    EXPECT_TRUE(rect != rectRightLess);
    EXPECT_FALSE(rect < rectRightLess);
    EXPECT_FALSE(rect <= rectRightLess);
    EXPECT_TRUE(rect > rectRightLess);
    EXPECT_TRUE(rect >= rectRightLess);

    EXPECT_FALSE(rect == rectTopLess);
    EXPECT_TRUE(rect != rectTopLess);
    EXPECT_FALSE(rect < rectTopLess);
    EXPECT_FALSE(rect <= rectTopLess);
    EXPECT_TRUE(rect > rectTopLess);
    EXPECT_TRUE(rect >= rectTopLess);

    EXPECT_FALSE(rect == rectLeftLess);
    EXPECT_TRUE(rect != rectLeftLess);
    EXPECT_FALSE(rect < rectLeftLess);
    EXPECT_FALSE(rect <= rectLeftLess);
    EXPECT_TRUE(rect > rectLeftLess);
    EXPECT_TRUE(rect >= rectLeftLess);

    EXPECT_FALSE(rect == rectBottomMore);
    EXPECT_TRUE(rect != rectBottomMore);
    EXPECT_TRUE(rect < rectBottomMore);
    EXPECT_TRUE(rect <= rectBottomMore);
    EXPECT_FALSE(rect > rectBottomMore);
    EXPECT_FALSE(rect >= rectBottomMore);

    EXPECT_FALSE(rect == rectRightMore);
    EXPECT_TRUE(rect != rectRightMore);
    EXPECT_TRUE(rect < rectRightMore);
    EXPECT_TRUE(rect <= rectRightMore);
    EXPECT_FALSE(rect > rectRightMore);
    EXPECT_FALSE(rect >= rectRightMore);

    EXPECT_FALSE(rect == rectTopMore);
    EXPECT_TRUE(rect != rectTopMore);
    EXPECT_TRUE(rect < rectTopMore);
    EXPECT_TRUE(rect <= rectTopMore);
    EXPECT_FALSE(rect > rectTopMore);
    EXPECT_FALSE(rect >= rectTopMore);

    EXPECT_FALSE(rect == rectLeftMore);
    EXPECT_TRUE(rect != rectLeftMore);
    EXPECT_TRUE(rect < rectLeftMore);
    EXPECT_TRUE(rect <= rectLeftMore);
    EXPECT_FALSE(rect > rectLeftMore);
    EXPECT_FALSE(rect >= rectLeftMore);
}

TEST(RectTest, StreamInsertion)
{
    Rect rect{ 1, 2, 3, 4 };
    std::string expected{ "[x:1,y:2,w:3,h:4]" };
    std::ostringstream stream;
    stream << rect;
    EXPECT_EQ(expected, stream.str());
}

TEST(RectTest, Hash)
{
    Rect rect{ 10, 10, 20, 20 };
    Rect rectEmpty;
    Rect rectEqual{ 10, 10, 20, 20 };
    Rect rectDifferent{ 1, 1, 10, 10 };
    
    EXPECT_TRUE(std::hash<Rect>{}(rect) == std::hash<Rect>{}(rect));
    EXPECT_FALSE(std::hash<Rect>{}(rect) == std::hash<Rect>{}(rectEmpty));
    EXPECT_TRUE(std::hash<Rect>{}(rect) == std::hash<Rect>{}(rectEqual));
    EXPECT_FALSE(std::hash<Rect>{}(rect) == std::hash<Rect>{}(rectDifferent));
}

} // namespace SDL3CPP
