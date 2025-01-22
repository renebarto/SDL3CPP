#pragma once

#include "MemoryGeneric.h"

class MemorySpace
    : public GenericMemorySpace<uint16_t>
{
public:
    MemorySpace(uint16_t maxAddress)
        : GenericMemorySpace<uint16_t>{ maxAddress }
    {
    }
};

class MemoryMap
    : public GenericMemoryMap<uint16_t>
{
public:
    MemoryMap(const std::vector<MemoryMapping<uint16_t>> &mappings)
        : GenericMemoryMap<uint16_t>{ mappings }
    {
    }
};

class ROM
    : public GenericROM<uint16_t>
{
public:
    ROM(MemorySpace& memorySpace, uint16_t offset, uint16_t size)
        : GenericROM<uint16_t>{ memorySpace, offset, size }
    {
    }
    ROM(const ROM &) = delete;
    ROM(ROM &&) = delete;

    ROM &operator =(const ROM &) = delete;
    ROM &operator =(ROM &&) = delete;
};

class RAM
    : public GenericRAM<uint16_t>
{
public:
    RAM(MemorySpace& memorySpace, uint16_t offset, uint16_t size)
        : GenericRAM<uint16_t>{ memorySpace, offset, size }
    {
    }
    RAM(const RAM &) = delete;
    RAM(RAM &&) = delete;

    RAM &operator =(const RAM &) = delete;
    RAM &operator =(RAM &&) = delete;
};
