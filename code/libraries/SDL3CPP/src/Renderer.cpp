#include "SDL3CPP/Renderer.h"

#include <sstream>

#include <SDL3/SDL.h>
#include "SDL3CPP/Surface.h"
#include "SDL3CPP/Texture.h"
#include "SDL3CPP/Window.h"

using namespace SDL3CPP;

Renderer::Renderer()
    : m_renderer{}
{
}

Renderer::Renderer(Window &window, const char *name /*= nullptr*/, RendererVSyncMode vsyncMode /*= RendererVSyncMode::Disabled*/)
{
    m_renderer = SDL_CreateRenderer(window.Get(), name);
    if (m_renderer == nullptr)
    {
        std::ostringstream stream;
        stream << "SDL_CreateRenderer failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    SetVsync(vsyncMode);
}

Renderer::Renderer(Renderer &&other) noexcept
    : m_renderer(other.m_renderer)
{
    other.m_renderer = nullptr;
}

Renderer::~Renderer()
{
    if (m_renderer != nullptr)
        SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
}

Renderer &Renderer::operator=(Renderer &&other) noexcept
{
    if (&other == this)
        return *this;
    if (m_renderer != nullptr)
        SDL_DestroyRenderer(m_renderer);
    m_renderer = other.m_renderer;
    other.m_renderer = nullptr;
    return *this;
}

SDL_Renderer *Renderer::Get() const
{
    return m_renderer;
}

bool Renderer::IsEmpty() const
{
    return m_renderer == nullptr;
}

Renderer &Renderer::Present()
{
    SDL_RenderPresent(m_renderer);
    return *this;
}

Renderer &Renderer::Clear()
{
    if (!SDL_RenderClear(m_renderer))
    {
        std::ostringstream stream;
        stream << "SDL_RenderClear failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

const char *Renderer::GetName()
{
    auto name = SDL_GetRendererName(m_renderer);
    if (name == nullptr)
    {
        std::ostringstream stream;
        stream << "SDL_GetRendererInfo failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return name;
}

Renderer &Renderer::Copy(Texture &texture, const Optional<FRect> &srcrect, const Optional<FRect> &dstrect)
{
    if (!SDL_RenderTexture(m_renderer, texture.Get(), srcrect ? &*srcrect : nullptr, dstrect ? &*dstrect : nullptr))
    {
        std::ostringstream stream;
        stream << "SDL_RenderCopy failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Renderer &Renderer::Copy(Texture &texture, const Optional<FRect> &srcrect, const FPoint &dstpoint)
{
    FRect dstrect(dstpoint.x, dstpoint.y, srcrect ? srcrect->w : texture.GetWidth(),
                  srcrect ? srcrect->h : texture.GetHeight());
    return Copy(texture, srcrect, dstrect);
}

Renderer &Renderer::Copy(Texture &texture, const Optional<FRect> &srcrect, const Optional<FRect> &dstrect, double angle,
                         const Optional<FPoint> &center, int flip)
{
    if (!SDL_RenderTextureRotated(m_renderer, texture.Get(), srcrect ? &*srcrect : nullptr, dstrect ? &*dstrect : nullptr, angle,
                         center ? &*center : nullptr, static_cast<SDL_FlipMode>(flip)))
    {
        std::ostringstream stream;
        stream << "SDL_RenderCopyEx failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Renderer &Renderer::Copy(Texture &texture, const Optional<FRect> &srcrect, const FPoint &dstpoint, double angle,
                         const Optional<FPoint> &center, int flip)
{
    FRect dstrect(dstpoint.x, dstpoint.y, srcrect ? srcrect->w : texture.GetWidth(),
                  srcrect ? srcrect->h : texture.GetHeight());
    return Copy(texture, srcrect, dstrect, angle, center, flip);
}

Renderer &Renderer::FillCopy(Texture &texture, const Optional<FRect> &srcrect, const Optional<FRect> &dstrect,
                             const FPoint &offset, int flip)
{
    // resolve rectangles
    FRect src = srcrect ? *srcrect : FRect(0, 0, texture.GetWidth(), texture.GetHeight());
    FRect dst = dstrect ? *dstrect : FRect(0, 0, static_cast<float>(GetOutputWidth()), static_cast<float>(GetOutputHeight()));

    // rectangle for single tile
    FRect startTile(offset.x, offset.y, src.w, src.h);

    // ensure tile is leftmost and topmost
    if (startTile.x + startTile.w <= 0)
        startTile.x += ((-startTile.x) / startTile.w) * startTile.w;
    if (startTile.x > 0)
        startTile.x -= ((startTile.x + startTile.w - 1) / startTile.w) * startTile.w;

    if (startTile.y + startTile.h <= 0)
        startTile.y += ((-startTile.y) / startTile.h) * startTile.h;
    if (startTile.y > 0)
        startTile.y -= ((startTile.y + startTile.h - 1) / startTile.h) * startTile.h;

    // paint tile array
    for (float y = startTile.y; y < dst.h; y += startTile.h)
    {
        for (float x = startTile.x; x < dst.w; x += startTile.w)
        {
            FRect tileSrc = src;
            FRect tileDst(x, y, startTile.w, startTile.h);

            // clamp with dstrect
            float xunderflow = -x;
            if (xunderflow > 0)
            {
                tileSrc.w -= xunderflow;
                tileSrc.x += xunderflow;
                tileDst.w -= xunderflow;
                tileDst.x += xunderflow;
            }

            float yunderflow = -y;
            if (yunderflow > 0)
            {
                tileSrc.h -= yunderflow;
                tileSrc.y += yunderflow;
                tileDst.h -= yunderflow;
                tileDst.y += yunderflow;
            }

            float xoverflow = tileDst.x + tileDst.w - dst.w;
            if (xoverflow > 0)
            {
                tileSrc.w -= xoverflow;
                tileDst.w -= xoverflow;
            }

            float yoverflow = tileDst.y + tileDst.h - dst.h;
            if (yoverflow > 0)
            {
                tileSrc.h -= yoverflow;
                tileDst.h -= yoverflow;
            }

            // make tileDst absolute
            tileDst.x += dst.x;
            tileDst.y += dst.y;

            if (flip != 0)
            {
                // mirror tileSrc inside src to take flipping into account
                if (flip & SDL_FLIP_HORIZONTAL)
                    tileSrc.x = src.w - tileSrc.x - tileSrc.w;

                if (flip & SDL_FLIP_VERTICAL)
                    tileSrc.y = src.h - tileSrc.y - tileSrc.h;

                Copy(texture, tileSrc, tileDst, 0.0, NullOpt, flip);
            }
            else
            {
                Copy(texture, tileSrc, tileDst);
            }
        }
    }
    return *this;
}

Texture Renderer::CreateTexture(const Surface &surface)
{
    return Texture(SDL_CreateTextureFromSurface(m_renderer, surface.Get()));
}

Renderer &Renderer::SetTarget()
{
    if (!SDL_SetRenderTarget(m_renderer, nullptr))
    {
        std::ostringstream stream;
        stream << "SDL_SetRenderTarget failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Renderer &Renderer::SetTarget(Texture &texture)
{
    if (!SDL_SetRenderTarget(m_renderer, texture.Get()))
    {
        std::ostringstream stream;
        stream << "SDL_SetRenderTarget failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Renderer &Renderer::DrawPoint(float x, float y)
{
    if (!SDL_RenderPoint(m_renderer, x, y))
    {
        std::ostringstream stream;
        stream << "SDL_RenderPoint failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Renderer &Renderer::DrawPoint(const FPoint &p)
{
    return DrawPoint(p.x, p.y);
}

Renderer &Renderer::DrawPoints(const FPoint *points, int count)
{
    std::vector<SDL_FPoint> sdl_points;
    sdl_points.reserve(static_cast<size_t>(count));
    for (const FPoint *p = points; p != points + count; ++p)
        sdl_points.emplace_back(*p);

    if (!SDL_RenderPoints(m_renderer, sdl_points.data(), count))
    {
        std::ostringstream stream;
        stream << "SDL_RenderPoints failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }

    return *this;
}

Renderer &Renderer::DrawLine(float x1, float y1, float x2, float y2)
{
    if (!SDL_RenderLine(m_renderer, x1, y1, x2, y2))
    {
        std::ostringstream stream;
        stream << "SDL_RenderLine failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Renderer &Renderer::DrawLine(const FPoint &p1, const FPoint &p2)
{
    return DrawLine(p1.x, p1.y, p2.x, p2.y);
}

Renderer &Renderer::DrawLines(const FPoint *points, int count)
{
    std::vector<SDL_FPoint> sdl_points;
    sdl_points.reserve(static_cast<size_t>(count));
    for (const FPoint *p = points; p != points + count; ++p)
        sdl_points.emplace_back(*p);

    if (!SDL_RenderLines(m_renderer, sdl_points.data(), count))
    {
        std::ostringstream stream;
        stream << "SDL_RenderLines failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }

    return *this;
}

Renderer &Renderer::DrawRect(float x1, float y1, float x2, float y2)
{
    return DrawRect(SDL_FRect{ x1, y1, x2 - x1 + 1, y2 - y1 + 1 });
}

Renderer &Renderer::DrawRect(const FPoint &p1, const FPoint &p2)
{
    return DrawRect(p1.x, p1.y, p2.x, p2.y);
}

Renderer &Renderer::DrawRect(const FRect &r)
{
    if (!SDL_RenderRect(m_renderer, &r))
    {
        std::ostringstream stream;
        stream << "SDL_RenderRect failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Renderer &Renderer::DrawRects(const FRect *rects, int count)
{
    std::vector<SDL_FRect> sdl_rects;
    sdl_rects.reserve(static_cast<size_t>(count));
    for (const FRect *r = rects; r != rects + count; ++r)
        sdl_rects.emplace_back(*r);

    if (!SDL_RenderRects(m_renderer, sdl_rects.data(), count))
    {
        std::ostringstream stream;
        stream << "SDL_RenderRects failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }

    return *this;
}

Renderer &Renderer::FillRect(float x1, float y1, float x2, float y2)
{
    return FillRect(SDL_FRect { x1, y1, x2 - x1 + 1, y2 - y1 + 1 });
}

Renderer &Renderer::FillRect(const FPoint &p1, const FPoint &p2)
{
    return FillRect(p1.x, p1.y, p2.x, p2.y);
}

Renderer &Renderer::FillRect(const FRect &r)
{
    if (!SDL_RenderFillRect(m_renderer, &r))
    {
        std::ostringstream stream;
        stream << "SDL_RenderFillRect failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Renderer &Renderer::FillRects(const FRect *rects, int count)
{
    std::vector<SDL_FRect> sdl_rects;
    sdl_rects.reserve(static_cast<size_t>(count));
    for (const FRect *r = rects; r != rects + count; ++r)
        sdl_rects.emplace_back(*r);

    if (!SDL_RenderFillRects(m_renderer, sdl_rects.data(), count))
    {
        std::ostringstream stream;
        stream << "SDL_RenderFillRects failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }

    return *this;
}

Surface Renderer::ReadPixels(const Optional<Rect> &rect)
{
    return Surface(SDL_RenderReadPixels(m_renderer, rect ? &*rect : nullptr));
}

Renderer &Renderer::SetClipRect(const Optional<Rect> &rect)
{
    if (!SDL_SetRenderClipRect(m_renderer, rect ? &*rect : nullptr))
    {
        std::ostringstream stream;
        stream << "SDL_SetRenderClipRect failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Optional<Rect> Renderer::GetClipRect() const
{
    SDL_Rect rect;
    SDL_GetRenderClipRect(m_renderer, &rect);

    if (SDL_RectEmpty(&rect))
        return NullOpt;
    else
        return Rect(rect);
}

Renderer &Renderer::SetLogicalSize(int w, int h, SDL_RendererLogicalPresentation mode)
{
    if (!SDL_SetRenderLogicalPresentation(m_renderer, w, h, mode))
    {
        std::ostringstream stream;
        stream << "SDL_SetRenderLogicalPresentation failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Point Renderer::GetLogicalSize() const
{
    int w, h;
    SDL_GetRenderLogicalPresentation(m_renderer, &w, &h, nullptr);
    return Point(w, h);
}

int Renderer::GetLogicalWidth() const
{
    int w;
    SDL_GetRenderLogicalPresentation(m_renderer, &w, nullptr, nullptr);
    return w;
}

int Renderer::GetLogicalHeight() const
{
    int h;
    SDL_GetRenderLogicalPresentation(m_renderer, nullptr, &h, nullptr);
    return h;
}

Renderer &Renderer::SetScale(float scaleX, float scaleY)
{
    if (!SDL_SetRenderScale(m_renderer, scaleX, scaleY))
    {
        std::ostringstream stream;
        stream << "SDL_RenderSetScale failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

bool Renderer::GetScale(float &scalex, float &scaley) const
{
    if (!SDL_GetRenderScale(m_renderer, &scalex, &scaley))
    {
        std::ostringstream stream;
        stream << "SDL_GetRenderScale failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return true;
}

float Renderer::GetXScale() const
{
    float scalex;
    if (!SDL_GetRenderScale(m_renderer, &scalex, nullptr))
    {
        std::ostringstream stream;
        stream << "SDL_GetRenderScale failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return scalex;
}

float Renderer::GetYScale() const
{
    float scaley;
    if (!SDL_GetRenderScale(m_renderer, nullptr, &scaley))
    {
        std::ostringstream stream;
        stream << "SDL_GetRenderScale failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return scaley;
}

Renderer &Renderer::SetViewport(const Optional<Rect> &rect)
{
    if (!SDL_SetRenderViewport(m_renderer, rect ? &*rect : nullptr))
    {
        std::ostringstream stream;
        stream << "SDL_RenderSetViewport failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Rect Renderer::GetViewport() const
{
    SDL_Rect rect;
    SDL_GetRenderViewport(m_renderer, &rect);
    return rect;
}

Renderer &Renderer::SetDrawBlendMode(SDL_BlendMode blendMode)
{
    if (!SDL_SetRenderDrawBlendMode(m_renderer, blendMode))
    {
        std::ostringstream stream;
        stream << "SDL_SetRenderDrawBlendMode failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

SDL_BlendMode Renderer::GetDrawBlendMode() const
{
    SDL_BlendMode mode;
    if (!SDL_GetRenderDrawBlendMode(m_renderer, &mode))
    {
        std::ostringstream stream;
        stream << "SDL_GetRenderDrawBlendMode failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return mode;
}

Renderer &Renderer::SetVsync(RendererVSyncMode mode)
{
    if (!SDL_SetRenderVSync(m_renderer, static_cast<int>(mode)))
    {
        std::ostringstream stream;
        stream << "SDL_SetRenderVSync failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

RendererVSyncMode Renderer::GetVsync() const
{
    int mode;
    if (!SDL_GetRenderVSync(m_renderer, &mode))
    {
        std::ostringstream stream;
        stream << "SDL_GetRenderDrawBlendMode failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return static_cast<RendererVSyncMode>(mode);
}

Renderer &Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    if (!SDL_SetRenderDrawColor(m_renderer, r, g, b, a))
    {
        std::ostringstream stream;
        stream << "SDL_SetRenderDrawColor failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return *this;
}

Renderer &Renderer::SetDrawColor(const Color &color)
{
    return SetDrawColor(color.r, color.g, color.b, color.a);
}

Color Renderer::GetDrawColor() const
{
    Color color;
    GetDrawColor(color.r, color.g, color.b, color.a);
    return color;
}

void Renderer::GetDrawColor(Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a) const
{
    if (!SDL_GetRenderDrawColor(m_renderer, &r, &g, &b, &a))
    {
        std::ostringstream stream;
        stream << "SDL_GetRenderDrawColor failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
}

Point Renderer::GetOutputSize() const
{
    int w, h;
    if (!SDL_GetCurrentRenderOutputSize(m_renderer, &w, &h))
    {
        std::ostringstream stream;
        stream << "SDL_GetRendererOutputSize failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return Point(w, h);
}

int Renderer::GetOutputWidth() const
{
    return GetOutputSize().x;
}

int Renderer::GetOutputHeight() const
{
    return GetOutputSize().y;
}
