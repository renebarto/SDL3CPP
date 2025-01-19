//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceChannel.h
//
// Namespace   : -
//
// Class       : TraceChannel
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <iostream>
#include "serialization/EnumSerialization.h"

namespace tracing {

enum class TraceChannel
{
    Frontal,
    Lateral,
    AllChannels
};

inline std::ostream& operator << (std::ostream& stream, TraceChannel value)
{
    return stream << serialization::Serialize(value);
}

inline std::string ToShortDescription(TraceChannel value)
{
    return (value == TraceChannel::Frontal ? "F" : (value == TraceChannel::Lateral ? "L" : "A"));
}

} // namespace tracing
