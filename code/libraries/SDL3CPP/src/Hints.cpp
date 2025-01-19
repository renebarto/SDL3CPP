#include "SDL3CPP/Hints.h"

using namespace SDL3CPP;

bool Hints::SetHintWithPriority(const char *name, const char *value, SDL_HintPriority priority)
{
    return SDL_SetHintWithPriority(name, value, priority) != 0;
}

bool Hints::SetHint(const char *name, const char *value)
{
    return SDL_SetHint(name, value) != 0;
}

bool Hints::ResetHint(const char *name)
{
    return SDL_ResetHint(name) != 0;
}

void Hints::ResetHints()
{
    SDL_ResetHints();
}

const char *Hints::GetHint(const char *name)
{
    return SDL_GetHint(name);
}

bool Hints::GetHintBoolean(const char *name, bool defaultValue)
{
    return SDL_GetHintBoolean(name, defaultValue) != 0;
}

void Hints::AddHintCallback(const char *name, SDL_HintCallback callback, void *userData)
{
    SDL_AddHintCallback(name, callback, userData);
}

void Hints::DelHintCallback(const char *name, SDL_HintCallback callback, void *userData)
{
    SDL_RemoveHintCallback(name, callback, userData);
}

void Hints::ClearHints()
{
    SDL_ResetHints();
}
