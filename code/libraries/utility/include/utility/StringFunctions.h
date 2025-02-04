//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : StringFunctions.h
//
// Namespace   : utility
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>

namespace utility {

std::string Trim(const std::string& value, const std::string& stripChars);

std::string TrimSpaces(const std::string& value);

std::string TrimLeft(const std::string& value, const std::string& stripChars);

std::string TrimSpacesLeft(const std::string& value);

std::string TrimRight(const std::string& value, const std::string& stripChars);

std::string TrimSpacesRight(const std::string& value);

std::vector<std::string> Split(const std::string& text, char delimiter);

inline bool IsEqual(const std::string& lhs, const std::string& rhs)
{
    return lhs == rhs;
}

inline bool IsEqualIgnoreCase(const std::string& lhs, const std::string& rhs)
{
    return (lhs.length() == rhs.length()) &&
        std::equal(lhs.begin(), lhs.end(), rhs.begin(),
                      [](char a, char b) {
                          return std::tolower(a) == std::tolower(b);
                      });
}

std::string ToLower(const std::string& text);

std::string ToUpper(const std::string& text);

std::string Quote(const std::string& text);

std::string UnQuote(const std::string& text);

} // namespace utility
