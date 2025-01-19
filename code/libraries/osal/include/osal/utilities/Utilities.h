//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Utilities.h
//
// Namespace   : osal
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <cstdint>

#if defined(PLATFORM_WINDOWS)
#elif defined(PLATFORM_LINUX)
#include <byteswap.h>
#else
#error Unsupported platform
#endif

namespace osal {

template<class T> T SwapBytes(T value);

template<> inline int8_t SwapBytes<int8_t>(int8_t value)
{
    return value;
}
template<> inline uint8_t SwapBytes<uint8_t>(uint8_t value)
{
    return value;
}
template<> inline int16_t SwapBytes<int16_t>(int16_t value)
{
#if defined(PLATFORM_WINDOWS)
    return static_cast<int16_t>(_byteswap_ushort(static_cast<uint16_t>(value)));
#else
    return static_cast<int16_t>(bswap_16(value));
#endif
}
template<> inline uint16_t SwapBytes<uint16_t>(uint16_t value)
{
#if defined(PLATFORM_WINDOWS)
    return _byteswap_ushort(value);
#else
    return bswap_16(value);
#endif
}
template<> inline int32_t SwapBytes<int32_t>(int32_t value)
{
#if defined(PLATFORM_WINDOWS)
    return static_cast<int32_t>(_byteswap_ulong(static_cast<uint32_t>(value)));
#else
    return static_cast<int32_t>(bswap_32(value));
#endif
}
template<> inline uint32_t SwapBytes<uint32_t>(uint32_t value)
{
#if defined(PLATFORM_WINDOWS)
    return _byteswap_ulong(value);
#else
    return bswap_32(value);
#endif
}
template<> inline int64_t SwapBytes<int64_t>(int64_t value)
{
#if defined(PLATFORM_WINDOWS)
    return static_cast<int64_t>(_byteswap_uint64(static_cast<uint64_t>(value)));
#else
    return static_cast<int64_t>(bswap_64(value));
#endif
}
template<> inline uint64_t SwapBytes<uint64_t>(uint64_t value)
{
#if defined(PLATFORM_WINDOWS)
    return _byteswap_uint64(value);
#else
    return bswap_64(value);
#endif
}

#if !defined (PLATFORM_LINUX)
template<> inline unsigned long SwapBytes<unsigned long>(unsigned long value)
{
    return SwapBytes<uint32_t>(value);
}
#endif

} // namespace osal
