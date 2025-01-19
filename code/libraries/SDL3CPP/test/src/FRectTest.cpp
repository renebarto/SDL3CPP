//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 René Barto
//
// File        : FRectTest.cpp
//
// Namespace   : SDL2
//
// Class       : -
//
// Description : 
//  Test for SDL2 FRect class
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "SDL3CPP/FRect.h"

namespace SDL3CPP {

TEST(FRectTest, ConstructDefault)
{
    FRect rect;

    EXPECT_EQ(0.0F, rect.x);
    EXPECT_EQ(0.0F, rect.y);
    EXPECT_EQ(0.0F, rect.w);
    EXPECT_EQ(0.0F, rect.h);
}

TEST(FRectTest, ConstructFromSDL_FRect)
{
    FRect rect{SDL_FRect{ 1.0F, 2.0F, 3.0F, 4.0F }};

    EXPECT_EQ(1.0F, rect.x);
    EXPECT_EQ(2.0F, rect.y);
    EXPECT_EQ(3.0F, rect.w);
    EXPECT_EQ(4.0F, rect.h);
}

TEST(FRectTest, ConstructFromPoints)
{
    FPoint topLeft{ 1.0F, 2.0F };
    FPoint size {3.0F, 4.0F};
    FRect rect{ topLeft, size };

    EXPECT_EQ(1.0F, rect.x);
    EXPECT_EQ(2.0F, rect.y);
    EXPECT_EQ(3.0F, rect.w);
    EXPECT_EQ(4.0F, rect.h);
}

TEST(FRectTest, ConstructFromValues)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };

    EXPECT_EQ(1.0F, rect.x);
    EXPECT_EQ(2.0F, rect.y);
    EXPECT_EQ(3.0F, rect.w);
    EXPECT_EQ(4.0F, rect.h);
}

TEST(FRectTest, ConstructCopy)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };
    FRect target{ rect };

    EXPECT_EQ(1.0F, rect.x);
    EXPECT_EQ(2.0F, rect.y);
    EXPECT_EQ(3.0F, rect.w);
    EXPECT_EQ(4.0F, rect.h);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
    EXPECT_EQ(3.0F, target.w);
    EXPECT_EQ(4.0F, target.h);
}

TEST(FRectTest, ConstructMove)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };
    FRect target{ std::move(rect) };

    EXPECT_EQ(1.0F, rect.x);
    EXPECT_EQ(2.0F, rect.y);
    EXPECT_EQ(3.0F, rect.w);
    EXPECT_EQ(4.0F, rect.h);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
    EXPECT_EQ(3.0F, target.w);
    EXPECT_EQ(4.0F, target.h);
}

TEST(FRectTest, FromCenterValues)
{
    FRect rect{ FRect::FromCenter(5.0F, 5.0F, 3.0F, 4.0F) };

    EXPECT_EQ(3.5F, rect.x); // 5 - 3/2
    EXPECT_EQ(3.0F, rect.y); // 5 - 4/2
    EXPECT_EQ(3.0F, rect.w);
    EXPECT_EQ(4.0F, rect.h);
}

TEST(FRectTest, FromCenterPoints)
{
    FPoint topLeft{ 5.0F, 5.0F };
    FPoint size {3.0F, 4.0F};
    FRect rect{ FRect::FromCenter(topLeft, size) };

    EXPECT_EQ(3.5F, rect.x); // 5 - 3/2
    EXPECT_EQ(3.0F, rect.y); // 5 - 4/2
    EXPECT_EQ(3.0F, rect.w);
    EXPECT_EQ(4.0F, rect.h);
}

TEST(FRectTest, FromCornersValues)
{
    FRect rect{ FRect::FromCorners(1.0F, 2.0F, 3.0F, 4.0F) };

    EXPECT_EQ(1.0F, rect.x);
    EXPECT_EQ(2.0F, rect.y);
    EXPECT_EQ(3.0F, rect.w); // 3 - 1 + 1
    EXPECT_EQ(3.0F, rect.h); // 4 - 2 + 1
}

