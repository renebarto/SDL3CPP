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
    , m_promptTexture{}
    , m_music{}
    , m_scratch{}
    , m_high{}
    , m_medium{}
    , m_low{}
    , m_angle{}
    , m_center{}
    , m_flipMode{SDL_FLIP_NONE}
    , m_font{}
{
}

App::~App()
{
    // Free the sound effects
    Mix_FreeChunk(m_scratch);
    Mix_FreeChunk(m_high);
    Mix_FreeChunk(m_medium);
    Mix_FreeChunk(m_low);

    // Free the music
    Mix_FreeMusic(m_music);
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

        // Initialize SDL_mixer
        SDL_AudioSpec audio_spec{};
        SDL_zero(audio_spec);
        audio_spec.format = MIX_DEFAULT_FORMAT;
        audio_spec.channels = 2;
        audio_spec.freq = 44100;
        if (!Mix_OpenAudio(0, &audio_spec))
        {
            SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", SDL_GetError());
            success = false;
        }
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

    // Load prompt texture
    m_promptTexture = LoadTextureWithColorKey(std::filesystem::path(IMAGE_DIR) / "prompt.png", 0, 0xFF, 0xFF);
    if (m_promptTexture.IsEmpty())
    {
        SDL_Log("Failed to load press texture!\n");
        success = false;
    }

    // Load music
    m_music = Mix_LoadMUS((std::filesystem::path(SOUND_DIR) / "beat.wav").string().c_str());
    if (m_music == NULL)
    {
        SDL_Log("Failed to load beat music! SDL_mixer Error: %s\n", SDL_GetError());
        success = false;
    }

    // Load sound effects
    m_scratch = Mix_LoadWAV((std::filesystem::path(SOUND_DIR) / "scratch.wav").string().c_str());
    if (m_scratch == NULL)
    {
        SDL_Log("Failed to load scratch sound effect! SDL_mixer Error: %s\n", SDL_GetError());
        success = false;
    }

    m_high = Mix_LoadWAV((std::filesystem::path(SOUND_DIR) / "high.wav").string().c_str());
    if (m_high == NULL)
    {
        SDL_Log("Failed to load high sound effect! SDL_mixer Error: %s\n", SDL_GetError());
        success = false;
    }

    m_medium = Mix_LoadWAV((std::filesystem::path(SOUND_DIR) / "medium.wav").string().c_str());
    if (m_medium == NULL)
    {
        SDL_Log("Failed to load medium sound effect! SDL_mixer Error: %s\n", SDL_GetError());
        success = false;
    }

    m_low = Mix_LoadWAV((std::filesystem::path(SOUND_DIR) / "low.wav").string().c_str());
    if (m_low == NULL)
    {
        SDL_Log("Failed to load low sound effect! SDL_mixer Error: %s\n", SDL_GetError());
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
    return m_promptTexture.GetSize();
}

void App::SetColor(uint8_t red, uint8_t green, uint8_t blue)
{
    m_promptTexture.SetColorMod(red, green, blue);
}

void App::SetAlpha(uint8_t alpha)
{
    m_promptTexture.SetAlphaMod(alpha);
}

void App::SetColorAndAlpha(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    m_promptTexture.SetColorAndAlphaMod(Color(red, green, blue, alpha));
}

void App::SetBlendMode(SDL_BlendMode blending)
{
    m_promptTexture.SetBlendMode(blending);
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
}

void App::Render()
{
    // Clear screen
    m_renderer.SetDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    m_renderer.Clear();

    // Render sprite texture
    m_renderer.Copy(m_promptTexture, NullOpt, NullOpt, m_angle, NullOpt, m_flipMode);

    // Update screen
    m_renderer.Present();
}
