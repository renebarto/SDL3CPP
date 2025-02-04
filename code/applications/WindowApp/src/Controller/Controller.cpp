#include "Controller/Controller.h"

#include <filesystem>
#include <fstream>
#include "tracing/ScopedTracing.h"
#include "tracing/Tracing.h"
#include <SDL3/SDL_keycode.h>
#include "SDL3CPP/Events.h"
#include "View/MainView.h"

using namespace SDL3CPP;

using KeyboardShortcutMap = std::map<SDL_Keycode, SDL3CPP::Event>;

KeyboardShortcutMap s_shortcuts{
    { SDLK_ESCAPE, SDL3CPP::QuitEvent{} },
};

Controller::Controller(Model& model, MainView& view)
    : m_model{model}
    , m_mainView{view}
    , m_quit{false}
    , m_keyDownEvent{}
    , m_keyDownEventTrigger{}
{
    TRACE_DEBUG("Controller::Controller");
}

Controller::~Controller()
{
    TRACE_DEBUG("Controller::~Controller");
}

bool Controller::Init()
{
    SCOPEDTRACE(nullptr, nullptr);
    std::filesystem::path romDir{ ROM_DIR };
    std::filesystem::path romFilePath{(romDir / "spec48.rom").generic_string() };
    auto fileSize = std::filesystem::file_size(romFilePath);
    std::ifstream romFile{ romFilePath, std::ios::binary };
    if (!romFile)
        TRACE_FATAL("Can't open ROM file");
    std::vector<uint8_t> romContents;
    romContents.reserve(fileSize);
    romContents.resize(fileSize);
    romFile.read(reinterpret_cast<char *>(romContents.data()), static_cast<std::streamsize>(fileSize));

    bool result{ true };

    if (result)
    {
        result = m_mainView.Init();
    }
    return result;
}

bool Controller::Run()
{
    SCOPEDTRACE(nullptr, nullptr);
    Event e;
    bool result{ true };

    while (!Quit())
    {
        while (Events::Poll(e))
        {
            HandleEvent(e);
        }

        // Render the texture
        if (!m_mainView.Render())
            return false;
    }
    return result;
}

bool Controller::DoRun()
{
    return true;
}

void Controller::Stop()
{
    SCOPEDTRACE(nullptr, nullptr);
    m_quit = true;
    m_keyDownEventTrigger.Set();
}

bool Controller::Quit() const
{
    return m_quit;
}

void Controller::HandleEvent(const SDL3CPP::Event &e)
{
    switch (e.Type())
    {
        // User requests quit
        case SDL_EVENT_QUIT:
            TRACE_DEBUG("SDL_EVENT_QUIT");
            Stop();
            break;
        // User presses a key
        case SDL_EVENT_KEY_DOWN:
            TRACE_DEBUG("SDL_EVENT_KEY_DOWN {}", e.Key());
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
            {
                auto mouseMotionEvent = static_cast<const MouseMotionEvent &>(e);
//                TRACE_DEBUG("SDL_EVENT_MOUSE_MOTION x={}, y={}, down={}", mouseMotionEvent.GetX(), mouseMotionEvent.GetY(), mouseMotionEvent.ButtonState());
                auto element = m_mainView.FindElementAtPosition(mouseMotionEvent.GetX(), mouseMotionEvent.GetY());
                if (element != nullptr)
                {
                    OnMouseMove(*element.get(), mouseMotionEvent);
                }
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            {
                auto mouseButtonEvent = static_cast<const MouseButtonEvent &>(e);
                TRACE_DEBUG("SDL_EVENT_MOUSE_BUTTON_DOWN x={}, y={}, down={}", mouseButtonEvent.GetX(), mouseButtonEvent.GetY(), mouseButtonEvent.IsPressed());
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            {
                auto mouseButtonEvent = static_cast<const MouseButtonEvent &>(e);
                TRACE_DEBUG("SDL_EVENT_MOUSE_BUTTON_UP x={}, y={}, down={}", mouseButtonEvent.GetX(), mouseButtonEvent.GetY(), mouseButtonEvent.IsPressed());
            }
            break;
        default:
            break;
    }
}

void Controller::OnMouseMove(GUI::UIElement &element, SDL3CPP::MouseMotionEvent &event)
{
//    SCOPEDTRACE(nullptr, nullptr);
    element.SetFocus(true);
    auto ui = element.GetUI();
    float xRel = event.GetX() / ui->Width();
    float yRel = event.GetY() / ui->Height();
}

void Controller::WaitForInput()
{
    SCOPEDTRACE(nullptr, nullptr);
    m_keyDownEventTrigger.Wait();
    m_keyDownEventTrigger.Reset();
}
