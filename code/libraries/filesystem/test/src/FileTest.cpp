//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : FileTest.cpp
//
// Namespace   : filesystem
//
// Class       : FileTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "filesystem/File.h"
#include "FileSystemMock.h"

#include "utility/Serialization.h"
#include "utility/StringFunctions.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::SaveArg;
using ::testing::Return;

namespace filesystem
{

class FileTest
    : public ::testing::Test
{

};

static Path s_path;
static std::string s_pathString;
static OpenMode s_openMode;

TEST_F(FileTest, ConstructDefault)
{
    FileSystemMock fileSystem;
    File file(fileSystem);

    EXPECT_CALL(fileSystem, IsRegularFile(_)).WillOnce(Return(false));

    EXPECT_FALSE(file.IsOpen());
    EXPECT_EQ(Path{}, file.GetPath());
    EXPECT_EQ(OpenMode{}, file.GetOpenMode());
    EXPECT_EQ(false, file.IsReadable());
    EXPECT_EQ(false, file.IsWritable());
    EXPECT_EQ(false, file.IsRegularFile());
    EXPECT_EQ(false, file.IsTextFile());
    EXPECT_EQ(false, file.IsBinaryFile());
}

TEST_F(FileTest, ConstructPath)
{
    FileSystemMock fileSystem;
    Path path("abc.txt");

    EXPECT_CALL(fileSystem, OpenFile(_, _, _)).WillOnce(DoAll(SaveArg<1>(&s_path), SaveArg<2>(&s_openMode), Return(true)));
    EXPECT_CALL(fileSystem, IsRegularFile(_)).WillOnce(Return(true));

    File file(fileSystem, path);
    EXPECT_EQ(path, s_path);
    EXPECT_EQ(OpenMode::Read, s_openMode);
    EXPECT_EQ(path, file.GetPath());
    EXPECT_EQ(OpenMode::Read, file.GetOpenMode());
    EXPECT_EQ(true, file.IsReadable());
    EXPECT_EQ(false, file.IsWritable());
    EXPECT_EQ(true, file.IsRegularFile());
    EXPECT_EQ(true, file.IsTextFile());
    EXPECT_EQ(false, file.IsBinaryFile());
}

TEST_F(FileTest, ConstructString)
{
    FileSystemMock fileSystem;
    std::string path("abc.txt");

    EXPECT_CALL(fileSystem, OpenFile(_, _, _)).WillOnce(DoAll(SaveArg<1>(&s_pathString), SaveArg<2>(&s_openMode), Return(true)));
    EXPECT_CALL(fileSystem, IsRegularFile(_)).WillOnce(Return(true));

    File file(fileSystem, path);
    EXPECT_EQ(path, s_pathString);
    EXPECT_EQ(OpenMode::Read, s_openMode);
    EXPECT_EQ(Path{ path }, file.GetPath());
    EXPECT_EQ(OpenMode::Read, file.GetOpenMode());
    EXPECT_EQ(true, file.IsReadable());
    EXPECT_EQ(false, file.IsWritable());
    EXPECT_EQ(true, file.IsRegularFile());
    EXPECT_EQ(true, file.IsTextFile());
    EXPECT_EQ(false, file.IsBinaryFile());
}

TEST_F(FileTest, OpenDefaultModeFails)
{
    FileSystemMock fileSystem;
    File file(fileSystem);

    EXPECT_CALL(fileSystem, OpenFile(_, _, _)).WillOnce(DoAll(SaveArg<1>(&s_path), SaveArg<2>(&s_openMode), Return(false)));
    EXPECT_CALL(fileSystem, IsRegularFile(_)).WillOnce(Return(false));

    Path path("abc.txt");
    EXPECT_FALSE(file.Open(path));
    EXPECT_EQ(path, s_path);
    EXPECT_EQ(OpenMode::Read, s_openMode);
    EXPECT_EQ(path, file.GetPath());
    EXPECT_EQ(OpenMode{}, file.GetOpenMode());
    EXPECT_EQ(false, file.IsReadable());
    EXPECT_EQ(false, file.IsWritable());
    EXPECT_EQ(false, file.IsRegularFile());
    EXPECT_EQ(false, file.IsTextFile());
    EXPECT_EQ(false, file.IsBinaryFile());
}

TEST_F(FileTest, OpenDefaultModePath)
{
    FileSystemMock fileSystem;
    File file(fileSystem);

    EXPECT_CALL(fileSystem, OpenFile(_, _, _)).WillOnce(DoAll(SaveArg<1>(&s_path), SaveArg<2>(&s_openMode), Return(true)));
    EXPECT_CALL(fileSystem, IsRegularFile(_)).WillOnce(Return(true));

    Path path("abc.txt");
    EXPECT_TRUE(file.Open(path));
    EXPECT_EQ(path, s_path);
    EXPECT_EQ(OpenMode::Read, s_openMode);
    EXPECT_EQ(Path{ path }, file.GetPath());
    EXPECT_EQ(OpenMode::Read, file.GetOpenMode());
    EXPECT_EQ(true, file.IsReadable());
    EXPECT_EQ(false, file.IsWritable());
    EXPECT_EQ(true, file.IsRegularFile());
    EXPECT_EQ(true, file.IsTextFile());
    EXPECT_EQ(false, file.IsBinaryFile());
}

TEST_F(FileTest, OpenDefaultModeString)
{
    FileSystemMock fileSystem;
    File file(fileSystem);

    EXPECT_CALL(fileSystem, OpenFile(_, _, _)).WillOnce(DoAll(SaveArg<1>(&s_pathString), SaveArg<2>(&s_openMode), Return(true)));
    EXPECT_CALL(fileSystem, IsRegularFile(_)).WillOnce(Return(true));

    std::string path("abc.txt");
    EXPECT_TRUE(file.Open(path));
    EXPECT_EQ(path, s_pathString);
    EXPECT_EQ(OpenMode::Read, s_openMode);
    EXPECT_EQ(Path{ path }, file.GetPath());
    EXPECT_EQ(OpenMode::Read, file.GetOpenMode());
    EXPECT_EQ(true, file.IsReadable());
    EXPECT_EQ(false, file.IsWritable());
    EXPECT_EQ(true, file.IsRegularFile());
    EXPECT_EQ(true, file.IsTextFile());
    EXPECT_EQ(false, file.IsBinaryFile());
}

TEST_F(FileTest, OpenSpecificMode)
{
    FileSystemMock fileSystem;
    File file(fileSystem);

    EXPECT_CALL(fileSystem, OpenFile(_, _, _)).WillOnce(DoAll(SaveArg<1>(&s_path), SaveArg<2>(&s_openMode), Return(true)));
    EXPECT_CALL(fileSystem, IsRegularFile(_)).WillOnce(Return(true));

    Path path("abc.txt");
    EXPECT_TRUE(file.Open(path, OpenMode::ReadWrite | OpenMode::Binary));
    EXPECT_EQ(path, s_path);
    EXPECT_EQ(OpenMode::ReadWrite | OpenMode::Binary, s_openMode);
    EXPECT_EQ(Path{ path }, file.GetPath());
    EXPECT_EQ(OpenMode::ReadWrite | OpenMode::Binary, file.GetOpenMode());
    EXPECT_EQ(true, file.IsReadable());
    EXPECT_EQ(true, file.IsWritable());
    EXPECT_EQ(true, file.IsRegularFile());
    EXPECT_EQ(false, file.IsTextFile());
    EXPECT_EQ(true, file.IsBinaryFile());
}

TEST_F(FileTest, OpenClose)
{
    FileSystemMock fileSystem;
    File file(fileSystem);

    EXPECT_CALL(fileSystem, OpenFile(_, _, _)).WillOnce(Return(true));
    EXPECT_CALL(fileSystem, CloseFile(_)).WillOnce(Return());
    EXPECT_CALL(fileSystem, IsRegularFile(_)).WillOnce(Return(false));

    Path path("abc.txt");
    EXPECT_TRUE(file.Open(path, OpenMode::ReadWrite | OpenMode::Binary));
    file.Close();
    EXPECT_EQ(path, file.GetPath());
    EXPECT_EQ(OpenMode{}, file.GetOpenMode());
    EXPECT_EQ(false, file.IsReadable());
    EXPECT_EQ(false, file.IsWritable());
    EXPECT_EQ(false, file.IsRegularFile());
    EXPECT_EQ(false, file.IsTextFile());
    EXPECT_EQ(false, file.IsBinaryFile());
}

TEST_F(FileTest, Exists)
{
    FileSystemMock fileSystem;

    EXPECT_CALL(fileSystem, OpenFile(_, _, _)).WillOnce(Return(true));
    EXPECT_CALL(fileSystem, Exists(_)).WillOnce(Return(true));

    Path path("abc.txt");
    File file(fileSystem, path);
    EXPECT_TRUE(file.Exists());
}

TEST_F(FileTest, CopyToPath)
{
    FileSystemMock fileSystem;

    EXPECT_CALL(fileSystem, OpenFile(_, _, _)).WillOnce(Return(true));
    EXPECT_CALL(fileSystem, CloseFile(_)).WillOnce(Return());
    EXPECT_CALL(fileSystem, Copy(_, _)).WillOnce(DoAll(SaveArg<1>(&s_path), Return(true)));

    Path path("abc.txt");
    Path destination("def.txt");
    File file(fileSystem, path);
    EXPECT_TRUE(file.Copy(destination));
    EXPECT_EQ(destination, s_path);
}

TEST_F(FileTest, CopyToString)
{
    FileSystemMock fileSystem;

    EXPECT_CALL(fileSystem, OpenFile(_, _, _)).WillOnce(Return(true));
    EXPECT_CALL(fileSystem, CloseFile(_)).WillOnce(Return());
    EXPECT_CALL(fileSystem, Copy(_, _)).WillOnce(DoAll(SaveArg<1>(&s_pathString), Return(true)));

    Path path("abc.txt");
    std::string destination("def.txt");
    File file(fileSystem, path);
    EXPECT_TRUE(file.Copy(destination));
    EXPECT_EQ(destination, s_pathString);
}

TEST_F(FileTest, MoveToPath)
{
    FileSystemMock fileSystem;

    EXPECT_CALL(fileSystem, OpenFile(_, _, _)).WillOnce(Return(true));
    EXPECT_CALL(fileSystem, CloseFile(_)).WillOnce(Return());
    EXPECT_CALL(fileSystem, Move(_, _)).WillOnce(DoAll(SaveArg<1>(&s_path), Return(true)));

    Path path("abc.txt");
    Path destination("def.txt");
    File file(fileSystem, path);
    EXPECT_TRUE(file.Move(destination));
    EXPECT_EQ(destination, s_path);
}

TEST_F(FileTest, MoveToString)
{
    FileSystemMock fileSystem;

    EXPECT_CALL(fileSystem, OpenFile(_, _, _)).WillOnce(Return(true));
    EXPECT_CALL(fileSystem, CloseFile(_)).WillOnce(Return());
    EXPECT_CALL(fileSystem, Move(_, _)).WillOnce(DoAll(SaveArg<1>(&s_pathString), Return(true)));

    Path path("abc.txt");
    std::string destination("def.txt");
    File file(fileSystem, path);
    EXPECT_TRUE(file.Move(destination));
    EXPECT_EQ(destination, s_pathString);
}

TEST_F(FileTest, Remove)
{
    FileSystemMock fileSystem;

    EXPECT_CALL(fileSystem, OpenFile(_, _, _)).WillOnce(Return(true));
    EXPECT_CALL(fileSystem, CloseFile(_)).WillOnce(Return());
    EXPECT_CALL(fileSystem, Remove(_)).WillOnce(DoAll(SaveArg<0>(&s_pathString), Return(true)));

    Path path("abc.txt");
    File file(fileSystem, path);
    EXPECT_TRUE(file.Remove());
    EXPECT_EQ(path, s_pathString);
}

} // namespace filesystem
