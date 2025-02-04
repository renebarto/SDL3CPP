//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2021 Ren� Barto
//
// File        : Thread.h
//
// Namespace   : core::threading
//
// Class       : Thread
//
// Description : Simple abstraction of std::thread executor, that also catches exceptions thrown in the thread
//
//------------------------------------------------------------------------------

#pragma once

#if defined(PLATFORM_WINDOWS)
#pragma warning(disable: 4265)
#pragma warning(disable: 4355)
#pragma warning(disable: 5204)
#pragma warning(disable: 5220)
#endif
#include <future>
#if defined(PLATFORM_WINDOWS)
#pragma warning(default: 4265)
#pragma warning(default: 4355)
#pragma warning(default: 5204)
#pragma warning(default: 5220)
#endif

#include <functional>
#include <mutex>
#include <ostream>
#include <thread>
#include "osal/utilities/ThreadFunctions.h"
#include "osal/utilities/TypeInfo.h"

namespace core {
namespace threading {

using ThreadFunction = std::function<void ()>;

enum class ThreadState
{
    NotStarted,
    Running,
    Finished,
    Killed,
};

class Thread
{
public:
    Thread();
    Thread(const std::string & name);
    Thread(const Thread &) = delete;
    Thread(ThreadFunction threadFunc);
    Thread(ThreadFunction threadFunc, const std::string & name);
    virtual ~Thread();

    Thread & operator = (const Thread &) = delete;

    void Create(ThreadFunction threadFunc);
    void Destroy();
    bool IsAlive();
    bool IsRunning();
    bool IsFinished();
    bool HasDied();
    const std::string & GetName() const;
    // Important: on Linux, thread must be running for SetName to succeed!
    void SetName(const std::string & name);

    // Wait until thread is in signaled state (thread died)
    void WaitForDeath();

    osal::ThreadPriority GetPriority();
    void SetPriority(osal::ThreadPriority priority);

    void GetResult()
    {
        // Will throw exception thrown by thread if it threw,
        // or std::future_error when thread was not run
        m_threadResult.get();
    }
    bool HaveResult()
    {
        return m_threadResult.valid();
    }

protected:
    typedef std::recursive_mutex Mutex;
    typedef std::lock_guard<Mutex> Lock;

    Mutex m_threadMutex;
    std::thread m_thread;
    std::string m_name;
    ThreadState m_state;
    std::future<void> m_threadResult;
    void Cleanup();
};

template<class ReturnType>
class TypedReturnThread
    : public Thread
{
private:
    std::function<ReturnType ()> m_threadFunc;
    ReturnType m_result;

public:
    TypedReturnThread(std::function<ReturnType ()> threadFunc, const std::string & threadName = {})
        : Thread(threadName)
        , m_threadFunc(threadFunc)
        , m_result()
    {
        Create(std::bind(&TypedReturnThread::ThreadFunc, this));
    }

    ReturnType GetResult() { return m_result; }
    void SetResult(ReturnType value) { m_result = value; }

    void ThreadFunc()
    {
        SetResult(m_threadFunc());
    }
};

} // namespace threading
} // namespace core

inline std::ostream& operator << (std::ostream& stream, const core::threading::Thread& thread)
{
    return stream << osal::type(thread) << "Name=" << thread.GetName();
}