TEST(FRectTest, FromCornersPoints)
{
    FPoint topLeft{ 1.0F, 2.0F };
    FPoint bottomRight {3.0F, 4.0F};
    FRect rect{ FRect::FromCorners(topLeft, bottomRight) };

    EXPECT_EQ(1.0F, rect.x);
    EXPECT_EQ(2.0F, rect.y);
    EXPECT_EQ(3.0F, rect.w); // 3 - 1 + 1
    EXPECT_EQ(3.0F, rect.h); // 4 - 2 + 1
}

TEST(FRectTest, Assign)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };
    FRect target;
    
    target = rect;

    EXPECT_EQ(1.0F, rect.x);
    EXPECT_EQ(2.0F, rect.y);
    EXPECT_EQ(3.0F, rect.w);
    EXPECT_EQ(4.0F, rect.h);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
    EXPECT_EQ(3.0F, target.w);
    EXPECT_EQ(4.0F, target.h);
}

TEST(FRectTest, AssignMove)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };
    FRect target;
    
    target = std::move(rect);

    EXPECT_EQ(1.0F, rect.x);
    EXPECT_EQ(2.0F, rect.y);
    EXPECT_EQ(3.0F, rect.w);
    EXPECT_EQ(4.0F, rect.h);
    EXPECT_EQ(1.0F, target.x);
    EXPECT_EQ(2.0F, target.y);
    EXPECT_EQ(3.0F, target.w);
    EXPECT_EQ(4.0F, target.h);
}

TEST(FRectTest, GetXYWH)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };
    
    EXPECT_EQ(1.0F, rect.GetX());
    EXPECT_EQ(2.0F, rect.GetY());
    EXPECT_EQ(3.0F, rect.GetW());
    EXPECT_EQ(4.0F, rect.GetH());
}

TEST(FRectTest, SetXYWH)
{
    FRect rect;
    
    EXPECT_EQ(0.0F, rect.GetX());
    EXPECT_EQ(0.0F, rect.GetY());
    EXPECT_EQ(0.0F, rect.GetW());
    EXPECT_EQ(0.0F, rect.GetH());
    rect.SetX(1.0F);
    rect.SetY(2.0F);
    EXPECT_EQ(1.0F, rect.GetX());
    EXPECT_EQ(2.0F, rect.GetY());
    EXPECT_EQ(0.0F, rect.GetW());
    EXPECT_EQ(0.0F, rect.GetH());
    rect.SetW(3.0F);
    rect.SetH(4.0F);
    EXPECT_EQ(1.0F, rect.GetX());
    EXPECT_EQ(2.0F, rect.GetY());
    EXPECT_EQ(3.0F, rect.GetW());
    EXPECT_EQ(4.0F, rect.GetH());
}

TEST(FRectTest, GetX2Y2)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };
    
    EXPECT_EQ(1.0F, rect.GetX());
    EXPECT_EQ(2.0F, rect.GetY());
    EXPECT_EQ(3.0F, rect.GetW());
    EXPECT_EQ(4.0F, rect.GetH());
    EXPECT_EQ(3.0F, rect.GetX2());
    EXPECT_EQ(5.0F, rect.GetY2());
}

