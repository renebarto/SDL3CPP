#pragma once

#include <functional>

#include <SDL3/SDL_rect.h>

#include "SDL3CPP/Optional.h"
#include "SDL3CPP/FPoint.h"

namespace SDL3CPP {

class FPoint;

class FRect
    : public SDL_FRect
{
public:
    constexpr FRect()
        : SDL_FRect{0, 0, 0, 0}
    {
    }

    constexpr FRect(const SDL_FRect &rect)
        : SDL_FRect{rect.x, rect.y, rect.w, rect.h}
    {
    }

    constexpr FRect(const FPoint &corner, const FPoint &size)
        : SDL_FRect{corner.x, corner.y, size.x, size.y}
    {
    }

    constexpr FRect(float x, float y, float w, float h)
        : SDL_FRect{x, y, w, h}
    {
    }

    FRect(const FRect &) noexcept = default;

    FRect(FRect &&) noexcept = default;

    static constexpr FRect FromCenter(float cx, float cy, float w, float h)
    {
        return FRect(cx - w / 2, cy - h / 2, w, h);
    }

    static constexpr FRect FromCenter(const FPoint &center, const FPoint &size)
    {
        return FRect(center - size / 2, size);
    }

    static constexpr FRect FromCorners(float x1, float y1, float x2, float y2)
    {
        return FRect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
    }

    static constexpr FRect FromCorners(const FPoint &p1, const FPoint &p2)
    {
        return FRect(p1, p2 - p1 + FPoint(1, 1));
    }

    FRect &operator=(const FRect &) noexcept = default;

    FRect &operator=(FRect &&) noexcept = default;

    constexpr float GetX() const
    {
        return x;
    }

    FRect &SetX(float nx)
    {
        x = nx;
        return *this;
    }

    constexpr float GetY() const
    {
        return y;
    }

    FRect &SetY(float ny)
    {
        y = ny;
        return *this;
    }

    constexpr float GetW() const
    {
        return w;
    }

    FRect &SetW(float nw)
    {
        w = nw;
        return *this;
    }

    constexpr float GetH() const
    {
        return h;
    }

    FRect &SetH(float nh)
    {
        h = nh;
        return *this;
    }

    constexpr float GetX2() const
    {
        return x + w - 1;
    }

    FRect &SetX2(float x2)
    {
        w = x2 - x + 1;
        return *this;
    }

    constexpr float GetY2() const
    {
        return y + h - 1;
    }

    FRect &SetY2(float y2)
    {
        h = y2 - y + 1;
        return *this;
    }

    constexpr FPoint GetTopLeft() const
    {
        return FPoint(x, y);
    }

    constexpr FPoint GetTopRight() const
    {
        return FPoint(GetX2(), y);
    }

    constexpr FPoint GetBottomLeft() const
    {
        return FPoint(x, GetY2());
    }

    constexpr FPoint GetBottomRight() const
    {
        return FPoint(GetX2(), GetY2());
    }

    constexpr FPoint GetSize() const
    {
        return FPoint(w, h);
    }

    constexpr FPoint GetCentroid() const
    {
        return FPoint(x + w / 2, y + h / 2);
    }

    constexpr bool Contains(float px, float py) const
    {
        return px >= x && py >= y && px <= GetX2() && py <= GetY2();
    }

    constexpr bool Contains(const FPoint &point) const
    {
        return point.x >= x && point.y >= y && point.x <= GetX2() && point.y <= GetY2();
    }

    constexpr bool Contains(const FRect &rect) const
    {
        return rect.x >= x && rect.y >= y && rect.GetX2() <= GetX2() && rect.GetY2() <= GetY2();
    }

    constexpr bool Intersects(const FRect &rect) const
    {
        return !(rect.GetX2() < x || rect.GetY2() < y || rect.x > GetX2() || rect.y > GetY2());
    }

    FRect GetUnion(const FRect &rect) const;

    FRect &Union(const FRect &rect);

    FRect GetExtension(float amount) const;

    FRect GetExtension(float hamount, float vamount) const;

    FRect &Extend(float amount);

    FRect &Extend(float hamount, float vamount);

    Optional<FRect> GetIntersection(const FRect &rect) const;

    constexpr FRect operator+(const FPoint &offset) const
    {
        return FRect(x + offset.x, y + offset.y, w, h);
    }

    constexpr FRect operator-(const FPoint &offset) const
    {
        return FRect(x - offset.x, y - offset.y, w, h);
    }

    FRect &operator+=(const FPoint &offset)
    {
        x += offset.x;
        y += offset.y;
        return *this;
    }

    FRect &operator-=(const FPoint &offset)
    {
        x -= offset.x;
        y -= offset.y;
        return *this;
    }
};

} // namespace SDL3CPP

constexpr bool operator==(const SDL3CPP::FRect &a, const SDL3CPP::FRect &b)
{
    return a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h;
}

constexpr bool operator!=(const SDL3CPP::FRect &a, const SDL3CPP::FRect &b)
{
    return !(a == b);
}

constexpr bool operator<(const SDL3CPP::FRect &a, const SDL3CPP::FRect &b)
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

constexpr bool operator<=(const SDL3CPP::FRect &a, const SDL3CPP::FRect &b)
{
    return (a < b) || (a == b);
}
constexpr bool operator>(const SDL3CPP::FRect &a, const SDL3CPP::FRect &b)
{
    return !(a <= b);
}
constexpr bool operator>=(const SDL3CPP::FRect &a, const SDL3CPP::FRect &b)
{
    return !(a < b);
}

std::ostream &operator<<(std::ostream &stream, const SDL3CPP::FRect &rect);

namespace std {

template <> struct hash<SDL3CPP::FRect>
{
    size_t operator()(const SDL3CPP::FRect &r) const
    {
        size_t seed = std::hash<float>()(r.x);
        seed ^= std::hash<float>()(r.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<float>()(r.w) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<float>()(r.h) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

} // namespace std
