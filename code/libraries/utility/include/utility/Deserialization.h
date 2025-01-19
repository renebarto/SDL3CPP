//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Deserialization.h
//
// Namespace   : serialization
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <sstream>
#include <string>
#include "serialization/Deserialization.h"
#include "utility/Endian.h"
#include "utility/StringFunctions.h"

namespace serialization {

// String Deserialization
bool Deserialize(const std::string& text, bool& value);
bool Deserialize(const std::string& text, int8_t& value, int base = 10);
bool Deserialize(const std::string& text, uint8_t& value, int base = 10);
bool Deserialize(const std::string& text, int16_t& value, int base = 10);
bool Deserialize(const std::string& text, uint16_t& value, int base = 10);
bool Deserialize(const std::string& text, int32_t& value, int base = 10);
bool Deserialize(const std::string& text, uint32_t& value, int base = 10);
bool Deserialize(const std::string& text, int64_t& value, int base = 10);
bool Deserialize(const std::string& text, uint64_t& value, int base = 10);
bool Deserialize(const std::string& text, float& value);
bool Deserialize(const std::string& text, double& value);

bool Deserialize(const std::string& text, std::string& value);

// Binary Deserialization

bool Extract(const std::vector<uint8_t>& buffer, std::size_t& offset, void * data, std::size_t length);

template <typename T>
typename std::enable_if<!std::is_enum<T>::value, bool>::type
DeserializeBinary(T& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness /*endianness = utility::Endianness::LittleEndian*/)
{
    return Extract(buffer, offset, &value, sizeof(value));
}

bool DeserializeBinary(bool& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
bool DeserializeBinary(int8_t& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
bool DeserializeBinary(uint8_t& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
bool DeserializeBinary(int16_t& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
bool DeserializeBinary(unsigned short& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
bool DeserializeBinary(int32_t& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
bool DeserializeBinary(uint32_t& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
bool DeserializeBinary(int64_t& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
bool DeserializeBinary(uint64_t& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
bool DeserializeBinary(float& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
bool DeserializeBinary(double& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
bool DeserializeBinary(std::string& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);

template<typename EnumType>
typename std::enable_if<std::is_enum<EnumType>::value, bool>::type
DeserializeBinary(EnumType& value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian)
{
    typename std::underlying_type<EnumType>::type data {};
    if (!DeserializeBinary(data, buffer, offset, endianness))
        return false;
    value = static_cast<EnumType>(data);
    return true;
}

template<class T>
class IStringDeserializer
{
public:
    IStringDeserializer()
    {}

    virtual ~IStringDeserializer()
    {}

    virtual bool Deserialize(const std::string& text, T& result) = 0;
};

} // namespace serialization
