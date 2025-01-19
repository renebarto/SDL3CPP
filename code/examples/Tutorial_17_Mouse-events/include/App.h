#pragma once

#include "SDL3CPP/Events.h"
#include "SDL3CPP/Font.h"
#include "SDL3CPP/Renderer.h"
#include "SDL3CPP/Surface.h"
#include "SDL3CPP/Texture.h"
#include "SDL3CPP/Window.h"

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

// The mouse button
class LButton
{
public:
    // Button constants
    static const float ButtonWidth;
    static const float ButtonHeight;

    // Initializes internal variables
    LButton();

    // Sets top left position
    SDL3CPP::FPoint GetPosition() const;
    // Sets top left position
    void SetPosition(float x, float y);

    LButtonSprite GetCurrentSprite() const;

    // Handles mouse event
    void HandleEvent(SDL3CPP::Event &e);

    // Shows button sprite
    void Render();

private:
    // Top left position
    SDL3CPP::FPoint m_position;

    // Currently used global sprite
    LButtonSprite m_currentSprite;
};

class App
{
private:
    int m_screenWidth;
    int m_screenHeight;
    static constexpr int NumButtons = 4;
    // The window we'll be rendering to
    SDL3CPP::Window m_window;

    // The window renderer
    SDL3CPP::Renderer m_renderer;

    // The surface contained by the window
    SDL3CPP::Surface m_screenSurface;

    // Walking animation
    SDL3CPP::FRect m_spriteClips[LButtonSprite::BUTTON_SPRITE_TOTAL];
    // Scene textures
    SDL3CPP::Texture m_buttonSpriteSheetTexture;

    // Button object
    LButton m_buttons[NumButtons]; 

    double m_angle;
    SDL3CPP::FPoint m_center;
    SDL_FlipMode m_flipMode;
    SDL3CPP::Font m_font;

public:
    App();
    virtual ~App();

    // Starts up SDL and creates window
    bool Init(int width, int height);

    // Loads media
    bool LoadMedia();
    SDL3CPP::Surface LoadSurface(const std::filesystem::path &path);
    SDL3CPP::Texture LoadTexture(const std::filesystem::path &path);
    SDL3CPP::Texture LoadFromRenderedText(const std::string textureText, SDL3CPP::Color textColor);
    SDL3CPP::Texture LoadTextureWithColorKey(const std::filesystem::path &path, uint8_t colorKeyR, uint8_t colorKeyG,
                                             uint8_t colorKeyB);

    SDL3CPP::FPoint GetTextureSize();
    void SetColor(uint8_t red, uint8_t green, uint8_t blue);
    void SetAlpha(uint8_t alpha);
    void SetColorAndAlpha(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    void SetAngle(double angle);
    void SetCenter(const SDL3CPP::FPoint &center);
    void SetFlipMode(SDL_FlipMode flipMode);

    // Set blending
    void SetBlendMode(SDL_BlendMode blending);

    void Close();

    void HandleEvent(SDL3CPP::Event &e);
    void Render();
};
