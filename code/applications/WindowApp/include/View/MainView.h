#pragma once

#include "SDL3CPP/Color.h"
#include "SDL3CPP/Renderer.h"
#include "SDL3CPP/Surface.h"
#include "SDL3CPP/Texture.h"
#include "SDL3CPP/Window.h"
#include "View/UI.h"

class Model;

class MainView
{
private:
    Model &m_model;

    SDL3CPP::Window m_window;
    SDL3CPP::Renderer m_renderer;
    SDL3CPP::Surface m_screenSurface;

    SDL3CPP::Texture m_infoPanelTexture;
    std::shared_ptr<GUI::UI> m_ui;

    int m_displayScreenWidth;
    int m_displayScreenHeight;
    void *m_imageData;
    int m_imagePitch;
    float m_zxSpectrumZoom;
    SDL3CPP::Color m_borderColor;
    SDL3CPP::FRect m_screenRect;

public:
    MainView(Model &model);
    MainView(const MainView &) = delete;
    virtual ~MainView();

    MainView &operator=(const MainView &) = delete;
    MainView &operator=(MainView &&) = delete;

    bool Init();
    bool Run();

    bool Render();

    GUI::UI *GetUI() { return m_ui.get(); }
    std::shared_ptr<GUI::UIElement> FindElementAtPosition(float x, float y);

    void UpdateBuffer(uint8_t r, uint8_t g, uint8_t b);
    void SetPixel(int x, int y, SDL3CPP::Color color);
    void SetBorderColor(uint8_t r, uint8_t g, uint8_t b);
};
