//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : PathFunctions.h
//
// Namespace   : filesystem
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>

namespace filesystem
{

std::string NormalizePath(const std::string & path);
bool HasDrive(const std::string & path);
void SplitPath(const std::string & path, std::string & root, std::string & directory, std::string & fileName);
void SplitPath(const std::string & path, std::string & rootPath, std::vector<std::string> & parts);
std::vector<std::string> PathParts(const std::string & path);
std::string RelativePath(const std::string & path, const std::string & relativeTo);
std::string AbsolutePath(const std::string & path);
bool JoinPaths(std::string & result, const std::string & root, const std::string & subPath);
bool JoinPaths(std::string & result, const std::vector<std::string> & parts);
template <typename ... Args>
bool JoinPaths(std::string & result, const std::string & root, const std::string & subPath, Args const & ... args)
{
    std::string tempPath;
    if (!JoinPaths(tempPath, root, subPath))
        return false;
    return JoinPaths(result, tempPath, args ...);
}

} // namespace filesystem
