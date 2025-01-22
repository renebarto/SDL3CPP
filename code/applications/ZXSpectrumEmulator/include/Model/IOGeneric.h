#pragma once

#include <vector>

template<class AddressType>
class IIOAccess
{
public:
    virtual ~IIOAccess() = default;

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
class IOMapping
{
private:
    IIOAccess<AddressType>& m_device;
    AddressType m_startAddress;
    AddressType m_endAddress;

public:
    IOMapping(IIOAccess<AddressType>& device, AddressType startAddress, AddressType endAddress)
        : m_device{ device }
        , m_startAddress{ startAddress }
        , m_endAddress{ endAddress }
    {
    }
    IOMapping(const IOMapping &other)
        : m_device{ other.m_device }
        , m_startAddress{ other.m_startAddress }
        , m_endAddress{ other.m_endAddress }
    {
    }
    IOMapping(IOMapping &&) = delete;

    IOMapping &operator =(const IOMapping &) = delete;
    IOMapping &operator =(IOMapping &&) = delete;

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
using IOMappingSet = std::vector<IOMapping<AddressType>>;

template<class AddressType>
class GenericIOMap
{
private:
    IOMappingSet<AddressType> m_mappings;

public:
    GenericIOMap(const IOMappingSet<AddressType> &mappings)
        : m_mappings{ mappings}
    {
    }
    void AddIOMapping(const IOMapping<AddressType> &mapping)
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
