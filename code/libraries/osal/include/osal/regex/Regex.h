//---------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Regex.h
//
// Namespace   : osal
//
// Class       : -
//
// Description :
//  Regular expression matches
//  Needed as long as older WindRiver compiler is used
//
//---------------------------------------------------------------

#pragma once

#include <string>
#include <vector>

namespace osal {

using Matches = std::vector<std::string>;
bool VerifyMatch(const std::string& stringToVerify, const std::string& regexString, bool usePOSIX = false);
bool VerifyMatch(const std::string& stringToVerify, Matches& matches, const std::string& regexString, bool usePOSIX = false);
bool VerifyMatches(const std::string& stringToVerify, std::vector<Matches>& matches, const std::string& regexString, bool usePOSIX = false);

} // namespace osal
