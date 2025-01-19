#include "SDL3CPP/FPoint.h"

#include "SDL3CPP/FRect.h"

using namespace SDL3CPP;

FPoint FPoint::GetClamped(const FRect &rect) const
{
    FPoint p = *this;
    p.Clamp(rect);
    return p;
}

FPoint &FPoint::Clamp(const FRect &rect)
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

FPoint FPoint::GetWrapped(const FRect &rect) const
{
    FPoint p = *this;
    p.Wrap(rect);
    return p;
}

FPoint &FPoint::Wrap(const FRect &rect)
{
    if (x < rect.x)
        x = rect.x + rect.w - 1 - remainderf((rect.x - x + rect.w - 1), rect.w);
    else if (x >= rect.x + rect.w)
        x = rect.x + remainderf((x - rect.x - rect.w), rect.w);

    if (y < rect.y)
        y = rect.y + rect.h - 1 - remainderf((rect.y - y + rect.h - 1), rect.h);
    else if (y >= rect.y + rect.h)
        y = rect.y + remainderf((y - rect.y - rect.h), rect.h);

    return *this;
}

std::ostream &operator<<(std::ostream &stream, const FPoint &point)
{
    stream << "[x:" << point.x << ",y:" << point.y << "]";
    return stream;
}

bool operator<(const FPoint &a, const FPoint &b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
