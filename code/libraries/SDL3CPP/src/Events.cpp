#include "SDL3CPP/Events.h"

#include "SDL3CPP/Timers.h"

using namespace SDL3CPP;

Event::Event(const SDL_Event &e)
    : m_event{ e }
{
}

QuitEvent::QuitEvent()
    : Event{}
{
    m_event = {};
    m_event.type = SDL_EVENT_QUIT;
    m_event.quit = SDL_QuitEvent{ SDL_EVENT_QUIT, 0, Timers::GetTicksNanoSecond() };
}

#define BUTTON_MASK(X)  (1u << ((X)-1))
const MouseButtonFlags SDL3CPP::MouseButtonMaskLeft =   SDL_BUTTON_MASK(MouseButton::Left);
const MouseButtonFlags SDL3CPP::MouseButtonMaskMiddle = SDL_BUTTON_MASK(MouseButton::Middle);
const MouseButtonFlags SDL3CPP::MouseButtonMaskRight =  SDL_BUTTON_MASK(MouseButton::Right);
const MouseButtonFlags SDL3CPP::MouseButtonMaskX1 =     SDL_BUTTON_MASK(MouseButton::X1);
const MouseButtonFlags SDL3CPP::MouseButtonMaskX2 =     SDL_BUTTON_MASK(MouseButton::X2);

bool Events::Poll(Event &event)
{
    return SDL_PollEvent(&event.m_event);
}

bool Events::PushEvent(const SDL_Event *e)
{
    return SDL_PushEvent(const_cast<SDL_Event *>(e));
}
bool Events::PushEvent(const Event &e)
{
    return SDL_PushEvent(const_cast<SDL_Event *>(&e.m_event));
}
