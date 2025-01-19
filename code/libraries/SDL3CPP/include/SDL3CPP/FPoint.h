#pragma once

#include <SDL3/SDL_rect.h>
#include <cmath>
#include <ostream>

namespace SDL3CPP {

class FRect;

class FPoint : public SDL_FPoint
{
  public:
    constexpr FPoint()
        : SDL_FPoint{0, 0}
    {
    }

    constexpr FPoint(const SDL_FPoint &point)
        : SDL_FPoint{point.x, point.y}
    {
    }

    constexpr FPoint(float x, float y)
        : SDL_FPoint{x, y}
    {
    }

    FPoint(const FPoint &) noexcept = default;
    FPoint(FPoint &&) noexcept = default;

    FPoint &operator=(const FPoint &) noexcept = default;
    FPoint &operator=(FPoint &&) noexcept = default;

    constexpr float GetX() const
    {
        return x;
    }
    FPoint &SetX(float nx)
    {
        x = nx;
        return *this;
    }

    constexpr float GetY() const
    {
        return y;
    }
    FPoint &SetY(float ny)
    {
        y = ny;
        return *this;
    }

    constexpr FPoint operator-() const
    {
        return FPoint(-x, -y);
    }
    constexpr FPoint operator+(const FPoint &other) const
    {
        return FPoint(x + other.x, y + other.y);
    }
    constexpr FPoint operator-(const FPoint &other) const
    {
        return FPoint(x - other.x, y - other.y);
    }

    constexpr FPoint operator/(float value) const
    {
        return FPoint(x / value, y / value);
    }
    constexpr FPoint operator/(const FPoint &other) const
    {
        return FPoint(x / other.x, y / other.y);
    }

    constexpr FPoint operator%(float value) const
    {
        return FPoint(remainderf(x, value), remainderf(y, value));
    }
    constexpr FPoint operator%(const FPoint &other) const
    {
        return FPoint(remainderf(x, other.x), remainderf(y, other.y));
    }

    constexpr FPoint operator*(float value) const
    {
        return FPoint(x * value, y * value);
    }
    constexpr FPoint operator*(const FPoint &other) const
    {
        return FPoint(x * other.x, y * other.y);
    }

    FPoint &operator+=(const FPoint &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    FPoint &operator-=(const FPoint &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    FPoint &operator/=(float value)
    {
        x /= value;
        y /= value;
        return *this;
    }
    FPoint &operator/=(const FPoint &other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    FPoint &operator%=(float value)
    {
        x = remainderf(x, value);
        y = remainderf(y, value);
        return *this;
    }
    FPoint &operator%=(const FPoint &other)
    {
        x = remainderf(x, other.x);
        y = remainderf(y, other.y);
        return *this;
    }

    FPoint &operator*=(float value)
    {
        x *= value;
        y *= value;
        return *this;
    }
    FPoint &operator*=(const FPoint &other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    FPoint GetClamped(const FRect &rect) const;
    FPoint &Clamp(const FRect &rect);

    FPoint GetWrapped(const FRect &rect) const;
    FPoint &Wrap(const FRect &rect);
};

} // namespace SDL3CPP

constexpr bool operator==(const SDL3CPP::FPoint &a, const SDL3CPP::FPoint &b)
{
    return a.x == b.x && a.y == b.y;
}

constexpr bool operator!=(const SDL3CPP::FPoint &a, const SDL3CPP::FPoint &b)
{
    return !(a == b);
}

bool operator<(const SDL3CPP::FPoint &a, const SDL3CPP::FPoint &b);
std::ostream &operator<<(std::ostream &stream, const SDL3CPP::FPoint &point);

namespace std {

template <> struct hash<SDL3CPP::FPoint>
{
    size_t operator()(const SDL3CPP::FPoint &p) const
    {
        size_t seed = std::hash<float>()(p.x);
        seed ^= std::hash<float>()(p.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

} // namespace std