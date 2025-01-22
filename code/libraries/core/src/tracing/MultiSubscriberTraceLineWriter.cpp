//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : MultiSubscriberTraceLineWriter.cpp
//
// Namespace   : core::tracing
//
// Class       : MultiSubscriberTraceLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#include "core/tracing/MultiSubscriberTraceLineWriter.h"

namespace core {
namespace tracing {

MultiSubscriberTraceLineWriter::MultiSubscriberTraceLineWriter()
{
}

MultiSubscriberTraceLineWriter::~MultiSubscriberTraceLineWriter()
{
}

void MultiSubscriberTraceLineWriter::WriteLine(::tracing::TraceCategory category, const std::string & line)
{
    ForAll([&](::tracing::ITraceLineWriter* writer) { writer->WriteLine(category, line); });
}

} // namespace tracing
} // namespace core