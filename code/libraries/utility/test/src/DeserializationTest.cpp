//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : DeserializationTest.cpp
//
// Namespace   : serialization
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "utility/Deserialization.h"

namespace serialization {

TEST(DeserializationTest, DeserializeBool)
{
    bool expected = true;
    bool actual {};
    EXPECT_TRUE(Deserialize("true", actual));
    EXPECT_EQ(expected, actual);

    expected = false;
    EXPECT_TRUE(Deserialize("FaLsE", actual));
    EXPECT_EQ(expected, actual);

    EXPECT_FALSE(Deserialize("abcd", actual));
    EXPECT_FALSE(Deserialize("1234", actual));
}

TEST(DeserializationTest, DeserializeInt8)
{
    int8_t expected = 127;
    int8_t actual {};
    EXPECT_TRUE(Deserialize("127", actual));
    EXPECT_EQ(expected, actual);

    expected = 0x55;
    EXPECT_TRUE(Deserialize("55", actual, 16));
    EXPECT_EQ(expected, actual);

    EXPECT_FALSE(Deserialize("xyz", actual));
    EXPECT_FALSE(Deserialize("1234", actual));
}

TEST(DeserializationTest, DeserializeUInt8)
{
    uint8_t expected = 254;
    uint8_t actual {};
    EXPECT_TRUE(Deserialize("254", actual));
    EXPECT_EQ(expected, actual);

    expected = 0xab;
    EXPECT_TRUE(Deserialize("aB", actual, 16));
    EXPECT_EQ(expected, actual);

    EXPECT_FALSE(Deserialize("xyz", actual));
    EXPECT_FALSE(Deserialize("1234", actual));
}

TEST(DeserializationTest, DeserializeInt16)
{
    int16_t expected = 12345;
    int16_t actual {};
    EXPECT_TRUE(Deserialize("12345", actual));
    EXPECT_EQ(expected, actual);

#if defined(PLATFORM_WINDOWS)
    #pragma warning(disable : 4309)
#endif
    expected = static_cast<int16_t>(0xabcd);
#if defined(PLATFORM_WINDOWS)
    #pragma warning(default : 4309)
#endif
    EXPECT_TRUE(Deserialize("aBcD", actual, 16));
    EXPECT_EQ(expected, actual);

    EXPECT_FALSE(Deserialize("xyz", actual));
    EXPECT_FALSE(Deserialize("54321", actual));
}

TEST(DeserializationTest, DeserializeUInt16)
{
    uint16_t expected = 54321;
    uint16_t actual {};
    EXPECT_TRUE(Deserialize("54321", actual));
    EXPECT_EQ(expected, actual);

    expected = 0xabcd;
    EXPECT_TRUE(Deserialize("aBcD", actual, 16));
    EXPECT_EQ(expected, actual);

    EXPECT_FALSE(Deserialize("xyz", actual));
    EXPECT_FALSE(Deserialize("654321", actual));
}

TEST(DeserializationTest, DeserializeInt32)
{
    int32_t expected = 12345678;
    int32_t actual {};
    EXPECT_TRUE(Deserialize("12345678", actual));
    EXPECT_EQ(expected, actual);

    expected = static_cast<int32_t>(0x7bcdefef);
    EXPECT_TRUE(Deserialize("7BcDEfeF", actual, 16));
    EXPECT_EQ(expected, actual);

    // Depending on platform, this conversion with fail and return 0 or succeed
    // On Windows 64-bit and ARM platforms it fails
    // On Linux 64 bit it succeeds
    auto result = Deserialize("aBcDEfeF", actual, 16);
    if (result)
        expected = -1412567057;
    else
        expected = 0;
    EXPECT_EQ(expected, actual);

    EXPECT_FALSE(Deserialize("xyz", actual));
    EXPECT_FALSE(Deserialize("FFFFFFFFF", actual));
}

TEST(DeserializationTest, DeserializeUInt32)
{
    uint32_t expected = 4000000000u;
    uint32_t actual {};
    EXPECT_TRUE(Deserialize("4000000000", actual));
    EXPECT_EQ(expected, actual);

    expected = 0xabcdefef;
    EXPECT_TRUE(Deserialize("aBcDeFeF", actual, 16));
    EXPECT_EQ(expected, actual);

    EXPECT_FALSE(Deserialize("xyz", actual));
    EXPECT_FALSE(Deserialize("FFFFFFFFF", actual));
}

TEST(DeserializationTest, DeserializeInt64)
{
    int64_t expected = 987654321;
    int64_t actual {};
    EXPECT_TRUE(Deserialize("987654321", actual));
    EXPECT_EQ(expected, actual);

    expected = 0x7edcba9876543210;
    EXPECT_TRUE(Deserialize("7EdCbA9876543210", actual, 16));
    EXPECT_EQ(expected, actual);

    expected = 0;
    EXPECT_FALSE(Deserialize("fEdCbA9876543210", actual, 16));
    EXPECT_EQ(expected, actual);

    EXPECT_FALSE(Deserialize("xyz", actual));
    EXPECT_FALSE(Deserialize("FFFFFFFFFFFFFFFFF", actual));
}

TEST(DeserializationTest, DeserializeUInt64)
{
    uint64_t expected = 9223372036854775808ULL;
    uint64_t actual {};
    EXPECT_TRUE(Deserialize("9223372036854775808", actual));
    EXPECT_EQ(expected, actual);

    expected = 0xfedcba9876543210;
    EXPECT_TRUE(Deserialize("fEdCbA9876543210", actual, 16));
    EXPECT_EQ(expected, actual);

    EXPECT_FALSE(Deserialize("xyz", actual));
    EXPECT_FALSE(Deserialize("FFFFFFFFFFFFFFFFF", actual));
}

TEST(DeserializationTest, DeserializeFloat)
{
    float expected = 1002;
    float actual {};
    EXPECT_TRUE(Deserialize("1.002E+03", actual));
    EXPECT_NEAR(expected, actual, 0.0F);

    expected = 5.0E-37F;
    EXPECT_TRUE(Deserialize("5e-37", actual));
    EXPECT_NEAR(expected, actual, 0.0F);

    EXPECT_FALSE(Deserialize("xyz", actual));
}

TEST(DeserializationTest, DeserializeDouble)
{
    double expected = 1000002;
    double actual {};
    EXPECT_TRUE(Deserialize("1.000002E+06", actual));
    EXPECT_NEAR(expected, actual, 0.0);

    expected = 1e-200;
    EXPECT_TRUE(Deserialize("1e-200", actual));
    EXPECT_NEAR(expected, actual, 0.0);

    EXPECT_FALSE(Deserialize("xyz", actual));
}

TEST(DeserializationTest, DeserializeString)
{
    std::string expected = "Hello World";
    std::string actual {};
    EXPECT_TRUE(Deserialize("Hello World", actual));
    EXPECT_EQ(expected, actual);
}

TEST(DeserializationTest, DeserializeBinaryBool)
{
    bool value {};
    std::vector<uint8_t> buffer = { 0x01, 0x00 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset));
    EXPECT_EQ(std::size_t {1}, offset);
    EXPECT_EQ(true, value);
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_TRUE(false == value);
}

