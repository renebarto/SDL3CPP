#include "App.h"

#include "SDL3CPP/Hints.h"
#include "SDL3CPP/Rect.h"
#include "SDL3CPP/SDL.h"
#include "SDL3CPP/SDLImage.h"
#include <iostream>
#include <ostream>

using namespace SDL3CPP;

App::App()
    : m_screenWidth{}
    , m_screenHeight{}
    , m_window{}
    , m_renderer{}
    , m_screenSurface{}
    , m_spriteClips{}
    , m_spriteSheetTexture{}
    , m_frameIndex{}
    , m_currentClip{}
{
}

App::~App()
{
}

bool App::Init(int width, int height)
{
    // Initialization flag
    bool success = true;

    try
    {
        m_screenWidth = width;
        m_screenHeight = height;
        GetSDL(SDL_INIT_VIDEO);
        // Create window
        if (!m_window.Create("SDL Tutorial", m_screenWidth, m_screenHeight, 0))
        {
            std::cout << "Window could not be created!: " << SDL_GetError() << std::endl;
            success = false;
        }
        // Create renderer for window
        m_renderer = Renderer(m_window, nullptr, RendererVSyncMode::EveryRefresh);
        if (m_renderer.IsEmpty())
        {
            std::cout << "Renderer could not be created!: " << SDL_GetError() << std::endl;
            success = false;
        }
        // Initialize renderer color
        m_screenSurface = std::move(Surface(m_window.GetSurface()));
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        success = false;
    }
    return success;
}

bool App::LoadMedia()
{
    // Loading success flag
    bool success = true;

    // Load modulated texture
    m_spriteSheetTexture = LoadTextureWithColorKey(std::filesystem::path(IMAGE_DIR) / "foo_walking.png", 0, 255, 255);
    if (m_spriteSheetTexture.IsEmpty())
    {
        std::cout << "Failed to load sprite sheet texture image!" << std::endl;
        success = false;
    }
    else
    {
        // Set sprite clips
        m_spriteClips[0].x = 0.0F;
        m_spriteClips[0].y = 0.0F;
        m_spriteClips[0].w = 64.0F;
        m_spriteClips[0].h = 205.0F;

        m_spriteClips[1].x = 64.0F;
        m_spriteClips[1].y = 0.0F;
        m_spriteClips[1].w = 64.0F;
        m_spriteClips[1].h = 205.0F;

        m_spriteClips[2].x = 128.0F;
        m_spriteClips[2].y = 0.0F;
        m_spriteClips[2].w = 64.0F;
        m_spriteClips[2].h = 205.0F;

        m_spriteClips[3].x = 192.0F;
        m_spriteClips[3].y = 0.0F;
        m_spriteClips[3].w = 64.0F;
        m_spriteClips[3].h = 205.0F;
    }

    return success;
}

Surface App::LoadSurface(const std::filesystem::path &path)
{
    try
    {
        // Load image at specified path
        Surface loadedSurface = GetSDLImage().Load(path);

        // Convert surface to screen format
        Surface optimizedSurface = loadedSurface.Convert(m_screenSurface.GetFormatCode());
        return optimizedSurface;
    }
    catch (std::exception &e)
    {
        std::cout << "Cannot load image " << path << ":" << e.what() << std::endl;
    }

    return Surface();
}

Texture App::LoadTexture(const std::filesystem::path &path)
{
    try
    {
        // Load image at specified path
        Surface loadedSurface = GetSDLImage().Load(path);

        // Create texture from surface pixels
        Texture loadedTexture(m_renderer, loadedSurface);
        if (loadedTexture.IsEmpty())
        {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }

        return loadedTexture;
    }
    catch (std::exception &e)
    {
        std::cout << "Cannot load image " << path << ":" << e.what() << std::endl;
    }

    return Texture();
}

Texture App::LoadTextureWithColorKey(const std::filesystem::path &path, uint8_t colorKeyR, uint8_t colorKeyG,
                                     uint8_t colorKeyB)
{
    try
    {
        // Load image at specified path
        Surface loadedSurface = GetSDLImage().Load(path);
        loadedSurface.SetColorKey(true, SDL_MapRGB(loadedSurface.GetPixelFormat(), nullptr, colorKeyR, colorKeyG, colorKeyB));

        // Create texture from surface pixels
        Texture loadedTexture(m_renderer, loadedSurface);
        if (loadedTexture.IsEmpty())
        {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }

        return loadedTexture;
    }
    catch (std::exception &e)
    {
        std::cout << "Cannot load image " << path << ":" << e.what() << std::endl;
    }

    return Texture();
}

void App::SetFrameIndex(int frameIndex)
{
    // Render current frame
    m_frameIndex = frameIndex;
    m_currentClip = m_spriteClips[m_frameIndex / WALKING_HOLD_FRAMES];
}

void App::AdvanceFrameIndex()
{
    SetFrameIndex((m_frameIndex + 1) % (WALKING_ANIMATION_FRAMES * WALKING_HOLD_FRAMES));
}

void App::Close()
{
}

void App::Render()
{
    // Clear screen
    m_renderer.SetDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    m_renderer.Clear();

    // Render sprite texture
    m_renderer.Copy(m_spriteSheetTexture, m_currentClip, FPoint((static_cast<float>(m_screenWidth) - m_currentClip.w) / 2.0F, (static_cast<float>(m_screenHeight) - m_currentClip.h) / 2.0F));

    // Update screen
    m_renderer.Present();
}
