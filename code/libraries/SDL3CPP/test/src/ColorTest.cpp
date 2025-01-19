//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 René Barto
//
// File        : ColorTest.cpp
//
// Namespace   : SDL2
//
// Class       : -
//
// Description : 
//  Test for SDL2 Color class
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "SDL3CPP/Color.h"

namespace SDL3CPP {

TEST(ColorTest, ConstructDefault)
{
    Color color;

    EXPECT_EQ(0, color.r);
    EXPECT_EQ(0, color.g);
    EXPECT_EQ(0, color.b);
    EXPECT_EQ(0, color.a);
}

TEST(ColorTest, ConstructFromSDL_Color)
{
    Color color{SDL_Color{ 1, 2, 3, 4 }};

    EXPECT_EQ(1, color.r);
    EXPECT_EQ(2, color.g);
    EXPECT_EQ(3, color.b);
    EXPECT_EQ(4, color.a);
}

TEST(ColorTest, ConstructFromValuesNoAlpha)
{
    Color color{ 1, 2, 3 };

    EXPECT_EQ(1, color.r);
    EXPECT_EQ(2, color.g);
    EXPECT_EQ(3, color.b);
    EXPECT_EQ(SDL_ALPHA_OPAQUE, color.a);
}

TEST(ColorTest, ConstructFromValues)
{
    Color color{ 1, 2, 3, 4 };

    EXPECT_EQ(1, color.r);
    EXPECT_EQ(2, color.g);
    EXPECT_EQ(3, color.b);
    EXPECT_EQ(4, color.a);
}

TEST(ColorTest, ConstructCopy)
{
    Color color{ 1, 2, 3, 4 };
    Color target{ color };

    EXPECT_EQ(1, color.r);
    EXPECT_EQ(2, color.g);
    EXPECT_EQ(3, color.b);
    EXPECT_EQ(4, color.a);
    EXPECT_EQ(1, target.r);
    EXPECT_EQ(2, target.g);
    EXPECT_EQ(3, target.b);
    EXPECT_EQ(4, target.a);
}

TEST(ColorTest, ConstructMove)
{
    Color color{ 1, 2, 3, 4 };
    Color target{ std::move(color) };

    EXPECT_EQ(1, color.r);
    EXPECT_EQ(2, color.g);
    EXPECT_EQ(3, color.b);
    EXPECT_EQ(4, color.a);
    EXPECT_EQ(1, target.r);
    EXPECT_EQ(2, target.g);
    EXPECT_EQ(3, target.b);
    EXPECT_EQ(4, target.a);
}

TEST(ColorTest, Assign)
{
    Color color{ 1, 2, 3, 4 };
    Color target;
    
    target = color;

    EXPECT_EQ(1, color.r);
    EXPECT_EQ(2, color.g);
    EXPECT_EQ(3, color.b);
    EXPECT_EQ(4, color.a);
    EXPECT_EQ(1, target.r);
    EXPECT_EQ(2, target.g);
    EXPECT_EQ(3, target.b);
    EXPECT_EQ(4, target.a);
}

TEST(ColorTest, AssignMove)
{
    Color color{ 1, 2, 3, 4 };
    Color target;
    
    target = std::move(color);

    EXPECT_EQ(1, color.r);
    EXPECT_EQ(2, color.g);
    EXPECT_EQ(3, color.b);
    EXPECT_EQ(4, color.a);
    EXPECT_EQ(1, target.r);
    EXPECT_EQ(2, target.g);
    EXPECT_EQ(3, target.b);
    EXPECT_EQ(4, target.a);
}

TEST(ColorTest, GetRGBA)
{
    Color color{ 1, 2, 3, 4 };
    
    EXPECT_EQ(1, color.GetRed());
    EXPECT_EQ(2, color.GetGreen());
    EXPECT_EQ(3, color.GetBlue());
    EXPECT_EQ(4, color.GetAlpha());
}

TEST(ColorTest, SetRGBA)
{
    Color color;
    
    EXPECT_EQ(0, color.GetRed());
    EXPECT_EQ(0, color.GetGreen());
    EXPECT_EQ(0, color.GetBlue());
    EXPECT_EQ(0, color.GetAlpha());
    color.SetRed(1);
    color.SetGreen(2);
    color.SetBlue(3);
    color.SetAlpha(4);
    EXPECT_EQ(1, color.GetRed());
    EXPECT_EQ(2, color.GetGreen());
    EXPECT_EQ(3, color.GetBlue());
    EXPECT_EQ(4, color.GetAlpha());
}

TEST(ColorTest, ComparisonEqual)
{
    Color color{ 1, 2, 3, 4 };
    Color colorDefault;
    Color colorEqual{ 1, 2, 3, 4 };
    Color colorDifferentColor{ 11, 12, 13, 4 };
    Color colorDifferentAlpha{ 1, 2, 3, 255 };
    
    EXPECT_TRUE(color == color);
    EXPECT_FALSE(color == colorDefault);
    EXPECT_TRUE(color == colorEqual);
    EXPECT_FALSE(color == colorDifferentColor);
    EXPECT_FALSE(color == colorDifferentAlpha);
}

TEST(ColorTest, ComparisonNotEqual)
{
    Color color{ 1, 2, 3, 4 };
    Color colorDefault;
    Color colorEqual{ 1, 2, 3, 4 };
    Color colorDifferentColor{ 11, 12, 13, 4 };
    Color colorDifferentAlpha{ 1, 2, 3, 255 };
    
    EXPECT_FALSE(color != color);
    EXPECT_TRUE(color != colorDefault);
    EXPECT_FALSE(color != colorEqual);
    EXPECT_TRUE(color != colorDifferentColor);
    EXPECT_TRUE(color != colorDifferentAlpha);
}

TEST(ColorTest, StreamInsertion)
{
    Color color{ 1, 2, 3, 4 };
    std::string expected{ "[r:1,g:2,b:3,a:4]" };
    std::ostringstream stream;
    stream << color;
    EXPECT_EQ(expected, stream.str());
}

TEST(ColorTest, Hash)
{
    Color color{ 1, 2, 3, 4 };
    Color colorDefault;
    Color colorEqual{ 1, 2, 3, 4 };
    Color colorDifferentColor{ 11, 12, 13, 4 };
    Color colorDifferentAlpha{ 1, 2, 3, 255 };
    
    EXPECT_TRUE(std::hash<Color>{}(color) == std::hash<Color>{}(color));
    EXPECT_FALSE(std::hash<Color>{}(color) == std::hash<Color>{}(colorDefault));
    EXPECT_TRUE(std::hash<Color>{}(color) == std::hash<Color>{}(colorEqual));
    EXPECT_FALSE(std::hash<Color>{}(color) == std::hash<Color>{}(colorDifferentColor));
    EXPECT_FALSE(std::hash<Color>{}(color) == std::hash<Color>{}(colorDifferentAlpha));
}

} // namespace SDL3CPP