TEST(FRectTest, SetX2Y2)
{
    FRect rect;
    
    EXPECT_EQ(0.0F, rect.GetX());
    EXPECT_EQ(0.0F, rect.GetY());
    EXPECT_EQ(0.0F, rect.GetW());
    EXPECT_EQ(0.0F, rect.GetH());
    EXPECT_EQ(-1.0F, rect.GetX2()); // X + W - 1
    EXPECT_EQ(-1.0F, rect.GetY2()); // Y + H - 1
    rect.SetX(1.0F);
    rect.SetY(2.0F);
    EXPECT_EQ(1.0F, rect.GetX());
    EXPECT_EQ(2.0F, rect.GetY());
    EXPECT_EQ(0.0F, rect.GetW());
    EXPECT_EQ(0.0F, rect.GetH());
    EXPECT_EQ(0.0F, rect.GetX2()); // X + W - 1
    EXPECT_EQ(1.0F, rect.GetY2()); // Y + H - 1
    rect.SetX2(3.0F);
    rect.SetY2(5.0F);
    EXPECT_EQ(1.0F, rect.GetX());
    EXPECT_EQ(2.0F, rect.GetY());
    EXPECT_EQ(3.0F, rect.GetW()); // X2 - X + 1
    EXPECT_EQ(4.0F, rect.GetH()); // Y2 - Y + 1
    EXPECT_EQ(3.0F, rect.GetX2());
    EXPECT_EQ(5.0F, rect.GetY2());
}

TEST(FRectTest, GetCorners)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };
    
    EXPECT_EQ(1.0F, rect.GetTopLeft().x);
    EXPECT_EQ(2.0F, rect.GetTopLeft().y);
    EXPECT_EQ(3.0F, rect.GetTopRight().x); // X + W - 1
    EXPECT_EQ(2.0F, rect.GetTopRight().y);
    EXPECT_EQ(1.0F, rect.GetBottomLeft().x);
    EXPECT_EQ(5.0F, rect.GetBottomLeft().y); // Y + H - 1
    EXPECT_EQ(3.0F, rect.GetBottomRight().x); // X + W - 1
    EXPECT_EQ(5.0F, rect.GetBottomRight().y); // Y + H - 1
}

TEST(FRectTest, GetSize)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };
    
    EXPECT_EQ(3.0F, rect.GetSize().x);
    EXPECT_EQ(4.0F, rect.GetSize().y);
}

TEST(FRectTest, GetCentroid)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };
    
    EXPECT_EQ(2.5F, rect.GetCentroid().x); // X + W/2
    EXPECT_EQ(4.0F, rect.GetCentroid().y); // Y + H/2
}

TEST(FRectTest, ContainsValue)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };
    
    EXPECT_FALSE(rect.Contains(0.0F, 0.0F));
    EXPECT_FALSE(rect.Contains(1.0F, 0.0F));
    EXPECT_FALSE(rect.Contains(0.0F, 2.0F));
    EXPECT_TRUE(rect.Contains(1.0F, 2.0F));
    EXPECT_TRUE(rect.Contains(3.0F, 5.0F));
    EXPECT_FALSE(rect.Contains(4.0F, 5.0F));
    EXPECT_FALSE(rect.Contains(3.0F, 6.0F));
}

TEST(FRectTest, ContainsPoint)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };
    
    EXPECT_FALSE(rect.Contains(FPoint{ 0.0F, 0.0F }));
    EXPECT_FALSE(rect.Contains(FPoint{ 1.0F, 0.0F }));
    EXPECT_FALSE(rect.Contains(FPoint{ 0.0F, 2.0F }));
    EXPECT_TRUE(rect.Contains(FPoint{ 1.0F, 2.0F }));
    EXPECT_TRUE(rect.Contains(FPoint{ 3.0F, 5.0F }));
    EXPECT_FALSE(rect.Contains(FPoint{ 4.0F, 5.0F }));
    EXPECT_FALSE(rect.Contains(FPoint{ 3.0F, 6.0F }));
    EXPECT_TRUE(rect.Contains(rect.GetTopLeft()));
    EXPECT_TRUE(rect.Contains(rect.GetTopRight()));
    EXPECT_TRUE(rect.Contains(rect.GetBottomLeft()));
    EXPECT_TRUE(rect.Contains(rect.GetBottomLeft()));
    EXPECT_TRUE(rect.Contains(rect.GetCentroid()));
}

