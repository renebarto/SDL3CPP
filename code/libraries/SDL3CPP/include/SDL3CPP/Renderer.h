#pragma once

#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_render.h>
#include "SDL3CPP/FRect.h"
#include "SDL3CPP/Optional.h"
#include "SDL3CPP/Rect.h"

struct SDL_Renderer;
struct SDL_RendererInfo;

namespace SDL3CPP {

class Color;
class Point;
class Surface;
class Texture;
class Window;

enum class RendererVSyncMode
{
    Disabled = 0,
    EveryRefresh = 1,
    EverySecondRefresh = 2,
    Adaptive = -1
};

class Renderer
{
private:
    SDL_Renderer *m_renderer;

public:
    Renderer();
    explicit Renderer(SDL_Renderer *renderer);

    Renderer(Window &window, const char *name = nullptr, RendererVSyncMode vsyncMode = RendererVSyncMode::Disabled);

    Renderer(const Renderer &other) = delete;
    Renderer(Renderer &&other) noexcept;

    virtual ~Renderer();

    Renderer &operator=(const Renderer &other) = delete;
    Renderer &operator=(Renderer &&other) noexcept;

    bool IsEmpty() const;
    SDL_Renderer *Get() const;

    Renderer &Present();
    Renderer &Clear();

    const char *GetName();

    Renderer &Copy(Texture &texture, const Optional<FRect> &srcrect = NullOpt, const Optional<FRect> &dstrect = NullOpt);
    Renderer &Copy(Texture &texture, const Optional<FRect> &srcrect, const FPoint &dstpoint);
    Renderer &Copy(Texture &texture, const Optional<FRect> &srcrect, const Optional<FRect> &dstrect, double angle,
                   const Optional<FPoint> &center = NullOpt, int flip = 0);
    Renderer &Copy(Texture &texture, const Optional<FRect> &srcrect, const FPoint &dstpoint, double angle,
                   const Optional<FPoint> &center = NullOpt, int flip = 0);

    Renderer &FillCopy(Texture &texture, const Optional<FRect> &srcrect = NullOpt,
                       const Optional<FRect> &dstrect = NullOpt, const FPoint &offset = FPoint(0, 0), int flip = 0);

    Texture CreateTexture(const Surface &texture);

    Renderer &SetTarget();
    Renderer &SetTarget(Texture &texture);

    Renderer &DrawPoint(float x, float y);
    Renderer &DrawPoint(const FPoint &p);
    Renderer &DrawPoints(const FPoint *points, int count);

    Renderer &DrawLine(float x1, float y1, float x2, float y2);
    Renderer &DrawLine(const FPoint &p1, const FPoint &p2);
    Renderer &DrawLines(const FPoint *points, int count);

    Renderer &DrawRect(float x1, float y1, float x2, float y2);
    Renderer &DrawRect(const FPoint &p1, const FPoint &p2);
    Renderer &DrawRect(const FRect &r);
    Renderer &DrawRects(const FRect *rects, int count);

    Renderer &FillRect(float x1, float y1, float x2, float y2);
    Renderer &FillRect(const FPoint &p1, const FPoint &p2);
    Renderer &FillRect(const FRect &r);
    Renderer &FillRects(const FRect *rects, int count);

    Surface ReadPixels(const Optional<Rect> &rect);

    Renderer &SetClipRect(const Optional<Rect> &rect = NullOpt);
    Optional<Rect> GetClipRect() const;

    Renderer &SetLogicalSize(int w, int h, SDL_RendererLogicalPresentation mode);
    Point GetLogicalSize() const;
    int GetLogicalWidth() const;
    int GetLogicalHeight() const;

    Renderer &SetScale(float scaleX, float scaleY);
    bool GetScale(float &scalex, float &scaley) const;
    float GetXScale() const;
    float GetYScale() const;

    Renderer &SetViewport(const Optional<Rect> &rect = NullOpt);
    Rect GetViewport() const;

    Renderer &SetDrawBlendMode(SDL_BlendMode blendMode = SDL_BLENDMODE_NONE);
    SDL_BlendMode GetDrawBlendMode() const;

    Renderer &SetVsync(RendererVSyncMode mode);
    RendererVSyncMode GetVsync() const;

    Renderer &SetDrawColor(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255);
    Renderer &SetDrawColor(const Color &color);
    Color GetDrawColor() const;
    void GetDrawColor(uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) const;

    Point GetOutputSize() const;
    int GetOutputWidth() const;
    int GetOutputHeight() const;
};

} // namespace SDL3CPP
