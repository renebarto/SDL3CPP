#include "View/UIPanel.h"

#include "tracing/ScopedTracing.h"
#include "SDL3CPP/Renderer.h"
#include "View/UIContainer.h"

using namespace GUI;

UIPanel::UIPanel(UIContainer *parent, const SDL3CPP::FRect &rect, const SDL3CPP::Color &backgroundColor)
    : UIElement{ parent, rect }
    , m_backgroundColor{ backgroundColor}
    , m_haveFocus{ false }
    , m_focusReEnter{ false }
{
}

UIPanel::~UIPanel()
{
}

void UIPanel::Render(SDL3CPP::Renderer &renderer)
{
    renderer.SetDrawColor(m_backgroundColor);
    renderer.FillRect(m_rect);
    if (m_haveFocus)
    {
        renderer.SetDrawColor(SDL3CPP::Color::White);
        renderer.DrawRect(m_rect);
    }
}

void UIPanel::SetFocus(bool focus)
{
//    SCOPEDTRACE(nullptr, nullptr);
    if (m_haveFocus != focus)
    {
        TRACE_INFO("UIPanel::SetFocus: {}", focus);
        m_haveFocus = focus;
        if (m_haveFocus && m_parent)
        {
            m_parent->FocusElement(shared_from_this());
        }
    }
}

void UIPanel::SetBackgroundColor(const SDL3CPP::Color &color)
{
    m_backgroundColor = color;
}
