#pragma once

#include <functional>
#include "SDL3CPP/AudioConfiguration.h"

struct SDL_AudioStream;

using AudioDeviceCallback = void (*)(void */*userdata*/, SDL_AudioStream */*stream*/, int /*additional_amount*/, int /*total_amount*/);

namespace SDL3CPP
{

class AudioStream
{
private:
    SDL_AudioStream *m_stream;
    bool m_isPaused;

public:
    AudioStream(AudioDeviceID id, const AudioDeviceSpec &audioSpec, AudioDeviceCallback callback);
    virtual ~AudioStream();

    bool Open(AudioDeviceID id, const AudioDeviceSpec &audioSpec, AudioDeviceCallback callback);
    bool IsEmpty() const;

    float GetSampleFrequencyRatio() const;
    void SetSampleFrequencyRatio(float ratio);

    float GetGain() const;
    void SetGain(float gain);

    bool Clear();
    bool Flush();

    bool IsPaused();
    bool Pause();
    bool Resume();
};

} // namespace SDL3CPP