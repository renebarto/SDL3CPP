//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : FileSystem.cpp
//
// Namespace   : filesystem
//
// Class       : FileSystem
//
// Description :
//
//------------------------------------------------------------------------------

#include "filesystem/FileSystem.h"

#include <filesystem>
#include "filesystem/File.h"

namespace filesystem {

std::ios_base::openmode ConvertMode(OpenMode mode)
{
    std::ios_base::openmode result;

    if ((mode & OpenMode::Append) != filesystem::OpenMode::None)
    {
        result |= std::ios_base::app;
    }
    if ((mode & OpenMode::AtEnd) != filesystem::OpenMode::None)
    {
        result |= std::ios_base::ate;
    }
    if ((mode & OpenMode::Truncate) != filesystem::OpenMode::None)
    {
        result |= std::ios_base::trunc;
    }
    if ((mode & OpenMode::Binary) != filesystem::OpenMode::None)
    {
        result |= std::ios_base::binary;
    }
    if ((mode & OpenMode::Write) != filesystem::OpenMode::None)
    {
        result |= std::ios_base::out;
    }
    if ((mode & OpenMode::Read) != filesystem::OpenMode::None)
    {
        result |= std::ios_base::in;
    }
    if (mode == OpenMode::None)
    {
        result = std::ios_base::in;
    }
    return result;
}

bool FileSystem::OpenFile(File& file, const std::string& path, OpenMode mode)
{
    bool result{};
    if (FileIsOpen(file))
        CloseFile(file);
    try
    {
        file.m_stream.open(path, ConvertMode(mode));
        result = FileIsOpen(file);
    }
    catch (std::exception&)
    {
        result = false;
    }
    return result;
}

void FileSystem::CloseFile(File& file)
{
    try
    {
        file.m_stream.close();
    }
    catch (std::exception&)
    {
    }
}

bool FileSystem::FileIsOpen(const File& file) const
{
    return file.m_stream.is_open();
}

bool FileSystem::Exists(const std::string& path)
{
    std::error_code errorCode{};
    auto result = std::filesystem::exists(std::filesystem::path(path), errorCode);
    return result && (errorCode.value() == 0);
}

bool FileSystem::Copy(const std::string& source, const std::string& destination)
{
    std::error_code errorCode{};
    std::filesystem::copy(std::filesystem::path(source), std::filesystem::path(destination), errorCode);
    return errorCode.value() == 0;
}

bool FileSystem::Move(const std::string& source, const std::string& destination)
{
    std::error_code errorCode{};
    std::filesystem::rename(std::filesystem::path(source), std::filesystem::path(destination), errorCode);
    return errorCode.value() == 0;
}

bool FileSystem::Remove(const std::string& path)
{
    std::error_code errorCode{};
    std::filesystem::remove(std::filesystem::path(path), errorCode);
    return errorCode.value() == 0;
}

bool FileSystem::IsRegularFile(const std::string& path)
{
    std::error_code errorCode{};
    auto result = std::filesystem::is_regular_file(std::filesystem::path(path), errorCode);
    return result && (errorCode.value() == 0);
}

std::size_t FileSystem::Read(File& /*file*/, char* /*buffer*/, std::size_t /*numChars*/)
{
    return {};
}

std::size_t FileSystem::Write(File& /*file*/, const char* /*buffer*/, std::size_t /*numChars*/)
{
    return {};
}

} // namespace filesystem
