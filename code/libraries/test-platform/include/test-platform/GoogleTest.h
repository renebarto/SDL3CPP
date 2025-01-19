//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : GoogleTest.h
//
// Namespace   : -
//
// Class       : -
//
// Description :
//      Google Test inclusion header
//
//------------------------------------------------------------------------------

#pragma once

#include <iostream>

//TICS -PRE-POR#021 We suppress warnings for Windows only
#if defined (PLATFORM_WINDOWS)
#pragma warning(disable: 4826) //TICS !POR#018 !POR#037 !PRE-POR#037 Suppress compilation warnings on GoogleTest for Windows only
#pragma warning(disable: 4868) //TICS !POR#018 !POR#037 !PRE-POR#037 Suppress compilation warnings on GoogleTest for Windows only
#pragma warning(disable: 4355) //TICS !POR#018 !POR#037 !PRE-POR#037 Suppress compilation warnings on GoogleTest for Windows only
#endif
#include "gtest/gtest.h"
#if defined (PLATFORM_WINDOWS)
#pragma warning(default: 4826) //TICS !POR#018 !POR#037 !PRE-POR#037 Suppress compilation warnings on GoogleTest for Windows only
#pragma warning(default: 4868) //TICS !POR#018 !POR#037 !PRE-POR#037 Suppress compilation warnings on GoogleTest for Windows only
#pragma warning(default: 4355) //TICS !POR#018 !POR#037 !PRE-POR#037 Suppress compilation warnings on GoogleTest for Windows only
#endif
//TICS +PRE-POR#021

#define EXPECT_NULL(a) EXPECT_TRUE(nullptr == (a))
#define EXPECT_NOT_NULL(a) EXPECT_FALSE(nullptr == (a))
#define ASSERT_NULL(a) ASSERT_TRUE(nullptr == (a))
#define ASSERT_NOT_NULL(a) ASSERT_FALSE(nullptr == (a))
