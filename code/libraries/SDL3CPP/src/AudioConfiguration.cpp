#include "SDL3CPP/AudioConfiguration.h"

#include <SDL3/SDL_audio.h>

using namespace SDL3CPP;

const AudioDeviceID SDL3CPP::DefaultPlaybackAudioDeviceID = SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK;
const AudioDeviceID SDL3CPP::DefaultRecordingAudioDeviceID = SDL_AUDIO_DEVICE_DEFAULT_RECORDING;

AudioConfiguration::AudioConfiguration()
    : m_numAudioDevices{}
    , m_audioDevices{}
    , m_audioDeviceNames{}
    , m_audioPlaybackDevices{}
    , m_audioRecordingDevices{}
{
}

void AudioConfiguration::Init()
{
    m_numAudioDevices = SDL_GetNumAudioDrivers();
    for (int i = 0; i < m_numAudioDevices; ++i)
    {
        m_audioDevices.insert({i, SDL_GetAudioDriver(i) });
    }
    int numDevices{};
    auto playbackDeviceIDs = SDL_GetAudioPlaybackDevices(&numDevices);
    for (int i = 0; i < numDevices; ++i)
    {
        auto id = playbackDeviceIDs[i];
        m_audioPlaybackDevices.insert(id);
        m_audioDeviceNames.insert({id, SDL_GetAudioDeviceName(id)});
    }
    SDL_free(playbackDeviceIDs);
    auto recordingDeviceIDs = SDL_GetAudioRecordingDevices(&numDevices);
    for (int i = 0; i < numDevices; ++i)
    {
        auto id = recordingDeviceIDs[i];
        m_audioRecordingDevices.insert(id);
        m_audioDeviceNames.insert({id, SDL_GetAudioDeviceName(id)});
    }
    SDL_free(recordingDeviceIDs);
}

bool AudioConfiguration::IsPlaybackDevice(AudioDeviceID id) const
{
    return m_audioPlaybackDevices.find(id) != m_audioPlaybackDevices.end();
}

bool AudioConfiguration::IsRecordingDevice(AudioDeviceID id) const
{
    return m_audioRecordingDevices.find(id) != m_audioRecordingDevices.end();
}

bool AudioConfiguration::GetDeviceFormat(AudioDeviceID id, AudioDeviceFormat &format) const
{
    SDL_AudioSpec spec;
    int sampleFrames;
    auto result = SDL_GetAudioDeviceFormat(id, &spec, &sampleFrames);
    format = {};
    if (result)
    {
        format.audioFormat.sampleFormat = static_cast<AudioFormat>(spec.format);
        format.audioFormat.channels = spec.channels;
        format.audioFormat.sampleFreq = spec.freq;
        format.bufferSampleFrames = sampleFrames;
    }
    return result;
}
