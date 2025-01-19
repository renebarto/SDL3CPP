//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceChannelTest.cpp
//
// Namespace   : tracing
//
// Class       : TraceChannelTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "tracing/TraceChannel.h"
#include "serialization/EnumSerialization.h"

namespace tracing {

    TEST(TraceChannelTest, Trace)
    {
        EXPECT_EQ("Frontal", serialization::Serialize(TraceChannel::Frontal));
        EXPECT_EQ("Lateral", serialization::Serialize(TraceChannel::Lateral));
        EXPECT_EQ("AllChannels", serialization::Serialize(TraceChannel::AllChannels));
    }

} // namespace tracing