TEST(FRectTest, ContainsFRect)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };
    
    EXPECT_TRUE(rect.Contains(rect));
    EXPECT_FALSE(rect.Contains(FRect::FromCorners(1.0F, 0.0F, 3.0F, 5.0F)));
    EXPECT_FALSE(rect.Contains(FRect::FromCorners(0.0F, 2.0F, 3.0F, 5.0F)));
    EXPECT_TRUE(rect.Contains(FRect::FromCorners(1.0F, 2.0F, 3.0F, 5.0F)));
    EXPECT_TRUE(rect.Contains(FRect::FromCorners(2.0F, 2.0F, 3.0F, 5.0F)));
    EXPECT_TRUE(rect.Contains(FRect::FromCorners(1.0F, 3.0F, 3.0F, 5.0F)));
    EXPECT_FALSE(rect.Contains(FRect::FromCorners(2.0F, 3.0F, 4.0F, 5.0F)));
    EXPECT_FALSE(rect.Contains(FRect::FromCorners(2.0F, 3.0F, 3.0F, 6.0F)));
    EXPECT_TRUE(rect.Contains(FRect::FromCorners(rect.GetTopLeft(), rect.GetBottomRight())));
}

TEST(FRectTest, Intersects)
{
    FRect rect{ FRect::FromCorners(1.0F, 2.0F, 3.0F, 5.0F) };
    FRect rectNonIntersecting{ FRect::FromCorners(5.0F, 5.0F, 8.0F, 8.0F) };
    FRect rectContaining{ FRect::FromCorners(0.0F, 0.0F, 5.0F, 5.0F) };
    FRect rectIntersecting{ FRect::FromCorners(3.0F, 3.0F, 5.0F, 5.0F) };
    FRect rectTouchingBottomLeft{ FRect::FromCorners(0.0F, 0.0F, 1.0F, 2.0F) };
    FRect rectTouchingTopRight{ FRect::FromCorners(3.0F, 5.0F, 8.0F, 8.0F) };
    
    EXPECT_TRUE(rect.Intersects(rect));
    EXPECT_FALSE(rect.Intersects(rectNonIntersecting));
    EXPECT_TRUE(rect.Intersects(rectContaining));
    EXPECT_TRUE(rect.Intersects(rectIntersecting));
    EXPECT_TRUE(rect.Intersects(rectTouchingBottomLeft));
    EXPECT_TRUE(rect.Intersects(rectTouchingTopRight));
}

TEST(FRectTest, GetUnion)
{
    FRect rect{ FRect::FromCorners(0.0F, 0.0F, 5.0F, 5.0F) };
    FRect rectNonOverlapping{ FRect::FromCorners(10.0F, 10.0F, 15.0F, 15.0F) };
    FRect rectContaining{ FRect::FromCorners(0.0F, 0.0F, 10.0F, 10.0F) };
    FRect rectIntersecting{ FRect::FromCorners(3.0F, 3.0F, 10.0F, 10.0F) };
    FRect unionIdentity = rect.GetUnion(rect);
    FRect unionNonOverlapping = rect.GetUnion(rectNonOverlapping);
    FRect unionContaining = rect.GetUnion(rectContaining);
    FRect unionIntersecting = rect.GetUnion(rectIntersecting);
    
    EXPECT_EQ(FRect::FromCorners(0.0F, 0.0F, 5.0F, 5.0F), unionIdentity);
    EXPECT_EQ(FRect::FromCorners(0.0F, 0.0F, 15.0F, 15.0F), unionNonOverlapping);
    EXPECT_EQ(FRect::FromCorners(0.0F, 0.0F, 10.0F, 10.0F), unionContaining);
    EXPECT_EQ(FRect::FromCorners(0.0F, 0.0F, 10.0F, 10.0F), unionIntersecting);
}

