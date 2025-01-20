#pragma once

#include <cstdint>
#include <string>
#include "utility/Format.h"
#include "SDL3CPP/AudioConfiguration.h"
#include "SDL3CPP/DisplayConfiguration.h"

namespace SDL3CPP {

enum class SDLInitFlags : uint32_t
{
    Audio = 0x00000010u,        // `Audio` implies `Events`
    Video = 0x00000020u,        // `Video` implies `Events`, should be initialized on the main thread
    Joystick = 0x00000200u,     // `Joystick` implies `Events`, should be initialized on the same thread as Video on Windows if you don't set SDL_HINT_JOYSTICK_THREAD
    Haptic = 0x00001000u,
    Gamepad = 0x00002000u,      // `Gamepad` implies `Joystick`
    Events = 0x00004000u,
    Sensor = 0x00008000u,       // `Sensor` implies `Events`
    Camera = 0x00010000u,       // `Camera` implies `Events`
    Mixer = 0x00100000u,        // Include and start up SDL_mixer
    Image = 0x00200000u,        // Include and start up SDL_image
    TTF = 0x00400000u,          // Include and start up SDL_ttf
    RTF = 0x00800000u,          // Include and start up SDL_rtf
    MixerFLAC = 0x01000000,     // FLAC support, implies `Mixer`
    MixerMOD = 0x02000000,      // MOD support, implies `Mixer`
    MixerMP3 = 0x04000000,      // MP3 support, implies `Mixer`
    MixerOGG = 0x08000000,      // OGG support, implies `Mixer`
    MixerMID = 0x10000000,      // MID support, implies `Mixer`
    MixerOPUS = 0x20000000,     // OPUS support, implies `Mixer`
    MixerWAVPACK = 0x40000000,  // WAV support, implies `Mixer`
    MixerALL = 0x7F000000,      // All audio support, implies `Mixer`
};
SDLInitFlags operator | (SDLInitFlags lhs, SDLInitFlags rhs);
SDLInitFlags operator & (SDLInitFlags lhs, SDLInitFlags rhs);
bool operator ==(SDLInitFlags lhs, uint32_t rhs);
bool operator ==(uint32_t lhs, SDLInitFlags rhs);
bool operator !=(SDLInitFlags lhs, uint32_t rhs);
bool operator !=(uint32_t lhs, SDLInitFlags rhs);

class SDL
{
private:
    SDLInitFlags m_flags;
    DisplayConfiguration m_displayConfiguration;
    AudioConfiguration m_audioConfiguration;

public:
    static const SDLInitFlags DefaultFlags;
    friend SDL &GetSDL(SDLInitFlags flags = DefaultFlags);
    SDL(SDLInitFlags flags = DefaultFlags);
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

    SDLInitFlags WasInitialized(SDLInitFlags flags);
    void InitSubSystem(SDLInitFlags flags);
    void QuitSubSystem(SDLInitFlags flags);

    DisplayConfiguration GetDisplayConfiguration() const;
    AudioConfiguration GetAudioConfiguration() const;
};

SDL &GetSDL(SDLInitFlags flags /*= DefaultFlags*/);

} // namespace SDL3CPP