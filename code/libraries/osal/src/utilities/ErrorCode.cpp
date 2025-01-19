//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ErrorCode.cpp
//
// Namespace   : osal
//
// Class       : ErrorCode
//
// Description :
//
//------------------------------------------------------------------------------

#include "osal/utilities/ErrorCode.h"

#include <cstring>

#if defined(PLATFORM_LINUX)

// #include <unistd.h>

#elif defined(PLATFORM_WINDOWS)

#if _MSC_VER > 1900 // Versions after VS 2015
#pragma warning(disable: 5039)
#endif
#include <windows.h>
#if _MSC_VER > 1900 // Versions after VS 2015
#pragma warning(default: 5039)
#endif

#else

#error "Unsupported platform"

#endif

namespace osal {

int GetErrorCode()
{
#if defined(PLATFORM_LINUX)

    return errno;

#else

    return static_cast<int>(GetLastError());

#endif
}

std::string GetErrorDescription(int errorCode)
{
#if defined(PLATFORM_LINUX)

    return Convert(strerror(errorCode));

#else

    if (errorCode == 0) {
        return std::string("Success"); // No error message has been recorded
    }
    
    char * messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 nullptr, static_cast<DWORD>(errorCode), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, nullptr);
    
    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);
    
    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
            
    return message;

#endif
}

std::string ErrorCode::Description() const
{
    return GetErrorDescription(m_errorCode);
}

} // namespace osal
