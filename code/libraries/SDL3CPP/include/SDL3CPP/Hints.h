#pragma once

#include <SDL3/SDL_hints.h>

namespace SDL3CPP {

class Hints
{
public:
    static bool SetHintWithPriority(const char *name, const char *value, SDL_HintPriority priority);
    static bool SetHint(const char *name, const char *value);
    static bool ResetHint(const char *name);
    static void ResetHints();
    static const char *GetHint(const char *name);
    static bool GetHintBoolean(const char *name, bool default_value);
    static void AddHintCallback(const char *name, SDL_HintCallback callback, void *userdata);
    static void DelHintCallback(const char *name, SDL_HintCallback callback, void *userdata);
    static void ClearHints();
};

} // namespace SDL3CPP
