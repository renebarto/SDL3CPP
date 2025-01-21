#pragma once

#include <map>
#include <string>
#include <set>

namespace SDL3CPP {

using AudioDeviceID = uint32_t;
extern const AudioDeviceID DefaultPlaybackAudioDeviceID;
extern const AudioDeviceID DefaultRecordingAudioDeviceID;

enum class AudioFormat
{
    Unknown   = 0x0000u,    // Unspecified audio format
    UInt8     = 0x0008u,    // Unsigned 8-bit samples SDL_DEFINE_AUDIO_FORMAT(0, 0, 0, 8),
    SInt8     = 0x8008u,    // Signed 8-bit samples SDL_DEFINE_AUDIO_FORMAT(1, 0, 0, 8),
    SInt16LE  = 0x8010u,    // Signed 16-bit samples SDL_DEFINE_AUDIO_FORMAT(1, 0, 0, 16),
    SInt16BE  = 0x9010u,    // As above, but big-endian byte order SDL_DEFINE_AUDIO_FORMAT(1, 1, 0, 16),
    SInt32LE  = 0x8020u,    // 32-bit integer samples SDL_DEFINE_AUDIO_FORMAT(1, 0, 0, 32),
    SInt32BE  = 0x9020u,    // As above, but big-endian byte order SDL_DEFINE_AUDIO_FORMAT(1, 1, 0, 32),
    Float32LE = 0x8120u,    // 32-bit floating point samples SDL_DEFINE_AUDIO_FORMAT(1, 0, 1, 32),
    Float32BE = 0x9120u,    // As above, but big-endian byte order SDL_DEFINE_AUDIO_FORMAT(1, 1, 1, 32),
};

struct AudioDeviceSpec
{
    AudioFormat sampleFormat;
    int channels;
    int sampleFreq;
};

struct AudioDeviceFormat
{
    AudioDeviceSpec audioFormat;
    int bufferSampleFrames;
};
using AudioDriverName = std::string;

class AudioStream;

class AudioConfiguration
{
private:
    int m_numAudioDevices;
    std::map<int, AudioDriverName> m_audioDevices;
    std::map<AudioDeviceID, std::string> m_audioDeviceNames;
    std::set<AudioDeviceID> m_audioPlaybackDevices;
    std::set<AudioDeviceID> m_audioRecordingDevices;

public:
    AudioConfiguration();
    void Init();
    void Update();

    bool IsPlaybackDevice(AudioDeviceID id) const;
    bool IsRecordingDevice(AudioDeviceID id) const;
    bool GetDeviceFormat(AudioDeviceID id, AudioDeviceFormat &format) const;
};

} // namespace SDL3CPP