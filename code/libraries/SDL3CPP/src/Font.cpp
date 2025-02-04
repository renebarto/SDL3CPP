#include "SDL3CPP/Font.h"

#include "SDL3CPP/Color.h"
#include "SDL3CPP/Point.h"
#include "SDL3CPP/Rect.h"
#include "SDL3CPP/Surface.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <sstream>

using namespace SDL3CPP;

Font::Font()
    : m_font{}
{
}

Font::Font(TTF_Font *font)
    : m_font{font}
{
}

Font::Font(const std::filesystem::path &file, float pointSize)
    : m_font{}
{
    m_font = TTF_OpenFont(file.string().c_str(), pointSize);
    if (m_font == nullptr)
    {
        std::ostringstream stream;
        stream << "TTF_OpenFontIndex failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
}

// Font::Font(RWops &rwops, float pointSize)
//     : m_font{}
//{
// }

Font::Font(Font &&other) noexcept
    : m_font(other.m_font)
{
    other.m_font = nullptr;
}

Font::~Font()
{
    if (m_font != nullptr)
        TTF_CloseFont(m_font);
}

Font &Font::operator=(Font &&other) noexcept
{
    if (&other == this)
        return *this;
    if (m_font != nullptr)
        TTF_CloseFont(m_font);
    m_font = other.m_font;
    other.m_font = nullptr;
    return *this;
}

bool Font::IsEmpty() const
{
    return m_font == nullptr;
}

TTF_Font *Font::Get() const
{
    return m_font;
}

int Font::GetStyle() const
{
    return {};
}

Font &Font::SetStyle(int /*style*/ /*= TTF_STYLE_NORMAL*/)
{
    return *this;
}

int Font::GetOutline() const
{
    return {};
}

Font &Font::SetOutline(int /*outline*/ /*= 0*/)
{
    return *this;
}

int Font::GetHinting() const
{
    return {};
}

Font &Font::SetHinting(int /*hinting*/ /*= TTF_HINTING_NORMAL*/)
{
    return *this;
}

bool Font::GetKerning() const
{
    return {};
}

Font &Font::SetKerning(bool /*allowed*/ /*= true*/)
{
    return *this;
}

int Font::GetHeight() const
{
    return {};
}

int Font::GetAscent() const
{
    return {};
}

int Font::GetDescent() const
{
    return {};
}

int Font::GetLineSkip() const
{
    return {};
}

long Font::GetNumFaces() const
{
    return {};
}

bool Font::IsFixedWidth() const
{
    return {};
}

Optional<std::string> Font::GetFamilyName() const
{
    return {};
}

Optional<std::string> Font::GetStyleName() const
{
    return {};
}

int Font::IsGlyphProvided(char16_t /*ch*/) const
{
    return {};
}

void Font::GetGlyphMetrics(char16_t /*ch*/, int &/*minx*/, int &/*maxx*/, int &/*miny*/, int &/*maxy*/, int &/*advance*/) const
{
}

Rect Font::GetGlyphRect(char16_t /*ch*/) const
{
    return {};
}

int Font::GetGlyphAdvance(char16_t /*ch*/) const
{
    return {};
}

Point Font::GetSize(const char */*text*/)
{
    return {};
}

Point Font::GetSize(const std::string &/*text*/) const
{
    return {};
}

Point Font::GetSizeUTF8(const char */*text*/)
{
    return {};
}

Point Font::GetSizeUTF8(const std::string &/*text*/) const
{
    return {};
}

Point Font::GetSize(const char16_t */*text*/) const
{
    return {};
}

Point Font::GetSize(const std::u16string &/*text*/) const
{
    return {};
}

Point Font::GetSize(const char32_t */*text*/) const
{
    return {};
}

Point Font::GetSize(const std::u32string &/*text*/) const
{
    return {};
}

Surface Font::RenderSolid(const char *text, Color fg) const
{
    SDL_Surface *surface = TTF_RenderText_Solid(m_font, text, strlen(text), fg);
    if (surface == nullptr)
    {
        std::ostringstream stream;
        stream << "TTF_RenderText_Solid failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return Surface(surface);
}

Surface Font::RenderSolid(const std::string &text, Color fg) const
{
    SDL_Surface *surface = TTF_RenderText_Solid(m_font, text.c_str(), text.length(), fg);
    if (surface == nullptr)
    {
        std::ostringstream stream;
        stream << "TTF_RenderText_Solid failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return Surface(surface);
}

Surface Font::RenderSolidUTF8(const char */*text*/, Color /*fg*/) const
{
    return {};
}

Surface Font::RenderSolidUTF8(const std::string &/*text*/, Color /*fg*/) const
{
    return {};
}

Surface Font::RenderSolid(const char16_t */*text*/, Color /*fg*/) const
{
    return {};
}

Surface Font::RenderSolid(const std::u16string &/*text*/, Color /*fg*/) const
{
    return {};
}

Surface Font::RenderSolid(const char32_t */*text*/, Color /*fg*/) const
{
    return {};
}

Surface Font::RenderSolid(const std::u32string &/*text*/, Color /*fg*/) const
{
    return {};
}

Surface Font::RenderGlyph_Solid(char16_t /*ch*/, Color /*fg*/)
{
    return {};
}

Surface Font::RenderShaded(const char */*text*/, Color /*fg*/)
{
    return {};
}

Surface Font::RenderShaded(const std::string &/*text*/, Color /*fg*/, Color /*bg*/)
{
    return {};
}

Surface Font::RenderShadedUTF8(const char */*text*/, Color /*fg*/)
{
    return {};
}

Surface Font::RenderShadedUTF8(const std::string &/*text*/, Color /*fg*/, Color /*bg*/)
{
    return {};
}

Surface Font::RenderShaded(const char16_t */*text*/, Color /*fg*/, Color /*bg*/)
{
    return {};
}

Surface Font::RenderShaded(const std::u16string &/*text*/, Color /*fg*/, Color /*bg*/)
{
    return {};
}

Surface Font::RenderShaded(const char32_t */*text*/, Color /*fg*/, Color /*bg*/)
{
    return {};
}

Surface Font::RenderShaded(const std::u32string &/*text*/, Color /*fg*/, Color /*bg*/)
{
    return {};
}

Surface Font::RenderGlyphShaded(char16_t /*ch*/, Color /*fg*/, Color /*bg*/)
{
    return {};
}

Surface Font::RenderBlended(const char *text, Color fg)
{
    SDL_Surface *surface = TTF_RenderText_Blended(m_font, text, strlen(text), fg);
    if (surface == nullptr)
    {
        std::ostringstream stream;
        stream << "TTF_RenderText_Blended failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return Surface(surface);
}

Surface Font::RenderBlended(const std::string &text, Color fg)
{
    SDL_Surface *surface = TTF_RenderText_Blended(m_font, text.c_str(), text.length(), fg);
    if (surface == nullptr)
    {
        std::ostringstream stream;
        stream << "TTF_RenderText_Blended failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return Surface(surface);
}

Surface Font::RenderBlendedUTF8(const char *text, Color fg)
{
    SDL_Surface *surface = TTF_RenderText_Blended(m_font, text, strlen(text), fg);
    if (surface == nullptr)
    {
        std::ostringstream stream;
        stream << "TTF_RenderText_Blended failed: " << SDL_GetError();
        throw std::runtime_error(stream.str());
    }
    return Surface(surface);
}

Surface Font::RenderBlendedUTF8(const std::string &/*text*/, Color /*fg*/)
{
    return {};
}

Surface Font::RenderBlended(const char16_t */*text*/, Color /*fg*/)
{
    return {};
}

Surface Font::RenderBlended(const std::u16string &/*text*/, Color /*fg*/)
{
    return {};
}

Surface Font::RenderBlended(const char32_t */*text*/, Color /*fg*/)
{
    return {};
}

Surface Font::RenderBlended(const std::u32string &/*text*/, Color /*fg*/)
{
    return {};
}

Surface Font::RenderGlyphBlended(char16_t /*ch*/, Color /*fg*/)
{
    return {};
}
