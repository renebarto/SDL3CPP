#pragma once

#include <memory>
#include <vector>
#include "SDL3CPP/Events.h"
#include "View/UIElement.h"

namespace GUI {

class UI
{
private:
    std::vector<std::unique_ptr<UIElement>> m_Elements;

public:
    UI();
    ~UI();
    void HandleEvent(const SDL3CPP::Event & event);
    void Render();
};

} // namespace GUI
