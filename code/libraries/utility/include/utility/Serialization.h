//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Serialization.h
//
// Namespace   : serialization
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <chrono>
#include <sstream>
#include <string>
#include <vector>
#include "serialization/Serialization.h"
#include "utility/Endian.h"

namespace serialization {

// String serialization
// Every serialization specialization uses a width parameter, which is used for expansion
// width < 0 Left aligned
// width > 0 right aligned
// width < actual length no alignment
template<>
inline std::string Serialize(const bool& value)
{
    return std::string(value ? "true" : "false");
}

std::string Serialize(char value, int width = 0);
std::string Serialize(int8_t value, int width = 0, int base = 10, bool showHexBase = false);
std::string Serialize(uint8_t value, int width = 0, int base = 10, bool showHexBase = false);
std::string Serialize(int16_t value, int width = 0, int base = 10, bool showHexBase = false);
std::string Serialize(uint16_t value, int width = 0, int base = 10, bool showHexBase = false);
std::string Serialize(int32_t value, int width = 0, int base = 10, bool showHexBase = false);
std::string Serialize(uint32_t value, int width = 0, int base = 10, bool showHexBase = false);
std::string Serialize(int64_t value, int width = 0, int base = 10, bool showHexBase = false);
std::string Serialize(uint64_t value, int width = 0, int base = 10, bool showHexBase = false);
#if defined(PLATFORM_WINDOWS)
inline std::string Serialize(long unsigned int value, int width = 0, int base = 10, bool showHexBase = false)
{
    return Serialize(static_cast<uint32_t>(value), width, base, showHexBase);
}
#endif
enum class FloatingPointRepresentation
{
    Fixed,
    Exponential,
    Mixed
};
std::string Serialize(float value, int width = 0, int precision = 16, FloatingPointRepresentation representation = FloatingPointRepresentation::Mixed);
std::string Serialize(double value, int width = 0, int precision = 16, FloatingPointRepresentation representation = FloatingPointRepresentation::Mixed);
std::string Serialize(long double value, int width = 0, int precision = 16, FloatingPointRepresentation representation = FloatingPointRepresentation::Mixed);
std::string Serialize(const std::string& value, int width = 0, bool quote = false);
std::string Serialize(const char* value, int width = 0, bool quote = false);
std::string Serialize(const void* value, int width = 0);
std::string Serialize(void* value, int width = 0);
std::string Serialize(const std::chrono::nanoseconds& value, int width = 0);
std::string Serialize(const std::chrono::milliseconds& value, int width = 0);
std::string Serialize(const std::chrono::seconds& value, int width = 0);
std::string SerializeData(const uint8_t* value, std::size_t size);
std::string SerializeData(const std::vector<uint8_t>& value);
std::string SerializeMACAddress(const std::vector<uint8_t>& value);
// Needed as osal cannot implement serialization as it cannot depend on utility

template<typename T>
std::string Serialize(const std::vector<T>& value)
{
    std::ostringstream stream;
    stream << "[";
    for (auto it = value.begin(); it != value.end(); ++it)
    {
        stream << *it;
        auto nextIt = it + 1;
        if (nextIt != value.end())
        {
            stream << ",";
        }
    }
    stream << "]";
    return stream.str();

}
template<typename T>
std::string Serialize(const std::vector<T>& value, int width)
{
    return serialization::Align(Serialize(value), width);
}

template<>
inline std::string Serialize<uint8_t>(const std::vector<uint8_t>& value)
{
    std::ostringstream stream;
    stream << "[";
    for (auto it = value.begin(); it != value.end(); ++it)
    {
        stream << Serialize(*it, 0, 16, true);
        auto nextIt = it + 1;
        if (nextIt != value.end())
        {
            stream << ",";
        }
    }
    stream << "]";
    return stream.str();
}

// Binary Serialization

void AppendOrReplace(std::vector<uint8_t>& buffer, std::size_t& offset, const void* data, std::size_t length);

template <typename T>
typename std::enable_if<!std::is_enum<T>::value, void>::type
SerializeBinary(T value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness /*endianness = utility::Endianness::LittleEndian*/)
{
    AppendOrReplace(buffer, offset, &value, sizeof(value));
}

void SerializeBinary(bool value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(int8_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(uint8_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(int16_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(uint16_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(int32_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(uint32_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(int64_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(uint64_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(float value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(double value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(long double value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(const std::string& value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(const char* value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
void SerializeBinary(const std::vector<uint8_t>& value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian);
template<typename EnumType>
typename std::enable_if<std::is_enum<EnumType>::value, void>::type
SerializeBinary(const EnumType& value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness = utility::Endianness::LittleEndian)
{
    SerializeBinary(static_cast<typename std::underlying_type<EnumType>::type>(value), buffer, offset, endianness);
}


template<class T>
class IStringSerializer
{
public:
    IStringSerializer()
    {}

    virtual ~IStringSerializer()
    {}

    virtual void Serialize(std::string& text, const T& result) = 0;
};

} // namespace serialization
