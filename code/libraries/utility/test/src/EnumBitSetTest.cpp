//------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 René Barto
//
// File        : EnumBitSetTest.cpp
//
// Namespace   : utility
//
// Class       : -
//
// Description :
//  EnumBitSet tests
//
//---------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include <string>
#include "utility/EnumBitSet.h"

enum class DummyBits : uint8_t
{
    Bit0 = 0x01,
    Bit1 = 0x02,
    Bit2 = 0x04,
    Bit3 = 0x08,
    Bit4 = 0x10,
    Bit5 = 0x20,
    Bit6 = 0x40,
    Bit7 = 0x80,
};
std::vector<DummyBits> EnumDummyBits()
{
    return serialization::EnumSerializationMap<DummyBits>::GetKeys();
}

namespace utility {

TEST(EnumBitSetTest, ConstructDefault)
{
    EnumBitSet<DummyBits> set;
    for (auto const& bits : EnumDummyBits())
    {
        EXPECT_FALSE(set.IsSet(bits));
    }
}

TEST(EnumBitSetTest, Construct)
{
    EnumBitSet<DummyBits> set(DummyBits::Bit0);
    for (auto const& bits : EnumDummyBits())
    {
        if (bits != DummyBits::Bit0)
            EXPECT_FALSE(set.IsSet(bits));
        else
            EXPECT_TRUE(set.IsSet(bits));
    }
}

TEST(EnumBitSetTest, ConstructMaskNone)
{
    EnumBitSet<DummyBits> set(0x00);
    for (auto const& bits : EnumDummyBits())
    {
        EXPECT_FALSE(set.IsSet(bits));
    }
}

TEST(EnumBitSetTest, ConstructMaskAll)
{
    EnumBitSet<DummyBits> set(0xFF);
    for (auto const& bits : EnumDummyBits())
    {
        EXPECT_TRUE(set.IsSet(bits));
    }
}

TEST(EnumBitSetTest, ConstructMaskOnlyBit0)
{
    EnumBitSet<DummyBits> set(0x01);
    for (auto const& bits : EnumDummyBits())
    {
        if (bits != DummyBits::Bit0)
            EXPECT_FALSE(set.IsSet(bits));
        else
            EXPECT_TRUE(set.IsSet(bits));
    }
}

TEST(EnumBitSetTest, Set)
{
    EnumBitSet<DummyBits> set;
    set.Set(DummyBits::Bit1);
    set.Set(DummyBits::Bit2);
    for (auto const& bits : EnumDummyBits())
    {
        if ((bits != DummyBits::Bit1) && (bits != DummyBits::Bit2))
            EXPECT_FALSE(set.IsSet(bits));
        else
            EXPECT_TRUE(set.IsSet(bits));
    }
}

TEST(EnumBitSetTest, Reset)
{
    EnumBitSet<DummyBits> set(0xFF);
    set.Reset(DummyBits::Bit1);
    set.Reset(DummyBits::Bit2);
    for (auto const& bits : EnumDummyBits())
    {
        if ((bits != DummyBits::Bit1) && (bits != DummyBits::Bit2))
            EXPECT_TRUE(set.IsSet(bits));
        else
            EXPECT_FALSE(set.IsSet(bits));
    }
}

TEST(EnumBitSetTest, GetMask)
{
    EnumBitSet<DummyBits> set(DummyBits::Bit1 | DummyBits::Bit2);
    uint8_t actual = set.GetMask();
    uint8_t expected = static_cast<uint8_t>(DummyBits::Bit1) | static_cast<uint8_t>(DummyBits::Bit2);
    EXPECT_EQ(expected, actual);
}

TEST(EnumBitSetTest, ClassOperatorOr)
{
    EnumBitSet<DummyBits> set;
    set |= DummyBits::Bit1;
    set |= DummyBits::Bit2;
    for (auto const& bits : EnumDummyBits())
    {
        if ((bits != DummyBits::Bit1) && (bits != DummyBits::Bit2))
            EXPECT_FALSE(set.IsSet(bits));
        else
            EXPECT_TRUE(set.IsSet(bits));
    }
}

TEST(EnumBitSetTest, OperatorOrSetCategory)
{
    EnumBitSet<DummyBits> set;
    set = set | DummyBits::Bit1;
    set = set | DummyBits::Bit2;
    for (auto const& bits : EnumDummyBits())
    {
        if ((bits != DummyBits::Bit1) && (bits != DummyBits::Bit2))
            EXPECT_FALSE(set.IsSet(bits));
        else
            EXPECT_TRUE(set.IsSet(bits));
    }
}

TEST(EnumBitSetTest, OperatorOrCategoryCategory)
{
    EnumBitSet<DummyBits> set = DummyBits::Bit1 | DummyBits::Bit2;
    for (auto const& bits : EnumDummyBits())
    {
        if ((bits != DummyBits::Bit1) && (bits != DummyBits::Bit2))
            EXPECT_FALSE(set.IsSet(bits));
        else
            EXPECT_TRUE(set.IsSet(bits));
    }
}

TEST(EnumBitSetTest, OperatorEqualsSetSet)
{
    EnumBitSet<DummyBits> set1 = DummyBits::Bit1 | DummyBits::Bit2;
    EnumBitSet<DummyBits> set2 = DummyBits::Bit1 | DummyBits::Bit2;
    EnumBitSet<DummyBits> set3 = DummyBits::Bit0;
    EXPECT_EQ(set1, set2);
    EXPECT_NE(set1, set3);
    EXPECT_NE(set2, set3);
    EXPECT_TRUE(set1 == set2);
    EXPECT_FALSE(set1 == set3);
    EXPECT_FALSE(set2 == set3);
}

TEST(EnumBitSetTest, OperatorEqualsMaskTypeSet)
{
    EnumBitSet<DummyBits> set1 = DummyBits::Bit1 | DummyBits::Bit2;
    EnumBitSet<DummyBits> set2 = DummyBits::Bit0;
    uint8_t mask1 = static_cast<uint8_t>(DummyBits::Bit1) | static_cast<uint8_t>(DummyBits::Bit2);
    uint8_t mask2 = static_cast<uint8_t>(DummyBits::Bit0);
    EXPECT_EQ(set1, mask1);
    EXPECT_NE(set1, mask2);
    EXPECT_NE(set2, mask1);
    EXPECT_EQ(set2, mask2);
    EXPECT_TRUE(set1 == mask1);
    EXPECT_FALSE(set1 == mask2);
    EXPECT_FALSE(set2 == mask1);
    EXPECT_TRUE(set2 == mask2);
}

TEST(EnumBitSetTest, OperatorEqualsSetMaskType)
{
    EnumBitSet<DummyBits> set1 = DummyBits::Bit1 | DummyBits::Bit2;
    EnumBitSet<DummyBits> set2 = DummyBits::Bit0;
    uint8_t mask1 = static_cast<uint8_t>(DummyBits::Bit1) | static_cast<uint8_t>(DummyBits::Bit2);
    uint8_t mask2 = static_cast<uint8_t>(DummyBits::Bit0);
    EXPECT_EQ(mask1, set1);
    EXPECT_NE(mask1, set2);
    EXPECT_NE(mask2, set1);
    EXPECT_EQ(mask2, set2);
    EXPECT_TRUE(mask1 == set1);
    EXPECT_FALSE(mask1 == set2);
    EXPECT_FALSE(mask2 == set1);
    EXPECT_TRUE(mask2 == set2);
}

TEST(EnumBitSetTest, OperatorNotEqualsSetSet)
{
    EnumBitSet<DummyBits> set1 = DummyBits::Bit1 | DummyBits::Bit2;
    EnumBitSet<DummyBits> set2 = DummyBits::Bit1 | DummyBits::Bit2;
    EnumBitSet<DummyBits> set3 = DummyBits::Bit0;
    EXPECT_FALSE(set1 != set2);
    EXPECT_TRUE(set1 != set3);
    EXPECT_TRUE(set2 != set3);
}

TEST(EnumBitSetTest, OperatorNotEqualsMaskTypeSet)
{
    EnumBitSet<DummyBits> set1 = DummyBits::Bit1 | DummyBits::Bit2;
    EnumBitSet<DummyBits> set2 = DummyBits::Bit0;
    uint8_t mask1 = static_cast<uint8_t>(DummyBits::Bit1) | static_cast<uint8_t>(DummyBits::Bit2);
    uint8_t mask2 = static_cast<uint8_t>(DummyBits::Bit0);
    EXPECT_FALSE(set1 != mask1);
    EXPECT_TRUE(set1 != mask2);
    EXPECT_TRUE(set2 != mask1);
    EXPECT_FALSE(set2 != mask2);
}

TEST(EnumBitSetTest, OperatorNotEqualsSetMaskType)
{
    EnumBitSet<DummyBits> set1 = DummyBits::Bit1 | DummyBits::Bit2;
    EnumBitSet<DummyBits> set2 = DummyBits::Bit0;
    uint8_t mask1 = static_cast<uint8_t>(DummyBits::Bit1) | static_cast<uint8_t>(DummyBits::Bit2);
    uint8_t mask2 = static_cast<uint8_t>(DummyBits::Bit0);
    EXPECT_FALSE(mask1 != set1);
    EXPECT_TRUE(mask1 != set2);
    EXPECT_TRUE(mask2 != set1);
    EXPECT_FALSE(mask2 != set2);
}

TEST(EnumBitSetTest, Serialize)
{
    EnumBitSet<DummyBits> set00{};
    EnumBitSet<DummyBits> set01 = DummyBits::Bit0;
    EnumBitSet<DummyBits> set10 = DummyBits::Bit4;
    EnumBitSet<DummyBits> set20 = DummyBits::Bit5;
    EnumBitSet<DummyBits> set1E = DummyBits::Bit4 | DummyBits::Bit3 | DummyBits::Bit2 | DummyBits::Bit1;
    EnumBitSet<DummyBits> set4E = DummyBits::Bit6 | DummyBits::Bit3 | DummyBits::Bit2 | DummyBits::Bit1;
    EXPECT_EQ("", serialization::Serialize(set00));
    EXPECT_EQ("Bit0", serialization::Serialize(set01));
    EXPECT_EQ("Bit4", serialization::Serialize(set10));
    EXPECT_EQ("Bit5", serialization::Serialize(set20));
    EXPECT_EQ("Bit4|Bit3|Bit2|Bit1", serialization::Serialize(set1E));
    EXPECT_EQ("Bit6|Bit3|Bit2|Bit1", serialization::Serialize(set4E));
}

} // namespace utility

namespace serialization {

template<>
const BidirectionalMap<DummyBits, std::string> EnumSerializationMap<DummyBits>::ConversionMap = {
    { DummyBits::Bit0, "Bit0" },
    { DummyBits::Bit1, "Bit1" },
    { DummyBits::Bit2, "Bit2" },
    { DummyBits::Bit3, "Bit3" },
    { DummyBits::Bit4, "Bit4" },
    { DummyBits::Bit5, "Bit5" },
    { DummyBits::Bit6, "Bit6" },
    { DummyBits::Bit7, "Bit7" },
};

} // namespace serialization

