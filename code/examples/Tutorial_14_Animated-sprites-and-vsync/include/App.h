#pragma once

#include "SDL3CPP/Renderer.h"
#include "SDL3CPP/Surface.h"
#include "SDL3CPP/Texture.h"
#include "SDL3CPP/Window.h"

class App
{
private:
    int m_screenWidth;
    int m_screenHeight;
    // The window we'll be rendering to
    SDL3CPP::Window m_window;

    // The window renderer
    SDL3CPP::Renderer m_renderer;

    // The surface contained by the window
    SDL3CPP::Surface m_screenSurface;

    // Walking animation
    static const int WALKING_ANIMATION_FRAMES = 4;
    static const int WALKING_HOLD_FRAMES = 8;
    SDL3CPP::FRect m_spriteClips[WALKING_ANIMATION_FRAMES];
    // Scene textures
    SDL3CPP::Texture m_spriteSheetTexture;
    int m_frameIndex{};
    SDL3CPP::FRect m_currentClip;

public:
    App();
    virtual ~App();

    // Starts up SDL and creates window
    bool Init(int width, int height);

    // Loads media
    bool LoadMedia();
    SDL3CPP::Surface LoadSurface(const std::filesystem::path &path);
    SDL3CPP::Texture LoadTexture(const std::filesystem::path &path);
    SDL3CPP::Texture LoadTextureWithColorKey(const std::filesystem::path &path, uint8_t colorKeyR, uint8_t colorKeyG,
                                          uint8_t colorKeyB);

    void SetFrameIndex(int frameIndex);
    void AdvanceFrameIndex();

    void Close();

    void Render();
};
