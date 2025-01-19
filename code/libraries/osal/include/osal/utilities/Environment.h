//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Environment.h
//
// Namespace   : osal
//
// Class       : Environment
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

namespace osal {

class Environment
{
public:
    static const char *Get(const char* name);
    static int Set(const char* name, const char* value, bool overwrite = true);
    static int Unset(const char* name);
};

} // namespace osal
