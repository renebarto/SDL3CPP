//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Deserialization.h
//
// Namespace   : serialization
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <sstream>
#include <string>

namespace serialization {

template<class T>
typename std::enable_if<!std::is_enum<T>::value, bool>::type
Deserialize(const std::string& text, T & value)
{
    T t{};
    std::istringstream stream(text);
    stream >> t;
    if (!stream.bad())
    {
        value = t;
        return true;
    }
    return false;
}

} // namespace serialization
