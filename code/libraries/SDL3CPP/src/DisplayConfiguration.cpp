#include "SDL3CPP/DisplayConfiguration.h"

#include <SDL3/SDL.h>

using namespace SDL3CPP;

static void CopyDisplayMode(const SDL_DisplayMode &displayMode, DisplayInfo &displayInfo)
{
    displayInfo.displayID = static_cast<DisplayID>(displayMode.displayID);
    displayInfo.format = static_cast<PixelFormat>(displayMode.format);
    displayInfo.w = displayMode.w;
    displayInfo.h = displayMode.h;
    displayInfo.pixel_density = displayMode.pixel_density;
    displayInfo.refresh_rate = displayMode.refresh_rate;
    displayInfo.refresh_rate_numerator = displayMode.refresh_rate_numerator;
    displayInfo.refresh_rate_denominator = displayMode.refresh_rate_denominator;
}

DisplayConfiguration::DisplayConfiguration()
    : m_displayCount{}
    , m_primaryDisplay{}
    , m_displayInfo{}
{
        auto displayNumbers = SDL_GetDisplays(&m_displayCount);

        for (int i = 0; i < m_displayCount; ++i)
        {
            auto displayMode = SDL_GetCurrentDisplayMode(displayNumbers[i]);
            DisplayInfo displayInfo{};
            CopyDisplayMode(*displayMode, displayInfo);
            m_displayInfo.insert({displayNumbers[i], displayInfo });
        }
        SDL_free(displayNumbers);
        m_primaryDisplay = static_cast<DisplayID>(SDL_GetPrimaryDisplay());
}

int DisplayConfiguration::GetDisplayCount()
{
    return m_displayCount;
}

DisplayID DisplayConfiguration::GetPrimaryDisplay()
{
    return m_primaryDisplay;
}

bool DisplayConfiguration::GetDisplayInfo(DisplayID displayID, DisplayInfo& info)
{
    info = {};
    if (m_displayInfo.find(displayID) != m_displayInfo.end())
    {
        info = m_displayInfo[displayID];
        return true;
    }
    return false;
}

bool DisplayConfiguration::GetPrimaryDisplayInfo(DisplayInfo &info)
{
    return GetDisplayInfo(m_primaryDisplay, info);
}
