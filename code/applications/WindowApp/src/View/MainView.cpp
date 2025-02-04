#include "View/MainView.h"

#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "tracing/ScopedTracing.h"
#include "tracing/Tracing.h"
#include "SDL3CPP/SDL.h"
#include "Model/Model.h"
#include "View/Button.h"
#include "View/UIPanel.h"

using namespace tracing;
using namespace SDL3CPP;

MainView::MainView(Model& model)
    : m_model{model}
    , m_window{}
    , m_renderer{}
    , m_screenSurface{}
    , m_infoPanelTexture{}
    , m_ui{}
    , m_displayScreenWidth{}
    , m_displayScreenHeight{}
    , m_imageData{}
    , m_imagePitch{}
    , m_zxSpectrumZoom{4.0F}
    , m_borderColor{}
    , m_screenRect{}
{
    TRACE_DEBUG("MainView::MainView");
}

MainView::~MainView()
{
    TRACE_DEBUG("MainView::~MainView");
}

bool MainView::Init()
{
    SCOPEDTRACE(nullptr, nullptr);
    bool success = true;
    try
    {
        SDL &sdl = Singleton<SDL>::Get();
        sdl.InitSubSystem(SDLInitFlags::Video | SDLInitFlags::Mixer | SDLInitFlags::TTF);

        auto displayConfiguration = sdl.GetDisplayConfiguration();
        DisplayInfo displayInfo{};
        if (!displayConfiguration.GetPrimaryDisplayInfo(displayInfo))
        {
            sdl.Log("Could not retrieve primary display info: {}", SDL_GetError());
            success = false;
        }
        m_displayScreenWidth = displayInfo.w;
        m_displayScreenHeight = displayInfo.h;

        // Create window
        if (!m_window.Create("ZX Spectrum Emulator", m_displayScreenWidth, m_displayScreenHeight, 0))
        {
            sdl.Log("Window could not be created!: {}", SDL_GetError());
            success = false;
        }
        // Create renderer for window
        m_renderer = Renderer(m_window);
        if (m_renderer.IsEmpty())
        {
            sdl.Log("Renderer could not be created!: {}", SDL_GetError());
            success = false;
        }
        m_screenSurface = std::move(Surface(m_window.GetSurface()));

        m_infoPanelTexture =
            Texture(m_renderer, SDL_PixelFormat::SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING,
                              m_displayScreenWidth, m_displayScreenHeight);

        m_borderColor = Color{ 0xFF, 0x00, 0x00 };
        m_ui = std::make_shared<GUI::UI>(m_screenRect);
        auto displayWidth = static_cast<float>(m_displayScreenWidth);
        auto displayHeight = static_cast<float>(m_displayScreenHeight);
        m_screenRect = FRect{ 0.0F, 0.0F, displayWidth, displayHeight };

        auto panel = std::make_shared<GUI::UIPanel>(m_ui.get(), m_screenRect, m_borderColor);
        FRect buttonRect{ displayWidth - 100.0F, displayHeight - 40.0F, 100.0F, 40.0F };
        auto button = std::make_shared<GUI::Button>(m_ui.get(), buttonRect, "Hello");
        button->SetBackgroundColor(Color{0x00, 0x00, 0xFF});
        assert(m_ui);
        m_ui->AddElement(panel);
        m_ui->AddElement(button);
    }

    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        success = false;
    }
    return success;
}

bool MainView::Render()
{
    // Clear screen
    m_renderer.SetDrawColor(0x0, 0x0, 0x0, 0xFF);
    m_renderer.Clear();

    assert(m_ui);
    m_ui->Render(m_renderer);

    // Update screen
    m_renderer.Present();

    return true;
}

std::shared_ptr<GUI::UIElement> MainView::FindElementAtPosition(float x, float y)
{
    assert(m_ui);
    return m_ui->GetElementAt(static_cast<int>(x), static_cast<int>(y));
}

struct RGB
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

void MainView::SetBorderColor(uint8_t r, uint8_t g, uint8_t b)
{
    SCOPEDTRACE(nullptr, nullptr);
    m_borderColor.SetRed(r);
    m_borderColor.SetGreen(g);
    m_borderColor.SetBlue(b);
}

void MainView::UpdateBuffer(uint8_t /*r*/, uint8_t /*g*/, uint8_t /*b*/)
{
    SCOPEDTRACE(nullptr, nullptr);
}

void MainView::SetPixel(int x, int y, Color color)
{
    SCOPEDTRACE(nullptr, nullptr);
    RGB* imagePtr = reinterpret_cast<RGB *>(reinterpret_cast<uint8_t *>(m_imageData) + y * m_imagePitch) + x;
    *imagePtr++ = RGB{ color.r, color.g, color.b };
}

