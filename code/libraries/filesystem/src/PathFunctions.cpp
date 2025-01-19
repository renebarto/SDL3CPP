//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : PathFunctions.cpp
//
// Namespace   : filesystem
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "filesystem/PathFunctions.h"

#include "utility/StringFunctions.h"
#include <algorithm>
#include <cctype>
#include <iostream>

// TICS -PRE-POR#021 We suppress warnings for Windows only
#if defined(PLATFORM_LINUX)

#include <limits.h>

#else

#endif
// TICS +PRE-POR#021

namespace filesystem {

static const char ForwardSlashChar = '/';
static const char BackSlashChar = '\\';

std::string NormalizePath(const std::string &path)
{
    auto normalizedPath = path;
    std::replace(normalizedPath.begin(), normalizedPath.end(), BackSlashChar, ForwardSlashChar);
    return normalizedPath;
}

static void SplitDirectory(const std::string &path, std::string &directory, std::string &fileName)
{
    // No guarantee that these are initialize before this function is called, so put them inside the function.
    // Function is called why static compilation unit set up is performed
    static const std::string CurrentDirString = ".";
    static const std::string ParentDirString = "..";

    auto pathParts = utility::Split(path, ForwardSlashChar);
    directory = {};
    fileName = {};
    for (auto it = pathParts.begin(); it != pathParts.end(); ++it)
    {
        auto part = *it;
        if (it == pathParts.end() - 1)
        {
            if ((part == CurrentDirString) || (part == ParentDirString))
            {
                if (!directory.empty())
                    directory += ForwardSlashChar;
                directory += part;
            }
            else
            {
                fileName = part;
            }
        }
        else if (!part.empty())
        {
            if (!directory.empty())
                directory += ForwardSlashChar;
            directory += part;
        }
    }
    if (!directory.empty() && (directory[directory.length() - 1] == ForwardSlashChar))
        directory = directory.substr(0, directory.length() - 1);
}

bool HasDrive(const std::string &path)
{
    return (path.length() >= 2) && std::isalpha(path[0]) && (path[1] == ':');
}

void SplitPath(const std::string &path, std::string &root, std::string &directory, std::string &fileName)
{
    auto normalizedPath = NormalizePath(path);
    root = {};
    directory = {};
    fileName = {};
    if (HasDrive(normalizedPath))
    {
        // Have root C: or C:/
        root = utility::ToUpper(normalizedPath.substr(0, 2));
        normalizedPath = normalizedPath.substr(2);
    }
    if ((normalizedPath.length() >= 1) && (normalizedPath[0] == ForwardSlashChar))
    {
        // Have UNC?
        if ((normalizedPath.length() >= 2) && (normalizedPath[1] == ForwardSlashChar))
        {
            // UNC path, so root //server/share or //server
            auto firstSlashPos = normalizedPath.find(ForwardSlashChar, 2);
            if (firstSlashPos != std::string::npos)
            {
                // UNC path with root //server/share
                auto nextSlashPos = normalizedPath.find(ForwardSlashChar, firstSlashPos + 1);
                if (nextSlashPos != std::string::npos)
                {
                    // Have additional slash, terminate root
                    root += normalizedPath.substr(0, nextSlashPos);
                    normalizedPath = normalizedPath.substr(nextSlashPos);
                }
                else
                {
                    // Complete string is root
                    root += normalizedPath;
                    normalizedPath = {};
                }
            }
            else
            {
                // UNC path with root //server
                root += normalizedPath;
                normalizedPath = {};
            }
        }
        else
        {
            // Absolute path directory
            root += normalizedPath[0];
            normalizedPath = normalizedPath.substr(1);
        }
    }
    SplitDirectory(normalizedPath, directory, fileName);
}

void SplitPath(const std::string &path, std::string &rootPath, std::vector<std::string> &parts)
{
    rootPath = {};
    parts.clear();
    if (path.empty())
        return;

    std::string directory;
    std::string fileName;

    SplitPath(path, rootPath, directory, fileName);

    if (directory.empty() && fileName.empty())
        return;

    auto pathParts = utility::Split(directory, ForwardSlashChar);
    for (auto const &item : pathParts)
    {
        if (!item.empty())
            parts.push_back(item);
    }
    if (!fileName.empty())
        parts.push_back(fileName);
}

std::vector<std::string> PathParts(const std::string &path)
{
    std::vector<std::string> result;
    if (path.empty())
        return result;

    std::string root;
    std::string directory;
    std::string fileName;

    SplitPath(path, root, directory, fileName);

    if (!root.empty())
        result.push_back(root);

    auto pathParts = utility::Split(directory, ForwardSlashChar);
    for (auto const &item : pathParts)
    {
        if (!item.empty())
            result.push_back(item);
    }
    if (!fileName.empty())
        result.push_back(fileName);

    return result;
}

std::string RelativePath(const std::string &path, const std::string &relativeTo)
{
    auto pathNormalized = NormalizePath(path);
    auto relativeToAbsolute = NormalizePath(relativeTo);

    std::string rootPath;
    std::string rootPathRelativeTo;
    std::vector<std::string> pathParts;
    std::vector<std::string> pathPartsRelativeTo;

    SplitPath(pathNormalized, rootPath, pathParts);
    SplitPath(relativeToAbsolute, rootPathRelativeTo, pathPartsRelativeTo);

    if (!rootPath.empty() && (rootPath != rootPathRelativeTo))
        return pathNormalized;

    std::size_t index = 0;
    while ((index < pathParts.size()) && (index < pathPartsRelativeTo.size()) &&
           (pathParts[index] == pathPartsRelativeTo[index]))
        ++index;

    std::string result;
    for (std::size_t i = index; i < pathPartsRelativeTo.size(); ++i)
    {
        if (!result.empty())
            result += ForwardSlashChar;
        result += "..";
    }
    for (std::size_t i = index; i < pathParts.size(); ++i)
    {
        if (!result.empty())
            result += ForwardSlashChar;
        result += pathParts[i];
    }
    return result;
}

std::string FullPath(const std::string &path)
{
    std::string result;
#if defined(PLATFORM_LINUX)
    char absolutePath[PATH_MAX];
    if (nullptr == realpath(path.c_str(), absolutePath))
        return {};
    result = absolutePath;
#else
    char absolutePath[_MAX_PATH];
    if (nullptr == _fullpath(absolutePath, path.c_str(), sizeof(absolutePath)))
        return {};
    result = absolutePath;
#endif
    return result;
}

std::string AbsolutePath(const std::string &path)
{
    return NormalizePath(FullPath(path));
}

bool JoinPaths(std::string &result, const std::string &root, const std::string &subPath)
{
    result = {};

    if (HasDrive(root) && HasDrive(subPath))
    {
        result = NormalizePath(subPath);
        return true;
    }

    std::string rootPath;
    std::vector<std::string> rootParts;
    SplitPath(root, rootPath, rootParts);
    std::string subPathRootPath;
    std::vector<std::string> subPathParts;
    SplitPath(subPath, subPathRootPath, subPathParts);
    if (!subPathParts.empty())
    {
        while ((subPathParts.size() > 0) && (subPathParts[0] == ".."))
        {
            if (rootParts.size() > 0)
            {
                rootParts.erase(rootParts.end() - 1);
                subPathParts.erase(subPathParts.begin());
            }
            else
            {
                // No parent to go to
                return false;
            }
        }
        while ((subPathParts.size() > 0) && (subPathParts[0] == "."))
        {
            subPathParts.erase(subPathParts.begin());
        }
    }

    for (auto const &item : rootParts)
    {
        if (!result.empty())
            result += ForwardSlashChar;
        result += item;
    }
    for (auto const &item : subPathParts)
    {
        if (!result.empty())
            result += ForwardSlashChar;
        result += item;
    }
    // Prefix with root, do not do this in advance otherwise a relative directory will become a root
    result = rootPath + result;
    return true;
}

bool JoinPaths(std::string &result, const std::vector<std::string> &parts)
{
    result = {};
    if (parts.empty())
        return false;
    std::string tempResult = parts[0];
    for (std::size_t index = 1; index < parts.size(); ++index)
    {
        JoinPaths(result, tempResult, parts[index]);
        tempResult = result;
    }

    return true;
}

} // namespace filesystem
