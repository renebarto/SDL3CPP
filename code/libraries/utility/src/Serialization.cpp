//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : Serialization.cpp
//
// Namespace   : serialization
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "utility/Serialization.h"

//#include <algorithm>
#include <bitset>
//#include <cctype>
//#include <chrono>
//#include <cstring>
//#include <ctime>
#include <iomanip>
//#include <sstream>
#include "osal/utilities/Clock.h"
#include "utility/StringFunctions.h"
#include "utility/TypeCast.h"

#if defined(PLATFORM_LINUX)
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

namespace serialization {

constexpr int BitsToOctalDigits(int bits)
{
    return (bits + 2) / 3;
}

constexpr int BitsToHexaDecimalDigits(int bits)
{
    return (bits + 3) / 4;
}

template <typename T>
std::string SerializeImpl(T value, int width, int base, bool showHexBase)
{
    std::ostringstream stream;

    switch (base)
    {
    case 2:
        {
            std::bitset<sizeof(T) * 8> x(static_cast<typename std::make_unsigned<T>::type>(value));
            stream << std::setfill('0') << std::setw(sizeof(T) * 8) << x;
            break;
        }
    case 8:
        {
            if (std::is_signed<T>::value)
                stream << std::oct << std::setfill('0') << std::setw((width > 0) ? width : BitsToOctalDigits(sizeof(T) * 8)) << static_cast<int64_t>(value) << std::dec;
            else
                stream << std::oct << std::setfill('0') << std::setw((width > 0) ? width : BitsToOctalDigits(sizeof(T) * 8)) << static_cast<uint64_t>(value) << std::dec;
            break;
        }
    case 10:
        {
            if (std::is_signed<T>::value)
                stream << std::dec << std::setfill('0') << static_cast<int64_t>(value);
            else
                stream << std::dec << std::setfill('0') << static_cast<uint64_t>(value);
            break;
        }
    case 16:
        {
            if (showHexBase) stream << "0x";
            if (std::is_signed<T>::value)
                stream << std::hex << std::noshowbase << std::uppercase << std::setfill('0') << std::setw((width > 0) ? width : BitsToHexaDecimalDigits(sizeof(T) * 8)) << static_cast<int64_t>(value) << std::dec;
            else
                stream << std::hex << std::noshowbase << std::uppercase << std::setfill('0') << std::setw((width > 0) ? width : BitsToHexaDecimalDigits(sizeof(T) * 8)) << static_cast<uint64_t>(value) << std::dec;
            break;
        }
    default:
        {
            throw std::logic_error("Invalid base specified: " + std::to_string(base));
        }
    }
    return serialization::Align(stream.str(), width);
}

std::string Serialize(int8_t value, int width, int base, bool showHexBase)
{
    return SerializeImpl(value, width, base, showHexBase);
}

std::string Serialize(uint8_t value, int width, int base, bool showHexBase)
{
    return SerializeImpl(value, width, base, showHexBase);
}

std::string Serialize(int16_t value, int width, int base, bool showHexBase)
{
    return SerializeImpl(value, width, base, showHexBase);
}

std::string Serialize(uint16_t value, int width, int base, bool showHexBase)
{
    return SerializeImpl(value, width, base, showHexBase);
}

std::string Serialize(int32_t value, int width, int base, bool showHexBase)
{
    return SerializeImpl(value, width, base, showHexBase);
}

std::string Serialize(uint32_t value, int width, int base, bool showHexBase)
{
    return SerializeImpl(value, width, base, showHexBase);
}

std::string Serialize(int64_t value, int width, int base, bool showHexBase)
{
    return SerializeImpl(value, width, base, showHexBase);
}

std::string Serialize(uint64_t value, int width, int base, bool showHexBase)
{
    return SerializeImpl(value, width, base, showHexBase);
}

template <typename T>
std::string SerializeFloatingPoint(T value, int width, int precision, FloatingPointRepresentation representation)
{
    std::ostringstream stream;

    switch (representation)
    {
    case FloatingPointRepresentation::Fixed:
        stream.setf(std::ios_base::floatfield, std::ios_base::fixed);
        stream << std::setfill('0') << std::setw(width) << std::setprecision(precision) << value;
        break;
    case FloatingPointRepresentation::Exponential:
        stream.setf(std::ios_base::floatfield, std::ios_base::scientific);
        stream << std::setfill('0') << std::setw(width) << std::setprecision(precision) << value;
        break;
    case FloatingPointRepresentation::Mixed:
        stream.unsetf(std::ios_base::floatfield);
        stream << std::setfill('0') << std::setprecision(precision) << value;
        break;
    default:
        throw std::logic_error("Invalid representation specified: " + std::to_string(static_cast<int>(representation)));
    }

    return serialization::Align(stream.str(), width);
}

std::string Serialize(float value, int width, int precision, FloatingPointRepresentation representation)
{
    return SerializeFloatingPoint(value, width, precision, representation);
}

std::string Serialize(double value, int width, int precision, FloatingPointRepresentation representation)
{
    return SerializeFloatingPoint(value, width, precision, representation);
}

std::string Serialize(long double value, int width, int precision, FloatingPointRepresentation representation)
{
    return SerializeFloatingPoint(value, width, precision, representation);
}

std::string Serialize(const std::string& value, int width, bool quote)
{
    std::ostringstream stream;

    if (quote) stream << "\"";
    stream << value;
    if (quote) stream << "\"";

    return serialization::Align(stream.str(), width);
}

std::string Serialize(const char* value, int width, bool quote)
{
    std::ostringstream stream;

    stream << Serialize(std::string(value), width, quote);

    return serialization::Align(stream.str(), width);
}

std::string Serialize(const void* value, int width)
{
    std::ostringstream stream;

    if (value != nullptr)
    {
        stream << "0x" + Serialize(CastPointerToInteger(value), 0, 16);
    }
    else
    {
        stream << "null";
    }

    return serialization::Align(stream.str(), width);
}

std::string Serialize(void* value, int width)
{
    return Serialize(const_cast<const void *>(value), width);
}

std::string Serialize(const std::chrono::nanoseconds& value, int width)
{
    std::ostringstream stream;
    stream << value.count() << " ns";
    return serialization::Align(stream.str(), width);
}

std::string Serialize(const std::chrono::milliseconds& value, int width)
{
    std::ostringstream stream;
    stream << value.count() << " ms";
    return serialization::Align(stream.str(), width);
}

std::string Serialize(const std::chrono::seconds& value, int width)
{
    std::ostringstream stream;
    stream << value.count() << " s";
    return serialization::Align(stream.str(), width);
}

template<class Rep, class Period>
std::string Serialize(std::chrono::duration<Rep, Period>& value, int width)
{
    return Serialize(std::chrono::duration_cast<std::chrono::nanoseconds>(value), width);
}

std::string SerializeData(const uint8_t* value, std::size_t size)
{
    std::ostringstream stream;

    if (value != nullptr)
    {
        stream << std::endl;
        const std::size_t LineDisplayBytes = 16;
        const std::size_t MaxDisplayBytes = 4096;
        std::size_t displayBytes = (size < MaxDisplayBytes) ? size : MaxDisplayBytes;
        for (std::size_t i = 0; i < displayBytes; i += LineDisplayBytes)
        {
            stream << Serialize(i, 0, 16) << "  ";
            for (std::size_t j = 0; j < LineDisplayBytes; ++j)
            {
                if (j != 0) stream << " ";
                if ((i + j) < displayBytes) stream << Serialize(value[i + j], 2, 16);
                else stream << "  ";
            }
            stream << "  ";
            for (std::size_t j = 0; j < LineDisplayBytes; ++j)
            {
                if (j != 0) stream << " ";
                if ((i + j) < displayBytes)
                {
                    auto ch = value[i + j];
                    stream << ((std::isprint(ch) ? static_cast<char>(ch) : '.'));
                }
                else
                {
                    stream << " ";
                }
            }
            stream << std::endl;
        }
    }
    else
    {
        stream << "null";
    }
    return stream.str();
}

std::string SerializeData(const std::vector<uint8_t>& value)
{
    if (value.size() > 0)
        return SerializeData(value.data(), value.size());
    return "-";
}

std::string SerializeMACAddress(const std::vector<uint8_t>& address)
{
    std::ostringstream stream;
    if (address.size() != 6)
        return "Invalid format for MAC address";
    stream << std::hex << std::setw(2) << std::setfill('0') << std::noshowbase 
        << static_cast<int>(address[0]) << ":";
    stream << std::hex << std::setw(2) << std::setfill('0') << std::noshowbase 
        << static_cast<int>(address[1]) << ":";
    stream << std::hex << std::setw(2) << std::setfill('0') << std::noshowbase 
        << static_cast<int>(address[2]) << ":";
    stream << std::hex << std::setw(2) << std::setfill('0') << std::noshowbase 
        << static_cast<int>(address[3]) << ":";
    stream << std::hex << std::setw(2) << std::setfill('0') << std::noshowbase 
        << static_cast<int>(address[4]) << ":";
    stream << std::hex << std::setw(2) << std::setfill('0') << std::noshowbase 
        << static_cast<int>(address[5]);
    return stream.str();
}

// Binary Serialization

void AppendOrReplace(std::vector<uint8_t>& buffer, std::size_t& offset, const void* data, std::size_t length)
{
    if (buffer.size() < offset + length)
        buffer.resize(offset + length);
    const uint8_t* bytePtr = reinterpret_cast<const uint8_t *>(data);
    std::copy(bytePtr, bytePtr + length, &buffer[offset]);
    offset += length;
}

void SerializeBinary(bool value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness /*endianness*/)
{
    uint8_t data = static_cast<uint8_t>(value ? 0x01 : 0x00);
    AppendOrReplace(buffer, offset, &data, sizeof(data));
}

void SerializeBinary(int8_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness /*endianness*/)
{
    uint8_t data = static_cast<uint8_t>(value);
    AppendOrReplace(buffer, offset, &data, sizeof(data));
}

void SerializeBinary(uint8_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness /*endianness*/)
{
    AppendOrReplace(buffer, offset, &value, sizeof(value));
}

void SerializeBinary(int16_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness)
{
    int16_t convertedValue = utility::ToEndianness(value, endianness);
    const uint8_t* data = reinterpret_cast<const uint8_t *>(&convertedValue);
    AppendOrReplace(buffer, offset, data, sizeof(convertedValue));
}

void SerializeBinary(uint16_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness)
{
    uint16_t convertedValue = utility::ToEndianness(value, endianness);
    const uint8_t* data = reinterpret_cast<const uint8_t *>(&convertedValue);
    AppendOrReplace(buffer, offset, data, sizeof(convertedValue));
}

void SerializeBinary(int32_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness)
{
    int32_t convertedValue = utility::ToEndianness(value, endianness);
    const uint8_t* data = reinterpret_cast<const uint8_t *>(&convertedValue);
    AppendOrReplace(buffer, offset, data, sizeof(convertedValue));
}

void SerializeBinary(uint32_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness)
{
    uint32_t convertedValue = utility::ToEndianness(value, endianness);
    const uint8_t* data = reinterpret_cast<const uint8_t *>(&convertedValue);
    AppendOrReplace(buffer, offset, data, sizeof(convertedValue));
}

void SerializeBinary(int64_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness)
{
    int64_t convertedValue = utility::ToEndianness(value, endianness);
    const uint8_t* data = reinterpret_cast<const uint8_t *>(&convertedValue);
    AppendOrReplace(buffer, offset, data, sizeof(convertedValue));
}

void SerializeBinary(uint64_t value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness)
{
    uint64_t convertedValue = utility::ToEndianness(value, endianness);
    const uint8_t* data = reinterpret_cast<const uint8_t *>(&convertedValue);
    AppendOrReplace(buffer, offset, data, sizeof(convertedValue));
}

void SerializeBinary(float value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness)
{
    const uint32_t convertedValue = utility::ToEndianness(*reinterpret_cast<const uint32_t *>(&value), endianness);
    const uint8_t* data = reinterpret_cast<const uint8_t *>(&convertedValue);
    AppendOrReplace(buffer, offset, data, sizeof(convertedValue));
}

void SerializeBinary(double value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness)
{
    const uint64_t convertedValue = utility::ToEndianness(*reinterpret_cast<const uint64_t *>(&value), endianness);
    const uint8_t* data = reinterpret_cast<const uint8_t *>(&convertedValue);
    AppendOrReplace(buffer, offset, data, sizeof(convertedValue));
}

void SerializeBinary(long double value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness)
{
    uint8_t convertedValue[16]{};
    std::copy(reinterpret_cast<const uint8_t*>(&value), reinterpret_cast<const uint8_t*>(&value) + sizeof(value), std::begin(convertedValue));
    if (endianness != utility::PlatformEndianness())
    {
        std::reverse(std::begin(convertedValue), std::end(convertedValue));
    }
#if defined(PLATFORM_LINUX)
    // For Linux (Debian etc.) long double is implemented as 80 bit floating point, but serialized to 128 bit, with 6 bytes of garbage at the end
    // (or begin for Big Endian). So we clear these 6 bytes.
    if (endianness == utility::Endianness::LittleEndian)
    {
        std::fill_n(&convertedValue[10], 6, 0);
    }
    else
    {
        std::fill_n(std::begin(convertedValue), 6, 0);
    }
#endif

    const uint8_t* data = convertedValue;
    AppendOrReplace(buffer, offset, data, sizeof(convertedValue));
}

void SerializeBinary(const std::string& value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness)
{
    // Always make length 32 bits, as size_t is 32 bit or 64 bit depending on platform
    SerializeBinary(static_cast<uint32_t>(value.length()), buffer, offset, endianness);
    for (auto ch : value)
    {
        SerializeBinary(CastToInteger(ch), buffer, offset, endianness);
    }
}

void SerializeBinary(const char* value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness)
{
    auto length = static_cast<uint32_t>(std::strlen(value));
    SerializeBinary(length, buffer, offset, endianness);
    for (std::size_t i = 0; i < length; ++i)
    {
        SerializeBinary(CastToInteger(value[i]), buffer, offset, endianness);
    }
}

void SerializeBinary(const std::vector<uint8_t>& value, std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness)
{
    auto length = static_cast<uint32_t>(value.size());
    SerializeBinary(length, buffer, offset, endianness);
    for (auto byte : value)
    {
        SerializeBinary(byte, buffer, offset, endianness);
    }
}

} // namespace serialization
