//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : EndianTest.cpp
//
// Namespace   : utility
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "utility/Endian.h"

namespace utility {

TEST(EndianTest, PlatformEndianness)
{
    EXPECT_EQ(Endianness::LittleEndian, PlatformEndianness());
}

TEST(EndianTest, ToNetworkByteOrder)
{
    EXPECT_EQ(0x12, ToNetworkByteOrder(int8_t {0x12}));
    EXPECT_EQ(0x12, ToNetworkByteOrder(uint8_t {0x12}));
    EXPECT_EQ(0x3412, ToNetworkByteOrder(int16_t {0x1234}));
    EXPECT_EQ(0x3412, ToNetworkByteOrder(uint16_t {0x1234}));
    EXPECT_EQ(0x78563412, ToNetworkByteOrder(int32_t {0x12345678}));
    EXPECT_EQ(0x78563412u, ToNetworkByteOrder(uint32_t {0x12345678}));
    EXPECT_EQ(static_cast<int64_t>(0xEFCDAB8967452301ll), ToNetworkByteOrder(int64_t {0x0123456789ABCDEF}));
    EXPECT_EQ(0xEFCDAB8967452301ull, ToNetworkByteOrder(uint64_t {0x0123456789ABCDEF}));
}

TEST(EndianTest, FromNetworkByteOrder)
{
    EXPECT_EQ(0x12, FromNetworkByteOrder(int8_t {0x12}));
    EXPECT_EQ(0x12, FromNetworkByteOrder(uint8_t {0x12}));
    EXPECT_EQ(0x3412, FromNetworkByteOrder(int16_t {0x1234}));
    EXPECT_EQ(0x3412, FromNetworkByteOrder(uint16_t {0x1234}));
    EXPECT_EQ(0x78563412, FromNetworkByteOrder(int32_t {0x12345678}));
    EXPECT_EQ(0x78563412u, FromNetworkByteOrder(uint32_t {0x12345678}));
    EXPECT_EQ(static_cast<int64_t>(0xEFCDAB8967452301ll), FromNetworkByteOrder(int64_t {0x0123456789ABCDEF}));
    EXPECT_EQ(0xEFCDAB8967452301ull, FromNetworkByteOrder(uint64_t {0x0123456789ABCDEF}));
}

} // namespace utility
