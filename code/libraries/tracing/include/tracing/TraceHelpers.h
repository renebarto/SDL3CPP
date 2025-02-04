//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceHelpers.h
//
// Namespace   : tracing
//
// Class       : -
//
// Description : Tracing helper functions
//
//------------------------------------------------------------------------------

#pragma once

#include <string>

std::string ExtractFileName(const std::string& path);

#if defined(PLATFORM_WINDOWS)

#define __BASE_FILE__ std::string(__FILE__)
// Every compiled file (cpp) will create the next object. It passes it's name in
// the constructor: the gcc extension __BASE_FILE__ returns the name of the src file
#endif
