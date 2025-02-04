#include "App.h"

#include <filesystem>
#include <iostream>
#include <ostream>

#include "SDL3CPP/Rect.h"
#include "SDL3CPP/SDL.h"
#include "SDL3CPP/SDLTTF.h"
#include "SDL3CPP/SDLImage.h"

using namespace SDL3CPP;

App::App()
    : m_screenWidth{}
    , m_screenHeight{}
    , m_window{}
    , m_renderer{}
    , m_screenSurface{}
    , m_texture{}
    , m_angle{}
    , m_center{}
    , m_flipMode{SDL_FLIP_NONE}
    , m_font{}
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
        GetSDL(SDLInitFlags::Video);
        // Create window
        if (!m_window.Create("SDL Tutorial", m_screenWidth, m_screenHeight, 0))
        {
            SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        // Create renderer for window
        m_renderer = Renderer(m_window, nullptr, RendererVSyncMode::EveryRefresh);
        if (m_renderer.IsEmpty())
        {
            SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        // Initialize renderer color
        m_screenSurface = std::move(Surface(m_window.GetSurface()));
        GetSDLTTF();
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

    // Open the font
    m_font = Font(std::filesystem::path(FONT_DIR) / "lazy.ttf", 28);
    if (m_font.IsEmpty())
    {
        SDL_Log("Failed to load lazy font! SDL_ttf Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Render text
        Color textColor{0, 0, 0};
        m_texture = LoadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor);
        if (m_texture.IsEmpty())
        {
            SDL_Log("Failed to render text texture!\n");
            success = false;
        }
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

SDL3CPP::Texture App::LoadFromRenderedText(const std::string textureText, Color textColor)
{
    // Render text surface
    Surface textSurface = {m_font.RenderBlended(textureText, textColor)};
    Texture texture;
    if (textSurface.IsEmpty())
    {
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create texture from surface pixels
        texture = m_renderer.CreateTexture(textSurface);
        if (texture.IsEmpty())
        {
            SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
    }

    // Return success
    return texture;
}

Texture App::LoadTextureWithColorKey(const std::filesystem::path &path, uint8_t colorKeyR, uint8_t colorKeyG,
                                     uint8_t colorKeyB)
{
    try
    {
        // Load image at specified path
        Surface loadedSurface = GetSDLImage().Load(path);
        loadedSurface.SetColorKey(true,
                                  SDL_MapRGB(loadedSurface.GetPixelFormat(), nullptr, colorKeyR, colorKeyG, colorKeyB));

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

SDL3CPP::FPoint App::GetTextureSize()
{
    return m_texture.GetSize();
}

void App::SetColor(uint8_t red, uint8_t green, uint8_t blue)
{
    m_texture.SetColorMod(red, green, blue);
}

void App::SetAlpha(uint8_t alpha)
{
    m_texture.SetAlphaMod(alpha);
}

void App::SetColorAndAlpha(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    m_texture.SetColorAndAlphaMod(Color(red, green, blue, alpha));
}

void App::SetBlendMode(SDL_BlendMode blending)
{
    m_texture.SetBlendMode(blending);
}

void App::SetAngle(double angle)
{
    m_angle = angle;
}

void App::SetCenter(const SDL3CPP::FPoint &center)
{
    m_center = center;
}

void App::SetFlipMode(SDL_FlipMode flipMode)
{
    m_flipMode = flipMode;
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
    m_renderer.Copy(m_texture, NullOpt, FRect{m_center, m_texture.GetSize()}, m_angle, NullOpt, m_flipMode);

    // Update screen
    m_renderer.Present();
}
