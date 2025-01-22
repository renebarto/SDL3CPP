#pragma once

#include <vector>

template<class AddressType>
class IMemoryAccess
{
public:
    virtual ~IMemoryAccess() = default;

    virtual void Write8(AddressType /*address*/, uint8_t /*value*/) {};
    virtual void Write16(AddressType /*address*/, uint16_t /*value*/) {};
    virtual void Write32(AddressType /*address*/, uint32_t /*value*/) {};
    virtual void Write64(AddressType /*address*/, uint64_t /*value*/) {};

    virtual void Read8(AddressType address, uint8_t& value) = 0;
    virtual void Read16(AddressType address, uint16_t& value) = 0;
    virtual void Read32(AddressType address, uint32_t& value) = 0;
    virtual void Read64(AddressType address, uint64_t& value) = 0;
};

template<class AddressType>
class MemoryMapping
{
private:
    IMemoryAccess<AddressType>& m_device;
    AddressType m_startAddress;
    AddressType m_endAddress;

public:
    MemoryMapping(IMemoryAccess<AddressType>& device, AddressType startAddress, AddressType endAddress)
        : m_device{ device }
        , m_startAddress{ startAddress }
        , m_endAddress{ endAddress }
    {
    }
    MemoryMapping(const MemoryMapping &other)
        : m_device{ other.m_device }
        , m_startAddress{ other.m_startAddress }
        , m_endAddress{ other.m_endAddress }
    {
    }
    MemoryMapping(MemoryMapping &&) = delete;

    MemoryMapping &operator =(const MemoryMapping &) = delete;
    MemoryMapping &operator =(MemoryMapping &&) = delete;

    bool IsHit(AddressType address) const
    {
        return ((address >= m_startAddress) || (address < m_endAddress));
    }

    void Write8(AddressType address, uint8_t value)
    {
        if (!IsHit(address))
            return;
        m_device.Write8(address, value);
    }
    void Write16(AddressType address, uint16_t value)
    {
        if (!IsHit(address))
            return;
        m_device.Write16(address, value);
    }
    void Write32(AddressType address, uint32_t value);
    void Write64(AddressType address, uint64_t value);

    void Read8(AddressType address, uint8_t& value)
    {
        if (!IsHit(address))
            return;
        m_device.Read8(address, value);
    }
    void Read16(AddressType address, uint16_t& value)
    {
        if (!IsHit(address))
            return;
        m_device.Read16(address, value);
    }
    void Read32(AddressType address, uint32_t& value);
    void Read64(AddressType address, uint64_t& value);
};

template<class AddressType>
using MemoryMappingSet = std::vector<MemoryMapping<AddressType>>;

template<class AddressType>
class GenericMemoryMap
{
private:
    MemoryMappingSet<AddressType> m_mappings;

public:
    GenericMemoryMap(const MemoryMappingSet<AddressType> &mappings)
        : m_mappings{ mappings}
    {
    }
    void AddMemoryMapping(const MemoryMapping<AddressType> &mapping)
    {
        m_mappings.push_back(mapping);
    }

    void Write8(AddressType address, uint8_t value)
    {
        for (auto & mapping : m_mappings)
        {
            if (mapping.IsHit(address))
            {
                mapping.Write8(address, value);
                break;
            }
        }
    }
    void Write16(AddressType address, uint16_t value)
    {
        for (auto & mapping : m_mappings)
        {
            if (mapping.IsHit(address))
            {
                mapping.Write16(address, value);
                break;
            }
        }
    }
    void Write32(AddressType address, uint32_t value);
    void Write64(AddressType address, uint64_t value);

    void Read8(AddressType address, uint8_t& value)
    {
        for (auto & mapping : m_mappings)
        {
            if (mapping.IsHit(address))
            {
                mapping.Read8(address, value);
                break;
            }
        }
    }
    void Read16(AddressType address, uint16_t& value)
    {
        for (auto & mapping : m_mappings)
        {
            if (mapping.IsHit(address))
            {
                mapping.Read16(address, value);
                break;
            }
        }
    }
    void Read32(AddressType address, uint32_t& value);
    void Read64(AddressType address, uint64_t& value);
};

