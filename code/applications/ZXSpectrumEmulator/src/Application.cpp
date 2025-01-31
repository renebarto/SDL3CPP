#include "Application.h"

#include "SDL3CPP/Rect.h"
#include "SDL3CPP/SDL.h"
#include "SDL3CPP/SDLImage.h"
#include "tracing/ScopedTracing.h"
#include <ostream>

using namespace SDL3CPP;
using namespace tracing;

static constexpr int ZXSpectrumScreenWidth = 256;
static constexpr int ZXSpectrumScreenHeight = 192;
static constexpr int ZXSpectrumScreenBorderWidth = 48;
static constexpr int ZXSpectrumScreenBorderHeight = 48;

Application::Application()
    : m_savedTraceFilter{}
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
    , m_model{}
    , m_view{ m_model }
    , m_controller{ m_model, m_view }
{
    m_savedTraceFilter = Tracing::GetDefaultTraceFilter();
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TRACE_DEBUG("Construct");
}

Application::~Application()
{
    TRACE_DEBUG("Destruct");
}

bool Application::Init(tracing::TraceWriter* traceWriter)
{
    SCOPEDTRACE(nullptr, nullptr);

    if (traceWriter)
    {
        Tracing::SetTraceWriter(traceWriter);
    }
    // Initialization flag
    bool success = m_controller.Init();
    if (!success)
    {
        return false;
    }

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

void Application::SetDebug(bool on)
{
    m_controller.SetDebug(on);
}

bool Application::Run()
{
    SCOPEDTRACE(nullptr, nullptr);
    Event e;
    bool quit = false;
    while (quit == false)
    {
        while (Events::Poll(e))
        {
            // User requests quit
            if (e.Type() == SDL_EVENT_QUIT)
            {
                quit = true;
            }
            // User presses a key
            else if (e.Type() == SDL_EVENT_KEY_DOWN)
            {
                switch (e.Key())
                {
                case SDLK_ESCAPE:
                    TRACE_DEBUG("ESC key pressed");
                    quit = true;
                    break;

                default:
                    HandleEvent(e);
                    break;
                }
            }
            else
            {
                HandleEvent(e);
            }
        }

        // Render the texture
        if (!Render())
            return false;
    }
    return true;
}

bool Application::HandleEvent(const Event &e)
{
    if (e.Type() == SDL_EVENT_KEY_DOWN)
    {
        m_controller.OnKeyDown(e);
    }
    return true;
}

void Application::Close()
{
}

bool Application::Render()
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

void Application::SetBorderColor(uint8_t r, uint8_t g, uint8_t b)
{
    m_borderColor.SetRed(r);
    m_borderColor.SetGreen(g);
    m_borderColor.SetBlue(b);
}

void Application::UpdateBuffer(uint8_t r, uint8_t g, uint8_t b)
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

void Application::SetPixel(int x, int y, Color color)
{
    RGB* imagePtr = reinterpret_cast<RGB *>(reinterpret_cast<uint8_t *>(m_imageData) + y * m_imagePitch) + x;
    *imagePtr++ = RGB{ color.r, color.g, color.b };
}

bool Application::LockTexture()
{
    m_zxSpectumScreenBufferIndexForUpdate = (m_zxSpectumScreenBufferIndex + 1) % ScreenBufferDepth;
    auto &bufferTexture = m_zxSpectumScreenBuffer[m_zxSpectumScreenBufferIndexForUpdate];
    if (bufferTexture.GetAccess() != SDL_TEXTUREACCESS_STREAMING)
        return false;
    Rect bufferRect{ Point{0, 0}, bufferTexture.GetSizeInt() };
    SDL_LockTexture(bufferTexture.Get(), &bufferRect, &m_imageData, &m_imagePitch);
    return true;
}

bool Application::UnlockTexture()
{
    m_zxSpectumScreenBufferIndexForUpdate = (m_zxSpectumScreenBufferIndex + 1) % ScreenBufferDepth;
    auto &bufferTexture = m_zxSpectumScreenBuffer[m_zxSpectumScreenBufferIndexForUpdate];
    SDL_UnlockTexture(bufferTexture.Get());
    m_zxSpectumScreenBufferIndex = m_zxSpectumScreenBufferIndexForUpdate;
    return true;
}
