#include "App.h"

#include <filesystem>
#include <iostream>
#include <ostream>

#include "SDL3CPP/Rect.h"
#include "SDL3CPP/SDL.h"
#include "SDL3CPP/SDLImage.h"
#include "SDL3CPP/SDLTTF.h"

using namespace SDL3CPP;

const float LButton::ButtonWidth = 300;
const float LButton::ButtonHeight = 200;

LButton::LButton()
{
    m_position.x = 0;
    m_position.y = 0;

    m_currentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

SDL3CPP::FPoint LButton::GetPosition() const
{
    return m_position;
}

void LButton::SetPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}

LButtonSprite LButton::GetCurrentSprite() const
{
    return m_currentSprite;
}

void LButton::HandleEvent(SDL3CPP::Event &e)
{
    // If mouse event happened
    if (e.Type() == SDL_EVENT_MOUSE_MOTION || e.Type() == SDL_EVENT_MOUSE_BUTTON_DOWN ||
        e.Type() == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        // Get mouse position
        float x, y;
        SDL_GetMouseState(&x, &y);

        // Check if mouse is in button
        bool inside = true;

        // Mouse is left of the button
        if (x < m_position.x)
        {
            inside = false;
        }
        // Mouse is right of the button
        else if (x > m_position.x + ButtonWidth)
        {
            inside = false;
        }
        // Mouse above the button
        else if (y < m_position.y)
        {
            inside = false;
        }
        // Mouse below the button
        else if (y > m_position.y + ButtonHeight)
        {
            inside = false;
        }

        // Mouse is outside button
        if (!inside)
        {
            m_currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        // Mouse is inside button
        else
        {
            // Set mouse over sprite
            switch (e.Type())
            {
            case SDL_EVENT_MOUSE_MOTION:
                m_currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                m_currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                m_currentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}

App::App()
    : m_screenWidth{}
    , m_screenHeight{}
    , m_window{}
    , m_renderer{}
    , m_screenSurface{}
    , m_buttonSpriteSheetTexture{}
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

    // Load sprites
    m_buttonSpriteSheetTexture = LoadTextureWithColorKey(std::filesystem::path(IMAGE_DIR) / "button.png", 0, 0xFF, 0xFF);
    if (m_buttonSpriteSheetTexture.IsEmpty())
    {
        SDL_Log("Failed to load button sprite texture!\n");
        success = false;
    }
    else
    {
        // Set sprites
        for (int i = 0; i < LButtonSprite::BUTTON_SPRITE_TOTAL; ++i)
        {
            m_spriteClips[i].x = 0.0F;
            m_spriteClips[i].y = static_cast<float>(i) * LButton::ButtonHeight;
            m_spriteClips[i].w = LButton::ButtonWidth;
            m_spriteClips[i].h = LButton::ButtonHeight;
        }

        // Set buttons in corners
        m_buttons[0].SetPosition(0, 0);
        m_buttons[1].SetPosition(static_cast<float>(m_screenWidth) - LButton::ButtonWidth, 0);
        m_buttons[2].SetPosition(0, static_cast<float>(m_screenHeight) - LButton::ButtonHeight);
        m_buttons[3].SetPosition(static_cast<float>(m_screenWidth) - LButton::ButtonWidth, static_cast<float>(m_screenHeight) - LButton::ButtonHeight);
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
    return m_buttonSpriteSheetTexture.GetSize();
}

void App::SetColor(uint8_t red, uint8_t green, uint8_t blue)
{
    m_buttonSpriteSheetTexture.SetColorMod(red, green, blue);
}

void App::SetAlpha(uint8_t alpha)
{
    m_buttonSpriteSheetTexture.SetAlphaMod(alpha);
}

void App::SetColorAndAlpha(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    m_buttonSpriteSheetTexture.SetColorAndAlphaMod(Color(red, green, blue, alpha));
}

void App::SetBlendMode(SDL_BlendMode blending)
{
    m_buttonSpriteSheetTexture.SetBlendMode(blending);
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

void App::HandleEvent(Event &e)
{
    // Handle button events
    for (int i = 0; i < NumButtons; ++i)
    {
        m_buttons[i].HandleEvent(e);
    }
}

void App::Render()
{
    // Clear screen
    m_renderer.SetDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    m_renderer.Clear();

    // Render sprite texture

    for (int i = 0; i < NumButtons; ++i)
    {
        auto &clipRect = m_spriteClips[m_buttons[i].GetCurrentSprite()];
        FRect dstRect{m_buttons[i].GetPosition(), clipRect.GetSize()};
        m_renderer.Copy(m_buttonSpriteSheetTexture, clipRect, dstRect, m_angle, NullOpt, m_flipMode);
    }

    // Update screen
    m_renderer.Present();
}
