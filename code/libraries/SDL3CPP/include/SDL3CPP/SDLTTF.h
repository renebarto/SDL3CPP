#pragma once

#include <cstdint>
#include <SDL3_ttf/SDL_ttf.h>

namespace SDL3CPP {

class SDLTTF
{
public:
    friend SDLTTF &GetSDLTTF();
    SDLTTF();
    virtual ~SDLTTF();

    SDLTTF(const SDLTTF &other) = delete;
    SDLTTF(SDLTTF &&other) = delete;

    SDLTTF &operator=(const SDLTTF &other) = delete;
    SDLTTF &operator=(SDLTTF &&other) = delete;
};

SDLTTF &GetSDLTTF();

} // namespace SDL3CPP