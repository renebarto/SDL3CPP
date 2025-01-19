#include "SDL3CPP/SDLTTF.h"

#include <sstream>
#include <stdexcept>

#include <SDL3_ttf/SDL_ttf.h>

using namespace SDL3CPP;

SDLTTF::SDLTTF()
{
    if (!TTF_Init())
    {
        std::ostringstream stream;
        stream << "TTF_Init failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
}

SDLTTF::~SDLTTF()
{
    TTF_Quit();
}

SDLTTF &SDL3CPP::GetSDLTTF()
{
    static SDLTTF instance;
    return instance;
}
