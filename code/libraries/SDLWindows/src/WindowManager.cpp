#include "SDLWindows/WindowManager.h"

#include "SDL3CPP/SDL.h"

using namespace SDLWindows;
using namespace SDL3CPP;

WindowManager::WindowManager()
    : m_displayConfiguration{}
    , m_displayID{}
    , m_displayInfo{}
    , m_screenRect{}
    , m_isFullScreen{}
{
    m_displayConfiguration = Singleton<SDL3CPP::SDL>::Get().GetDisplayConfiguration();
    m_displayID = m_displayConfiguration.GetPrimaryDisplay();
    m_displayConfiguration.GetDisplayInfo(m_displayID, m_displayInfo);
    SetSize(Point{ m_displayInfo.w, m_displayInfo.h });
}

WindowManager::~WindowManager()
{
}

SDL3CPP::DisplayID WindowManager::GetDisplay()
{
    return m_displayID;
}

bool WindowManager::SetDisplay(DisplayID id)
{
    DisplayInfo newDisplayInfo{};
    auto result = m_displayConfiguration.GetDisplayInfo(id, newDisplayInfo);
    if (result)
    {
        m_displayID = id;
        m_displayInfo = newDisplayInfo;
    }
    return result;
}

bool WindowManager::IsFullScreen() const
{
    return m_isFullScreen;
}

void WindowManager::SetFullScreen(bool fullScreen)
{
    if (m_isFullScreen != fullScreen)
    {
        m_isFullScreen = fullScreen;
        if (fullScreen)
        {
            SetPosition(Point{});
            SetSize(Point{ m_displayInfo.w, m_displayInfo.h });
        }
        else
        {
            SetPosition(GetPosition());
            SetSize(GetSize());
        }
    }
}

Point WindowManager::GetPosition() const
{
    return Point{m_screenRect.x, m_screenRect.y};
}

void WindowManager::SetPosition(const Point &position)
{
    auto clampedPosition = position.GetClamped(Rect{ 0, 0, m_displayInfo.w, m_displayInfo.h });
    m_screenRect.x = clampedPosition.GetX();
    m_screenRect.y = clampedPosition.GetY();
}

Size WindowManager::GetSize() const
{
    return Size{m_screenRect.w, m_screenRect.h};
}

void WindowManager::SetSize(const Size &size)
{
    auto clampedSize = size.GetClamped(Rect{ m_screenRect.x, m_screenRect.y, m_displayInfo.w - m_screenRect.x, m_displayInfo.h - m_screenRect.y });
    m_screenRect.w = clampedSize.GetWidth();
    m_screenRect.h = clampedSize.GetHeight();
}
