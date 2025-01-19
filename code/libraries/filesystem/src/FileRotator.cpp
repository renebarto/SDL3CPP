//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : FileRotator.cpp
//
// Namespace   : filesystem
//
// Class       : FileRotator
//
// Description :
//
//------------------------------------------------------------------------------

#include "filesystem/FileRotator.h"

#include "filesystem/IFileSystem.h"

namespace filesystem {

FileRotate::FileRotate(IFileSystem& fileSystem, const Path& directory, const std::string& filePattern, const FileRotatorPolicy& policy);

std::size_t FileRotate::Write(const uint8_t* buffer, std::size_t numBytes);
std::size_t FileRotate::Write(const std::vector<uint8_t> buffer, std::size_t numBytes);

std::size_t FileRotate::WriteText(const char* buffer, std::size_t numChars);
std::size_t FileRotate::WriteText(const std::string& text, std::size_t numChars);
std::size_t FileRotate::WriteText(const std::string& text)
{
    if (m_fileRotator.ShouldRotate(*this))
    {
        Close();
        m_fileRotator.RotateFile();
        Open(m_basePath, OpenMode::Write);
    }
    return File::WriteLine(text);
}

std::size_t FileRotate::WriteLine(const std::string& text)
{
    return File::WriteLine(text);
}

} // namespace filesystem
