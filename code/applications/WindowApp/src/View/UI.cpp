#include "View/UI.h"

#include "tracing/ScopedTracing.h"
#include "SDL3CPP/Color.h"

using namespace GUI;
using namespace SDL3CPP;

UI::UI(const FRect &rect)
    : UIContainer{ nullptr, rect }
    , m_buttonTextFont{ std::filesystem::path(STOCK_FONT_DIR) / "Arial.ttf", 30 }
    , m_buttonTextColor{ Color::White }
{
    TRACE_DEBUG("UI::UI");
    m_ui = this;
}

UI::~UI()
{
    TRACE_DEBUG("UI::~UI");
}

const SDL3CPP::Font &UI::GetButtonTextFont() const
{
    return m_buttonTextFont;
}

const SDL3CPP::Color &UI::GetButtonTextColor() const
{
    return m_buttonTextColor;
}
