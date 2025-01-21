#pragma once

#include <map>
#include "SDL3CPP/PixelFormat.h"

namespace SDL3CPP {

using DisplayID = uint32_t;

struct DisplayInfo
{
    DisplayID displayID;            // the display this mode is associated with
    PixelFormat format;             // pixel format
    int w;                          // width
    int h;                          // height
    float pixel_density;            // scale converting size to pixels (e.g. a 1920x1080 mode with 2.0 scale would have 3840x2160 pixels)
    float refresh_rate;             // refresh rate (or 0.0f for unspecified)
    int refresh_rate_numerator;     // precise refresh rate numerator (or 0 for unspecified)
    int refresh_rate_denominator;   // precise refresh rate denominator
};

class DisplayConfiguration
{
private:
    int m_displayCount;
    DisplayID m_primaryDisplay;
    std::map<DisplayID, DisplayInfo> m_displayInfo;

public:
    DisplayConfiguration();
    void Init();

    int GetDisplayCount();
    DisplayID GetPrimaryDisplay();
    bool GetDisplayInfo(DisplayID displayID, DisplayInfo& info);
    bool GetPrimaryDisplayInfo(DisplayInfo& info);
};

} // namespace SDL3CPP