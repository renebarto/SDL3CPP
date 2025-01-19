//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : PathTest.cpp
//
// Namespace   : filesystem
//
// Class       : PathTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "filesystem/Path.h"

#include "utility/Serialization.h"
#include "utility/StringFunctions.h"

namespace filesystem
{

class PathTest
    : public ::testing::Test
{

};

TEST_F(PathTest, ConstructDefault)
{
    Path path;
    std::string expected = "";
    EXPECT_EQ(expected, path.Get());
}

TEST_F(PathTest, Construct)
{
    std::string text("/home");
    Path path(text);
    std::string expected = text;
    EXPECT_EQ(expected, path.Get());
}

TEST_F(PathTest, ConstructMultipleWithoutSlashes)
{
    Path path("/home", "user");
    std::string expected = "/home/user";
    EXPECT_EQ(expected, path.Get());
}

TEST_F(PathTest, ConstructMultipleWithSlashes)
{
    Path path("/home", "/user");
    std::string expected = "/home/user";
    EXPECT_EQ(expected, path.Get());
}

TEST_F(PathTest, ConstructMultiple)
{
    Path path("/home", "user", "data");
    std::string expected = "/home/user/data";
    EXPECT_EQ(expected, path.Get());
}

TEST_F(PathTest, ConstructMultipleWithEmpty)
{
    Path path("/home", "");
    std::string expected = "/home";
    EXPECT_EQ(expected, path.Get());
}

TEST_F(PathTest, ConstructMultipleWithEmptyTrailingSlash)
{
    Path path("/home/", "");
    std::string expected = "/home/";
    EXPECT_EQ(expected, path.Get());
}

TEST_F(PathTest, AppendWithoutSlash)
{
    Path path("/home");
    path.Append("user");
    std::string expected = "/home/user";
    EXPECT_EQ(expected, path.Get());
}

TEST_F(PathTest, AppendWithSlash)
{
    Path path("/home");
    path.Append("/user");
    std::string expected = "/home/user";
    EXPECT_EQ(expected, path.Get());
}

TEST_F(PathTest, SlashOperatorWithoutSlash)
{
    Path path("/home");
    path = path / "user";
    std::string expected = "/home/user";
    EXPECT_EQ(expected, path.Get());
}

TEST_F(PathTest, SlashOperatorWithSlash)
{
    Path path("/home");
    path = path / "/user";
    std::string expected = "/home/user";
    EXPECT_EQ(expected, path.Get());
}

TEST_F(PathTest, GetParts)
{
    Path path("/home/user/data");
    std::vector<std::string> expected = { "/", "home", "user", "data" };
    EXPECT_EQ(expected, path.GetParts());
}

} // namespace filesystem
