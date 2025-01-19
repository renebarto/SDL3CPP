#pragma once

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_version.h>
#include <SDL3/SDL_video.h>
#include <memory>
#include <string>

struct SDL_Window;
struct SDL_Surface;

namespace SDL3CPP {

class Surface;
class Point;

////////////////////////////////////////////////////////////
/// \brief GUI window object
///
/// \ingroup windows
///
/// \headerfile SDL/Window.h
///
/// SDL::Window is a wrapper around SDL_Window structure
/// and related functions which take care of GUI window
/// management.
///
/// Usage example:
/// \code
/// {
///     SDL::SDL sdl(SDL_INIT_VIDEO);
///     SDL::Window window("Test Window",
///                           SDL_WINDOWPOS_UNDEFINED,
///                           SDL_WINDOWPOS_UNDEFINED,
///                           640,
///                           480,
///                           SDL_WINDOW_OPENGL);
///
///     SDL_Delay(3000); // show window for 3 seconds
/// }
/// \endcode
///
////////////////////////////////////////////////////////////
class Window
{
  private:
    SDL_Window *m_window;

  public:
    explicit Window(SDL_Window *window);
    Window();
    Window(const std::string &title, int w, int h, uint32_t flags);
    virtual ~Window();

    Window(const Window &other) = delete;
    Window(Window &&other) noexcept;

    Window &operator=(const Window &other) = delete;
    Window &operator=(Window &&other) noexcept;

    bool Create(const std::string &title, int w, int h, uint32_t flags);

    SDL_Window *Get() const;
    SDL_Surface *GetSurface() const;

    Point GetSize() const;
    int GetWidth() const;
    int GetHeight() const;

    Point GetDrawableSize() const;
    int GetDrawableWidth() const;
    int GetDrawableHeight() const;

    Window &SetTitle(const std::string &title);
    std::string GetTitle() const;

    Window &Maximize();
    Window &Minimize();
    Window &Hide();
    Window &Restore();
    Window &Raise();
    Window &Show();
    Window &SetFullscreen(bool fullScreen);

    Window &SetSize(int w, int h);
    Window &SetSize(const Point &size);

    float GetBrightness() const;
    Window &SetBrightness(float brightness);

    Point GetPosition() const;
    Window &SetPosition(int x, int y);
    Window &SetPosition(const Point &pos);

    Point GetMinimumSize() const;
    Window &SetMinimumSize(int w, int h);
    Window &SetMinimumSize(const Point &size);

    Point GetMaximumSize() const;
    Window &SetMaximumSize(int w, int h);
    Window &SetMaximumSize(const Point &size);

    bool GetGrab() const;
    Window &SetGrab(bool grabbed);

    SDL_DisplayID GetDisplayIndex() const;
    void GetDisplayMode(SDL_DisplayMode &mode) const;
    SDL_WindowFlags GetFlags() const;

    Window &SetIcon(const Surface &icon);
    Window &SetBordered(bool bordered = true);

#if SDL_VERSION_ATLEAST(2, 0, 5)
    Window &SetOpacity(float opacity = 1.0f);
    float GetOpacity() const;

    Window &SetResizable(bool resizable = true);
#endif

    void UpdateSurface();
};

} // namespace SDL3CPP
