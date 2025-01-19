#include "SDL3CPP/Surface.h"

#include <cassert>
#include <sstream>

#include <SDL3_Image/SDL_image.h>

#include "SDL3CPP/Color.h"
#include "SDL3CPP/Rect.h"
#include "SDL3CPP/SDLImage.h"
#include "SDL3CPP/Window.h"

using namespace SDL3CPP;

Surface::Surface()
    : m_surface{}
{
}

Surface::Surface(SDL_Surface *surface)
    : m_surface{surface}
{
    if (!m_surface)
    {
        std::ostringstream stream;
        stream << "Empty surface";
        throw std::runtime_error(stream.str());
    }
}

Surface::Surface(const Window &window)
    : m_surface{window.GetSurface()}
{
    if (m_surface == nullptr)
    {
        std::ostringstream stream;
        stream << "SDL_GetWindowSurface failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
}

#ifdef SDL2_WITH_IMAGE

Surface::Surface(const std::filesystem::path &path)
    : m_surface{}
{
    *this = std::move(GetSDLImage().Load(path.string()));
    if (m_surface == nullptr)
    {
        std::ostringstream stream;
        stream << "IMG_Load failed: " << IMG_GetError();
        throw std::runtime_error(stream.str());
    }
}

#endif

Surface::Surface(Surface &&other) noexcept
    : m_surface(other.m_surface)
{
    other.m_surface = nullptr;
}

Surface::~Surface()
{
    if (m_surface != nullptr)
        SDL_DestroySurface(m_surface);
    m_surface = nullptr;
}

Surface &Surface::operator=(Surface &&other) noexcept
{
    if (&other == this)
        return *this;
    if (m_surface != nullptr)
        SDL_DestroySurface(m_surface);
    m_surface = other.m_surface;
    other.m_surface = nullptr;
    return *this;
}

bool Surface::IsEmpty() const
{
    return m_surface == nullptr;
}

SDL_Surface *Surface::Get() const
{
    return m_surface;
}

Surface Surface::Convert(const SDL_PixelFormat &format)
{
    SDL_Surface *surface = SDL_ConvertSurface(m_surface, format);
    if (surface == nullptr)
    {
        std::ostringstream stream;
        stream << "SDL_ConvertSurface failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return Surface(surface);
}

Surface Surface::Convert(uint32_t pixel_format)
{
    SDL_Surface *surface = SDL_ConvertSurface(m_surface, static_cast<SDL_PixelFormat>(pixel_format));
    if (surface == nullptr)
    {
        std::ostringstream stream;
        stream << "SDL_ConvertSurfaceFormat failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return Surface(surface);
}

void Surface::Blit(const Optional<Rect> &srcRect, Surface &dst, const Optional<Rect> &dstRect)
{
    SDL_Rect tmpDstRect; // 4th argument is non-const; does it modify rect?
    if (dstRect)
        tmpDstRect = *dstRect;
    if (!SDL_BlitSurface(m_surface, srcRect ? &*srcRect : nullptr, dst.Get(), dstRect ? &tmpDstRect : nullptr))
    {
        std::ostringstream stream;
        stream << "SDL_BlitSurface failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
}

void Surface::BlitScaled(const Optional<Rect> &srcRect, Surface &dst, const Optional<Rect> &dstRect, SDL_ScaleMode scaleMode)
{
    SDL_Rect tmpDstRect; // 4th argument is non-const; does it modify rect?
    if (dstRect)
        tmpDstRect = *dstRect;
    if (!SDL_BlitSurfaceScaled(m_surface, srcRect ? &*srcRect : nullptr, dst.Get(), dstRect ? &tmpDstRect : nullptr, scaleMode))
    {
        std::ostringstream stream;
        stream << "SDL_BlitScaled failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
}

Surface &Surface::SetClipRect(const Optional<Rect> &rect)
{
    if (!SDL_SetSurfaceClipRect(m_surface, rect ? &*rect : nullptr))
    {
        std::ostringstream stream;
        stream << "SDL_SetClipRect failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Rect Surface::GetClipRect() const
{
    SDL_Rect rect;
    SDL_GetSurfaceClipRect(m_surface, &rect);
    return Rect(rect);
}

Surface &Surface::SetColorKey(bool flag, uint32_t key)
{
    if (!SDL_SetSurfaceColorKey(m_surface, flag, key))
    {
        std::ostringstream stream;
        stream << "SDL_SetColorKey failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

uint32_t Surface::GetColorKey() const
{
    uint32_t key;
    if (!SDL_GetSurfaceColorKey(m_surface, &key))
    {
        std::ostringstream stream;
        stream << "SDL_GetColorKey failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return key;
}

Surface &Surface::SetAlphaMod(uint8_t alpha)
{
    if (!SDL_SetSurfaceAlphaMod(m_surface, alpha))
    {
        std::ostringstream stream;
        stream << "SDL_SetSurfaceAlphaMod failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

uint8_t Surface::GetAlphaMod() const
{
    uint8_t alpha;
    if (!SDL_GetSurfaceAlphaMod(m_surface, &alpha))
    {
        std::ostringstream stream;
        stream << "SDL_GetSurfaceAlphaMod failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return alpha;
}

Surface &Surface::SetBlendMode(SDL_BlendMode blendMode)
{
    if (!SDL_SetSurfaceBlendMode(m_surface, blendMode))
    {
        std::ostringstream stream;
        stream << "SDL_SetSurfaceBlendMode failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

SDL_BlendMode Surface::GetBlendMode() const
{
    SDL_BlendMode blendMode;
    if (!SDL_GetSurfaceBlendMode(m_surface, &blendMode))
    {
        std::ostringstream stream;
        stream << "SDL_GetSurfaceBlendMode failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return blendMode;
}

Surface &Surface::SetColorMod(uint8_t r, uint8_t g, uint8_t b)
{
    if (!SDL_SetSurfaceColorMod(m_surface, r, g, b))
    {
        std::ostringstream stream;
        stream << "SDL_SetSurfaceColorMod failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

void Surface::GetColorMod(uint8_t &r, uint8_t &g, uint8_t &b) const
{
    if (!SDL_GetSurfaceColorMod(m_surface, &r, &g, &b))
    {
        std::ostringstream stream;
        stream << "SDL_GetSurfaceColorMod failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
}

Surface &Surface::SetColorAndAlphaMod(const Color &color)
{
    return SetColorMod(color.r, color.g, color.b).SetAlphaMod(color.a);
}

Color Surface::GetColorAndAlphaMod() const
{
    Color color;
    GetColorMod(color.r, color.g, color.b);
    color.a = GetAlphaMod();
    return color;
}

Surface &Surface::SetRLE(bool flag)
{
    if (!SDL_SetSurfaceRLE(m_surface, flag))
    {
        std::ostringstream stream;
        stream << "SDL_SetSurfaceRLE failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Surface &Surface::FillRect(const Optional<Rect> &rect, uint32_t color)
{
    if (!SDL_FillSurfaceRect(m_surface, rect ? &*rect : nullptr, color))
    {
        std::ostringstream stream;
        stream << "SDL_FillRect failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Surface &Surface::FillRects(const Rect *rects, int count, uint32_t color)
{
    std::vector<SDL_Rect> sdl_rects;
    sdl_rects.reserve(static_cast<size_t>(count));
    for (const Rect *r = rects; r != rects + count; ++r)
        sdl_rects.emplace_back(*r);

    if (!SDL_FillSurfaceRects(m_surface, sdl_rects.data(), count, color))
    {
        std::ostringstream stream;
        stream << "SDL_FillRects failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

int Surface::GetWidth() const
{
    return m_surface->w;
}

int Surface::GetHeight() const
{
    return m_surface->h;
}

Point Surface::GetSize() const
{
    return Point(m_surface->w, m_surface->h);
}

const SDL_PixelFormatDetails *Surface::GetPixelFormat() const
{
    return SDL_GetPixelFormatDetails(m_surface->format);
}


SDL_PixelFormat Surface::GetFormatCode() const
{
    return m_surface->format;
}
