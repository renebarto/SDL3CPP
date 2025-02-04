#pragma once

#include <SDL3/SDL_pixels.h>
#include <ostream>

namespace SDL3CPP {

class Color : public SDL_Color
{
public:
    constexpr Color()
        : SDL_Color{0, 0, 0, 0}
    {
    }

    constexpr Color(const SDL_Color &color)
        : SDL_Color{color.r, color.g, color.b, color.a}
    {
    }

    constexpr Color(uint8_t r, uint8_t g, uint8_t b)
        : SDL_Color{r, g, b, SDL_ALPHA_OPAQUE}
    {
    }

    constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : SDL_Color{r, g, b, a}
    {
    }

    Color(const Color &) noexcept = default;
    Color(Color &&) noexcept = default;

    Color &operator=(const Color &) noexcept = default;
    Color &operator=(Color &&) noexcept = default;

    static const Color Black;
    static const Color Red;
    static const Color Green;
    static const Color Yellow;
    static const Color Blue;
    static const Color Magenta;
    static const Color Cyan;
    static const Color White;

    constexpr uint8_t GetRed() const
    {
        return r;
    }
    Color &SetRed(int nr)
    {
        r = static_cast<uint8_t>(nr);
        return *this;
    }
    constexpr uint8_t GetGreen() const
    {
        return g;
    }
    Color &SetGreen(int ng)
    {
        g = static_cast<uint8_t>(ng);
        return *this;
    }
    constexpr uint8_t GetBlue() const
    {
        return b;
    }
    Color &SetBlue(int nb)
    {
        b = static_cast<uint8_t>(nb);
        return *this;
    }
    constexpr uint8_t GetAlpha() const
    {
        return a;
    }
    Color &SetAlpha(int na)
    {
        a = static_cast<uint8_t>(na);
        return *this;
    }
};

} // namespace SDL3CPP

constexpr bool operator==(const SDL3CPP::Color &a, const SDL3CPP::Color &b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

constexpr bool operator!=(const SDL3CPP::Color &a, const SDL3CPP::Color &b)
{
    return !(a == b);
}

std::ostream &operator<<(std::ostream &stream, const SDL3CPP::Color &color);

namespace std {

template <> struct hash<SDL3CPP::Color>
{
    size_t operator()(const SDL3CPP::Color &c) const
    {
        size_t seed = std::hash<int>()(c.r);
        seed ^= std::hash<int>()(c.g) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<int>()(c.b) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<int>()(c.a) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

} // namespace std
