#include "View/MainView.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include "tracing/Tracing.h"
#include "SDL3CPP/Events.h"
#include "SDL3CPP/Rect.h"
#include "SDL3CPP/SDL.h"
#include "SDL3CPP/SDLImage.h"
#include "Model/Model.h"

using namespace tracing;
using namespace SDL3CPP;

static constexpr int ZXSpectrumScreenWidth = 256;
static constexpr int ZXSpectrumScreenHeight = 192;
static constexpr int ZXSpectrumScreenBorderWidth = 48;
static constexpr int ZXSpectrumScreenBorderHeight = 48;

using KeyboardShortcutMap = std::map<SDL_Keycode, SDL3CPP::Event>;

KeyboardShortcutMap s_shortcuts{
    { SDLK_ESCAPE, SDL3CPP::QuitEvent{} },
};

MainView::MainView(Model& model)
    : m_model{model}
    , m_system{}
    , m_window{}
    , m_renderer{}
    , m_screenSurface{}
    , m_infoPanelTexture{}
    , m_zxSpectumScreenBuffer{}
    , m_displayScreenWidth{}
    , m_displayScreenHeight{}
    , m_zxSpectumScreenBufferIndex{}
    , m_zxSpectumScreenBufferIndexForUpdate{}
    , m_imageData{}
    , m_imagePitch{}
    , m_zxSpectrumZoom{4.0F}
    , m_zxSpectrumScreenWidth{ static_cast<int>(m_zxSpectrumZoom * (ZXSpectrumScreenWidth + 2 * ZXSpectrumScreenBorderWidth)) }
    , m_zxSpectrumScreenHeight{ static_cast<int>(m_zxSpectrumZoom * (ZXSpectrumScreenHeight + 2 * ZXSpectrumScreenBorderHeight)) }
    , m_zxSpectrumImageRect{ 
        static_cast<float>(ZXSpectrumScreenBorderWidth), 
        static_cast<float>(ZXSpectrumScreenBorderHeight), 
        static_cast<float>(ZXSpectrumScreenWidth),
        static_cast<float>(ZXSpectrumScreenHeight) }
    , m_zxSpectrumScreenRect{ 
        0.0F, 
        0.0F,
        static_cast<float>(m_zxSpectrumScreenWidth),
        static_cast<float>(m_zxSpectrumScreenHeight) }
    , m_borderColor{}
    , m_quit{}
    , m_keyDownEvent{}
    , m_keyDownEventTrigger{}
{
    
}

bool MainView::Init(std::shared_ptr<ISystem> system)
{
    bool success = true;
    m_system = system;
    try
    {
        SDL &sdl = GetSDL(SDLInitFlags::Video | SDLInitFlags::Mixer);

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
                              m_displayScreenWidth - m_zxSpectrumScreenWidth, m_displayScreenHeight);

        for (int i = 0; i < ScreenBufferDepth; ++i)
        {
            m_zxSpectumScreenBuffer[i] =
                std::move(Texture(m_renderer, SDL_PixelFormat::SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING,
                                  ZXSpectrumScreenWidth, ZXSpectrumScreenHeight));
        }
        m_borderColor = Color(0x80, 0x80, 0x80);
    }

    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        success = false;
    }
    return success;
}

bool MainView::Run()
{
    m_quit = false;
    Event e;
    while (!Quit())
    {
        while (Events::Poll(e))
        {
            HandleEvent(e);
        }

        // Render the texture
        if (!Render())
            return false;
    }
    return true;
}

void MainView::ShowInstruction(const std::string& mnemonic)
{
    TRACE_INFO(mnemonic);
}

void MainView::ShowRegisters()
{
    TRACE_INFO(m_system->DumpRegisters());
}

void MainView::ShowCPUClock()
{
    auto cpuClock = m_system->GetCPUClock();
    auto cpuClockFreq = m_system->GetCPUClockFreq();
    std::ostringstream stream;
    double timeSecs = static_cast<double>(cpuClock) / static_cast<double>(cpuClockFreq);
    stream << "Clock: " << cpuClock << " = " << std::fixed << std::setprecision(9) << timeSecs;
    TRACE_INFO(stream.str());
}

