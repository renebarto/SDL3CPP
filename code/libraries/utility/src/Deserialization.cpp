//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : Deserialization.cpp
//
// Namespace   : serialization
//
// Class       : -
//
// Description :
//
//------------------------------------------------------------------------------

#include "utility/Deserialization.h"

#include <algorithm>
#include <climits>
#include <cctype>
#include <cfloat>
#include <cstring>
#include <sstream>

#if defined(PLATFORM_LINUX)
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

namespace serialization {

static bool HasValidCharactersForBase(const std::string & text, int base, bool maybeSigned)
{
    if (text.empty())
        return false;
        
    switch (base)
    {
        case 2:
            for (size_t i = 0; i < text.length(); i++)
            {
                if (std::strchr("01", static_cast<char>(std::toupper(text[i]))) == nullptr)
                    return false;
            }
            break;
        case 8:
            for (size_t i = 0; i < text.length(); i++)
            {
                if (std::strchr("01234567", static_cast<char>(std::toupper(text[i]))) == nullptr)
                    return false;
            }
            break;
        case 10:
            for (size_t i = 0; i < text.length(); i++)
            {
                if (maybeSigned)
                {
                    if (std::strchr("0123456789+-", static_cast<char>(std::toupper(text[i]))) == nullptr)
                        return false;
                }
                else
                {
                    if (std::strchr("0123456789+", static_cast<char>(std::toupper(text[i]))) == nullptr)
                        return false;
                }
            }
            break;
        case 16:
            for (size_t i = 0; i < text.length(); i++)
            {
                if (std::strchr("0123456789ABCDEF", static_cast<char>(std::toupper(text[i]))) == nullptr)
                    return false;
            }
            break;
        default:
            return false;
    }
    return true;
}

static bool HasValidCharactersFloatingPoint(const std::string & text)
{
    if (text.empty())
        return false;
    for (size_t i = 0; i < text.length(); i++)
    {
        if (std::strchr("0123456789.+-Ee", static_cast<char>(std::toupper(text[i]))) == nullptr)
            return false;
    }
    return true;
}

bool Deserialize(const std::string & text, bool & value)
{
    if (utility::IsEqualIgnoreCase("true", text))
    {
        value = true;
        return true;
    }
    if (utility::IsEqualIgnoreCase("false", text))
    {
        value = false;
        return true;
    }

    return false;
}

bool Deserialize(const std::string & text, int8_t & value, int base)
{
    value = {};
    if (!HasValidCharactersForBase(text, base, true))
        return false;

    long result = std::strtol(text.c_str(), nullptr, base);
    if ((base == 10) && ((result < SCHAR_MIN) || (result > SCHAR_MAX)))
        return false;
    value = static_cast<int8_t>(result);

    return true;
}

bool Deserialize(const std::string & text, uint8_t & value, int base /*= 10*/)
{
    value = {};
    if (!HasValidCharactersForBase(text, base, false))
        return false;

    long result = std::strtol(text.c_str(), nullptr, base);
    if ((base == 10) && ((result < 0) || (result > UCHAR_MAX)))
        return false;
    value = static_cast<uint8_t>(result);

    return true;
}

bool Deserialize(const std::string & text, int16_t & value, int base /*= 10*/)
{
    value = {};
    if (!HasValidCharactersForBase(text, base, true))
        return false;

    long result = std::strtol(text.c_str(), nullptr, base);
    if ((base == 10) && ((result < SHRT_MIN) || (result > SHRT_MAX)))
        return false;
    value = static_cast<int16_t>(result);

    return true;
}

bool Deserialize(const std::string & text, uint16_t & value, int base /*= 10*/)
{
    value = {};
    if (!HasValidCharactersForBase(text, base, false))
        return false;

    long result = std::strtol(text.c_str(), nullptr, base);
    if ((base == 10) && ((result < 0) || (result > USHRT_MAX)))
        return false;
    value = static_cast<uint16_t>(result);

    return true;
}

bool Deserialize(const std::string & text, int32_t & value, int base /*= 10*/)
{
    value = {};
    if (!HasValidCharactersForBase(text, base, true))
        return false;

    long result = std::strtol(text.c_str(), nullptr, base);
    unsigned long result_ul = std::strtoul(text.c_str(), nullptr, base);
    if (((result == LONG_MIN) || (result == LONG_MAX)) && (errno == ERANGE))
        return false;
    if ((base == 10) && ((result < INT_MIN) || (result > INT_MAX)))
        return false;
    if ((base != 10) && (result_ul > INT_MAX))
    {
        value = static_cast<int32_t>(result_ul);
    }
    else
    {
        value = static_cast<int32_t>(result);
    }

    return true;
}

bool Deserialize(const std::string & text, uint32_t & value, int base /*= 10*/)
{
    value = {};
    if (!HasValidCharactersForBase(text, base, false))
        return false;

    unsigned long long result = std::strtoull(text.c_str(), nullptr, base);
    if ((base == 10) && (result > UINT_MAX))
        return false;
    value = static_cast<uint32_t>(result);

    return true;
}

bool Deserialize(const std::string & text, int64_t & value, int base /*= 10*/)
{
    value = {};
    if (!HasValidCharactersForBase(text, base, true))
        return false;

    // For some strange reason stroull behaves incorrectly in some cases.
    long long result = std::strtoll(text.c_str(), nullptr, base);
    unsigned long long result_ull = std::strtoull(text.c_str(), nullptr, base);
    if (((result == LLONG_MIN) || (result == LLONG_MAX)) && (errno == ERANGE))
        return false;
    if ((base == 10) && (result >= 0) && (result_ull > LLONG_MAX))
        return false;
    if ((base != 10) && (result_ull > LLONG_MAX))
    {
        value = static_cast<int64_t>(result_ull);
    }
    else
    {
        value = result;
    }

    return true;
}

bool Deserialize(const std::string & text, uint64_t & value, int base /*= 10*/)
{
    value = {};
    if (!HasValidCharactersForBase(text, base, false))
        return false;

    unsigned long long result = std::strtoull(text.c_str(), nullptr, base);
    value = static_cast<uint64_t>(result);

    return true;
}

bool Deserialize(const std::string & text, float & value)
{
    value = {};
    if (!HasValidCharactersFloatingPoint(text))
        return false;

    double tmp {};
    std::istringstream stream(text);
    stream >> tmp;
    if ((std::abs(tmp) < FLT_MIN) || (std::abs(tmp) > FLT_MAX))
        return false;

    value = static_cast<float>(tmp);
    return true;
}

bool Deserialize(const std::string & text, double & value)
{
    value = {};
    if (!HasValidCharactersFloatingPoint(text))
        return false;

    std::istringstream stream(text);
    stream >> value;

    return true;
}

bool Deserialize(const std::string& text, std::string& value)
{
    value = text;
    return true;
}

bool Extract(const std::vector<uint8_t> & buffer, std::size_t & offset, void * data, std::size_t length)
{
    if ((buffer.size() - offset) < length)
        return false;
    uint8_t * bytePtr = reinterpret_cast<uint8_t *>(data);
    std::copy_n(&buffer[offset], length, bytePtr);
    offset += length;
    return true;
}

bool DeserializeBinary(bool & value, const std::vector<uint8_t> & buffer, std::size_t & offset, utility::Endianness /*endianness*/)
{
    uint8_t data {};
    if (!Extract(buffer, offset, &data, sizeof(data)))
        return false;
    value = (data == 0x00) ? false : true;
    return true;
}

bool DeserializeBinary(int8_t & value, const std::vector<uint8_t> & buffer, std::size_t & offset, utility::Endianness /*endianness*/)
{
    uint8_t data {};
    if (!Extract(buffer, offset, &data, sizeof(data)))
        return false;
    value = static_cast<int8_t>(data);
    return true;
}

bool DeserializeBinary(uint8_t & value, const std::vector<uint8_t> & buffer, std::size_t & offset, utility::Endianness /*endianness*/)
{
    if (!Extract(buffer, offset, &value, sizeof(value)))
        return false;
    return true;
}

bool DeserializeBinary(int16_t & value, const std::vector<uint8_t> & buffer, std::size_t & offset, utility::Endianness endianness)
{
    int16_t data {};
    uint8_t * bytePtr = reinterpret_cast<uint8_t *>(&data);
    if (!Extract(buffer, offset, bytePtr, sizeof(data)))
        return false;
    value = utility::ToEndianness(data, endianness);
    return true;
}

bool DeserializeBinary(uint16_t & value, const std::vector<uint8_t> & buffer, std::size_t & offset, utility::Endianness endianness)
{
    uint16_t data {};
    uint8_t * bytePtr = reinterpret_cast<uint8_t *>(&data);
    if (!Extract(buffer, offset, bytePtr, sizeof(data)))
        return false;
    value = utility::ToEndianness(data, endianness);
    return true;
}

bool DeserializeBinary(int32_t & value, const std::vector<uint8_t> & buffer, std::size_t & offset, utility::Endianness endianness)
{
    int32_t data {};
    uint8_t * bytePtr = reinterpret_cast<uint8_t *>(&data);
    if (!Extract(buffer, offset, bytePtr, sizeof(data)))
        return false;
    value = utility::ToEndianness(data, endianness);
    return true;
}

bool DeserializeBinary(uint32_t & value, const std::vector<uint8_t> & buffer, std::size_t & offset, utility::Endianness endianness)
{
    uint32_t data {};
    uint8_t * bytePtr = reinterpret_cast<uint8_t *>(&data);
    if (!Extract(buffer, offset, bytePtr, sizeof(data)))
        return false;
    value = utility::ToEndianness(data, endianness);
    return true;
}

bool DeserializeBinary(int64_t & value, const std::vector<uint8_t> & buffer, std::size_t & offset, utility::Endianness endianness)
{
    int64_t data {};
    uint8_t * bytePtr = reinterpret_cast<uint8_t *>(&data);
    if (!Extract(buffer, offset, bytePtr, sizeof(data)))
        return false;
    value = utility::ToEndianness(data, endianness);
    return true;
}

bool DeserializeBinary(uint64_t & value, const std::vector<uint8_t> & buffer, std::size_t & offset, utility::Endianness endianness)
{
    uint64_t data {};
    uint8_t * bytePtr = reinterpret_cast<uint8_t *>(&data);
    if (!Extract(buffer, offset, bytePtr, sizeof(data)))
        return false;
    value = utility::ToEndianness(data, endianness);
    return true;
}

bool DeserializeBinary(float & value, const std::vector<uint8_t> & buffer, std::size_t & offset, utility::Endianness endianness)
{
    float data {};
    uint8_t * bytePtr = reinterpret_cast<uint8_t *>(&data);
    if (!Extract(buffer, offset, bytePtr, sizeof(data)))
        return false;
    auto convertedValue = utility::ToEndianness(*reinterpret_cast<uint32_t *>(&data), endianness);
    value = *reinterpret_cast<float *>(&convertedValue);
    return true;
}

bool DeserializeBinary(double & value, const std::vector<uint8_t> & buffer, std::size_t & offset, utility::Endianness endianness)
{
    double data {};
    uint8_t * bytePtr = reinterpret_cast<uint8_t *>(&data);
    if (!Extract(buffer, offset, bytePtr, sizeof(data)))
        return false;
    auto convertedValue = utility::ToEndianness(*reinterpret_cast<uint64_t *>(&data), endianness);
    value = *reinterpret_cast<double *>(&convertedValue);
    return true;
}

bool DeserializeBinary(std::string &value, const std::vector<uint8_t>& buffer, std::size_t& offset, utility::Endianness endianness)
{
    // Always make length 32 bits, as size_t is 32 bit or 64 bit depending on platform
    uint32_t length {};
    if (!DeserializeBinary(length, buffer, offset, endianness))
        return false;
    for (uint32_t i = 0; i < length; ++i)
    {
        char ch {};
        if (!DeserializeBinary(ch, buffer, offset, endianness))
            return false;
        value += ch;
    }
    return true;
}

} // namespace serialization
