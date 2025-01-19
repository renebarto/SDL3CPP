//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : PlatformDefines.cpp
//
// Namespace   : osal
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "osal/utilities/PlatformDefines.h"

namespace osal {

#if defined(PLATFORM_WINDOWS)

const std::string EndOfLine = "\r\n";

#elif defined(PLATFORM_LINUX)

const std::string EndOfLine = "\n";

#else
#error Unsupported platform
#endif

} // namespace osal
