//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : ThreadedLogLineWriter.h
//
// Namespace   : core::tracing
//
// Class       : ThreadedLogLineWriter
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <deque>
#include "tracing/ILogLineWriter.h"
#include "core/threading/ActiveObject.h"

namespace core {
namespace tracing {

class ThreadedLogLineWriter
    : public ::tracing::ILogLineWriter
    , public threading::ActiveObject
{
private:
    ::tracing::ILogLineWriter& m_writer;
    std::deque<std::string> m_buffer;
    std::atomic_bool m_stopThread;

public:
    ThreadedLogLineWriter(::tracing::ILogLineWriter& writer);
    ~ThreadedLogLineWriter();

    void WriteLine(const std::string& line) override;

protected:
    void InitThread()  override;
    void Run() override;
    void ExitThread()  override;
    void FlushThread() override;
};

} // namespace tracing
} // namespace core
