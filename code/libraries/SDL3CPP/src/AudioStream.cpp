#include "SDL3CPP/AudioStream.h"

#include <SDL3/SDL.h>

using namespace SDL3CPP;

AudioStream::AudioStream(AudioDeviceID id, const AudioDeviceSpec &audioSpec, AudioDeviceCallback callback)
    : m_stream{}
    , m_isPaused{}
{
    Open(id, audioSpec, callback);
}

AudioStream::~AudioStream()
{
    if (m_stream != nullptr)
        SDL_DestroyAudioStream(m_stream);
}


bool AudioStream::Open(AudioDeviceID id, const AudioDeviceSpec &audioSpec, AudioDeviceCallback callback)
{
    SDL_AudioSpec spec { static_cast<SDL_AudioFormat>(audioSpec.sampleFormat), audioSpec.channels, audioSpec.sampleFreq };
    m_stream = SDL_OpenAudioDeviceStream(id, &spec, callback, nullptr);
    if (m_stream == nullptr)
    {
        SDL_Log("Cannot open stream %u, error %s", id, SDL_GetError());
        return false;
    }
    return true;
}

bool AudioStream::IsEmpty() const
{
    return m_stream == nullptr;
}

float AudioStream::GetSampleFrequencyRatio() const
{
    return SDL_GetAudioStreamFrequencyRatio(m_stream);
}

void AudioStream::SetSampleFrequencyRatio(float ratio)
{
    SDL_SetAudioStreamFrequencyRatio(m_stream, ratio);
}

float AudioStream::GetGain() const
{
    return SDL_GetAudioStreamGain(m_stream);
}

void AudioStream::SetGain(float gain)
{
    SDL_SetAudioStreamGain(m_stream, gain);
}

bool AudioStream::Clear()
{
    return SDL_ClearAudioStream(m_stream);
}

bool AudioStream::Flush()
{
    return SDL_FlushAudioStream(m_stream);
}

bool AudioStream::IsPaused()
{
    return m_isPaused;
}

bool AudioStream::Pause()
{
    m_isPaused = true;
    return SDL_PauseAudioStreamDevice(m_stream);
}

bool AudioStream::Resume()
{
    m_isPaused = false;
    return SDL_ResumeAudioStreamDevice(m_stream);
}
