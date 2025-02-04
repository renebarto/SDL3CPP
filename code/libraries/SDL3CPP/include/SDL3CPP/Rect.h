#pragma once

#include <functional>

#include <SDL3/SDL_rect.h>

#include "SDL3CPP/Optional.h"
#include "SDL3CPP/Point.h"
#include "SDL3CPP/Size.h"

namespace SDL3CPP {

class Point;

class Rect
    : public SDL_Rect
{
public:
    constexpr Rect()
        : SDL_Rect{0, 0, 0, 0}
    {
    }

    constexpr Rect(const SDL_Rect &rect)
        : SDL_Rect{rect.x, rect.y, rect.w, rect.h}
    {
    }

    constexpr Rect(const Point &corner, const Size &size)
        : SDL_Rect{corner.x, corner.y, size.x, size.y}
    {
    }

    constexpr Rect(int x, int y, int w, int h)
        : SDL_Rect{x, y, w, h}
    {
    }

    Rect(const Rect &) noexcept = default;

    Rect(Rect &&) noexcept = default;

    static constexpr Rect FromCenter(int cx, int cy, int w, int h)
    {
        return Rect(cx - w / 2, cy - h / 2, w, h);
    }

    static constexpr Rect FromCenter(const Point &center, const Size &size)
    {
        return Rect(center - size / 2, size);
    }

    static constexpr Rect FromCorners(int x1, int y1, int x2, int y2)
    {
        return Rect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
    }

    static constexpr Rect FromCorners(const Point &p1, const Point &p2)
    {
        return Rect(p1, p2 - p1 + Point(1, 1));
    }

    Rect &operator=(const Rect &) noexcept = default;

    Rect &operator=(Rect &&) noexcept = default;

    constexpr int GetX() const
    {
        return x;
    }

    Rect &SetX(int nx)
    {
        x = nx;
        return *this;
    }

    constexpr int GetY() const
    {
        return y;
    }

    Rect &SetY(int ny)
    {
        y = ny;
        return *this;
    }

    constexpr int GetW() const
    {
        return w;
    }

    Rect &SetW(int nw)
    {
        w = nw;
        return *this;
    }

    constexpr int GetH() const
    {
        return h;
    }

    Rect &SetH(int nh)
    {
        h = nh;
        return *this;
    }

    constexpr int GetX2() const
    {
        return x + w - 1;
    }

    Rect &SetX2(int x2)
    {
        w = x2 - x + 1;
        return *this;
    }

    constexpr int GetY2() const
    {
        return y + h - 1;
    }

    Rect &SetY2(int y2)
    {
        h = y2 - y + 1;
        return *this;
    }

    constexpr Point GetTopLeft() const
    {
        return Point(x, y);
    }

    constexpr Point GetTopRight() const
    {
        return Point(GetX2(), y);
    }

    constexpr Point GetBottomLeft() const
    {
        return Point(x, GetY2());
    }

    constexpr Point GetBottomRight() const
    {
        return Point(GetX2(), GetY2());
    }

    constexpr Size GetSize() const
    {
        return Size(w, h);
    }

    constexpr Point GetCentroid() const
    {
        return Point(x + w / 2, y + h / 2);
    }

    constexpr bool Contains(int px, int py) const
    {
        return px >= x && py >= y && px <= GetX2() && py <= GetY2();
    }

    constexpr bool Contains(const Point &point) const
    {
        return point.x >= x && point.y >= y && point.x <= GetX2() && point.y <= GetY2();
    }

    constexpr bool Contains(const Rect &rect) const
    {
        return rect.x >= x && rect.y >= y && rect.GetX2() <= GetX2() && rect.GetY2() <= GetY2();
    }

    constexpr bool Intersects(const Rect &rect) const
    {
        return !(rect.GetX2() < x || rect.GetY2() < y || rect.x > GetX2() || rect.y > GetY2());
    }

    Rect GetUnion(const Rect &rect) const;

    Rect &Union(const Rect &rect);

    Rect GetExtension(unsigned int amount) const;

    Rect GetExtension(unsigned int hamount, unsigned int vamount) const;

    Rect &Extend(unsigned int amount);

    Rect &Extend(unsigned int hamount, unsigned int vamount);

    Optional<Rect> GetIntersection(const Rect &rect) const;

    bool IntersectLine(int &x1, int &y1, int &x2, int &y2) const;

    bool IntersectLine(Point &p1, Point &p2) const;

    constexpr Rect operator+(const Point &offset) const
    {
        return Rect(x + offset.x, y + offset.y, w, h);
    }

    constexpr Rect operator-(const Point &offset) const
    {
        return Rect(x - offset.x, y - offset.y, w, h);
    }

    Rect &operator+=(const Point &offset)
    {
        x += offset.x;
        y += offset.y;
        return *this;
    }

    Rect &operator-=(const Point &offset)
    {
        x -= offset.x;
        y -= offset.y;
        return *this;
    }
};

} // namespace SDL3CPP

constexpr bool operator==(const SDL3CPP::Rect &a, const SDL3CPP::Rect &b)
{
    return a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h;
}

constexpr bool operator!=(const SDL3CPP::Rect &a, const SDL3CPP::Rect &b)
{
    return !(a == b);
}

constexpr bool operator<(const SDL3CPP::Rect &a, const SDL3CPP::Rect &b)
{
    if (a.x == b.x)
    {
        if (a.y == b.y)
        {
            if (a.w == b.w)
                return a.h < b.h;
            return a.w < b.w;
        }
        return a.y < b.y;
    }
    return a.x < b.x;
}

constexpr bool operator<=(const SDL3CPP::Rect &a, const SDL3CPP::Rect &b)
{
    return (a < b) || (a == b);
}
constexpr bool operator>(const SDL3CPP::Rect &a, const SDL3CPP::Rect &b)
{
    return !(a <= b);
}
constexpr bool operator>=(const SDL3CPP::Rect &a, const SDL3CPP::Rect &b)
{
    return !(a < b);
}

std::ostream &operator<<(std::ostream &stream, const SDL3CPP::Rect &rect);

namespace std {

template <> struct hash<SDL3CPP::Rect>
{
    size_t operator()(const SDL3CPP::Rect &r) const
    {
        size_t seed = std::hash<int>()(r.x);
        seed ^= std::hash<int>()(r.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<int>()(r.w) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<int>()(r.h) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

} // namespace std
