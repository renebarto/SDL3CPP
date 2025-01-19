//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Environment.cpp
//
// Namespace   : osal
//
// Class       : Environment
//
// Description :
//
//------------------------------------------------------------------------------

#include "osal/utilities/Environment.h"

#if defined(PLATFORM_WINDOWS)

#if _MSC_VER > 1900 // Versions after VS 2015
#pragma warning(disable: 5039)
#endif
#include <windows.h>
#if _MSC_VER > 1900 // Versions after VS 2015
#pragma warning(default: 5039)
#endif

#else
#include <cstdlib>
#endif

namespace osal {

const char* Environment::Get(const char* name)
{
#if defined(PLATFORM_WINDOWS)
    static char buffer[4096];
    if (::GetEnvironmentVariableA(name, buffer, sizeof(buffer)) == 0)
    {
        return nullptr;
    }
    return buffer;
#else
    return ::getenv(name);
#endif
}

int Environment::Set(const char* name, const char* value, bool overwrite)
{
#if defined(PLATFORM_WINDOWS)
    static char buffer[4096];
    if (!overwrite && ::GetEnvironmentVariableA(name, buffer, sizeof(buffer)) != 0)
        return 0;
    return ::SetEnvironmentVariableA(name, value) ? 0 : EINVAL;
#else
    return ::setenv(name, value, overwrite ? 1 : 0);
#endif
}

int Environment::Unset(const char* name)
{
#if defined(PLATFORM_WINDOWS)
    return ::SetEnvironmentVariableA(name, nullptr) ? 0 : EINVAL;
#else
    return ::unsetenv(name);
#endif
}

} // namespace osal
