#pragma once

#include "SDL3CPP/Color.h"
#include "SDL3CPP/Events.h"
#include "SDL3CPP/Font.h"
#include "View/UIContainer.h"
#include <memory>
#include <vector>

namespace GUI {

class UI : public UIContainer
{
private:
    SDL3CPP::Font m_buttonTextFont;
    SDL3CPP::Color m_buttonTextColor;

public:
    UI(const SDL3CPP::FRect &rect);
    ~UI();

    const SDL3CPP::Font &GetButtonTextFont() const;
    const SDL3CPP::Color &GetButtonTextColor() const;
};

} // namespace GUI
