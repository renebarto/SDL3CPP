#pragma once

#include "SDL3CPP/FRect.h"

namespace SDL3CPP
{
    class Color;
    class Event;
    class Renderer;
}

namespace GUI {

class UI;
class UIContainer;

using Handle = uint32_t;

class UIElement
{
protected:
    UIContainer *m_parent;
    UI *m_ui;
    SDL3CPP::FRect m_rect;
    Handle m_handle;

public:
    UIElement(UIContainer *parent, const SDL3CPP::FRect & rect);
    virtual ~UIElement() = default;

    UI *GetUI() const;
    UIContainer *GetParent() const;
    void SetParent(UIContainer *parent);

    Handle GetHandle() const;

    bool Destroy();

    static Handle Create(UIContainer *parent, const SDL3CPP::FRect & rect);
    static bool DestroyElement(Handle element);

    virtual void Render(SDL3CPP::Renderer &renderer) = 0;

    virtual void SetFocus(bool focus) = 0;
    virtual void SetBackgroundColor(const SDL3CPP::Color &color) = 0;

    float Width() const { return m_rect.w; }
    float Height() const { return m_rect.h; }
    const SDL3CPP::FRect &GetRect() const;
    void SetRect(const SDL3CPP::FRect &rect);
};

} // namespace GUI
