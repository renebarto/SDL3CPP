#include "View/Button.h"

#include "tracing/ScopedTracing.h"
#include "SDL3CPP/Color.h"
#include "SDL3CPP/Renderer.h"
#include "SDL3CPP/Surface.h"
#include "SDL3CPP/Texture.h"
#include "View/UI.h"
#include "View/UIContainer.h"

using namespace GUI;

Button::Button(UIContainer *parent, const SDL3CPP::FRect &rect, const std::string &text)
    : UIElement{ parent, rect }
    , m_backgroundColor{SDL3CPP::Color::White}
    , m_haveFocus{ false }
    , m_focusReEnter{ false }
    , m_text{ text }
{
}

Button::~Button()
{
}

void Button::Render(SDL3CPP::Renderer &renderer)
{
    renderer.SetDrawColor(m_backgroundColor);
    renderer.FillRect(m_rect);
    if (m_haveFocus)
    {
        renderer.SetDrawColor(SDL3CPP::Color::White);
        renderer.DrawRect(m_rect);
    }
    auto textSurface = m_ui->GetButtonTextFont().RenderSolid(m_text, m_ui->GetButtonTextColor());
    auto texture = renderer.CreateTexture(textSurface);
    float width = static_cast<float>(textSurface.GetWidth());
    float height = static_cast<float>(textSurface.GetHeight());
    float offsetX = (m_rect.w - width) / 2.0F;
    float offsetY = (m_rect.h - height) / 2.0F;
    renderer.Copy(texture, SDL3CPP::FRect{0.0F, 0.0F, width, height},
                  SDL3CPP::FRect{m_rect.x + offsetX, m_rect.y + offsetY, width, height});

}

void Button::SetFocus(bool focus)
{
//    SCOPEDTRACE(nullptr, nullptr);
    if (m_haveFocus != focus)
    {
        TRACE_INFO("Button::SetFocus: {}", focus);
        m_haveFocus = focus;
        if (m_haveFocus && m_parent)
        {
            m_parent->FocusElement(shared_from_this());
        }
    }
}

void Button::SetBackgroundColor(const SDL3CPP::Color &color)
{
    m_backgroundColor = color;
}
