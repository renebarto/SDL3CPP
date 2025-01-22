//---------------------------------------------------------------
// Copyright   : Copyright(c) 2021 René Barto
//
// File        : WorkerThread.h
//
// Namespace   : core::threading
//
// Class       : WorkerThread
//
//
// Description :
//  Thread that signals creator when actually started
//
//---------------------------------------------------------------

#pragma once

#include <chrono>
#include "osal/synchronization/ManualEvent.h"
#include "osal/synchronization/Signal.h"
#include "core/threading/Thread.h"
#include "tracing/Tracing.h"

namespace core {
namespace threading {

class WorkerThread
    : private Thread
{
public:
    WorkerThread() = delete;
    WorkerThread(const WorkerThread &) = delete;
    WorkerThread & operator = (const WorkerThread &) = delete;

    explicit WorkerThread(const StringType & name)
        : core::threading::Thread(name)
        , m_birthEvent()
    {
    }
    virtual ~WorkerThread()
    {
    }

    virtual void Create()
    {
        m_birthEvent.Reset();
        Thread::Create(std::bind(&WorkerThread::ThreadStarter, this));
        WaitForBirth();
    }
    void WaitForBirth()
    {
        m_birthEvent.Wait();
    }
    bool WaitForBirth(std::chrono::nanoseconds timeout)
    {
        return m_birthEvent.Wait(timeout);
    }

    virtual void Thread() = 0;

    using Thread::Destroy;
    using Thread::GetName;
    using Thread::IsRunning;
    using Thread::IsFinished;
    using Thread::WaitForDeath;

protected:
    osal::ManualEvent m_birthEvent;
    void ThreadStarter()
    {
        try
        {
            TraceInfo(__FILE__, __LINE__, __func__, TX("Thread {} starting"), GetName());
            m_birthEvent.Set();
            Thread();
            TraceInfo(__FILE__, __LINE__, __func__, TX("Thread {} stopping"), GetName());
            m_state = ThreadState::Finished;
        }
        catch (const std::exception & e)
        {
            TraceInfo(__FILE__, __LINE__, __func__, TX("Thread {}: Exception thown: {}"), GetName(), ::Convert(e.what()));
            m_birthEvent.Set();
            throw;
        }
    }
};

} // namespace threading
} // namespace core
