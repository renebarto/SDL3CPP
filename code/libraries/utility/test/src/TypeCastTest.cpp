//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TypeCastTest.cpp
//
// Namespace   : utility
//
// Class       : TypeCastTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "utility/TypeCast.h"

namespace utility {

TEST(TypeCastTest, CastToInteger8bits) {
    int8_t value = 123;
    EXPECT_EQ(uint8_t{ 123 }, CastToInteger(value));
}

TEST(TypeCastTest, CastToInteger16bits) {
    int16_t value = 12345;
    EXPECT_EQ(uint16_t{ 12345 }, CastToInteger(value));
}

TEST(TypeCastTest, CastToInteger32bits) {
    int32_t value = 12345678;
    EXPECT_EQ(uint32_t{ 12345678 }, CastToInteger(value));
}

TEST(TypeCastTest, CastToInteger64bits) {
    int64_t value = 1234567890123;
    EXPECT_EQ(uint64_t{ 1234567890123 }, CastToInteger(value));
}

#if defined(PLATFORM_WINDOWS)
#pragma warning(disable: 4127)
#endif
TEST(TypeCastTest, CastPointerToInteger) {
    if (sizeof(void*) == 4)
    {
        void* p = reinterpret_cast<void*>(int32_t{ 12345678 });
        EXPECT_EQ(uint32_t{ 12345678 }, CastPointerToInteger(p));
    }
    else
    {
        void* p = reinterpret_cast<void*>(int32_t{ 12345678 });
        EXPECT_EQ(uint64_t{ 12345678 }, CastPointerToInteger(p));
    }
}
#if defined(PLATFORM_WINDOWS)
#pragma warning(default: 4127)
#endif

} // namespace utility
