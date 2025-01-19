//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : FileRotator.h
//
// Namespace   : filesystem
//
// Class       : FileRotator
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "filesystem/File.h"

namespace filesystem {

class FileRotatorPolicy
{
private:
    FileRotatorPolicyType m_type;

public:
    FileRotatorPolicy(FileRotatorPolicyType type);

    FileRotatorPolicy Type() const { return m_type; }
    virtual bool ShouldRotate(const File& file);
};

class FileRotatorPolicySize
    : public FileRotatorPolicy
{
private:
    using Size = std::ios_base::streampos;
    Size m_rotateSize;

public:
    FileRotatorPolicySize(Size rotatSize);

    bool ShouldRotate(const File& file) override;
};

class FileRotate;

class FileRotator
{
private:
    IFileSystem& m_fileSystem;

public:
    FileRotator(const Path& directory, const std::string& filePattern, const FileRotatorPolicy& policy);

    bool ShouldRotate(const FileRotate& file) const;
    bool RotateFile(FileRotate& file);
};

class FileRotate
    : public File
{
private:
    FileRotator m_fileRotator;

public:
    FileRotate(IFileSystem& fileSystem, const Path& directory, const std::string& filePattern, const FileRotatorPolicy& policy);

    std::size_t Write(const uint8_t* buffer, std::size_t numBytes);
    std::size_t Write(const std::vector<uint8_t> buffer, std::size_t numBytes);

    std::size_t WriteText(const char* buffer, std::size_t numChars);
    std::size_t WriteText(const std::string& text, std::size_t numChars);
    std::size_t WriteText(const std::string& text);
    std::size_t WriteLine(const std::string& text);
};

} // namespace filesystem
