#pragma once

#include "SDL3CPP/Optional.h"
#include "SDL3CPP/Rect.h"
#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_surface.h>
#include <filesystem>

struct SDL_Surface;
struct SDL_PixelFormatDetails;

namespace SDL3CPP {

class Color;
class Point;
class RWops;
class Window;

class Surface
{
private:
    SDL_Surface *m_surface;

public:
    Surface();
    explicit Surface(SDL_Surface *surface);
    explicit Surface(const Window &window);

    Surface(uint32_t flags, int width, int height, int depth, uint32_t Rmask, uint32_t Gmask, uint32_t Bmask,
            uint32_t Amask);
    Surface(void *pixels, int width, int height, int depth, int pitch, uint32_t Rmask, uint32_t Gmask, uint32_t Bmask,
            uint32_t Amask);
#ifdef SDL2_WITH_IMAGE
    explicit Surface(RWops &rwops);

    explicit Surface(const std::filesystem::path &path);
#endif

    virtual ~Surface();

    Surface(const Surface &) = delete;
    Surface(Surface &&other) noexcept;

    bool IsEmpty() const;
    Surface &operator=(const Surface &) = delete;
    Surface &operator=(Surface &&other) noexcept;

    SDL_Surface *Get() const;

    Surface Convert(const SDL_PixelFormat &format);
    Surface Convert(uint32_t pixel_format);
    void Blit(const Optional<Rect> &srcRect, Surface &dst, const Optional<Rect> &dstRect);
    void BlitScaled(const Optional<Rect> &srcRect, Surface &dst, const Optional<Rect> &dstRect,
                    SDL_ScaleMode scaleMode);

    Surface &SetClipRect(const Optional<Rect> &rect = NullOpt);
    Rect GetClipRect() const;

    Surface &SetColorKey(bool flag, uint32_t key);
    uint32_t GetColorKey() const;

    Surface &SetAlphaMod(uint8_t alpha = 255);
    uint8_t GetAlphaMod() const;

    Surface &SetBlendMode(SDL_BlendMode blendMode);
    SDL_BlendMode GetBlendMode() const;

    Surface &SetColorMod(uint8_t r = 255, uint8_t g = 255, uint8_t b = 255);
    void GetColorMod(uint8_t &r, uint8_t &g, uint8_t &b) const;

    Surface &SetColorAndAlphaMod(const Color &color);
    Color GetColorAndAlphaMod() const;

    Surface &SetRLE(bool flag);

    Surface &FillRect(const Optional<Rect> &rect, uint32_t color);
    Surface &FillRects(const Rect *rects, int count, uint32_t color);

    int GetWidth() const;
    int GetHeight() const;
    Point GetSize() const;

    const SDL_PixelFormatDetails *GetPixelFormat() const;
    SDL_PixelFormat GetFormatCode() const;
};

} // namespace SDL3CPP