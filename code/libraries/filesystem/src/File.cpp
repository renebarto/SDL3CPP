//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : File.cpp
//
// Namespace   : filesystem
//
// Class       : File
//
// Description :
//
//------------------------------------------------------------------------------

#include "filesystem/File.h"

#include "osal/utilities/PlatformDefines.h"
#include "filesystem/IFileSystem.h"

namespace filesystem {

File::File(IFileSystem& fileSystem)
    : m_fileSystem{ fileSystem }
    , m_mode{}
    , m_path{}
    , m_stream{}
{

}
    
File::File(IFileSystem& fileSystem, const std::string& path, OpenMode mode)
    : m_fileSystem{ fileSystem }
    , m_mode{}
    , m_path{ m_path }
    , m_stream{}
{
    Open(path, mode);
}

File::File(IFileSystem& fileSystem, const Path& path, OpenMode mode)
    : m_fileSystem{ fileSystem }
    , m_mode{}
    , m_path{ m_path }
    , m_stream{}
{
    Open(path, mode);
}

File::~File()
{
}


bool File::Open(const std::string& path, OpenMode mode)
{
    auto result = m_fileSystem.OpenFile(*this, path, mode);
    if (result)
    {
        m_mode = mode;
        m_path = path;
    }
    return result;
}

bool File::Open(const Path& path, OpenMode mode)
{
    if (IsOpen())
        Close();
    m_path = path;
    auto result = m_fileSystem.OpenFile(*this, path, mode);
    if (result)
    {
        m_mode = mode;
    }
    return result;
}

void File::Close()
{
    m_fileSystem.CloseFile(*this);
    m_mode = {};
}

const Path& File::GetPath() const
{
    return m_path;
}

OpenMode File::GetOpenMode() const
{
    return m_mode;
}

bool File::IsOpen() const
{
    return m_mode != OpenMode::None;
}

bool File::IsReadable() const
{
    return ((static_cast<int>(m_mode) & static_cast<int>(OpenMode::Read)) != 0);
}

bool File::IsWritable() const
{
    return ((static_cast<int>(m_mode) & static_cast<int>(OpenMode::Write)) != 0);
}

bool File::IsTextFile() const
{
    return ((static_cast<int>(m_mode) & static_cast<int>(OpenMode::Binary)) == 0) && (m_mode != OpenMode::None);
}

bool File::IsBinaryFile() const
{
    return ((static_cast<int>(m_mode) & static_cast<int>(OpenMode::Binary)) != 0);
}

bool File::Exists() const
{
    return m_fileSystem.Exists(m_path);
}

bool File::Copy(File& destination)
{
    if (destination.IsOpen())
        destination.Close();
    return Copy(destination.m_path);
}

bool File::Copy(const std::string& destination)
{
    if (IsOpen())
        Close();
    return m_fileSystem.Copy(m_path.Get(), destination);
}

bool File::Copy(const Path& destination)
{
    return Copy(destination.Get());
}

bool File::Move(File& destination)
{
    if (destination.IsOpen())
        destination.Close();
    return Move(destination.m_path);
}
bool File::Move(const std::string& destination)
{
    if (IsOpen())
        Close();
    return m_fileSystem.Move(m_path.Get(), destination);
}

bool File::Move(const Path& destination)
{
    return Move(destination.Get());
}

bool File::Remove()
{
    if (IsOpen())
        Close();
    return m_fileSystem.Remove(m_path.Get());
}

bool File::IsRegularFile()
{
    return m_fileSystem.IsRegularFile(m_path.Get());
}

std::size_t File::ReadText(char* buffer, std::size_t numChars)
{
    return m_fileSystem.Read(*this, buffer, numChars);
}

std::size_t File::ReadText(std::string& text, std::size_t numChars)
{
    std::vector<char> buffer;
    buffer.reserve(numChars);
    auto charsRead = m_fileSystem.Read(*this, buffer.data(), numChars);
    text = std::string(buffer.data(), charsRead);
    return charsRead;
}

std::size_t File::ReadText(std::string& text)
{
    const std::size_t BufferSize = 4096;
    std::vector<char> buffer;
    buffer.reserve(BufferSize);
    std::size_t charsRead{};
    std::size_t totalCharsRead{};
    text = {};
    do
    {
        charsRead = m_fileSystem.Read(*this, buffer.data(), BufferSize);
        text += std::string(buffer.data(), charsRead);
        totalCharsRead += charsRead;
    } while (charsRead > 0);
    return totalCharsRead;

}

std::size_t File::ReadLine(std::string& text)
{
    (void)text;
    return {};
}

std::size_t File::WriteText(const char* buffer, std::size_t numChars)
{
    return m_fileSystem.Write(*this, buffer, numChars);
}

std::size_t File::WriteText(const std::string& text, std::size_t numChars)
{
    return WriteText(text.c_str(), numChars);
}

std::size_t File::WriteText(const std::string& text)
{
    return WriteText(text, text.length());
}

std::size_t File::WriteLine(const std::string& text)
{
    return WriteText(text + osal::EndOfLine);
}

} // namespace filesystem
