#include "View/UIElement.h"

#include "SDL3CPP/FRect.h"
#include "View/UI.h"

using namespace GUI;

UIElement::UIElement(UIContainer *parent, const SDL3CPP::FRect &rect)
    : m_parent{parent}
    , m_ui{nullptr}
    , m_rect{rect}
{
    if (m_parent)
    {
        m_ui = m_parent->GetUI();
    }
}

UI *UIElement::GetUI() const
{
    return m_ui;
}

UIContainer *UIElement::GetParent() const
{
    return m_parent;
}

void UIElement::SetParent(UIContainer *parent)
{
    m_parent = parent;
}

const SDL3CPP::FRect &UIElement::GetRect() const
{
    return m_rect;
}

void UIElement::SetRect(const SDL3CPP::FRect &rect)
{
    m_rect = rect;
}