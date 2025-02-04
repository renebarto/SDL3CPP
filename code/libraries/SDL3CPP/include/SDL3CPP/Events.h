#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3CPP/Window.h>

namespace SDL3CPP {

class Event
{
protected:
    SDL_Event m_event;

public:
    friend class Events;
    Event() = default;
    Event(const SDL_Event &e);

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

class QuitEvent
    : public Event
{
public:
    QuitEvent();
};

enum MouseButton
{
    Left = 1,
    Middle = 2,
    Right = 3,
    X1 = 4,
    X2 = 5,
};

using MouseButtonFlags = uint32_t;
extern const MouseButtonFlags MouseButtonMaskLeft;
extern const MouseButtonFlags MouseButtonMaskMiddle;
extern const MouseButtonFlags MouseButtonMaskRight;
extern const MouseButtonFlags MouseButtonMaskX1;
extern const MouseButtonFlags MouseButtonMaskX2;

class MouseMotionEvent
    : public Event
{
public:
    MouseMotionEvent() = default;

    uint64_t Timestamp() const { return m_event.motion.timestamp; }
    WindowID WindowID() const { return m_event.motion.windowID; }
    MouseButtonFlags ButtonState() const { return static_cast<MouseButtonFlags>(m_event.motion.state); }
    float GetX() const { return m_event.motion.x; }
    float GetY() const { return m_event.motion.y; }
    float GetXRel() const { return m_event.motion.xrel; }
    float GetYRel() const { return m_event.motion.yrel; }
    bool IsLeftPressed() const { return (ButtonState() & MouseButtonMaskLeft) != 0; }
    bool IsMiddlePressed() const { return (ButtonState() & MouseButtonMaskMiddle) != 0; }
    bool IsRightPressed() const { return (ButtonState() & MouseButtonMaskRight) != 0; }
    bool IsX1Pressed() const { return (ButtonState() & MouseButtonMaskX1) != 0; }
    bool IsX2Pressed() const { return (ButtonState() & MouseButtonMaskX2) != 0; }
};

class MouseButtonEvent
    : public Event
{
public:
    MouseButtonEvent() = default;

    uint64_t Timestamp() const { return m_event.button.timestamp; }
    WindowID WindowID() const { return m_event.button.windowID; }
    int Button() const { return m_event.button.button; }
    int NumClicks() const { return m_event.button.clicks; }
    float GetX() const { return m_event.button.x; }
    float GetY() const { return m_event.button.y; }
    bool IsPressed() const { return m_event.button.down; }
    bool IsReleased() const { return !m_event.button.down; }
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
    static bool Poll(Event &event);
    static bool WaitEvent(SDL_Event *e);
    static bool WaitEventTimeout(SDL_Event *e, int timeout);
    static bool PushEvent(const SDL_Event *e);
    static bool PushEvent(const Event &e);
    static void SetEventFilter(SDL_EventFilter filter, void *userdata);
    static bool GetEventFilter(SDL_EventFilter *filter, void **userdata);
    static void AddEventWatch(SDL_EventFilter filter, void *userdata);
    static void DelEventWatch(SDL_EventFilter filter, void *userdata);
    static void FilterEvents(SDL_EventFilter filter, void *userdata);
    static uint8_t EventState(uint32_t type, int state);
    static uint32_t RegisterEvents(int numevents);
};

} // namespace SDL3CPP