TEST(FRectTest, Union)
{
    FRect rect{ FRect::FromCorners(0.0F, 0.0F, 5.0F, 5.0F) };
    FRect rectIdentity{ rect };
    FRect rectNonOverlapping{ FRect::FromCorners(10.0F, 10.0F, 15.0F, 15.0F) };
    FRect rectContaining{ FRect::FromCorners(0.0F, 0.0F, 10.0F, 10.0F) };
    FRect rectIntersecting{ FRect::FromCorners(3.0F, 3.0F, 10.0F, 10.0F) };
    rectIdentity.Union(rect);
    rectNonOverlapping.Union(rect);
    rectContaining.Union(rect);
    rectIntersecting.Union(rect);
    
    EXPECT_EQ(FRect::FromCorners(0.0F, 0.0F, 5.0F, 5.0F), rectIdentity);
    EXPECT_EQ(FRect::FromCorners(0.0F, 0.0F, 15.0F, 15.0F), rectNonOverlapping);
    EXPECT_EQ(FRect::FromCorners(0.0F, 0.0F, 10.0F, 10.0F), rectContaining);
    EXPECT_EQ(FRect::FromCorners(0.0F, 0.0F, 10.0F, 10.0F), rectIntersecting);
}

TEST(FRectTest, GetExtensionSingleAmount)
{
    FRect rect{ FRect::FromCorners(10.0F, 10.0F, 20.0F, 20.0F) };
    FRect rectExtended{ rect.GetExtension(5.0F) };
    
    EXPECT_EQ(FRect::FromCorners(5.0F, 5.0F, 25.0F, 25.0F), rectExtended);
}

TEST(FRectTest, GetExtensionXYAmount)
{
    FRect rect{ FRect::FromCorners(10.0F, 10.0F, 20.0F, 20.0F) };
    FRect rectExtended{ rect.GetExtension(2.0F, 3.0F) };
    
    EXPECT_EQ(FRect::FromCorners(8.0F, 7.0F, 22.0F, 23.0F), rectExtended);
}

TEST(FRectTest, ExtendSingleAmount)
{
    FRect rect{ FRect::FromCorners(10.0F, 10.0F, 20.0F, 20.0F) };
    rect.Extend(5.0F);
    
    EXPECT_EQ(FRect::FromCorners(5.0F, 5.0F, 25.0F, 25.0F), rect);
}

TEST(FRectTest, ExtendXYAmount)
{
    FRect rect{ FRect::FromCorners(10.0F, 10.0F, 20.0F, 20.0F) };
    rect.Extend(2.0F, 3.0F);
    
    EXPECT_EQ(FRect::FromCorners(8.0F, 7.0F, 22.0F, 23.0F), rect);
}

TEST(FRectTest, GetIntersection)
{
    FRect rect{ FRect::FromCorners(1.0F, 2.0F, 3.0F, 5.0F) };
    FRect rectIdentity{ rect };
    FRect rectNonIntersecting{ FRect::FromCorners(5.0F, 5.0F, 8.0F, 8.0F) };
    FRect rectContaining{ FRect::FromCorners(0.0F, 0.0F, 5.0F, 5.0F) };
    FRect rectIntersecting{ FRect::FromCorners(3.0F, 3.0F, 5.0F, 5.0F) };
    FRect rectTouchingBottomLeft{ FRect::FromCorners(0.0F, 0.0F, 1.0F, 2.0F) };
    FRect rectTouchingTopRight{ FRect::FromCorners(3.0F, 5.0F, 8.0F, 8.0F) };
    
    EXPECT_EQ(FRect::FromCorners(1.0F, 2.0F, 3.0F, 5.0F), rect.GetIntersection(rectIdentity));
    EXPECT_EQ(NullOpt, rect.GetIntersection(rectNonIntersecting));
    EXPECT_EQ(FRect::FromCorners(1.0F, 2.0F, 3.0F, 5.0F), rect.GetIntersection(rectContaining));
    EXPECT_EQ(FRect::FromCorners(3.0F, 3.0F, 3.0F, 5.0F), rect.GetIntersection(rectIntersecting));
    EXPECT_EQ(FRect::FromCorners(1.0F, 2.0F, 1.0F, 2.0F), rect.GetIntersection(rectTouchingBottomLeft));
    EXPECT_EQ(FRect::FromCorners(3.0F, 5.0F, 3.0F, 5.0F), rect.GetIntersection(rectTouchingTopRight));
}

