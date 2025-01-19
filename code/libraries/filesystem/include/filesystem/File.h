//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : File.h
//
// Namespace   : filesystem
//
// Class       : File
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <fstream>
#include <ios>
#include "filesystem/Path.h"
#include "filesystem/IFileSystem.h"

namespace filesystem {

class IFileSystem;
class FileSystem;

class File
{
private:
    IFileSystem& m_fileSystem;
    OpenMode m_mode;
    Path m_path;
    std::fstream m_stream;

public:
    using Direction = std::ios_base::seekdir;
    File(IFileSystem& fileSystem);
    File(IFileSystem& fileSystem, const std::string& path, OpenMode mode = OpenMode::Read);
    File(IFileSystem& fileSystem, const Path& path, OpenMode mode = OpenMode::Read);
    virtual ~File();

    bool Open(const std::string& path, OpenMode mode = OpenMode::Read);
    bool Open(const Path& path, OpenMode mode = OpenMode::Read);
    void Close();

    const Path& GetPath() const;
    OpenMode GetOpenMode() const;
    bool IsOpen() const;
    bool IsReadable() const;
    bool IsWritable() const;
    bool IsTextFile() const;
    bool IsBinaryFile() const;

    bool Exists() const;

    bool Copy(File& destination);
    bool Copy(const std::string& destination);
    bool Copy(const Path& destination);

    bool Move(File& destination);
    bool Move(const std::string& destination);
    bool Move(const Path& destination);

    bool Remove();

    bool IsRegularFile();

    // Binary file operations
    std::size_t Read(uint8_t* buffer, std::size_t numBytes);
    std::size_t Read(std::vector<uint8_t> buffer, std::size_t numBytes);
    std::size_t Write(const uint8_t* buffer, std::size_t numBytes);
    std::size_t Write(const std::vector<uint8_t> buffer, std::size_t numBytes);
    std::size_t Position() const;
    std::size_t Size();
    bool SetPosition(std::streampos position) const;
    bool SetPosition(std::streamoff offset, Direction direction) const;

    // Text file operations
    std::size_t ReadText(char* buffer, std::size_t numChars);
    std::size_t ReadText(std::string& text, std::size_t numChars);
    std::size_t ReadText(std::string& text);
    std::size_t ReadLine(std::string& text);
    std::size_t WriteText(const char* buffer, std::size_t numChars);
    std::size_t WriteText(const std::string& text, std::size_t numChars);
    std::size_t WriteText(const std::string& text);
    std::size_t WriteLine(const std::string& text);

    friend class FileSystem;
};

} // namespace filesystem
