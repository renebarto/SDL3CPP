#pragma once

#include "IOGeneric.h"

class IOMap
    : public GenericIOMap<uint8_t>
{
public:
    IOMap(const std::vector<IOMapping<uint8_t>> &mappings)
        : GenericIOMap<uint8_t>{ mappings }
    {
    }
};

class VideoBorder
    : public IIOAccess<uint8_t>
{
    void Write8(uint8_t /*address*/, uint8_t /*value*/)
    {
    }
    void Write16(uint8_t /*address*/, uint16_t /*value*/) {};
    void Write32(uint8_t /*address*/, uint32_t /*value*/) {};
    void Write64(uint8_t /*address*/, uint64_t /*value*/) {};

    void Read8(uint8_t /*address*/, uint8_t& /*value*/) {};
    void Read16(uint8_t /*address*/, uint16_t& /*value*/) {};
    void Read32(uint8_t /*address*/, uint32_t& /*value*/) {};
    void Read64(uint8_t /*address*/, uint64_t& /*value*/) {};
};
