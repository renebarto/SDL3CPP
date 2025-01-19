//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : PathFunctionsTest.cpp
//
// Namespace   : filesystem
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "filesystem/PathFunctions.h"

namespace filesystem
{

TEST(PathFunctionsTest, NormalizePath)
{
    EXPECT_EQ("", NormalizePath(""));
    EXPECT_EQ("C:/", NormalizePath("C:\\"));
    EXPECT_EQ("C:/windows/temp/file.txt", NormalizePath("C:\\windows\\temp\\file.txt"));
    EXPECT_EQ("//server/share", NormalizePath("\\\\server\\share"));
    EXPECT_EQ("/var/log/DTC", NormalizePath("/var/log/DTC"));
}

TEST(PathFunctionsTest, SplitPathDriverRootDirFileName)
{
    std::string root;
    std::string directory;
    std::string fileName;

    SplitPath("", root, directory, fileName);
    EXPECT_EQ("", root);
    EXPECT_EQ("", directory);
    EXPECT_EQ("", fileName);

    SplitPath("C:", root, directory, fileName);
    EXPECT_EQ("C:", root);
    EXPECT_EQ("", directory);
    EXPECT_EQ("", fileName);

    SplitPath("C:/", root, directory, fileName);
    EXPECT_EQ("C:/", root);
    EXPECT_EQ("", directory);
    EXPECT_EQ("", fileName);

    SplitPath("\\\\server", root, directory, fileName);
    EXPECT_EQ("//server", root);
    EXPECT_EQ("", directory);
    EXPECT_EQ("", fileName);

    SplitPath("\\\\server\\share", root, directory, fileName);
    EXPECT_EQ("//server/share", root);
    EXPECT_EQ("", directory);
    EXPECT_EQ("", fileName);

    SplitPath("temp", root, directory, fileName);
    EXPECT_EQ("", root);
    EXPECT_EQ("", directory);
    EXPECT_EQ("temp", fileName);

    SplitPath(".", root, directory, fileName);
    EXPECT_EQ("", root);
    EXPECT_EQ(".", directory);
    EXPECT_EQ("", fileName);

    SplitPath("..", root, directory, fileName);
    EXPECT_EQ("", root);
    EXPECT_EQ("..", directory);
    EXPECT_EQ("", fileName);

    SplitPath("C:\\temp", root, directory, fileName);
    EXPECT_EQ("C:/", root);
    EXPECT_EQ("", directory);
    EXPECT_EQ("temp", fileName);

    SplitPath("C:\\temp\\", root, directory, fileName);
    EXPECT_EQ("C:/", root);
    EXPECT_EQ("temp", directory);
    EXPECT_EQ("", fileName);

    SplitPath("C:\\temp\\dir", root, directory, fileName);
    EXPECT_EQ("C:/", root);
    EXPECT_EQ("temp", directory);
    EXPECT_EQ("dir", fileName);

    SplitPath("C:\\temp\\\\dir", root, directory, fileName);
    EXPECT_EQ("C:/", root);
    EXPECT_EQ("temp", directory);
    EXPECT_EQ("dir", fileName);

    SplitPath("C:\\temp\\file.txt", root, directory, fileName);
    EXPECT_EQ("C:/", root);
    EXPECT_EQ("temp", directory);
    EXPECT_EQ("file.txt", fileName);

    SplitPath("/home/user", root, directory, fileName);
    EXPECT_EQ("/", root);
    EXPECT_EQ("home", directory);
    EXPECT_EQ("user", fileName);

    SplitPath("/home//user", root, directory, fileName);
    EXPECT_EQ("/", root);
    EXPECT_EQ("home", directory);
    EXPECT_EQ("user", fileName);
}

TEST(PathFunctionsTest, SplitPathRootParts)
{
    std::string rootPath;
    std::vector<std::string> parts;
    SplitPath("", rootPath, parts);
    EXPECT_EQ("", rootPath);
    EXPECT_EQ(std::vector<std::string>({}), parts);

    SplitPath("c:", rootPath, parts);
    EXPECT_EQ("C:", rootPath);
    EXPECT_EQ(std::vector<std::string>({}), parts);

    SplitPath("C:", rootPath, parts);
    EXPECT_EQ("C:", rootPath);
    EXPECT_EQ(std::vector<std::string>({}), parts);

    SplitPath("C:/", rootPath, parts);
    EXPECT_EQ("C:/", rootPath);
    EXPECT_EQ(std::vector<std::string>({}), parts);

    SplitPath("\\\\server", rootPath, parts);
    EXPECT_EQ("//server", rootPath);
    EXPECT_EQ(std::vector<std::string>({}), parts);

    SplitPath("\\\\server\\share", rootPath, parts);
    EXPECT_EQ("//server/share", rootPath);
    EXPECT_EQ(std::vector<std::string>({}), parts);

    SplitPath("temp", rootPath, parts);
    EXPECT_EQ("", rootPath);
    EXPECT_EQ(std::vector<std::string>({ "temp" }), parts);

    SplitPath(".", rootPath, parts);
    EXPECT_EQ("", rootPath);
    EXPECT_EQ(std::vector<std::string>({ "." }), parts);

    SplitPath("..", rootPath, parts);
    EXPECT_EQ("", rootPath);
    EXPECT_EQ(std::vector<std::string>({ ".." }), parts);

    SplitPath("C:\\temp", rootPath, parts);
    EXPECT_EQ("C:/", rootPath);
    EXPECT_EQ(std::vector<std::string>({ "temp" }), parts);

    SplitPath("C:\\temp\\", rootPath, parts);
    EXPECT_EQ("C:/", rootPath);
    EXPECT_EQ(std::vector<std::string>({ "temp" }), parts);

    SplitPath("C:\\temp\\dir", rootPath, parts);
    EXPECT_EQ("C:/", rootPath);
    EXPECT_EQ(std::vector<std::string>({ "temp", "dir" }), parts);

    SplitPath("C:\\temp\\\\dir", rootPath, parts);
    EXPECT_EQ("C:/", rootPath);
    EXPECT_EQ(std::vector<std::string>({ "temp", "dir" }), parts);

    SplitPath("/home/user", rootPath, parts);
    EXPECT_EQ("/", rootPath);
    EXPECT_EQ(std::vector<std::string>({ "home", "user" }), parts);

    SplitPath("/home//user", rootPath, parts);
    EXPECT_EQ("/", rootPath);
    EXPECT_EQ(std::vector<std::string>({ "home", "user" }), parts);
}

TEST(PathFunctionsTest, PathParts)
{
    EXPECT_EQ(std::vector<std::string>({ }), PathParts(""));
    EXPECT_EQ(std::vector<std::string>({ "C:" }), PathParts("C:"));
    EXPECT_EQ(std::vector<std::string>({ "C:/" }), PathParts("C:/"));
    EXPECT_EQ(std::vector<std::string>({ "//server" }), PathParts("\\\\server"));
    EXPECT_EQ(std::vector<std::string>({ "//server/share" }), PathParts("\\\\server\\share"));
    EXPECT_EQ(std::vector<std::string>({ "temp" }), PathParts("temp"));
    EXPECT_EQ(std::vector<std::string>({ "." }), PathParts("."));
    EXPECT_EQ(std::vector<std::string>({ ".." }), PathParts(".."));
    EXPECT_EQ(std::vector<std::string>({ "C:/", "temp" }), PathParts("C:\\temp"));
    EXPECT_EQ(std::vector<std::string>({ "C:/", "temp" }), PathParts("C:\\temp\\"));
    EXPECT_EQ(std::vector<std::string>({ "C:/", "temp", "dir" }), PathParts("C:\\temp\\dir"));
    EXPECT_EQ(std::vector<std::string>({ "C:/", "temp", "dir" }), PathParts("C:\\temp\\\\dir"));
    EXPECT_EQ(std::vector<std::string>({ "/", "home", "user" }), PathParts("/home/user"));
    EXPECT_EQ(std::vector<std::string>({ "/", "home", "user" }), PathParts("/home//user"));
}

TEST(PathFunctionsTest, JoinPaths)
{
    std::string result;
    EXPECT_TRUE(JoinPaths(result, "", ""));
    EXPECT_EQ("", result);

    EXPECT_TRUE(JoinPaths(result, "C:\\temp", "file.txt"));
    EXPECT_EQ("C:/temp/file.txt", result);

    EXPECT_TRUE(JoinPaths(result, "C:\\temp\\", "file.txt"));
    EXPECT_EQ("C:/temp/file.txt", result);

    EXPECT_TRUE(JoinPaths(result, "C:\\temp\\", "..\\file.txt"));
    EXPECT_EQ("C:/file.txt", result);

    EXPECT_TRUE(JoinPaths(result, "C:\\temp\\", ".\\file.txt"));
    EXPECT_EQ("C:/temp/file.txt", result);

    EXPECT_TRUE(JoinPaths(result, "C:\\temp\\", ".\\file.txt"));
    EXPECT_EQ("C:/temp/file.txt", result);

    EXPECT_TRUE(JoinPaths(result, "C:\\", "file.txt"));
    EXPECT_EQ("C:/file.txt", result);

    EXPECT_TRUE(JoinPaths(result, "C:\\temp\\file.txt", ""));
    EXPECT_EQ("C:/temp/file.txt", result);

    EXPECT_TRUE(JoinPaths(result, "/", "file.txt"));
    EXPECT_EQ("/file.txt", result);

    EXPECT_TRUE(JoinPaths(result, "/home", "file.txt"));
    EXPECT_EQ("/home/file.txt", result);

    EXPECT_TRUE(JoinPaths(result, "/home/", "file.txt"));
    EXPECT_EQ("/home/file.txt", result);

    EXPECT_TRUE(JoinPaths(result, "/home", "me/file.txt"));
    EXPECT_EQ("/home/me/file.txt", result);

    EXPECT_TRUE(JoinPaths(result, "C:", "file.txt"));
    EXPECT_EQ("C:file.txt", result);

    EXPECT_TRUE(JoinPaths(result, "/home", "me", "file.txt"));
    EXPECT_EQ("/home/me/file.txt", result);

    EXPECT_TRUE(JoinPaths(result, "C:\\", "temp", ".", "file.txt"));
    EXPECT_EQ("C:/temp/file.txt", result);
}

TEST(PathFunctionsTest, RelativePathRelativeToSameRoot)
{
    std::string path = "C:\\temp\\myfile.txt";
    std::string relativeTo = "C:\\";
    std::string expected = "temp/myfile.txt";
    EXPECT_EQ(expected, RelativePath(path, relativeTo));
}

TEST(PathFunctionsTest, RelativePathRelativeToSameDirectory)
{
    std::string path = "C:\\temp\\myfile.txt";
    std::string relativeTo = "C:\\temp";
    std::string expected = "myfile.txt";
    EXPECT_EQ(expected, RelativePath(path, relativeTo));
}

TEST(PathFunctionsTest, RelativePathRelativeToDifferentDirectory)
{
    std::string path = "C:\\other\\myfile.txt";
    std::string relativeTo = "C:\\temp";
    std::string expected = "../other/myfile.txt";
    EXPECT_EQ(expected, RelativePath(path, relativeTo));
}

TEST(PathFunctionsTest, RelativePathRelativeToDifferentDirectoryMultipleLevels)
{
    std::string path = "C:\\my\\other\\\\directory\\myfile.txt";
    std::string relativeTo = "C:\\my\\own\\directory";
    std::string expected = "../../other/directory/myfile.txt";
    EXPECT_EQ(expected, RelativePath(path, relativeTo));
}

TEST(PathFunctionsTest, RelativePathRelativeToDifferentDrive)
{
    std::string path = "C:\\other\\myfile.txt";
    std::string relativeTo = "D:\\temp";
    std::string expected = "C:/other/myfile.txt";
    EXPECT_EQ(expected, RelativePath(path, relativeTo));
}
} // namespace filesystem