TEST(FRectTest, Add)
{
    FRect rect{ FRect::FromCorners(10.0F, 10.0F, 20.0F, 20.0F) };
    
    FPoint offset{ 5.0F, 5.0F };
    FRect rectMoved = rect + offset;
    EXPECT_EQ(FRect::FromCorners(15.0F, 15.0F, 25.0F, 25.0F), rectMoved);
}

TEST(FRectTest, Subtract)
{
    FRect rect{ FRect::FromCorners(10.0F, 10.0F, 20.0F, 20.0F) };
    
    FPoint offset{ 5.0F, 5.0F };
    FRect rectMoved = rect - offset;
    EXPECT_EQ(FRect::FromCorners(5.0F, 5.0F, 15.0F, 15.0F), rectMoved);
}

TEST(FRectTest, AddAssign)
{
    FRect rect{ FRect::FromCorners(10.0F, 10.0F, 20.0F, 20.0F) };
    
    FPoint offset{ 5.0F, 5.0F };
    rect += offset;
    EXPECT_EQ(FRect::FromCorners(15.0F, 15.0F, 25.0F, 25.0F), rect);
}

TEST(FRectTest, SubtractAssign)
{
    FRect rect{ FRect::FromCorners(10.0F, 10.0F, 20.0F, 20.0F) };
    
    FPoint offset{ 5.0F, 5.0F };
    rect -= offset;
    EXPECT_EQ(FRect::FromCorners(5.0F, 5.0F, 15.0F, 15.0F), rect);
}

TEST(FRectTest, Comparison)
{
    FRect rect{ 10.0F, 10.0F, 20.0F, 20.0F };
    FRect rectEmpty;
    FRect rectEqual{ 10.0F, 10.0F, 20.0F, 20.0F };
    FRect rectBottomLess{ 10.0F, 10.0F, 20.0F, 19.0F };
    FRect rectRightLess{ 10.0F, 10.0F, 19.0F, 20.0F };
    FRect rectTopLess{ 10.0F, 9.0F, 20.0F, 20.0F };
    FRect rectLeftLess{ 9.0F, 10.0F, 20.0F, 20.0F };
    FRect rectBottomMore{ 10.0F, 10.0F, 20.0F, 21.0F };
    FRect rectRightMore{ 10.0F, 10.0F, 21.0F, 20.0F };
    FRect rectTopMore{ 10.0F, 11.0F, 20.0F, 20.0F };
    FRect rectLeftMore{ 11.0F, 10.0F, 20.0F, 20.0F };
    
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

TEST(FRectTest, StreamInsertion)
{
    FRect rect{ 1.0F, 2.0F, 3.0F, 4.0F };
    std::string expected{ "[x:1,y:2,w:3,h:4]" };
    std::ostringstream stream;
    stream << rect;
    EXPECT_EQ(expected, stream.str());
}

TEST(FRectTest, Hash)
{
    FRect rect{ 10.0F, 10.0F, 20.0F, 20.0F };
    FRect rectEmpty;
    FRect rectEqual{ 10.0F, 10.0F, 20.0F, 20.0F };
    FRect rectDifferent{ 1.0F, 1.0F, 10.0F, 10.0F };
    
    EXPECT_TRUE(std::hash<FRect>{}(rect) == std::hash<FRect>{}(rect));
    EXPECT_FALSE(std::hash<FRect>{}(rect) == std::hash<FRect>{}(rectEmpty));
    EXPECT_TRUE(std::hash<FRect>{}(rect) == std::hash<FRect>{}(rectEqual));
    EXPECT_FALSE(std::hash<FRect>{}(rect) == std::hash<FRect>{}(rectDifferent));
}

} // namespace SDL3CPP
