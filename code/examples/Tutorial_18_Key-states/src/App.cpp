#include "App.h"

#include <filesystem>
#include <iostream>
#include <ostream>

#include "SDL3CPP/Rect.h"
#include "SDL3CPP/SDL.h"
#include "SDL3CPP/SDLImage.h"
#include "SDL3CPP/SDLTTF.h"

using namespace SDL3CPP;

App::App()
    : m_screenWidth{}
    , m_screenHeight{}
    , m_window{}
    , m_renderer{}
    , m_screenSurface{}
    , m_pressTexture{}
    , m_upTexture{}
    , m_downTexture{}
    , m_leftTexture{}
    , m_rightTexture{}
    , m_selectedTexture{}
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
        GetSDL(SDL_INIT_VIDEO);
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

    // Load press texture
    m_pressTexture = LoadTextureWithColorKey(std::filesystem::path(IMAGE_DIR) / "press.png", 0, 0xFF, 0xFF);
    if (m_pressTexture.IsEmpty())
    {
        SDL_Log("Failed to load press texture!\n");
        success = false;
    }

    // Load up texture
    m_upTexture = LoadTextureWithColorKey(std::filesystem::path(IMAGE_DIR) / "up.png", 0, 0xFF, 0xFF);
    if (m_upTexture.IsEmpty())
    {
        SDL_Log("Failed to load up texture!\n");
        success = false;
    }

    // Load down texture
    m_downTexture = LoadTextureWithColorKey(std::filesystem::path(IMAGE_DIR) / "down.png", 0, 0xFF, 0xFF);
    if (m_downTexture.IsEmpty())
    {
        SDL_Log("Failed to load down texture!\n");
        success = false;
    }

    // Load left texture
    m_leftTexture = LoadTextureWithColorKey(std::filesystem::path(IMAGE_DIR) / "left.png", 0, 0xFF, 0xFF);
    if (m_leftTexture.IsEmpty())
    {
        SDL_Log("Failed to load left texture!\n");
        success = false;
    }

    // Load right texture
    m_rightTexture = LoadTextureWithColorKey(std::filesystem::path(IMAGE_DIR) / "right.png", 0, 0xFF, 0xFF);
    if (m_rightTexture.IsEmpty())
    {
        SDL_Log("Failed to load right texture!\n");
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
    return m_selectedTexture ? m_selectedTexture->GetSize() : FPoint{};
}

void App::SetColor(uint8_t red, uint8_t green, uint8_t blue)
{
    if (m_selectedTexture != nullptr)
        m_selectedTexture->SetColorMod(red, green, blue);
}

void App::SetAlpha(uint8_t alpha)
{
    if (m_selectedTexture != nullptr)
        m_selectedTexture->SetAlphaMod(alpha);
}

void App::SetColorAndAlpha(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    if (m_selectedTexture != nullptr)
        m_selectedTexture->SetColorAndAlphaMod(Color(red, green, blue, alpha));
}

void App::SetBlendMode(SDL_BlendMode blending)
{
    if (m_selectedTexture != nullptr)
        m_selectedTexture->SetBlendMode(blending);
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

void App::HandleKeyboard()
{
    // Set texture based on current keystate
    const bool *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_UP])
    {
        m_selectedTexture = &m_upTexture;
    }
    else if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        m_selectedTexture = &m_downTexture;
    }
    else if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        m_selectedTexture = &m_leftTexture;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        m_selectedTexture = &m_rightTexture;
    }
    else
    {
        m_selectedTexture = &m_pressTexture;
    }
}

void App::Render()
{
    // Clear screen
    m_renderer.SetDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    m_renderer.Clear();

    // Render sprite texture
    m_renderer.Copy(*m_selectedTexture, NullOpt, NullOpt, m_angle, NullOpt, m_flipMode);

    // Update screen
    m_renderer.Present();
}
