#pragma once

#include <map>
#include "core/utilities/Singleton.h"
#include "SDLWindows/Widget.h"

#include "SDL3CPP/DisplayConfiguration.h"
#include "SDL3CPP/Rect.h"

namespace SDLWindows {

using WidgetMap = std::map<WidgetHandle, std::shared_ptr<Widget>>;
class WindowManager : public Singleton<WindowManager>
{
private:
    SDL3CPP::DisplayConfiguration m_displayConfiguration;
    SDL3CPP::DisplayID m_displayID;
    SDL3CPP::DisplayInfo m_displayInfo;
    SDL3CPP::Rect m_screenRect;
    bool m_isFullScreen;

public:
    WindowManager();
    ~WindowManager();

    SDL3CPP::DisplayID GetDisplay();
    bool SetDisplay(SDL3CPP::DisplayID id);

    bool IsFullScreen() const;
    void SetFullScreen(bool fullScreen);

    SDL3CPP::Point GetPosition() const;
    void SetPosition(const SDL3CPP::Point &position);

    SDL3CPP::Size GetSize() const;
    void SetSize(const SDL3CPP::Size &size);

    template<class T>
    std::shared_ptr<T> Create(
        WidgetHandle parent,
        const std::string & title, 
        WidgetStyle style, 
        const SDL3CPP::Point &position = Widget::DefaultPosition, 
        const SDL3CPP::Point &size = Widget::DefaultSize);
};

} // namespace SDLWindows