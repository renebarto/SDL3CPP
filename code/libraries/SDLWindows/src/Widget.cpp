#include "SDLWindows/Widget.h"

using namespace SDLWindows;
using namespace SDL3CPP;

namespace serialization {

template<>
const BidirectionalMap<SDLWindows::WidgetStyle, std::string> EnumSerializationMap<SDLWindows::WidgetStyle>::ConversionMap =
{
    { SDLWindows::WidgetStyle::None, "None"},
    { SDLWindows::WidgetStyle::Child, "Child"},
};

} // namespace serialization

const WidgetHandle SDLWindows::NullHandle = 0;

Widget::Widget()
    : m_parent{ NullHandle }
    , m_title{}
    , m_style{}
    , m_rect{}
{
}

Widget::~Widget()
{
}

WidgetHandle Widget::GetParent() const
{
    return m_parent;
}

const std::string &Widget::GetTitle() const
{
    return m_title;
}

WidgetStyleFlags Widget::GetStyle() const
{
    return m_style;
}

const Rect &Widget::GetRect() const
{
    return m_rect;
}

Point Widget::GetPosition() const
{
    return m_rect.GetTopLeft();
}

Size Widget::GetSize() const
{
    return m_rect.GetSize();
}