TEST(DeserializationTest, DeserializeBinaryInt8)
{
    int8_t value {};
    std::vector<uint8_t> buffer = { 123 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(123, value);
}

TEST(DeserializationTest, DeserializeBinaryUInt8)
{
    uint8_t value {};
    std::vector<uint8_t> buffer = { 234 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(234, value);
}

TEST(DeserializationTest, DeserializeBinaryInt16LittleEndian)
{
    int16_t value {};
    std::vector<uint8_t> buffer = { 0x34, 0x12 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::LittleEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(0x1234, value);
}

TEST(DeserializationTest, DeserializeBinaryInt16BigEndian)
{
    int16_t value {};
    std::vector<uint8_t> buffer = { 0x12, 0x34 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::BigEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(0x1234, value);
}

TEST(DeserializationTest, DeserializeBinaryUInt16LittleEndian)
{
    uint16_t value {};
    std::vector<uint8_t> buffer = { 0x65, 0x87 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::LittleEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(0x8765, value);
}

TEST(DeserializationTest, DeserializeBinaryUInt16BigEndian)
{
    uint16_t value {};
    std::vector<uint8_t> buffer = { 0x87, 0x65 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::BigEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(0x8765, value);
}

TEST(DeserializationTest, DeserializeBinaryInt32LittleEndian)
{
    int32_t value {};
    std::vector<uint8_t> buffer = { 0x78, 0x56, 0x34, 0x12 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::LittleEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(0x12345678, value);
}

TEST(DeserializationTest, DeserializeBinaryInt32BigEndian)
{
    int32_t value {};
    std::vector<uint8_t> buffer = { 0x12, 0x34, 0x56, 0x78 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::BigEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(0x12345678, value);
}

TEST(DeserializationTest, DeserializeBinaryUInt32LittleEndian)
{
    uint32_t value {};
    std::vector<uint8_t> buffer = { 0x21, 0x43, 0x65, 0x87 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::LittleEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(0x87654321U, value);
}

TEST(DeserializationTest, DeserializeBinaryUInt32BigEndian)
{
    uint32_t value {};
    std::vector<uint8_t> buffer = { 0x87, 0x65, 0x43, 0x21 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::BigEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(0x87654321U, value);
}

TEST(DeserializationTest, DeserializeBinaryInt64LittleEndian)
{
    int64_t value {};
    std::vector<uint8_t> buffer = { 0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::LittleEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(0x0123456789ABCDEFLL, value);
}

TEST(DeserializationTest, DeserializeBinaryInt64BigEndian)
{
    int64_t value {};
    std::vector<uint8_t> buffer = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::BigEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(0x0123456789ABCDEFLL, value);
}

TEST(DeserializationTest, DeserializeBinaryUInt64LittleEndian)
{
    uint64_t value {};
    std::vector<uint8_t> buffer = { 0x10, 0x32, 0x54, 0x76, 0x98, 0xBA, 0xDC, 0xFE };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::LittleEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(0xFEDCBA9876543210LLU, value);
}

TEST(DeserializationTest, DeserializeBinaryUInt64BigEndian)
{
    uint64_t value {};
    std::vector<uint8_t> buffer = { 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::BigEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ(0xFEDCBA9876543210LLU, value);
}

TEST(DeserializationTest, DeserializeBinaryFloatLittleEndian)
{
    float value {};
    std::vector<uint8_t> buffer = { 0x00, 0x00, 0x00, 0x3F };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::LittleEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_NEAR(0.5F, value, 0.0F);
}

TEST(DeserializationTest, DeserializeBinaryFloatBigEndian)
{
    float value {};
    std::vector<uint8_t> buffer = { 0x3F, 0x00, 0x00, 0x00 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::BigEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_NEAR(0.5F, value, 0.0F);
}

TEST(DeserializationTest, DeserializeBinaryDoubleLittleEndian)
{
    double value {};
    std::vector<uint8_t> buffer = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x3F };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::LittleEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_NEAR(0.5, value, 0.0);
}

TEST(DeserializationTest, DeserializeBinaryDoubleBigEndian)
{
    double value {};
    std::vector<uint8_t> buffer = { 0x3F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::BigEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_NEAR(0.5, value, 0.0);
}

TEST(DeserializationTest, DeserializeBinaryStringLittleEndian)
{
    std::string value {};
    std::vector<uint8_t> buffer = { 
        0x0C, 0x00, 0x00, 0x00, 0x48, 0x65, 0x6C, 0x6C, 
        0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21
    };

    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::LittleEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ("Hello World!", value);
}

TEST(DeserializationTest, DeserializeBinaryStringBigEndian)
{
    std::string value {};
    std::vector<uint8_t> buffer = { 
        0x00, 0x00, 0x00, 0x0C, 0x48, 0x65, 0x6C, 0x6C, 
        0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21
    };
    std::size_t offset = 0;
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::BigEndian));
    EXPECT_EQ(offset, buffer.size());
    EXPECT_EQ("Hello World!", value);
}

namespace {

    enum class TestBool : uint16_t
    {
        True, // = 0
        False // = 1
    };

}

TEST(DeserializationTest, DeserializeBinaryEnumLittleEndian)
{
    std::vector<uint8_t> buffer = { 0x00, 0x00, 0x01, 0x00};
    std::size_t offset = 0;
    TestBool value {};
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::LittleEndian));
    EXPECT_EQ(TestBool::True, value);
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::LittleEndian));
    EXPECT_EQ(TestBool::False, value);
    EXPECT_EQ(buffer.size(), offset);
}

TEST(DeserializationTest, DeserializeBinaryEnumBigEndian)
{
    std::vector<uint8_t> buffer = { 0x00, 0x00, 0x00, 0x01};
    std::size_t offset = 0;
    TestBool value {};
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::BigEndian));
    EXPECT_EQ(TestBool::True, value);
    EXPECT_TRUE(DeserializeBinary(value, buffer, offset, utility::Endianness::BigEndian));
    EXPECT_EQ(TestBool::False, value);
    EXPECT_EQ(buffer.size(), offset);
}

} // namespace serialization
