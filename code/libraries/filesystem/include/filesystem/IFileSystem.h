//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : IFileSystem.h
//
// Namespace   : filesystem
//
// Class       : IFileSystem
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "filesystem/Path.h"
#include "serialization/EnumSerialization.h"

namespace filesystem {

class File;

enum class OpenMode
{
    None = 0,
    Read = 1,
    Write = 2,
    ReadWrite = 3,
    Binary = 4,
    AtEnd = 8,
    Append = 16,
    Truncate = 32,
};
inline OpenMode operator |(OpenMode lhs, OpenMode rhs)
{
    return static_cast<OpenMode>(static_cast<std::underlying_type_t<OpenMode>>(lhs) | static_cast<std::underlying_type_t<OpenMode>>(rhs));
}
inline OpenMode operator &(OpenMode lhs, OpenMode rhs)
{
    return static_cast<OpenMode>(static_cast<std::underlying_type_t<OpenMode>>(lhs) & static_cast<std::underlying_type_t<OpenMode>>(rhs));
}

class IFileSystem
{
public:
    virtual ~IFileSystem() = default;

    bool OpenFile(File& file, const Path& path, OpenMode mode) { return OpenFile(file, path.Get(), mode); }
    virtual bool OpenFile(File& file, const std::string& path, OpenMode mode) = 0;
    virtual void CloseFile(File& file) = 0;
    virtual bool FileIsOpen(const File& file) const = 0;

    bool Exists(const Path& path) { return Exists(path.Get()); }
    virtual bool Exists(const std::string& path) = 0;
    bool Copy(const Path& source, const Path& destination) { return Copy(source.Get(), destination.Get()); }
    virtual bool Copy(const std::string& source, const std::string& destination) = 0;
    bool Move(const Path& source, const Path& destination) { return Move(source.Get(), destination.Get()); }
    virtual bool Move(const std::string& source, const std::string& destination) = 0;
    bool Remove(const Path& path) { return Remove(path.Get()); }
    virtual bool Remove(const std::string& path) = 0;
    bool IsRegularFile(const Path& path) { return IsRegularFile(path.Get()); }
    virtual bool IsRegularFile(const std::string& path) = 0;
    bool IsDirectory(const Path& path) { return IsDirectory(path.Get()); }
    virtual bool IsDirectory(const std::string& path) = 0;

    virtual std::size_t GetLine(File& file, char* buffer, std::size_t numChars) = 0;
    virtual std::size_t Read(File& file, char* buffer, std::size_t numChars) = 0;
    virtual std::size_t Write(File& file, const char* buffer, std::size_t numChars) = 0;
};

inline std::ostream& operator << (std::ostream& stream, const filesystem::OpenMode& value)
{
    std::string result;
    if ((value & filesystem::OpenMode::Append) != filesystem::OpenMode::None)
    {
        result = "Append";
    }
    if ((value & filesystem::OpenMode::AtEnd) != filesystem::OpenMode::None)
    {
        if (!result.empty())
            result += "|";
        result += "AtEnd";
    }
    if ((value & filesystem::OpenMode::Truncate) != filesystem::OpenMode::None)
    {
        if (!result.empty())
            result += "|";
        result += "Truncate";
    }
    if ((value & filesystem::OpenMode::Binary) != filesystem::OpenMode::None)
    {
        if (!result.empty())
            result += "|";
        result += "Binary";
    }
    if ((value & filesystem::OpenMode::Write) != filesystem::OpenMode::None)
    {
        if (!result.empty())
            result += "|";
        result += "Write";
    }
    if ((value & filesystem::OpenMode::Read) != filesystem::OpenMode::None)
    {
        if (!result.empty())
            result += "|";
        result += "Read";
    }
    if (value == filesystem::OpenMode::None)
    {
        result = "Read";
    }
    return stream << result;
}

} // namespace filesystem
