#pragma once

#include "SDL3CPP/Color.h"
#include "View/UIElement.h"

namespace GUI {

class Button
    : public std::enable_shared_from_this<Button>
    , public UIElement
{
private:
    SDL3CPP::Color m_backgroundColor;
    bool m_haveFocus;
    bool m_focusReEnter;
    std::string m_text;

public:
    Button(UIContainer *parent, const SDL3CPP::FRect &rect, const std::string &text);
    virtual ~Button();
    Button(const Button &) = delete;
    Button(Button &&) = delete;
    Button &operator=(const Button &) = delete;
    Button &operator=(Button &&) = delete;

    void Render(SDL3CPP::Renderer &renderer) override;

    void SetFocus(bool focus) override;
    void SetBackgroundColor(const SDL3CPP::Color &color) override;
};

} // namespace GUI
