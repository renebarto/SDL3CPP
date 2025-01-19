#include "App.h"

#include "SDL3CPP/Hints.h"
#include "SDL3CPP/Rect.h"
#include "SDL3CPP/SDL.h"
#include "SDL3CPP/SDLImage.h"
#include <iostream>
#include <ostream>

using namespace SDL3CPP;

// Screen dimension constants
static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

App::App()
    : m_window{}
    , m_renderer{}
    , m_screenSurface{}
    , m_spriteClips{}
    , m_spriteSheetTexture{}
{
}

App::~App()
{
}

bool App::Init()
{
    // Initialization flag
    bool success = true;

    try
    {
        GetSDL(SDL_INIT_VIDEO);
        // Create window
        if (!m_window.Create("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0))
        {
            std::cout << "Window could not be created!: " << SDL_GetError() << std::endl;
            success = false;
        }
        // Create renderer for window
        m_renderer = Renderer(m_window, nullptr);
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

    // Load Foo' texture
    m_spriteSheetTexture = LoadTextureWithColorKey(std::filesystem::path(IMAGE_DIR) / "dots.png", 0x00, 0xFF, 0xFF);
    if (m_spriteSheetTexture.IsEmpty())
    {
        std::cout << "Failed to load sprite sheet texture image!" << std::endl;
        success = false;
    }

    // Set top left sprite
    m_spriteClips[0].x = 0.0F;
    m_spriteClips[0].y = 0.0F;
    m_spriteClips[0].w = 100.0F;
    m_spriteClips[0].h = 100.0F;

    // Set top right sprite
    m_spriteClips[1].x = 100.0F;
    m_spriteClips[1].y = 0.0F;
    m_spriteClips[1].w = 100.0F;
    m_spriteClips[1].h = 100.0F;

    // Set bottom left sprite
    m_spriteClips[2].x = 0.0F;
    m_spriteClips[2].y = 100.0F;
    m_spriteClips[2].w = 100.0F;
    m_spriteClips[2].h = 100.0F;

    // Set bottom right sprite
    m_spriteClips[3].x = 100.0F;
    m_spriteClips[3].y = 100.0F;
    m_spriteClips[3].w = 100.0F;
    m_spriteClips[3].h = 100.0F;

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

void App::Close()
{
}

void App::Render()
{
    // Clear screen
    m_renderer.SetDrawColor(0x8F, 0x8F, 0x8F, 0xFF);
    m_renderer.Clear();

    // Render top left sprite
    m_renderer.Copy(m_spriteSheetTexture, m_spriteClips[0], FPoint(0, 0));

    // Render top right sprite
    m_renderer.Copy(m_spriteSheetTexture, m_spriteClips[1], FPoint(SCREEN_WIDTH - m_spriteClips[1].w, 0));

    // Render bottom left sprite
    m_renderer.Copy(m_spriteSheetTexture, m_spriteClips[2], FPoint(0, SCREEN_HEIGHT - m_spriteClips[2].h));

    // Render bottom right sprite
    m_renderer.Copy(m_spriteSheetTexture, m_spriteClips[3], FPoint(SCREEN_WIDTH - m_spriteClips[3].w, SCREEN_HEIGHT - m_spriteClips[3].h));

    // Update screen
    m_renderer.Present();
}
