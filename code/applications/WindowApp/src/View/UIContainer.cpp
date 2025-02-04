#include "View/UIContainer.h"

#include "tracing/ScopedTracing.h"

using namespace GUI;
using namespace SDL3CPP;

UIContainer::UIContainer(UIContainer *parent, const SDL3CPP::FRect & rect)
    : UIElement{ parent, rect }
{
    TRACE_DEBUG("UIContainer::UIContainer");
}

UIContainer::~UIContainer()
{
    TRACE_DEBUG("UIContainer::~UIContainer");
}

void UIContainer::Render(SDL3CPP::Renderer &renderer)
{
    for (auto it = m_elements.rbegin(); it != m_elements.rend(); ++it)
    {
        (*it)->Render(renderer);
    }
}

void UIContainer::SetFocus(bool /*focus*/)
{
}

void UIContainer::SetBackgroundColor(const SDL3CPP::Color &/*color*/)
{
}

void UIContainer::FocusElement(std::shared_ptr<UIElement> element)
{
//    SCOPEDTRACE(nullptr, nullptr);
    for (auto &el : m_elements)
    {
        if (el != element)
        {
            el->SetFocus(false);
        }
    }
    element->SetFocus(true);
}

void UIContainer::AddElement(std::shared_ptr<UIElement> element)
{
    SCOPEDTRACE(nullptr, nullptr);
    m_elements.push_front(std::move(element));
}

void UIContainer::RemoveElement(std::shared_ptr<UIElement> element)
{
    SCOPEDTRACE(nullptr, nullptr);
    auto it = std::find(m_elements.begin(), m_elements.end(), element);
    if (it != m_elements.end())
    {
        m_elements.erase(it);
    }
}

std::shared_ptr<UIElement> UIContainer::GetElementAt(int x, int y)
{
//    SCOPEDTRACE(nullptr, nullptr);
    for (auto &element : m_elements)
    {
        auto &rect = GetElementRect(element);
        if (rect.Contains(static_cast<float>(x), static_cast<float>(y)))
        {
            return element;
        }
    }
    return nullptr;
}

const FRect &UIContainer::GetElementRect(std::shared_ptr<UIElement> element)
{
//    SCOPEDTRACE(nullptr, nullptr);
    return element->GetRect();
}
