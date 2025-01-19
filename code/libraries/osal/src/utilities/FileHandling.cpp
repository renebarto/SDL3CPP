//---------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : FileHandling.h
//
// Namespace   : osal
//
// Class       : -
//
// Description :
//
//---------------------------------------------------------------

#include "osal/utilities/FileHandling.h"

#include <cstdlib>

#if defined(PLATFORM_WINDOWS)
#if _MSC_VER > 1900 // Versions after VS 2015
#pragma warning(disable: 5039)
#endif
#include <windows.h>
#if _MSC_VER > 1900 // Versions after VS 2015
#pragma warning(default: 5039)
#endif
#include <io.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

FileDescriptor GetFileDescriptor(FILE * file)
{
    return ::_fileno(file);
}
bool IsTTY(int fd)
{
    return ::_isatty(fd) != 0;
}

#else

FileDescriptor GetFileDescriptor(FILE * file)
{
    return ::fileno(file);
}
bool IsTTY(int fd)
{
    return ::isatty(fd) != 0;
}

#endif
