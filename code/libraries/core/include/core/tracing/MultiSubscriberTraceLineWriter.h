//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : MultiSubscriberTraceLineWriter.h
//
// Namespace   : core::tracing
//
// Class       : MultiSubscriberTraceLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "tracing/ITraceLineWriter.h"
#include "utility/Observable.h"

namespace core {
namespace tracing {

class MultiSubscriberTraceLineWriter
    : public ::tracing::ITraceLineWriter
    , public utility::Observable<::tracing::ITraceLineWriter>
{
public:
    MultiSubscriberTraceLineWriter();
    ~MultiSubscriberTraceLineWriter();

    void WriteLine(::tracing::TraceCategory category, const std::string & line) override;
};

} // namespace tracing
} // namespace core
