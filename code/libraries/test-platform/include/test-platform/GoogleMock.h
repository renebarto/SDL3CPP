//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : GoogleMock.h
//
// Namespace   : -
//
// Class       : -
//
// Description :
//      Google Mock inclusion header
//
//------------------------------------------------------------------------------

#pragma once

//TICS -PRE-POR#021 We suppress warnings for Windows only
#if defined (PLATFORM_WINDOWS)
#pragma warning(disable: 4365) //TICS !POR#018 !POR#037 !PRE-POR#037 Suppress compilation warnings on GoogleMock for Windows only
#pragma warning(disable: 4623) //TICS !POR#018 !POR#037 !PRE-POR#037 Suppress compilation warnings on GoogleMock for Windows only
#endif
#include "gmock/gmock.h"
#if defined (PLATFORM_WINDOWS)
#pragma warning(default: 4365) //TICS !POR#018 !POR#037 !PRE-POR#037 Suppress compilation warnings on GoogleMock for Windows only
#pragma warning(default: 4623) //TICS !POR#018 !POR#037 !PRE-POR#037 Suppress compilation warnings on GoogleMock for Windows only
#endif
//TICS +PRE-POR#021
