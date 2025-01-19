#pragma once

#include <SDL3/SDL_rect.h>
#include <ostream>

namespace SDL3CPP {

class Rect;

class Point : public SDL_Point
{
  public:
    constexpr Point()
        : SDL_Point{0, 0}
    {
    }

    constexpr Point(const SDL_Point &point)
        : SDL_Point{point.x, point.y}
    {
    }

    constexpr Point(int x, int y)
        : SDL_Point{x, y}
    {
    }

    Point(const Point &) noexcept = default;
    Point(Point &&) noexcept = default;

    Point &operator=(const Point &) noexcept = default;
    Point &operator=(Point &&) noexcept = default;

    constexpr int GetX() const
    {
        return x;
    }
    Point &SetX(int nx)
    {
        x = nx;
        return *this;
    }

    constexpr int GetY() const
    {
        return y;
    }
    Point &SetY(int ny)
    {
        y = ny;
        return *this;
    }

    constexpr Point operator-() const
    {
        return Point(-x, -y);
    }
    constexpr Point operator+(const Point &other) const
    {
        return Point(x + other.x, y + other.y);
    }
    constexpr Point operator-(const Point &other) const
    {
        return Point(x - other.x, y - other.y);
    }

    constexpr Point operator/(int value) const
    {
        return Point(x / value, y / value);
    }
    constexpr Point operator/(const Point &other) const
    {
        return Point(x / other.x, y / other.y);
    }

    constexpr Point operator%(int value) const
    {
        return Point(x % value, y % value);
    }
    constexpr Point operator%(const Point &other) const
    {
        return Point(x % other.x, y % other.y);
    }

    constexpr Point operator*(int value) const
    {
        return Point(x * value, y * value);
    }
    constexpr Point operator*(const Point &other) const
    {
        return Point(x * other.x, y * other.y);
    }

    Point &operator+=(const Point &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    Point &operator-=(const Point &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Point &operator/=(int value)
    {
        x /= value;
        y /= value;
        return *this;
    }
    Point &operator/=(const Point &other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Point &operator%=(int value)
    {
        x %= value;
        y %= value;
        return *this;
    }
    Point &operator%=(const Point &other)
    {
        x %= other.x;
        y %= other.y;
        return *this;
    }

    Point &operator*=(int value)
    {
        x *= value;
        y *= value;
        return *this;
    }
    Point &operator*=(const Point &other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Point GetClamped(const Rect &rect) const;
    Point &Clamp(const Rect &rect);

    Point GetWrapped(const Rect &rect) const;
    Point &Wrap(const Rect &rect);
};

} // namespace SDL3CPP

constexpr bool operator==(const SDL3CPP::Point &a, const SDL3CPP::Point &b)
{
    return a.x == b.x && a.y == b.y;
}

constexpr bool operator!=(const SDL3CPP::Point &a, const SDL3CPP::Point &b)
{
    return !(a == b);
}

bool operator<(const SDL3CPP::Point &a, const SDL3CPP::Point &b);
std::ostream &operator<<(std::ostream &stream, const SDL3CPP::Point &point);

namespace std {

template <> struct hash<SDL3CPP::Point>
{
    size_t operator()(const SDL3CPP::Point &p) const
    {
        size_t seed = std::hash<int>()(p.x);
        seed ^= std::hash<int>()(p.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

} // namespace std