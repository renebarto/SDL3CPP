#include "SDL3CPP/Size.h"

#include "SDL3CPP/Rect.h"

using namespace SDL3CPP;

Size Size::GetClamped(const Rect &rect) const
{
    Size p = *this;
    p.Clamp(rect);
    return p;
}

Size &Size::Clamp(const Rect &rect)
{
    if (x > rect.w)
        x = rect.w;
    if (y > rect.h)
        y = rect.h;
    return *this;
}

Size Size::GetWrapped(const Rect &rect) const
{
    Size p = *this;
    p.Wrap(rect);
    return p;
}

Size &Size::Wrap(const Rect &rect)
{
    if (x > rect.w)
        x = x % rect.w;

    if (y > rect.y)
        y = y % rect.h;

    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Size &Size)
{
    stream << "[w:" << Size.x << ",h:" << Size.y << "]";
    return stream;
}

bool operator<(const Size &a, const Size &b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
