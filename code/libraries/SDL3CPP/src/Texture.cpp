#include "SDL3CPP/Texture.h"

#include <SDL3_image/SDL_image.h>
#include <cassert>
#include <sstream>

#include "SDL3CPP/FPoint.h"
#include "SDL3CPP/Renderer.h"
#include "SDL3CPP/Surface.h"

using namespace SDL3CPP;

Texture::Texture()
    : m_texture{}
{
}

Texture::Texture(SDL_Texture *texture)
    : m_texture(texture)
{
    assert(texture);
}

Texture::Texture(Renderer &renderer, SDL_PixelFormat format, SDL_TextureAccess access, int w, int h)
{
    if ((m_texture = SDL_CreateTexture(renderer.Get(), format, access, w, h)) == nullptr)
    {
        std::ostringstream stream;
        stream << "SDL_CreateTexture failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
}

#ifdef SDL2_WITH_IMAGE
// Texture::Texture(Renderer &renderer, RWops &rwops)
//{
//     if ((m_texture = IMG_LoadTexture_RW(renderer.Get(), rwops.Get(), 0)) == nullptr)
//     {
//         std::ostringstream stream;
//         stream << "IMG_LoadTexture_RW failed: " << SDL_GetError();
//         throw std::runtime_error(stream.str());
//     }
// }

Texture::Texture(Renderer &renderer, const std::filesystem::path &path)
{
    if ((m_texture = IMG_LoadTexture(renderer.Get(), path.string().c_str())) == nullptr)
    {
        std::ostringstream stream;
        stream << "IMG_LoadTexture failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
}
#endif

Texture::Texture(Renderer &renderer, const Surface &surface)
{
    if ((m_texture = SDL_CreateTextureFromSurface(renderer.Get(), surface.Get())) == nullptr)
    {
        std::ostringstream stream;
        stream << "SDL_CreateTextureFromSurface failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
}

Texture::Texture(Texture &&other) noexcept
    : m_texture(other.m_texture)
{
    other.m_texture = nullptr;
}

Texture::~Texture()
{
    if (m_texture != nullptr)
        SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
}

Texture &Texture::operator=(Texture &&other) noexcept
{
    if (&other == this)
        return *this;
    if (m_texture != nullptr)
        SDL_DestroyTexture(m_texture);
    m_texture = other.m_texture;
    other.m_texture = nullptr;
    return *this;
}

bool Texture::IsEmpty() const
{
    return m_texture == nullptr;
}

SDL_Texture *Texture::Get() const
{
    return m_texture;
}

Texture &Texture::Update(const Optional<Rect> &rect, const void *pixels, int pitch)
{
    if (SDL_UpdateTexture(m_texture, rect ? &*rect : nullptr, pixels, pitch) != 0)
    {
        std::ostringstream stream;
        stream << "SDL_UpdateTexture failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

// Texture &Texture::Update(const Optional<Rect> &rect, Surface &surface)
//{
//     Rect real_rect = rect ? *rect : Rect(0, 0, GetWidth(), GetHeight());
//
//     real_rect.w = std::min(real_rect.w, surface.GetWidth());
//     real_rect.h = std::min(real_rect.h, surface.GetHeight());
//
//     if (GetFormat() == surface.GetFormat())
//     {
//         Surface::LockHandle lock = surface.Lock();
//
//         return Update(real_rect, lock.GetPixels(), lock.GetPitch());
//     }
//     else
//     {
//         Surface converted = surface.Convert(GetFormat());
//         Surface::LockHandle lock = converted.Lock();
//
//         return Update(real_rect, lock.GetPixels(), lock.GetPitch());
//     }
// }
//
// Texture &Texture::Update(const Optional<Rect> &rect, Surface &&surface)
//{
//     Rect real_rect = rect ? *rect : Rect(0, 0, GetWidth(), GetHeight());
//
//     real_rect.w = std::min(real_rect.w, surface.GetWidth());
//     real_rect.h = std::min(real_rect.h, surface.GetHeight());
//
//     if (GetFormat() == surface.GetFormat())
//     {
//         Surface::LockHandle lock = surface.Lock();
//
//         return Update(real_rect, lock.GetPixels(), lock.GetPitch());
//     }
//     else
//     {
//         Surface converted = surface.Convert(GetFormat());
//         Surface::LockHandle lock = converted.Lock();
//
//         return Update(real_rect, lock.GetPixels(), lock.GetPitch());
//     }
// }

Texture &Texture::UpdateYUV(const Optional<Rect> &rect, const uint8_t *yplane, int ypitch, const uint8_t *uplane,
                            int upitch, const uint8_t *vplane, int vpitch)
{
    if (SDL_UpdateYUVTexture(m_texture, rect ? &*rect : nullptr, yplane, ypitch, uplane, upitch, vplane, vpitch) != 0)
    {
        std::ostringstream stream;
        stream << "SDL_UpdateYUVTexture failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

uint32_t Texture::GetFormat() const
{
    uint32_t format{};
    //if (SDL_QueryTexture(m_texture, &format, nullptr, nullptr, nullptr) != 0)
    //{
    //    std::ostringstream stream;
    //    stream << "SDL_QueryTexture failed: " << SDL_GetError();
    //    throw std::runtime_error(stream.str());
    //}
    return format;
}

int Texture::GetAccess() const
{
    auto propertiesID = SDL_GetTextureProperties(m_texture);
    return static_cast<int>(SDL_GetNumberProperty(propertiesID, SDL_PROP_TEXTURE_ACCESS_NUMBER, 0));
}

float Texture::GetWidth() const
{
    return GetSize().x;
}

float Texture::GetHeight() const
{
    return GetSize().y;
}

FPoint Texture::GetSize() const
{
    float w, h;
    if (!SDL_GetTextureSize(m_texture, &w, &h))
    {
        std::ostringstream stream;
        stream << "SDL_GetTextureSize failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return FPoint(w, h);
}

Point Texture::GetSizeInt() const
{
    float w, h;
    if (!SDL_GetTextureSize(m_texture, &w, &h))
    {
        std::ostringstream stream;
        stream << "SDL_GetTextureSize failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return Point(static_cast<int>(w), static_cast<int>(h));
}

Texture &Texture::SetColorMod(uint8_t r, uint8_t g, uint8_t b)
{
    if (!SDL_SetTextureColorMod(m_texture, r, g, b))
    {
        std::ostringstream stream;
        stream << "SDL_SetTextureColorMod failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

void Texture::GetColorMod(uint8_t &r, uint8_t &g, uint8_t &b) const
{
    if (!SDL_GetTextureColorMod(m_texture, &r, &g, &b))
    {
        std::ostringstream stream;
        stream << "SDL_GetTextureColorMod failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
}

Texture &Texture::SetAlphaMod(uint8_t alpha)
{
    if (!SDL_SetTextureAlphaMod(m_texture, alpha))
    {
        std::ostringstream stream;
        stream << "SDL_SetTextureAlphaMod failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

uint8_t Texture::GetAlphaMod() const
{
    uint8_t alpha;
    if (!SDL_GetTextureAlphaMod(m_texture, &alpha))
    {
        std::ostringstream stream;
        stream << "SDL_GetTextureAlphaMod failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return alpha;
}

Texture &Texture::SetColorAndAlphaMod(const Color &color)
{
    return SetColorMod(color.r, color.g, color.b).SetAlphaMod(color.a);
}

Color Texture::GetColorAndAlphaMod() const
{
    Color color;
    GetColorMod(color.r, color.g, color.b);
    color.a = GetAlphaMod();
    return color;
}

Texture &Texture::SetBlendMode(SDL_BlendMode blendMode)
{
    if (!SDL_SetTextureBlendMode(m_texture, blendMode))
    {
        std::ostringstream stream;
        stream << "SDL_SetTextureBlendMode failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

SDL_BlendMode Texture::GetBlendMode() const
{
    SDL_BlendMode mode;
    if (!SDL_GetTextureBlendMode(m_texture, &mode))
    {
        std::ostringstream stream;
        stream << "SDL_GetTextureBlendMode failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return mode;
}

Texture &Texture::SetScaleMode(SDL_ScaleMode scaleMode)
{
    if (!SDL_SetTextureScaleMode(m_texture, scaleMode))
    {
        std::ostringstream stream;
        stream << "SDL_SetTextureScaleMode failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

SDL_ScaleMode Texture::GetScaleMode() const
{
    SDL_ScaleMode mode;
    if (!SDL_GetTextureScaleMode(m_texture, &mode))
    {
        std::ostringstream stream;
        stream << "SDL_GetTextureScaleMode failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return mode;
}
