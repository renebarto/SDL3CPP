//------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : BidirectionalMap.h
//
// Namespace   : serialization
//
// Class       : BidirectionalMap
//
// Description :
// - Template for conversion between two types. Used to serialize and deserialize enum and enum class types
//
//---------------------------------------------------------------

#pragma once

#include <functional>
#include <map>
#include <vector>
#include <utility>
#include <iterator>
#include "serialization/MapUtilities.h"

namespace serialization {

template<class T1, class T2, typename Comp1=std::less<T1>, typename Comp2=std::less<T2>>
class BidirectionalMap
{
public:
    BidirectionalMap()
        : m_T1toT2Map{}
        , m_T2toT1Map{}
    {
    }
    BidirectionalMap(std::initializer_list<std::pair<T1, T2>> values)
    {
        for (auto pair : values)
        {
            m_T1toT2Map.emplace(pair.first, pair.second);
            m_T2toT1Map.emplace(pair.second, pair.first);
        }
    }

    virtual ~BidirectionalMap()
    {
    }

    void Init(const std::initializer_list<std::pair<T1, T2>> values)
    {
        m_T1toT2Map.clear();
        m_T2toT1Map.clear();
        for (auto pair : values)
        {
            m_T1toT2Map.emplace(pair.first, pair.second);
            m_T2toT1Map.emplace(pair.second, pair.first);
        }
    }

    void Init(const std::vector<std::pair<T1, T2>>& values)
    {
        m_T1toT2Map.clear();
        m_T2toT1Map.clear();
        for (auto pair : values)
        {
            m_T1toT2Map.emplace(pair.first, pair.second);
            m_T2toT1Map.emplace(pair.second, pair.first);
        }
    }

    const T2& operator[](const T1& key) const
    {
        return Translate(key);
    }

    const T1& operator[](const T2& key) const
    {
        return Translate(key);
    }

    const T2& Translate(const T1& key) const
    {
        return maptranslation::Translate(m_T1toT2Map, key);
    }

    const T2& Translate(const T1& key, const T2& defaultValue) const noexcept
    {
        return maptranslation::Translate(m_T1toT2Map, key, defaultValue);
    }

    bool Translate(const T1& key, T2 & value, const T2& defaultValue) const noexcept
    {
        return maptranslation::Translate(m_T1toT2Map, key, value, defaultValue);
    }

    const T1& Translate(const T2& key) const
    {
        return maptranslation::Translate(m_T2toT1Map, key);
    }

    const T1& Translate(const T2& key, const T1& defaultValue) const noexcept
    {
        return maptranslation::Translate(m_T2toT1Map, key, defaultValue);
    }

    bool Translate(const T2& key, T1& value, const T1& defaultValue) const noexcept
    {
        return maptranslation::Translate(m_T2toT1Map, key, value, defaultValue);
    }

    const std::map<T1, T2>& GetMap() const
    {
        return m_T1toT2Map;
    }

    std::vector<T1> GetKeys() const
    {
        std::vector<T1> keys;
        for (auto & keyValuePair : m_T1toT2Map)
        {
            keys.emplace_back(keyValuePair.first);
        }

        return keys;
    }

    std::vector<T2> GetValues() const
    {
        std::vector<T2> values;
        for (auto & keyValuePair : m_T1toT2Map)
        {
            values.emplace_back(keyValuePair.second);
        }

        return values;
    }

private:
    std::map<T1, T2, Comp1> m_T1toT2Map;
    std::map<T2, T1, Comp2> m_T2toT1Map;
};

} // namespace serialization
