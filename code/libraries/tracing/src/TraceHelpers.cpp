//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceHelpers.cpp
//
// Namespace   : tracing
//
// Class       : -
//
// Description : Tracing helper functions
//
//------------------------------------------------------------------------------

#include "tracing/TraceHelpers.h"

#include "filesystem/PathFunctions.h"
#include "tracing/TraceRegistryItem.h"

static const char ForwardSlashChar = '/';

std::string ExtractFileName(const std::string& path)
{
    std::string convertedPath = filesystem::NormalizePath(path);
    return convertedPath.substr(convertedPath.rfind(ForwardSlashChar) + 1u);
}

DEFINE_TRACE_ENTRY();
