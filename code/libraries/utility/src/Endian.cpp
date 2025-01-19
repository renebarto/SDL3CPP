//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Endian.cpp
//
// Namespace   : serialization
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "utility/Endian.h"

namespace serialization {

template<>
const BidirectionalMap<utility::Endianness, std::string> EnumSerializationMap<utility::Endianness>::ConversionMap = 
{
    {utility::Endianness::LittleEndian, "LittleEndian"},
    {utility::Endianness::BigEndian, "BigEndian"},
};

} // namespace serialization
