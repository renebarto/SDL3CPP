//---------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Assert.h
//
// Namespace   : osal
//
// Class       : -
//
// Description : Assert handler
//
//---------------------------------------------------------------

#pragma once

#include <functional>

namespace osal
{
    using AssertHandler = std::function<void (bool expression, const char* expressionText, const char* file, int line, const char* func)>;

    extern void InternalAssertionHandler(bool expression, const char* expressionText, const char* file, int line, const char* func);
    extern AssertHandler SetAssertionHandler(AssertHandler handler);

} // namespace osal

#define ASSERT(expression) \
osal::InternalAssertionHandler(expression, #expression, __FILE__, __LINE__, __func__)
