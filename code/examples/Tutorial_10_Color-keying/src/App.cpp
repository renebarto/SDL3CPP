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
    , m_fooTexture{}
    , m_backgroundTexture{}
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
    m_fooTexture = LoadTextureWithColorKey(std::filesystem::path(IMAGE_DIR) / "foo.png", 0x00, 0xFF, 0xFF);
    if (m_fooTexture.IsEmpty())
    {
        std::cout << "Failed to load Foo' texture image!" << std::endl;
        success = false;
    }

    // Load background texture
    m_backgroundTexture = LoadTexture(std::filesystem::path(IMAGE_DIR) / "background.png");
    if (m_backgroundTexture.IsEmpty())
    {
        std::cout << "Failed to load background texture image!" << std::endl;
        success = false;
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

Texture App::LoadTextureWithColorKey(const std::filesystem::path &path, uint8_t colorKeyR, uint8_t colorKeyG, uint8_t colorKeyB)
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
    m_renderer.SetDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    m_renderer.Clear();

    // Render background texture to screen
    m_renderer.Copy(m_backgroundTexture, NullOpt, FPoint(0, 0));

    // Render Foo' to the screen
    m_renderer.Copy(m_fooTexture, NullOpt, FPoint(240, 190));

    // Update screen
    m_renderer.Present();
}
