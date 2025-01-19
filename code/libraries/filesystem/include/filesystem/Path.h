//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Path.h
//
// Namespace   : filesystem
//
// Class       : Path
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>

namespace filesystem
{

class Path;

Path Join(const Path& rootPath) noexcept;
Path Join(const Path& rootPath, const std::string& subPath) noexcept;

template <typename ... Args>
Path Join(const Path& rootPath, const std::string& subPath, Args const& ... args);

Path Join(const std::string& path) noexcept;
Path Join(const std::string& path, const std::string& subPath) noexcept;

template<typename ... Args>
Path Join(const std::string& path, const std::string subPath, Args ...subPaths);

class Path
{
private:
    std::string m_path;

public:
    Path() = default;
    Path(const Path&);
    explicit Path(const std::string& path);
    template <typename ... Args>
    Path(const std::string& path, Args const& ... args) noexcept
        : Path(Join(path, args ...))
    {
    }
    Path& operator =(const Path&);

    void Append(const std::string& subPath);
    std::string Get() const;
    bool Equals(const Path& other) const;

    std::vector<std::string> GetParts() const;
};

Path operator / (const Path& path, const std::string& subPath);
inline bool operator == (const Path& lhs, const Path& rhs) { return lhs.Equals(rhs); }
inline bool operator != (const Path& lhs, const Path& rhs) { return !lhs.Equals(rhs); }

template <typename ... Args>
Path Join(const Path& rootPath, const std::string& subPath, Args const& ... args)
{
    Path joinedPath = rootPath / subPath;
    return Join(joinedPath, args ...);
}

template<typename ... Args>
Path Join(const std::string& path, const std::string subPath, Args ...subPaths)
{
    Path result(path);
    return Join(result, subPath, subPaths ...);
}

} // namespace filesystem
