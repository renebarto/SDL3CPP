#include "SDL3CPP/Events.h"

using namespace SDL3CPP;

int Events::Poll(Event &event)
{
    return SDL_PollEvent(&event.m_event);
}
