#include "SDL3CPP/SDL.h"

#include <sstream>
#include <stdexcept>

#include <SDL3/SDL.h>

using namespace SDL3CPP;

const uint32_t SDL::DefaultFlags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS;

SDL::SDL(uint32_t flags /*= DefaultFlags */)
{
    if (!SDL_Init(flags))
    {
        std::ostringstream stream;
        stream << "SDL_Init failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
}

SDL::~SDL()
{
    SDL_Quit();
}

void SDL::Log(const std::string &message)
{
    SDL_Log(message.c_str());
}

uint32_t SDL::WasInitialized(uint32_t flags)
{
    return SDL_WasInit(flags);
}

void SDL::InitSubSystem(uint32_t flags)
{
    if (!SDL_InitSubSystem(flags))
        throw std::runtime_error("SDL_InitSubsystem");
}

void SDL::QuitSubSystem(uint32_t flags)
{
    SDL_QuitSubSystem(flags);
}

SDL &SDL3CPP::GetSDL(uint32_t flags /*= SDL_INIT_EVERYTHING*/)
{
    static SDL instance{ flags };
    return instance;
}
