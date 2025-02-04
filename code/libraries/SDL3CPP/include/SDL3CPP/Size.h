#pragma once

#include <SDL3/SDL_rect.h>
#include <ostream>

namespace SDL3CPP {

class Rect;

class Size : public SDL_Point
{
  public:
    constexpr Size()
        : SDL_Point{0, 0}
    {
    }

    constexpr Size(const SDL_Point &Size)
        : SDL_Point{Size.x, Size.y}
    {
    }

    constexpr Size(int x, int y)
        : SDL_Point{x, y}
    {
    }

    Size(const Size &) noexcept = default;
    Size(Size &&) noexcept = default;

    Size &operator=(const Size &) noexcept = default;
    Size &operator=(Size &&) noexcept = default;

    constexpr int GetWidth() const
    {
        return x;
    }
    Size &SetWidth(int w)
    {
        x = w;
        return *this;
    }

    constexpr int GetHeight() const
    {
        return y;
    }
    Size &SetHeight(int h)
    {
        y = h;
        return *this;
    }

    constexpr Size operator-() const
    {
        return Size(-x, -y);
    }
    constexpr Size operator+(const Size &other) const
    {
        return Size(x + other.x, y + other.y);
    }
    constexpr Size operator-(const Size &other) const
    {
        return Size(x - other.x, y - other.y);
    }

    constexpr Size operator/(int value) const
    {
        return Size(x / value, y / value);
    }
    constexpr Size operator/(const Size &other) const
    {
        return Size(x / other.x, y / other.y);
    }

    constexpr Size operator%(int value) const
    {
        return Size(x % value, y % value);
    }
    constexpr Size operator%(const Size &other) const
    {
        return Size(x % other.x, y % other.y);
    }

    constexpr Size operator*(int value) const
    {
        return Size(x * value, y * value);
    }
    constexpr Size operator*(const Size &other) const
    {
        return Size(x * other.x, y * other.y);
    }

    Size &operator+=(const Size &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    Size &operator-=(const Size &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Size &operator/=(int value)
    {
        x /= value;
        y /= value;
        return *this;
    }
    Size &operator/=(const Size &other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Size &operator%=(int value)
    {
        x %= value;
        y %= value;
        return *this;
    }
    Size &operator%=(const Size &other)
    {
        x %= other.x;
        y %= other.y;
        return *this;
    }

    Size &operator*=(int value)
    {
        x *= value;
        y *= value;
        return *this;
    }
    Size &operator*=(const Size &other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Size GetClamped(const Rect &rect) const;
    Size &Clamp(const Rect &rect);

    Size GetWrapped(const Rect &rect) const;
    Size &Wrap(const Rect &rect);
};

} // namespace SDL3CPP

constexpr bool operator==(const SDL3CPP::Size &a, const SDL3CPP::Size &b)
{
    return a.x == b.x && a.y == b.y;
}

constexpr bool operator!=(const SDL3CPP::Size &a, const SDL3CPP::Size &b)
{
    return !(a == b);
}

bool operator<(const SDL3CPP::Size &a, const SDL3CPP::Size &b);
std::ostream &operator<<(std::ostream &stream, const SDL3CPP::Size &Size);

namespace std {

template <> struct hash<SDL3CPP::Size>
{
    size_t operator()(const SDL3CPP::Size &p) const
    {
        size_t seed = std::hash<int>()(p.x);
        seed ^= std::hash<int>()(p.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

} // namespace std