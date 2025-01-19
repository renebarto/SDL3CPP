//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TypeInfo.cpp
//
// Namespace   : osal
//
// Class       : -
//
// Description : Type info functions
//
//------------------------------------------------------------------------------

#include "osal/utilities/TypeInfo.h"

#if defined(PLATFORM_LINUX)
#include <cxxabi.h>
#include <cstdlib>
#include <memory>
#endif

namespace osal {

// Implementations (GNU and other) for demangle function used in the "type" method that returns the name of a class
// Class names are passed on to fatal and log functions as additional debug info

#if defined(PLATFORM_LINUX)

std::string demangle(const char* name)
 {
    int status {};
    std::unique_ptr<char, void(*)(void*)> res
    {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };
    return (status == 0) ? Convert(res.get()) : Convert(name);
}

#else
// For VS2019, the link qualifier is also added to the type name, so we need to strip this if it exists.
std::string demangle(const char* name) {
    std::string result = name;
    const std::string callingConvention = "__cdecl";
    auto pos = result.find(callingConvention);
    if (pos != std::string::npos)
    {
        result = result.substr(0, pos) + result.substr(pos + callingConvention.length());
    }
    return result;
}

#endif

} // namespace osal