template<class AddressType>
class GenericMemorySpace
    : public IMemoryAccess<AddressType>
{
private:
    std::size_t m_maxAddress;
    std::vector<uint8_t> m_memory;

public:
    GenericMemorySpace(AddressType maxAddress)
        : m_maxAddress{ static_cast<size_t>(maxAddress) }
        , m_memory{}
    {
        m_memory.reserve(m_maxAddress + 1);
        m_memory.resize(m_maxAddress + 1);
    }
    void Load(AddressType offset, AddressType size, const std::vector<uint8_t>& data)
    {
        std::copy(data.begin(), data.begin() + size, m_memory.begin() + offset);
    }
    void Save(AddressType offset, AddressType size, std::vector<uint8_t>& data)
    {
        std::copy(m_memory.begin() + offset, m_memory.begin() + offset + size, data.begin());
    }

    void Write8(AddressType address, uint8_t value)
    {
        if (static_cast<size_t>(address) <= m_maxAddress)
            m_memory[static_cast<size_t>(address)] = value;
    }
    void Write16(AddressType address, uint16_t value)
    {
        if (static_cast<size_t>(address + 1) <= m_maxAddress)
        {
            m_memory[static_cast<size_t>(address + 0)] = static_cast<uint8_t>((value >> 0) & 0xFF);
            m_memory[static_cast<size_t>(address + 1)] = static_cast<uint8_t>((value >> 8) & 0xFF);
        }
    }
    void Write32(AddressType address, uint32_t value)
    {
        if (static_cast<size_t>(address + 3) <= m_maxAddress)
        {
            m_memory[static_cast<size_t>(address + 0)] = static_cast<uint8_t>((value >> 0) & 0xFF);
            m_memory[static_cast<size_t>(address + 1)] = static_cast<uint8_t>((value >> 8) & 0xFF);
            m_memory[static_cast<size_t>(address + 2)] = static_cast<uint8_t>((value >> 16) & 0xFF);
            m_memory[static_cast<size_t>(address + 3)] = static_cast<uint8_t>((value >> 24) & 0xFF);
        }
    }
    void Write64(AddressType address, uint64_t value)
    {
        if (static_cast<size_t>(address + 7) <= m_maxAddress)
        {
            m_memory[static_cast<size_t>(address + 0)] = static_cast<uint8_t>((value >> 0) & 0xFF);
            m_memory[static_cast<size_t>(address + 1)] = static_cast<uint8_t>((value >> 8) & 0xFF);
            m_memory[static_cast<size_t>(address + 2)] = static_cast<uint8_t>((value >> 16) & 0xFF);
            m_memory[static_cast<size_t>(address + 3)] = static_cast<uint8_t>((value >> 24) & 0xFF);
            m_memory[static_cast<size_t>(address + 4)] = static_cast<uint8_t>((value >> 32) & 0xFF);
            m_memory[static_cast<size_t>(address + 5)] = static_cast<uint8_t>((value >> 40) & 0xFF);
            m_memory[static_cast<size_t>(address + 6)] = static_cast<uint8_t>((value >> 48) & 0xFF);
            m_memory[static_cast<size_t>(address + 7)] = static_cast<uint8_t>((value >> 56) & 0xFF);
        }
    }

    void Read8(AddressType address, uint8_t& value)
    {
        if (static_cast<size_t>(address) <= m_maxAddress)
            value = m_memory[static_cast<size_t>(address)];
    }
    void Read16(AddressType address, uint16_t& value)
    {
        if (static_cast<size_t>(address + 1) <= m_maxAddress)
        {
            value = static_cast<uint16_t>(static_cast<uint16_t>(m_memory[static_cast<size_t>(address + 0)]) << 0);
            value |= static_cast<uint16_t>(static_cast<uint16_t>(m_memory[static_cast<size_t>(address + 1)]) << 8);
        }
    }
    void Read32(AddressType address, uint32_t& value)
    {
        if (static_cast<size_t>(address + 3) <= m_maxAddress)
        {
            value = static_cast<uint32_t>(m_memory[static_cast<size_t>(address + 0)]) << 0;
            value |= static_cast<uint32_t>(m_memory[static_cast<size_t>(address + 1)]) << 8;
            value |= static_cast<uint32_t>(m_memory[static_cast<size_t>(address + 2)]) << 16;
            value |= static_cast<uint32_t>(m_memory[static_cast<size_t>(address + 3)]) << 24;
        }
    }
    void Read64(AddressType address, uint64_t& value)
    {
        if (static_cast<size_t>(address + 7) <= m_maxAddress)
        {
            value = static_cast<uint64_t>(m_memory[static_cast<size_t>(address + 0)]) << 0;
            value |= static_cast<uint64_t>(m_memory[static_cast<size_t>(address + 1)]) << 8;
            value |= static_cast<uint64_t>(m_memory[static_cast<size_t>(address + 2)]) << 16;
            value |= static_cast<uint64_t>(m_memory[static_cast<size_t>(address + 3)]) << 24;
            value |= static_cast<uint64_t>(m_memory[static_cast<size_t>(address + 4)]) << 32;
            value |= static_cast<uint64_t>(m_memory[static_cast<size_t>(address + 5)]) << 40;
            value |= static_cast<uint64_t>(m_memory[static_cast<size_t>(address + 6)]) << 48;
            value |= static_cast<uint64_t>(m_memory[static_cast<size_t>(address + 7)]) << 56;
        }
    }
};

