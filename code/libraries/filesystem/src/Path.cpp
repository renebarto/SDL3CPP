//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Path.cpp
//
// Namespace   : filesystem
//
// Class       : Path
//
// Description :
//
//------------------------------------------------------------------------------

#include "filesystem/Path.h"

#include <iostream>
#include "filesystem/PathFunctions.h"

namespace filesystem
{

static const char PathSeparatorChar = '/';

Path::Path(const std::string & path)
    : m_path(NormalizePath(path))
{
}

Path::Path(const Path& other)
    : m_path{ other.m_path }
{
}

Path& Path::operator =(const Path& other)
{
    if (this != &other)
    {
        this->m_path = other.m_path;
    }
    return *this;
}

std::string Path::Get() const
{
    return m_path;
}

void Path::Append(const std::string& subPath)
{
    if (!m_path.empty() && (m_path[m_path.length() - 1] != PathSeparatorChar) && !subPath.empty() && (subPath[0] != PathSeparatorChar))
        m_path += PathSeparatorChar;
    m_path += subPath;
}

std::vector<std::string> Path::GetParts() const
{
    return PathParts(m_path);
}

bool Path::Equals(const Path& other) const
{
    return m_path == other.m_path;
}

Path operator / (const Path& path, const std::string& subPath)
{
    Path result(path);
    result.Append(subPath);
    return result;
}

Path Join(const Path& rootPath) noexcept
{
    return rootPath;
}

Path Join(const Path & rootPath, const std::string & subPath) noexcept
{
    return rootPath / subPath;
}

Path Join(const std::string& path) noexcept
{
    return Path(path);
}

Path Join(const std::string & path, const std::string & subPath) noexcept
{
    Path tmp(path);
    return tmp / subPath;
}

} // namespace filesystem
