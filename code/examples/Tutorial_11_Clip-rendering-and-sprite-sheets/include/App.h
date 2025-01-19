#pragma once

#include "SDL3CPP/Renderer.h"
#include "SDL3CPP/Surface.h"
#include "SDL3CPP/Texture.h"
#include "SDL3CPP/Window.h"

class App
{
private:
    // The window we'll be rendering to
    SDL3CPP::Window m_window;

    // The window renderer
    SDL3CPP::Renderer m_renderer;

    // The surface contained by the window
    SDL3CPP::Surface m_screenSurface;

    // Scene textures
    SDL3CPP::FRect m_spriteClips[ 4 ];
    SDL3CPP::Texture m_spriteSheetTexture;

public:
    App();
    virtual ~App();

    // Starts up SDL and creates window
    bool Init();

    // Loads media
    bool LoadMedia();
    SDL3CPP::Surface LoadSurface(const std::filesystem::path &path);
    SDL3CPP::Texture LoadTexture(const std::filesystem::path &path);
    SDL3CPP::Texture LoadTextureWithColorKey(const std::filesystem::path &path, uint8_t colorKeyR, uint8_t colorKeyG, uint8_t colorKeyB);

    // Frees media and shuts down SDL
    void Close();

    void Render();
};
