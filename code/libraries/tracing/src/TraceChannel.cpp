//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceChannel.cpp
//
// Namespace   : tracing
//
// Class       : TraceChannel
//
// Description :
//
//------------------------------------------------------------------------------

#include "tracing/TraceChannel.h"

#include "serialization/BidirectionalMap.h"
#include "tracing/TraceRegistryItem.h"

namespace serialization {

template<>
const BidirectionalMap<tracing::TraceChannel, std::string> EnumSerializationMap<tracing::TraceChannel>::ConversionMap = 
{
    {tracing::TraceChannel::Frontal, "Frontal"},
    {tracing::TraceChannel::Lateral, "Lateral"},
    {tracing::TraceChannel::AllChannels, "AllChannels"},
};

} // namespace serialization

DEFINE_TRACE_ENTRY();
