#pragma once

#include <filesystem>
#include <SDL3/SDL.h>
#include "SDL3CPP/Color.h"
#include "SDL3CPP/Optional.h"
#include "SDL3CPP/Rect.h"

struct SDL_Texture;

namespace SDL3CPP {

class FPoint;
class Rect;
class Renderer;
class RWops;
class Surface;

class Texture
{
private:
    SDL_Texture *m_texture;

public:
    Texture();
    explicit Texture(SDL_Texture *texture);

    Texture(Renderer &renderer, SDL_PixelFormat format, SDL_TextureAccess access, int w, int h);

#ifdef SDL2_WITH_IMAGE
    Texture(Renderer &renderer, RWops &rwops);
    Texture(Renderer &renderer, const std::filesystem::path &path);
#endif

    Texture(Renderer &renderer, const Surface &surface);

    Texture(const Texture &other) = delete;
    Texture(Texture &&other) noexcept;

    virtual ~Texture();

    Texture &operator=(const Texture &other) = delete;
    Texture &operator=(Texture &&other) noexcept;

    bool IsEmpty() const;
    SDL_Texture *Get() const;

    Texture &Update(const Optional<Rect> &rect, const void *pixels, int pitch);
    Texture &Update(const Optional<Rect> &rect, Surface &surface);
    Texture &Update(const Optional<Rect> &rect, Surface &&surface);
    Texture &UpdateYUV(const Optional<Rect> &rect, const uint8_t *yplane, int ypitch, const uint8_t *uplane, int upitch,
                       const uint8_t *vplane, int vpitch);

    //	LockHandle Lock(const Optional<Rect>& rect = NullOpt);

    uint32_t GetFormat() const;

    int GetAccess() const;

    float GetWidth() const;
    float GetHeight() const;
    FPoint GetSize() const;
    Point GetSizeInt() const;

    Texture &SetColorMod(uint8_t r = 255, uint8_t g = 255, uint8_t b = 255);
    void GetColorMod(uint8_t &r, uint8_t &g, uint8_t &b) const;

    Texture &SetAlphaMod(uint8_t alpha = 255);
    uint8_t GetAlphaMod() const;

    Texture &SetColorAndAlphaMod(const Color &color = Color{255, 255, 255, SDL_ALPHA_OPAQUE});
    Color GetColorAndAlphaMod() const;

    Texture &SetBlendMode(SDL_BlendMode blendMode = SDL_BLENDMODE_NONE);
    SDL_BlendMode GetBlendMode() const;

    Texture &SetScaleMode(SDL_ScaleMode scaleMode = SDL_SCALEMODE_LINEAR);
    SDL_ScaleMode GetScaleMode() const;
};

} // namespace SDL3CPP
