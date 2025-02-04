#include "SDL3CPP/Window.h"

#include <cassert>
#include <stdexcept>
#include <sstream>

#include "SDL3CPP/Point.h"
#include "SDL3CPP/Surface.h"

using namespace SDL3CPP;

Window::Window(SDL_Window *window)
    : m_window{window}
{
    assert(m_window);
}

Window::Window()
    : m_window{}
{
}

Window::Window(const std::string &title, int w, int h, uint32_t flags)
    : m_window{}
{
    if (!Create(title, w, h, flags))
    {
        std::ostringstream stream;
        stream << "SDL_CreateWindow failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
}

Window::~Window()
{
    if (m_window != nullptr)
        SDL_DestroyWindow(m_window);
    m_window = nullptr;
}

Window::Window(Window &&other) noexcept
    : m_window(other.m_window)
{
    other.m_window = nullptr;
}

Window &Window::operator=(Window &&other) noexcept
{
    if (&other == this)
        return *this;
    if (m_window != nullptr)
        SDL_DestroyWindow(m_window);
    m_window = other.m_window;
    other.m_window = nullptr;
    return *this;
}

bool Window::Create(const std::string &title, int w, int h, uint32_t flags)
{
    m_window = SDL_CreateWindow(title.c_str(), w, h, flags);
    return m_window != nullptr;
}

SDL_Window *Window::Get() const
{
    return m_window;
}

SDL_Surface *Window::GetSurface() const
{
    return SDL_GetWindowSurface(m_window);
}

WindowID Window::GetID() const
{
    return SDL_GetWindowID(m_window);
}

Point Window::GetSize() const
{
    int w, h;
    SDL_GetWindowSize(m_window, &w, &h);
    return Point(w, h);
}

int Window::GetWidth() const
{
    int w;
    SDL_GetWindowSize(m_window, &w, nullptr);
    return w;
}

int Window::GetHeight() const
{
    int h;
    SDL_GetWindowSize(m_window, nullptr, &h);
    return h;
}

Point Window::GetDrawableSize() const
{
    int w, h;
    SDL_GetWindowSizeInPixels(m_window, &w, &h);
    return Point(w, h);
}

int Window::GetDrawableWidth() const
{
    int w;
    SDL_GetWindowSizeInPixels(m_window, &w, nullptr);
    return w;
}

int Window::GetDrawableHeight() const
{
    int h;
    SDL_GetWindowSizeInPixels(m_window, nullptr, &h);
    return h;
}

Window &Window::SetTitle(const std::string &title)
{
    SDL_SetWindowTitle(m_window, title.c_str());
    return *this;
}

std::string Window::GetTitle() const
{
    return SDL_GetWindowTitle(m_window);
}

Window &Window::Maximize()
{
    SDL_MaximizeWindow(m_window);
    return *this;
}

Window &Window::Minimize()
{
    SDL_MinimizeWindow(m_window);
    return *this;
}

Window &Window::Hide()
{
    SDL_HideWindow(m_window);
    return *this;
}

Window &Window::Restore()
{
    SDL_RestoreWindow(m_window);
    return *this;
}

Window &Window::Raise()
{
    SDL_RaiseWindow(m_window);
    return *this;
}

Window &Window::Show()
{
    SDL_ShowWindow(m_window);
    return *this;
}

Window &Window::SetFullscreen(bool fullScreen)
{
    if (!SDL_SetWindowFullscreen(m_window, fullScreen))
        throw std::runtime_error("SDL_SetWindowFullscreen");
    return *this;
}

Window &Window::SetSize(int w, int h)
{
    SDL_SetWindowSize(m_window, w, h);
    return *this;
}

Window &Window::SetSize(const Point &size)
{
    SDL_SetWindowSize(m_window, size.x, size.y);
    return *this;
}

//float Window::GetBrightness() const
//{
//    return SDL_GetWindowBrightness(m_window);
//}
//
//Window &Window::SetBrightness(float brightness)
//{
//    if (SDL_SetWindowBrightness(m_window, brightness) != 0)
//        throw std::runtime_error("SDL_SetWindowBrightness");
//    return *this;
//}

Point Window::GetPosition() const
{
    int x, y;
    SDL_GetWindowPosition(m_window, &x, &y);
    return Point(x, y);
}

Window &Window::SetPosition(int x, int y)
{
    SDL_SetWindowPosition(m_window, x, y);
    return *this;
}

Window &Window::SetPosition(const Point &pos)
{
    SDL_SetWindowPosition(m_window, pos.x, pos.y);
    return *this;
}

Point Window::GetMinimumSize() const
{
    int w, h;
    SDL_GetWindowMinimumSize(m_window, &w, &h);
    return Point(w, h);
}

Window &Window::SetMinimumSize(int w, int h)
{
    SDL_SetWindowMinimumSize(m_window, w, h);
    return *this;
}

Window &Window::SetMinimumSize(const Point &size)
{
    SDL_SetWindowMinimumSize(m_window, size.x, size.y);
    return *this;
}

Point Window::GetMaximumSize() const
{
    int w, h;
    SDL_GetWindowMaximumSize(m_window, &w, &h);
    return Point(w, h);
}

Window &Window::SetMaximumSize(int w, int h)
{
    SDL_SetWindowMaximumSize(m_window, w, h);
    return *this;
}

Window &Window::SetMaximumSize(const Point &size)
{
    SDL_SetWindowMaximumSize(m_window, size.x, size.y);
    return *this;
}

bool Window::GetGrab() const
{
    return SDL_GetWindowMouseGrab(m_window);
}

Window &Window::SetGrab(bool grabbed)
{
    SDL_SetWindowMouseGrab(m_window, grabbed ? true : false);
    return *this;
}

SDL_DisplayID Window::GetDisplayIndex() const
{
    return SDL_GetDisplayForWindow(m_window);
}

void Window::GetDisplayMode(SDL_DisplayMode &mode) const
{
    auto fullScreenMode = SDL_GetWindowFullscreenMode(m_window);
    if (fullScreenMode == nullptr)
        throw std::runtime_error("SDL_GetWindowDisplayMode");
    mode = *fullScreenMode;
}

SDL_WindowFlags Window::GetFlags() const
{
    return SDL_GetWindowFlags(m_window);
}

Window &Window::SetIcon(const Surface &icon)
{
    SDL_SetWindowIcon(m_window, icon.Get());
    return *this;
}

Window &Window::SetBordered(bool bordered /*= true*/)
{
    SDL_SetWindowBordered(m_window, bordered);
    return *this;
}

#if SDL_VERSION_ATLEAST(2, 0, 5)

Window &Window::SetOpacity(float opacity /*= 1.0f*/)
{
    if (SDL_SetWindowOpacity(m_window, opacity))
        throw std::runtime_error("SDL_SetWindowOpacity");
    return *this;
}

float Window::GetOpacity() const
{
    return SDL_GetWindowOpacity(m_window);
}

Window &Window::SetResizable(bool resizable /*= true*/)
{
    SDL_SetWindowResizable(m_window, resizable);
    return *this;
}

#endif

void Window::UpdateSurface()
{
    SDL_UpdateWindowSurface(m_window);
}
