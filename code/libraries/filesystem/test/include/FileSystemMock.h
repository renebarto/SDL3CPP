//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : FileSystemMock.h
//
// Namespace   : filesystem
//
// Class       : FileSystemMock
//
// Description :
//
//------------------------------------------------------------------------------

#include "filesystem/IFileSystem.h"

#include "test-platform/GoogleMock.h"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::NaggyMock;

namespace filesystem {

class FileSystemMock
    : public IFileSystem
{
public:
    MOCK_METHOD(bool, OpenFile, (File& file, const std::string& path, OpenMode mode), (override));
    MOCK_METHOD(void, CloseFile, (File& file), (override));
    MOCK_METHOD(bool, FileIsOpen, (const File& file), (const, override));

    MOCK_METHOD(bool, Exists, (const std::string& path), (override));
    MOCK_METHOD(bool, Copy, (const std::string& source, const std::string& destination), (override));
    MOCK_METHOD(bool, Move, (const std::string& source, const std::string& destination), (override));
    MOCK_METHOD(bool, Remove, (const std::string& path), (override));
    MOCK_METHOD(bool, IsRegularFile, (const std::string& path), (override));
    MOCK_METHOD(bool, IsDirectory, (const std::string& path), (override));

    MOCK_METHOD(std::size_t, GetLine, (File& file, char* buffer, std::size_t numChars), (override));
    MOCK_METHOD(std::size_t, Read, (File& file, char* buffer, std::size_t numChars), (override));
    MOCK_METHOD(std::size_t, Write, (File& file, const char* buffer, std::size_t numChars), (override));

};

} // namespace filesystem
