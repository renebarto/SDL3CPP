//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Rene Barto
//
// File        : EnumBitSet.h
//
// Namespace   : utility
//
// Class       : EnumBitSet
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "utility/Serialization.h"
#include <ostream>
#include <set>

namespace utility {

template <class BaseType> class EnumBitSet
{
private:
    std::set<BaseType> m_set;
    using MaskType = typename std::underlying_type<BaseType>::type;

public:
    EnumBitSet()
        : m_set()
    {
    }

    EnumBitSet(const EnumBitSet &other)
        : m_set()
    {
        Set(static_cast<BaseType>(other.GetMask()));
    }

    EnumBitSet(MaskType mask)
        : m_set()
    {
        Set(static_cast<BaseType>(mask));
    }

    EnumBitSet(BaseType traceBaseType)
        : m_set()
    {
        Set(traceBaseType);
    }

    EnumBitSet &operator=(const EnumBitSet &other)
    {
        if (this != &other)
        {
            m_set.clear();
            Set(static_cast<BaseType>(other.GetMask()));
        }
        return *this;
    }

    void Clear()
    {
        m_set.clear();
    }

    void Set(BaseType traceBaseType)
    {
        MaskType tmpMask = static_cast<MaskType>(1 << (sizeof(MaskType) * 8 - 1));
        while (tmpMask != 0)
        {
            if ((static_cast<MaskType>(traceBaseType) & tmpMask) != 0)
                m_set.emplace(static_cast<BaseType>(tmpMask));
            if (std::is_unsigned<MaskType>::value)
                tmpMask >>= 1;
            else
                tmpMask = static_cast<MaskType>((tmpMask >> 1) & ~(static_cast<MaskType>(1) << (sizeof(MaskType) * 8 - 1)));
        }
    }

    void Reset(BaseType traceBaseType)
    {
        m_set.erase(traceBaseType);
    }

    bool IsSet(BaseType traceBaseType) const
    {
        return m_set.find(traceBaseType) != m_set.end();
    }

    MaskType GetMask() const
    {
        MaskType result{};
        MaskType tmpMask = static_cast<MaskType>(1 << (sizeof(MaskType) * 8 - 1));
        while (tmpMask != 0)
        {
            if (IsSet(static_cast<BaseType>(tmpMask)))
                result |= tmpMask;
            if (std::is_unsigned<MaskType>::value)
                tmpMask >>= 1;
            else
                tmpMask = static_cast<MaskType>((tmpMask >> 1) & ~(static_cast<MaskType>(1) << (sizeof(MaskType) * 8 - 1)));
        }
        return result;
    }

    std::string ToString() const
    {
        std::string result;
        MaskType tmpMask = static_cast<MaskType>(1 << (sizeof(MaskType) * 8 - 1));
        while (tmpMask != 0)
        {
            if (IsSet(static_cast<BaseType>(tmpMask)))
            {
                if (!result.empty())
                    result += "|";
                result += serialization::Serialize(static_cast<BaseType>(tmpMask));
            }
            if (std::is_unsigned<MaskType>::value)
                tmpMask >>= 1;
            else
                tmpMask = static_cast<MaskType>((tmpMask >> 1) & ~(static_cast<MaskType>(1) << (sizeof(MaskType) * 8 - 1)));
        }
        return result;
    }

    EnumBitSet &operator|=(BaseType traceBaseType)
    {
        Set(traceBaseType);
        return *this;
    }
};

template <class BaseType>
typename std::enable_if<std::is_enum<BaseType>::value, utility::EnumBitSet<BaseType>>::type inline operator|(
    BaseType lhs, BaseType rhs)
{
    utility::EnumBitSet<BaseType> newSet = lhs;
    newSet |= rhs;
    return newSet;
}

template <class BaseType>
typename std::enable_if<std::is_enum<BaseType>::value, utility::EnumBitSet<BaseType>>::type
inline operator | (
    utility::EnumBitSet<BaseType> lhs, BaseType rhs)
{
    utility::EnumBitSet<BaseType> newSet = lhs;
    newSet |= rhs;
    return newSet;
}

template <class BaseType> inline bool operator ==(const utility::EnumBitSet<BaseType> &lhs, const utility::EnumBitSet<BaseType> &rhs)
{
    return lhs.GetMask() == rhs.GetMask();
}

template <class BaseType>
inline bool operator ==(const typename std::underlying_type<BaseType>::type &lhs, const utility::EnumBitSet<BaseType> &rhs)
{
    return lhs == rhs.GetMask();
}

template <class BaseType>
inline bool operator ==(const utility::EnumBitSet<BaseType> &lhs, const typename std::underlying_type<BaseType>::type &rhs)
{
    return lhs.GetMask() == rhs;
}

template <class BaseType> inline bool operator !=(const utility::EnumBitSet<BaseType> &lhs, const utility::EnumBitSet<BaseType> &rhs)
{
    return lhs.GetMask() != rhs.GetMask();
}

template <class BaseType>
inline bool operator !=(const typename std::underlying_type<BaseType>::type &lhs, const utility::EnumBitSet<BaseType> &rhs)
{
    return lhs != rhs.GetMask();
}

template <class BaseType>
inline bool operator !=(const utility::EnumBitSet<BaseType> &lhs, const typename std::underlying_type<BaseType>::type &rhs)
{
    return lhs.GetMask() != rhs;
}

} // namespace utility

namespace serialization {

template <class BaseType> std::string Serialize(const utility::EnumBitSet<BaseType> &value)
{
    return value.ToString();
}

} // namespace serialization

template <class BaseType> std::ostream &operator<<(std::ostream &stream, const utility::EnumBitSet<BaseType> &value)
{
    return stream << serialization::Serialize(value);
}
