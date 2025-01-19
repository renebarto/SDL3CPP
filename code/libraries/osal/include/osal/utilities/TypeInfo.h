//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TypeInfo.h
//
// Class       : osal
//
// Description : Type information functions
//
//------------------------------------------------------------------------------

#pragma once

#include <string>
#include <typeinfo>

namespace osal {

std::string demangle(const char* name);

template <class T>
std::string type(const T& t)
{
#if defined (PLATFORM_WINDOWS)
    (void)t; // Windows will otherwise issue warning
#endif
    std::string name = demangle(typeid(t).name());
    // strip type qualifier "class " from the name
    const std::string classPrefix = "class ";
    auto classPrefixIndex = name.find(classPrefix);
    if (classPrefixIndex != std::string::npos)
        return name.substr(classPrefixIndex + classPrefix.length());
    return name;
}

} // namespace osal