bool MainView::Render()
{
    // Clear screen
    m_renderer.SetDrawColor(0x0, 0x0, 0x0, 0xFF);
    m_renderer.Clear();

    // ZX Spectrum screen viewport
    Rect zxSpectumScreenViewport{
        0, 0, m_zxSpectrumScreenWidth, m_zxSpectrumScreenHeight
    };
    m_renderer.SetViewport(zxSpectumScreenViewport);
    m_renderer.SetDrawColor(m_borderColor);
    m_renderer.FillRect(m_zxSpectrumScreenRect);
    m_renderer.SetScale(m_zxSpectrumZoom, m_zxSpectrumZoom);

    // Render texture to screen
    m_renderer.Copy(m_zxSpectumScreenBuffer[m_zxSpectumScreenBufferIndex], NullOpt, m_zxSpectrumImageRect);

    m_renderer.SetScale(1.0F, 1.0F);

    // Top right viewport
    Rect infoPanelViewport{
        Point{m_zxSpectrumScreenWidth, 0},
        m_infoPanelTexture.GetSizeInt()
    };
    m_renderer.SetViewport(infoPanelViewport);

    // Render texture to screen
    //m_renderer.Copy(m_infoPanelTexture, NullOpt, NullOpt);

    // Update screen
    m_renderer.Present();

    return true;
}

struct RGB
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

void MainView::SetBorderColor(uint8_t r, uint8_t g, uint8_t b)
{
    m_borderColor.SetRed(r);
    m_borderColor.SetGreen(g);
    m_borderColor.SetBlue(b);
}

void MainView::UpdateBuffer(uint8_t r, uint8_t g, uint8_t b)
{
    if (LockTexture())
    {
        for (int y = 0; y < ZXSpectrumScreenHeight; ++y)
        {
            RGB* imagePtr = reinterpret_cast<RGB *>(reinterpret_cast<uint8_t *>(m_imageData) + y * m_imagePitch);
            for (int x = 0; x < ZXSpectrumScreenWidth; ++x)
            {
                *imagePtr++ = RGB{ r, g, b };
            }
        }
        SetPixel(0, 0, Color{ 0x00, 0x00, 0x00 });
        SetPixel(255, 0, Color{ 0x00, 0x00, 0x00 });
        SetPixel(0, 191, Color{ 0x00, 0x00, 0x00 });
        SetPixel(255, 191, Color{ 0x00, 0x00, 0x00 });
        UnlockTexture();
    }
}

void MainView::SetPixel(int x, int y, Color color)
{
    RGB* imagePtr = reinterpret_cast<RGB *>(reinterpret_cast<uint8_t *>(m_imageData) + y * m_imagePitch) + x;
    *imagePtr++ = RGB{ color.r, color.g, color.b };
}

bool MainView::LockTexture()
{
    m_zxSpectumScreenBufferIndexForUpdate = (m_zxSpectumScreenBufferIndex + 1) % ScreenBufferDepth;
    auto &bufferTexture = m_zxSpectumScreenBuffer[m_zxSpectumScreenBufferIndexForUpdate];
    if (bufferTexture.GetAccess() != SDL_TEXTUREACCESS_STREAMING)
        return false;
    Rect bufferRect{ Point{0, 0}, bufferTexture.GetSizeInt() };
    SDL_LockTexture(bufferTexture.Get(), &bufferRect, &m_imageData, &m_imagePitch);
    return true;
}

bool MainView::UnlockTexture()
{
    m_zxSpectumScreenBufferIndexForUpdate = (m_zxSpectumScreenBufferIndex + 1) % ScreenBufferDepth;
    auto &bufferTexture = m_zxSpectumScreenBuffer[m_zxSpectumScreenBufferIndexForUpdate];
    SDL_UnlockTexture(bufferTexture.Get());
    m_zxSpectumScreenBufferIndex = m_zxSpectumScreenBufferIndexForUpdate;
    return true;
}

void MainView::Stop()
{
    m_quit = true;
    m_keyDownEventTrigger.Set();
}

bool MainView::Quit() const
{
    return m_quit;
}

void MainView::HandleEvent(const SDL3CPP::Event &e)
{
    switch (e.Type())
    {
        // User requests quit
        case SDL_EVENT_QUIT:
            Stop();
            break;
        // User presses a key
        case SDL_EVENT_KEY_DOWN:
            if (s_shortcuts.find(e.Key()) != s_shortcuts.end())
            {
                SDL3CPP::Events::PushEvent(s_shortcuts[e.Key()]);
            }
            else
            {
                switch (e.Key())
                {
                case SDLK_ESCAPE:
                default:
                    m_keyDownEvent = e;
                    m_keyDownEventTrigger.Set();
                    break;
                }
            }
            break;
        case SDL_EVENT_MOUSE_MOTION:
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            break;
        default:
            break;
    }
}

void MainView::WaitForInput()
{
    m_keyDownEventTrigger.Wait();
    m_keyDownEventTrigger.Reset();
}
