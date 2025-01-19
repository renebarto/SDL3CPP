#pragma once

#include <cstdint>
#include <string>
#include "utility/Format.h"

namespace SDL3CPP {

class SDL
{
public:
    static const uint32_t DefaultFlags;
    friend SDL &GetSDL(uint32_t flags = DefaultFlags);
    SDL(uint32_t flags = DefaultFlags);
    virtual ~SDL();

    SDL(const SDL &other) = delete;
    SDL(SDL &&other) = delete;

    SDL &operator=(const SDL &other) = delete;
    SDL &operator=(SDL &&other) = delete;

    template <typename ... Args>
    void Log(const char *format, Args const& ... args)
    {
        Log(utility::FormatString(format, args ...));
    }
    void Log(const std::string &message);
    uint32_t WasInitialized(uint32_t flags);
    void InitSubSystem(uint32_t flags);
    void QuitSubSystem(uint32_t flags);
};

SDL &GetSDL(uint32_t initializer);

} // namespace SDL3CPP