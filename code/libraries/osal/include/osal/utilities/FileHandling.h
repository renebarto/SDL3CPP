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

#pragma once

#include <cstdio>

#if defined(PLATFORM_WINDOWS)

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

typedef int FileDescriptor;
constexpr FileDescriptor InvalidHandle = static_cast<FileDescriptor>(-1);

#else

#include <unistd.h>

typedef int FileDescriptor;
constexpr FileDescriptor InvalidHandle = static_cast<FileDescriptor>(-1);

#endif

FileDescriptor GetFileDescriptor(FILE * file);
bool IsTTY(int fd);
