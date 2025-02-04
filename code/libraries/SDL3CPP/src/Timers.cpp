#include "SDL3CPP/Timers.h"

using namespace SDL3CPP;

uint64_t Timers::GetTicksMilliSecond()
{
    return SDL_GetTicks();
}
uint64_t Timers::GetTicksNanoSecond()
{
    return SDL_GetTicksNS();
}
uint64_t Timers::GetPerformanceCounter()
{
    return SDL_GetPerformanceCounter();
}
uint64_t Timers::GetPerformanceFrequency()
{
    return SDL_GetPerformanceFrequency();
}
void Timers::DelayMilliSeconds(uint32_t milliSeconds)
{
    SDL_Delay(milliSeconds);
}
void Timers::DelayNanoSeconds(uint64_t nanoSeconds)
{
    SDL_DelayNS(nanoSeconds);
}
void Timers::DelayPrecise(uint64_t nanoSeconds)
{
    SDL_DelayPrecise(nanoSeconds);
}
bool Timers::Add(MilliSecondTimer &timer)
{
    auto id = SDL_AddTimer(timer.GetInterval(), timer.GetCallback(), timer.GetUserData());
    timer.SetID(id);
    return id != 0;
}
bool Timers::Remove(MilliSecondTimer &timer)
{
    if (timer.GetID() != 0)
        return SDL_RemoveTimer(timer.GetID());
    timer.SetID(0);
    return false;
}
bool Timers::Add(NanoSecondTimer &timer)
{
    auto id = SDL_AddTimerNS(timer.GetInterval(), timer.GetCallback(), timer.GetUserData());
    timer.SetID(id);
    return id != 0;
}
bool Timers::Remove(NanoSecondTimer &timer)
{
    if (timer.GetID() != 0)
        return SDL_RemoveTimer(timer.GetID());
    timer.SetID(0);
    return false;
}
