#pragma once

#include <memory>
#include <ostream>
#include "osal/synchronization/ManualEvent.h"
#include "tracing/TraceCategory.h"

#include "SDL3CPP/Events.h"
#include "SDL3CPP/Color.h"
#include "SDL3CPP/Renderer.h"
#include "SDL3CPP/Surface.h"
#include "SDL3CPP/Texture.h"
#include "SDL3CPP/Window.h"

#include "Model/ISystem.h"

class Model;

constexpr int ScreenBufferDepth = 2;

class MainView
{
private:
    Model &m_model;
    std::shared_ptr<ISystem> m_system;
    // The window we'll be rendering to
    SDL3CPP::Window m_window;

    //The window renderer
    SDL3CPP::Renderer m_renderer;

    // The surface contained by the window
    SDL3CPP::Surface m_screenSurface;

    SDL3CPP::Texture m_infoPanelTexture;

    SDL3CPP::Texture m_zxSpectumScreenBuffer[ScreenBufferDepth];
    int m_displayScreenWidth;
    int m_displayScreenHeight;
    int m_zxSpectumScreenBufferIndex;
    int m_zxSpectumScreenBufferIndexForUpdate;
    void *m_imageData;
    int m_imagePitch;
    float m_zxSpectrumZoom;
    int m_zxSpectrumScreenWidth;
    int m_zxSpectrumScreenHeight;
    SDL3CPP::FRect m_zxSpectrumImageRect;
    SDL3CPP::FRect m_zxSpectrumScreenRect;
    SDL3CPP::Color m_borderColor;
    bool m_quit;
    SDL3CPP::Event m_keyDownEvent;
    osal::ManualEvent m_keyDownEventTrigger;

public:
    MainView(Model &model);
    MainView(const MainView &) = delete;

    MainView& operator =(const MainView &) = delete;
    MainView& operator =(MainView &&) = delete;

    bool Init(std::shared_ptr<ISystem> system);
    bool Run();

    void ShowInstruction(const std::string& mnemonic);
    void ShowRegisters();
    void ShowCPUClock();

    bool Render();

    void UpdateBuffer(uint8_t r, uint8_t g, uint8_t b);
    void SetPixel(int x, int y, SDL3CPP::Color color);
    void SetBorderColor(uint8_t r, uint8_t g, uint8_t b);
    bool LockTexture();
    bool UnlockTexture();

    void Stop();
    bool Quit() const;
    void HandleEvent(const SDL3CPP::Event &e);
    void WaitForInput();
};
