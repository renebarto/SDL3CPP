//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : FileSystem.h
//
// Namespace   : filesystem
//
// Class       : FileSystem
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <ios>
#include "filesystem/IFileSystem.h"

namespace filesystem {

class FileSystem
    : public IFileSystem
{
public:
    bool OpenFile(File& file, const std::string& path, OpenMode mode) override;
    void CloseFile(File& file) override;
    bool FileIsOpen(const File& file) const override;

    bool Exists(const std::string& path) override;
    bool Copy(const std::string& source, const std::string& destination) override;
    bool Move(const std::string& source, const std::string& destination) override;
    bool Remove(const std::string& path) override;
    bool IsRegularFile(const std::string& path) override;
    bool IsDirectory(const std::string& path) override;

    std::size_t GetLine(File& file, char* buffer, std::size_t numChars) override;
    std::size_t Read(File& file, char* buffer, std::size_t numChars) override;
    std::size_t Write(File& file, const char* buffer, std::size_t numChars) override;
};

} // namespace filesystem