template<class AddressType>
class GenericROM
    : public IMemoryAccess<AddressType>
{
private:
    GenericMemorySpace<AddressType>& m_memorySpace;
    AddressType m_offset;
    AddressType m_size;

public:
    GenericROM(GenericMemorySpace<AddressType>& memorySpace, AddressType offset, AddressType size)
        : m_memorySpace{ memorySpace }
        , m_offset{ offset }
        , m_size{ size }
    {
    }
    GenericROM(const GenericROM &) = delete;
    GenericROM(GenericROM &&) = delete;

    GenericROM &operator = (const GenericROM &) = delete;
    GenericROM &operator = (GenericROM &&) = delete;

    AddressType StartAddress() const
    {
        return m_offset;
    }
    AddressType EndAddress() const
    {
        return static_cast<AddressType>(m_offset + m_size - 1);
    }
    AddressType Size() const
    {
        return m_size;
    }
    void Write8(AddressType /*address*/, uint8_t /*value*/)
    {
    }
    void Write16(AddressType /*address*/, uint16_t /*value*/)
    {
    }
    void Write32(AddressType /*address*/, uint32_t /*value*/)
    {
    }
    void Write64(AddressType /*address*/, uint64_t /*value*/)
    {
    }

    void Read8(AddressType address, uint8_t& value)
    {
        m_memorySpace.Read8(static_cast<AddressType>(address + m_offset), value);
    }
    void Read16(AddressType address, uint16_t& value)
    {
        m_memorySpace.Read16(static_cast<AddressType>(address + m_offset), value);
    }
    void Read32(AddressType address, uint32_t& value)
    {
        m_memorySpace.Read32(static_cast<AddressType>(address + m_offset), value);
    }
    void Read64(AddressType address, uint64_t& value)
    {
        m_memorySpace.Read64(static_cast<AddressType>(address + m_offset), value);
    }
};

template<class AddressType>
class GenericRAM
    : public IMemoryAccess<AddressType>
{
private:
    GenericMemorySpace<AddressType>& m_memorySpace;
    AddressType m_offset;
    AddressType m_size;

public:
    GenericRAM(GenericMemorySpace<AddressType>& memorySpace, AddressType offset, AddressType size)
        : m_memorySpace{ memorySpace }
        , m_offset{ offset }
        , m_size{ size }
    {
    }
    GenericRAM(const GenericRAM &) = delete;
    GenericRAM(GenericRAM &&) = delete;

    GenericRAM &operator = (const GenericRAM &) = delete;
    GenericRAM &operator = (GenericRAM &&) = delete;

    AddressType StartAddress() const
    {
        return m_offset;
    }
    AddressType EndAddress() const
    {
        return static_cast<AddressType>(m_offset + m_size - 1);
    }
    AddressType Size() const
    {
        return m_size;
    }

    void Write8(AddressType address, uint8_t value)
    {
        m_memorySpace.Write8(static_cast<AddressType>(address + m_offset), value);
    }
    void Write16(AddressType address, uint16_t value)
    {
        m_memorySpace.Write16(static_cast<AddressType>(address + m_offset), value);
    }
    void Write32(AddressType address, uint32_t value)
    {
        m_memorySpace.Write32(static_cast<AddressType>(address + m_offset), value);
    }
    void Write64(AddressType address, uint64_t value)
    {
        m_memorySpace.Write64(static_cast<AddressType>(address + m_offset), value);
    }

    void Read8(AddressType address, uint8_t& value)
    {
        m_memorySpace.Read8(static_cast<AddressType>(address + m_offset), value);
    }
    void Read16(AddressType address, uint16_t& value)
    {
        m_memorySpace.Read16(static_cast<AddressType>(address + m_offset), value);
    }
    void Read32(AddressType address, uint32_t& value)
    {
        m_memorySpace.Read32(static_cast<AddressType>(address + m_offset), value);
    }
    void Read64(AddressType address, uint64_t& value)
    {
        m_memorySpace.Read64(static_cast<AddressType>(address + m_offset), value);
    }
};
