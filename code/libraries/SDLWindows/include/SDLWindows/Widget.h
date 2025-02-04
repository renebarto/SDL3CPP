#pragma once

#include <cstdint>
#include "utility/EnumBitSet.h"
#include "SDL3CPP/Rect.h"

namespace SDL3CPP {
class Size;

} // namespace SDL3CPP

namespace SDLWindows {

enum class WidgetStyle : int16_t
{
    None = 0,
    Child = 0x0001,
};
using WidgetStyleFlags = utility::EnumBitSet<WidgetStyle>;

using WidgetHandle = uint32_t;
extern const WidgetHandle NullHandle;

class Widget
{
private:
    WidgetHandle m_parent;
    std::string m_title;
    WidgetStyleFlags m_style;
    SDL3CPP::Rect m_rect;

public:
    static const SDL3CPP::Point DefaultPosition;
    static const SDL3CPP::Size DefaultSize;

    Widget();
    ~Widget();

    WidgetHandle GetParent() const;
    const std::string &GetTitle() const;
    WidgetStyleFlags GetStyle() const;
    const SDL3CPP::Rect &GetRect() const;
    SDL3CPP::Point GetPosition() const;
    SDL3CPP::Size GetSize() const;

    bool Create(
        WidgetHandle parent,
        const std::string & title, 
        WidgetStyleFlags style, 
        const SDL3CPP::Point &position = DefaultPosition, 
        const SDL3CPP::Size &size = DefaultSize);
    void Destroy();

};

} // namespace SDLWindows