#pragma once

#include <SDL3/SDL_events.h>

namespace SDL3CPP {

class Event
{
private:
    SDL_Event m_event;

public:
    friend class Events;
    Event() = default;

    uint32_t Type() const
    {
        return m_event.type;
    }
    bool IsKeyDown() const
    {
        return m_event.type == SDL_EVENT_KEY_DOWN;
    }
    SDL_Keycode Key() const
    {
        return m_event.key.key;
    }
};

class Events
{
public:
    Events();

    static void PumpEvents();
    static int PeepEvents(SDL_Event *events, int numevents, SDL_EventAction action, uint32_t minType, uint32_t maxType);
    static bool HasEvent(uint32_t type);
    static bool HasEvents(uint32_t minType, uint32_t maxType);
    static void FlushEvent(uint32_t type);
    static void FlushEvents(uint32_t minType, uint32_t maxType);
    static int Poll(Event &event);
    static int WaitEvent(SDL_Event *event);
    static int WaitEventTimeout(SDL_Event *event, int timeout);
    static int PushEvent(SDL_Event *event);
    static void SetEventFilter(SDL_EventFilter filter, void *userdata);
    static bool GetEventFilter(SDL_EventFilter *filter, void **userdata);
    static void AddEventWatch(SDL_EventFilter filter, void *userdata);
    static void DelEventWatch(SDL_EventFilter filter, void *userdata);
    static void FilterEvents(SDL_EventFilter filter, void *userdata);
    static uint8_t EventState(uint32_t type, int state);
    static uint32_t RegisterEvents(int numevents);
};

} // namespace SDL3CPP