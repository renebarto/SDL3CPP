//---------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Regex.cpp
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

#include <osal/regex/Regex.h>

#include <regex>

namespace osal {

using Regex = std::basic_regex<char>;
#if WIDE_CHARS == 1
using Match = std::wsmatch;
using Iterator = std::wsregex_iterator;
#else
using Match = std::smatch;
using Iterator = std::sregex_iterator;
#endif

bool VerifyMatch(const std::string& stringToVerify, const std::string& regexString, bool usePOSIX)
{
    Regex matcher(regexString, (usePOSIX ? std::regex_constants::awk : std::regex_constants::ECMAScript));
    Match matchedCaptures;

    return std::regex_match(stringToVerify, matchedCaptures, matcher);
}

bool VerifyMatch(const std::string& stringToVerify, Matches& matches, const std::string& regexString, bool usePOSIX)
{
    Regex matcher(regexString, (usePOSIX ? std::regex_constants::awk : std::regex_constants::ECMAScript));
    Match matchedCaptures;

    auto result = std::regex_match(stringToVerify, matchedCaptures, matcher);
    matches.clear();
    if (result)
    {
        for (std::size_t i = 1; i < matchedCaptures.size(); ++i)
        {
            matches.push_back(matchedCaptures[i]);
        }
    }
    return result;
}

bool VerifyMatches(const std::string& stringToVerify, std::vector<Matches>& matches, const std::string& regexString, bool usePOSIX)
{
    Regex matcher(regexString, (usePOSIX ? std::regex_constants::awk : std::regex_constants::ECMAScript));
    auto begin = Iterator(stringToVerify.begin(), stringToVerify.end(), matcher);
    auto end = Iterator();
    matches.clear();
    for (auto it = begin; it != end; ++it)
    {
        Match matchedCaptures = *it;
        if (matchedCaptures.size() > 1)
        {
            Matches localMatches;
            for (std::size_t i = 1; i < matchedCaptures.size(); ++i)
            {
                localMatches.push_back(matchedCaptures[i]);
            }
            matches.push_back(localMatches);
        }
    }
    return !matches.empty();
}

} // namespace osal
