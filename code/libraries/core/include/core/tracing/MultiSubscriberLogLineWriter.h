//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : MultiSubscriberLogLineWriter.h
//
// Namespace   : core::tracing
//
// Class       : MultiSubscriberLogLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include "tracing/ILogLineWriter.h"
#include "utility/Observable.h"

namespace core {
namespace tracing {

class MultiSubscriberLogLineWriter
    : public ::tracing::ILogLineWriter
    , public utility::Observable<::tracing::ILogLineWriter>
{
public:
    MultiSubscriberLogLineWriter();
    ~MultiSubscriberLogLineWriter();

    void WriteLine(const std::string& line) override;
};

} // namespace tracing
} // namespace core
