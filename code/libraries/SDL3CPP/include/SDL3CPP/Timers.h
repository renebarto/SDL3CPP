#pragma once

#include <SDL3/SDL_timer.h>

namespace SDL3CPP {

class MilliSecondTimer
{
private:
    uint32_t m_intervalMilliSeconds;
    SDL_TimerCallback m_callback;
    void *m_userData;
    SDL_TimerID m_id;

public:
    MilliSecondTimer() = default;
    MilliSecondTimer(uint32_t intervalMilliSeconds, SDL_TimerCallback callback, void *userData)
        : m_intervalMilliSeconds{ intervalMilliSeconds }
        , m_callback{ callback }
        , m_userData{ userData }
    { }
    uint32_t GetInterval() const { return m_intervalMilliSeconds; }
    SDL_TimerCallback GetCallback() const { return m_callback; }
    void *GetUserData() const { return m_userData; }
    SDL_TimerID GetID() const { return m_id; }
    void SetID(SDL_TimerID id) { m_id = id; }
};

class NanoSecondTimer
{
private:
    uint64_t m_intervalNanoSeconds;
    SDL_NSTimerCallback m_callback;
    void *m_userData;
    SDL_TimerID m_id;

public:
    NanoSecondTimer() = default;
    NanoSecondTimer(uint32_t intervalNanoSeconds, SDL_NSTimerCallback callback, void *userData)
        : m_intervalNanoSeconds{ intervalNanoSeconds }
        , m_callback{ callback }
        , m_userData{ userData }
    { }
    uint64_t GetInterval() const { return m_intervalNanoSeconds; }
    SDL_NSTimerCallback GetCallback() const { return m_callback; }
    void *GetUserData() const { return m_userData; }
    SDL_TimerID GetID() const { return m_id; }
    void SetID(SDL_TimerID id) { m_id = id; }
};

class Timers
{
public:
    static uint64_t GetTicksMilliSecond();
    static uint64_t GetTicksNanoSecond();
    static uint64_t GetPerformanceCounter();
    static uint64_t GetPerformanceFrequency();
    static void DelayMilliSeconds(uint32_t milliSeconds);
    static void DelayNanoSeconds(uint64_t nanoSeconds);
    static void DelayPrecise(uint64_t nanoSeconds);
    static bool Add(MilliSecondTimer &timer);
    static bool Remove(MilliSecondTimer &timer);
    static bool Add(NanoSecondTimer &timer);
    static bool Remove(NanoSecondTimer &timer);
};

} // namespace SDL3CPP