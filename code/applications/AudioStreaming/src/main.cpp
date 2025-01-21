#include <SDL3CPP/SDL.h>
#include <SDL3CPP/AudioConfiguration.h>
#include <SDL3CPP/AudioStream.h>
#include <SDL3/SDL_audio.h>
#include <iostream>
#include <thread>

using namespace SDL3CPP;

static uint8_t audioBuffer[65536];
float phaseL = 0.0F;
float phaseR = 0.0F;
float sampleFreq = 48000.0F;
float freqL = 1000.0F;
float freqR = 4000.0F;
float twoPI = 2 * SDL_PI_D;
float stepL = freqL / sampleFreq * twoPI;
float stepR = freqR / sampleFreq * twoPI;

// Audio callback function
void audio_callback(void */*userdata*/, SDL_AudioStream *stream, int additional_amount, int total_amount)
{
    size_t offset{};
    int sampleFrames = additional_amount / 8;
    for (int i = 0; i < sampleFrames; ++i)
    {
        float sampleL = sin(phaseL);
        float sampleR = sin(phaseR);
        memcpy(audioBuffer + offset, &sampleL, 4);
        offset += 4;
        memcpy(audioBuffer + offset, &sampleR, 4);
        offset += 4;
        phaseL += stepL;
        phaseR += stepR;
        if (phaseL > twoPI)
            phaseL -= twoPI;
        if (phaseR > twoPI)
            phaseR -= twoPI;
    }
    // Put the audio data into the stream
    std::cout << "Get audio, size " << additional_amount << "\r\n";
    SDL_PutAudioStreamData(stream, audioBuffer, sampleFrames * 4);
}

int main(int argc, char *argv[])
{
    try
    {
        // Initialize SDL
        auto &sdl = GetSDL(SDLInitFlags::Audio);

        // Set the desired audio specification
        AudioDeviceSpec desired_spec { AudioFormat::Float32LE, 2, 48000 };
        // Signed 16 bit sample format
        // Two channels (stereo)
        // Sample rate 48000

        AudioStream stream(DefaultPlaybackAudioDeviceID, desired_spec, audio_callback);
        if (stream.IsEmpty())
        {
            std::cout << "Could not open audio: " << SDL_GetError() << "\n";
            return 1;
        }

        // Start playing audio
        stream.Resume();

        std::this_thread::sleep_for(std::chrono::seconds(10));
        stream.Pause();

        // Keep the application running to hear the audio
        std::cout << "Press Enter to quit...\n";
        getchar();
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}
