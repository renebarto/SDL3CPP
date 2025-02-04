#pragma once

#include "SDL3CPP/Color.h"
#include "SDL3CPP/Events.h"
#include "SDL3CPP/FRect.h"
#include "View/UIElement.h"

namespace GUI {

class UIPanel
    : public std::enable_shared_from_this<UIPanel>
    , public UIElement
{
private:
    SDL3CPP::Color m_backgroundColor;
    bool m_haveFocus;
    bool m_focusReEnter;

public:
    UIPanel(UIContainer *parent, const SDL3CPP::FRect &rect, const SDL3CPP::Color &backgroundColor);
    ~UIPanel();

    void Render(SDL3CPP::Renderer &renderer);

    void SetFocus(bool focus) override;
    void SetBackgroundColor(const SDL3CPP::Color &color) override;
};

} // namespace GUI
