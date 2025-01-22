#pragma once 

#include "tracing/ConsoleTraceLineWriter.h"
#include "tracing/TraceWriter.h"
#include "tracing/Tracing.h"
#include "SDL3CPP/Color.h"
#include "SDL3CPP/Events.h"
#include "SDL3CPP/Renderer.h"
#include "SDL3CPP/Surface.h"
#include "SDL3CPP/Texture.h"
#include "SDL3CPP/Window.h"
#include "Controller/Controller.h"
#include "Model/Model.h"
#include "View/MainView.h"

constexpr int ScreenBufferDepth = 2;

class Application
{
private:
    tracing::CategorySet<tracing::TraceCategory> m_savedTraceFilter;

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

    Model m_model;
    MainView m_view;
    Controller m_controller;

public:
    Application();
    virtual ~Application();

    // Starts up SDL and creates window
    bool Init(tracing::TraceWriter* traceWriter);

    void SetDebug(bool on);

    bool Run();

    bool HandleEvent(const SDL3CPP::Event &e);

    // Frees media and shuts down SDL
    void Close();

    bool Render();

    void UpdateBuffer(uint8_t r, uint8_t g, uint8_t b);
    void SetPixel(int x, int y, SDL3CPP::Color color);
    void SetBorderColor(uint8_t r, uint8_t g, uint8_t b);
    bool LockTexture();
    bool UnlockTexture();
};

