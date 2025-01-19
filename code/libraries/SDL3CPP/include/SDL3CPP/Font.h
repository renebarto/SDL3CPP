#pragma once

#include <filesystem>
#include <string>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3CPP/Optional.h>

struct TTF_Font;
struct RWops;

namespace SDL3CPP {

class Color;
class Point;
class Rect;
class Surface;

class Font
{
private:
    TTF_Font *m_font;

public:
    Font();
    explicit Font(TTF_Font *font);

    Font(const std::filesystem::path &file, float pointSize);
    Font(RWops &rwops, float pointSize);
    Font(const Font &) = delete;
    Font(Font &&other) noexcept;

    virtual ~Font();

    Font &operator=(const Font &) = delete;
    Font &operator=(Font &&other) noexcept;

    bool IsEmpty() const;
    TTF_Font *Get() const;

    int GetStyle() const;
    Font &SetStyle(int style = TTF_STYLE_NORMAL);

    int GetOutline() const;
    Font &SetOutline(int outline = 0);

    int GetHinting() const;
    Font &SetHinting(int hinting = TTF_HINTING_NORMAL);

    bool GetKerning() const;
    Font &SetKerning(bool allowed = true);

    int GetHeight() const;
    int GetAscent() const;
    int GetDescent() const;
    int GetLineSkip() const;
    long GetNumFaces() const;
    bool IsFixedWidth() const;

    Optional<std::string> GetFamilyName() const;
    Optional<std::string> GetStyleName() const;

    int IsGlyphProvided(char16_t ch) const;
    void GetGlyphMetrics(char16_t ch, int &minx, int &maxx, int &miny, int &maxy, int &advance) const;
    Rect GetGlyphRect(char16_t ch) const;
    int GetGlyphAdvance(char16_t ch) const;

    Point GetSize(const char *text);
    Point GetSize(const std::string &text) const;
    Point GetSizeUTF8(const char *text);
    Point GetSizeUTF8(const std::string &text) const;
    Point GetSize(const char16_t *text) const;
    Point GetSize(const std::u16string &text) const;
    Point GetSize(const char32_t *text) const;
    Point GetSize(const std::u32string &text) const;

    Surface RenderSolid(const char *text, Color fg);
    Surface RenderSolid(const std::string &text, Color fg);
    Surface RenderSolidUTF8(const char *text, Color fg);
    Surface RenderSolidUTF8(const std::string &text, Color fg);
    Surface RenderSolid(const char16_t *text, Color fg);
    Surface RenderSolid(const std::u16string &text, Color fg);
    Surface RenderSolid(const char32_t *text, Color fg);
    Surface RenderSolid(const std::u32string &text, Color fg);

    Surface RenderGlyph_Solid(char16_t ch, Color fg);

    Surface RenderShaded(const char *text, Color fg);
    Surface RenderShaded(const std::string &text, Color fg, Color bg);
    Surface RenderShadedUTF8(const char *text, Color fg);
    Surface RenderShadedUTF8(const std::string &text, Color fg, Color bg);
    Surface RenderShaded(const char16_t *text, Color fg, Color bg);
    Surface RenderShaded(const std::u16string &text, Color fg, Color bg);
    Surface RenderShaded(const char32_t *text, Color fg, Color bg);
    Surface RenderShaded(const std::u32string &text, Color fg, Color bg);

    Surface RenderGlyphShaded(char16_t ch, Color fg, Color bg);

    Surface RenderBlended(const char *text, Color fg);
    Surface RenderBlended(const std::string &text, Color fg);
    Surface RenderBlendedUTF8(const char *text, Color fg);
    Surface RenderBlendedUTF8(const std::string &text, Color fg);
    Surface RenderBlended(const char16_t *text, Color fg);
    Surface RenderBlended(const std::u16string &text, Color fg);
    Surface RenderBlended(const char32_t *text, Color fg);
    Surface RenderBlended(const std::u32string &text, Color fg);

    Surface RenderGlyphBlended(char16_t ch, Color fg);
};

} // namespace SDL3CPP
