#pragma once

#include "SDL3CPP/Events.h"
#include "SDL3CPP/Font.h"
#include "SDL3CPP/Renderer.h"
#include "SDL3CPP/Surface.h"
#include "SDL3CPP/Texture.h"
#include "SDL3CPP/Window.h"

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

    // Scene textures
    SDL3CPP::Texture m_pressTexture;
    SDL3CPP::Texture m_upTexture;
    SDL3CPP::Texture m_downTexture;
    SDL3CPP::Texture m_leftTexture;
    SDL3CPP::Texture m_rightTexture;
    SDL3CPP::Texture* m_selectedTexture;

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

    void HandleKeyboard();
    void Render();
};
