#pragma once

#include <memory>
#include <deque>
#include "SDL3CPP/Events.h"
#include "SDL3CPP/Rect.h"
#include "View/UIElement.h"

namespace SDL3CPP
{
    class Renderer;
}

namespace GUI {

class UIContainer
    : public UIElement
{
private:
    std::deque<std::shared_ptr<UIElement>> m_elements;

public:
    UIContainer(UIContainer *parent, const SDL3CPP::FRect & rect);
    virtual ~UIContainer();
    UIContainer(const UIContainer &) = delete;
    UIContainer(UIContainer &&) = delete;

    UIContainer &operator =(const UIContainer &) = delete;
    UIContainer &operator =(UIContainer &&) = delete;

    void Render(SDL3CPP::Renderer &renderer) override;

    void SetFocus(bool focus) override;
    void SetBackgroundColor(const SDL3CPP::Color &color) override;

    void FocusElement(std::shared_ptr<UIElement> element);
    void AddElement(std::shared_ptr<UIElement> element);
    void RemoveElement(std::shared_ptr<UIElement> element);

    std::shared_ptr<UIElement> GetElementAt(int x, int y);
    const SDL3CPP::FRect &GetElementRect(std::shared_ptr<UIElement>);
};

} // namespace GUI
