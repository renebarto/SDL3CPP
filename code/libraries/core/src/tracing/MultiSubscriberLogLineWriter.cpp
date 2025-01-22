//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : MultiSubscriberLogLineWriter.cpp
//
// Namespace   : core::tracing
//
// Class       : MultiSubscriberLogLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#include "core/tracing/MultiSubscriberLogLineWriter.h"

namespace core {
namespace tracing {

MultiSubscriberLogLineWriter::MultiSubscriberLogLineWriter()
{
}

MultiSubscriberLogLineWriter::~MultiSubscriberLogLineWriter()
{
}

void MultiSubscriberLogLineWriter::WriteLine(const std::string & line)
{
    ForAll([&](::tracing::ILogLineWriter* writer) { writer->WriteLine(line); });
}

} // namespace tracing
} // namespace core