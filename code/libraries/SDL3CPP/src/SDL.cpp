#include "SDL3CPP/SDL.h"

#include <sstream>
#include <stdexcept>

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_rtf/SDL_rtf.h>
#include "SDL3CPP/DisplayConfiguration.h"
#include "SDL3CPP/AudioConfiguration.h"

using namespace SDL3CPP;

SDLInitFlags SDL3CPP::operator | (SDLInitFlags lhs, SDLInitFlags rhs)
{
    return static_cast<SDLInitFlags>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}
SDLInitFlags SDL3CPP::operator & (SDLInitFlags lhs, SDLInitFlags rhs)
{
    return static_cast<SDLInitFlags>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}
bool SDL3CPP::operator ==(SDLInitFlags lhs, uint32_t rhs)
{
    return static_cast<uint32_t>(lhs) == rhs;
}
bool SDL3CPP::operator ==(uint32_t lhs, SDLInitFlags rhs)
{
    return static_cast<uint32_t>(rhs) == lhs;
}
bool SDL3CPP::operator !=(SDLInitFlags lhs, uint32_t rhs)
{
    return !operator == (lhs, rhs);
}
bool SDL3CPP::operator !=(uint32_t lhs, SDLInitFlags rhs)
{
    return !operator == (lhs, rhs);
}

static const SDLInitFlags SDLNativeFlagsMask = 
    SDLInitFlags::Audio | SDLInitFlags::Video | 
    SDLInitFlags::Joystick | SDLInitFlags::Haptic | SDLInitFlags::Gamepad | 
    SDLInitFlags::Events | SDLInitFlags::Sensor | SDLInitFlags::Camera; 

const SDLInitFlags SDL::DefaultFlags = static_cast<SDLInitFlags>(SDLInitFlags::Video | SDLInitFlags::Audio | SDLInitFlags::Events);

MIX_InitFlags ConvertMixerFlags(SDLInitFlags flags)
{
    MIX_InitFlags result{};

    if ((flags & SDLInitFlags::MixerFLAC) != 0) result |=  MIX_INIT_FLAC;
    if ((flags & SDLInitFlags::MixerMOD) != 0) result |=  MIX_INIT_MOD;
    if ((flags & SDLInitFlags::MixerMP3) != 0) result |=  MIX_INIT_MP3;
    if ((flags & SDLInitFlags::MixerOGG) != 0) result |=  MIX_INIT_OGG;
    if ((flags & SDLInitFlags::MixerMID) != 0) result |=  MIX_INIT_MID;
    if ((flags & SDLInitFlags::MixerOPUS) != 0) result |=  MIX_INIT_OPUS;
    if ((flags & SDLInitFlags::MixerWAVPACK) != 0) result |=  MIX_INIT_WAVPACK;
    return result;
}

SDL::SDL(SDLInitFlags flags /*= DefaultFlags */)
    : m_flags{ flags }
    , m_displayConfiguration{}
    , m_audioConfiguration{}
{
    if (!SDL_Init(static_cast<SDL_InitFlags>(flags & SDLNativeFlagsMask)))
    {
        std::ostringstream stream;
        stream << "SDL_Init failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    if ((m_flags & SDLInitFlags::Image) != 0)
    {
        // Nothing to do, IMG_Init no longer exists
    }
    if (((m_flags & SDLInitFlags::Mixer) != 0) | ((m_flags & SDLInitFlags::MixerALL) != 0))
    {
        m_flags = m_flags | SDLInitFlags::Mixer;
        MIX_InitFlags mixInitFlags = ConvertMixerFlags(m_flags);
        Mix_Init(mixInitFlags);
    }
    if ((m_flags & SDLInitFlags::TTF) != 0)
    {
        TTF_Init();
    }
    if ((m_flags & SDLInitFlags::RTF) != 0)
    {
        // Nothing to do
    }
    m_displayConfiguration.Init();
    m_audioConfiguration.Init();
}

SDL::~SDL()
{
    if ((m_flags & SDLInitFlags::Image) != 0)
    {
        // Nothing to do, IMG_Quit no longer exists
    }
    if ((m_flags & SDLInitFlags::Mixer) != 0)
    {
        Mix_Quit();
    }
    if ((m_flags & SDLInitFlags::TTF) != 0)
    {
        TTF_Quit();
    }
    if ((m_flags & SDLInitFlags::RTF) != 0)
    {
        // Nothing to do
    }
    SDL_Quit();
}

void SDL::Log(const std::string &message)
{
    SDL_Log(message.c_str());
}

SDLInitFlags SDL::WasInitialized(SDLInitFlags flags)
{
    SDLInitFlags result{};
    if ((flags & SDLInitFlags::Image) != 0)
    {
        result = result | (m_flags & SDLInitFlags::Image);
    }
    if ((flags & SDLInitFlags::Mixer) != 0)
    {
        result = result | (m_flags & SDLInitFlags::Mixer);
    }
    if ((flags & SDLInitFlags::TTF) != 0)
    {
        result = result | (m_flags & SDLInitFlags::TTF);
    }
    if ((flags & SDLInitFlags::RTF) != 0)
    {
        result = result | (m_flags & SDLInitFlags::RTF);
    }
    result = result | static_cast<SDLInitFlags>(SDL_WasInit(static_cast<SDL_InitFlags>(flags & SDLNativeFlagsMask)));
    return result;
}

void SDL::InitSubSystem(SDLInitFlags flags)
{
    if ((flags & SDLInitFlags::Image) != 0)
    {
        // Nothing to do, IMG_Init no longer exists
    }
    if ((flags & SDLInitFlags::Mixer) != 0)
    {
        Mix_Init(0);
    }
    if ((flags & SDLInitFlags::TTF) != 0)
    {
        TTF_Init();
    }
    if ((flags & SDLInitFlags::RTF) != 0)
    {
        // Nothing to do
    }
    if ((flags & SDLNativeFlagsMask) != 0)
    {
        if (!SDL_InitSubSystem(static_cast<SDL_InitFlags>(flags & SDLNativeFlagsMask)))
            throw std::runtime_error("SDL_InitSubsystem");
    }
}

void SDL::QuitSubSystem(SDLInitFlags flags)
{
    if ((flags & SDLInitFlags::Image) != 0)
    {
        // Nothing to do, IMG_Init no longer exists
    }
    if ((flags & SDLInitFlags::Mixer) != 0)
    {
        Mix_Quit();
    }
    if ((flags & SDLInitFlags::TTF) != 0)
    {
        TTF_Quit();
    }
    if ((flags & SDLInitFlags::RTF) != 0)
    {
        // Nothing to do
    }
    if ((flags & SDLNativeFlagsMask) != 0)
    {
        SDL_QuitSubSystem(static_cast<SDL_InitFlags>(flags & SDLNativeFlagsMask));
    }
}

DisplayConfiguration SDL::GetDisplayConfiguration() const
{
    return m_displayConfiguration;
}

AudioConfiguration SDL::GetAudioConfiguration() const
{
    return m_audioConfiguration;
}

SDL &SDL3CPP::GetSDL(SDLInitFlags flags /*= DefaultFlags*/)
{
    static SDL instance{ flags };
    return instance;
}
