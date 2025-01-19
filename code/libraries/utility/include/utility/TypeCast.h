//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TypeCast.h
//
// Namespace   : -
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

template <typename P>
typename std::enable_if<sizeof(P) == 1, uint8_t>::type CastToInteger(P value)
{
    return static_cast<uint8_t>(value);
}
template <typename P>
typename std::enable_if<sizeof(P) == 2, uint16_t>::type CastToInteger(P value)
{
    return static_cast<uint16_t>(value);
}
template <typename P>
typename std::enable_if<sizeof(P) == 4, uint32_t>::type CastToInteger(P value)
{
    return static_cast<uint32_t>(value);
}
template <typename P>
typename std::enable_if<sizeof(P) == 8, uint64_t>::type CastToInteger(P value)
{
    return static_cast<uint64_t>(value);
}
template <typename P>
typename std::enable_if<sizeof(P) == 4, uint32_t>::type CastPointerToInteger(P value)
{
    return reinterpret_cast<uint32_t>(value);
}
template <typename P>
typename std::enable_if<sizeof(P) == 8, uint64_t>::type CastPointerToInteger(P value)
{
    return reinterpret_cast<uint64_t>(value);
}
