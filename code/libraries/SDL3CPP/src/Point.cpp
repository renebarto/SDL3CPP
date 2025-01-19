#include "SDL3CPP/Point.h"

#include "SDL3CPP/Rect.h"

using namespace SDL3CPP;

Point Point::GetClamped(const Rect &rect) const
{
    Point p = *this;
    p.Clamp(rect);
    return p;
}

Point &Point::Clamp(const Rect &rect)
{
    if (x < rect.x)
        x = rect.x;
    if (x > rect.GetX2())
        x = rect.GetX2();
    if (y < rect.y)
        y = rect.y;
    if (y > rect.GetY2())
        y = rect.GetY2();
    return *this;
}

Point Point::GetWrapped(const Rect &rect) const
{
    Point p = *this;
    p.Wrap(rect);
    return p;
}

Point &Point::Wrap(const Rect &rect)
{
    if (x < rect.x)
        x = rect.x + rect.w - 1 - (rect.x - x + rect.w - 1) % rect.w;
    else if (x >= rect.x + rect.w)
        x = rect.x + (x - rect.x - rect.w) % rect.w;

    if (y < rect.y)
        y = rect.y + rect.h - 1 - (rect.y - y + rect.h - 1) % rect.h;
    else if (y >= rect.y + rect.h)
        y = rect.y + (y - rect.y - rect.h) % rect.h;

    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Point &point)
{
    stream << "[x:" << point.x << ",y:" << point.y << "]";
    return stream;
}

bool operator<(const Point &a, const Point &b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
