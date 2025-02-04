#include "SDL3CPP/Color.h"

using namespace SDL3CPP;

const Color Color::Black      = Color(0,   0,   0);
const Color Color::Red        = Color(255, 0,   0);
const Color Color::Green      = Color(0,   255, 0);
const Color Color::Yellow     = Color(255, 255, 0);
const Color Color::Blue       = Color(0,   0,   255);
const Color Color::Magenta    = Color(255, 0,   255);
const Color Color::Cyan       = Color(0,   255, 255);
const Color Color::White      = Color(255, 255, 255);

std::ostream &operator<<(std::ostream &stream, const Color &color)
{
    stream << "[r:" << static_cast<int>(color.r) << ",g:" << static_cast<int>(color.g)
           << ",b:" << static_cast<int>(color.b) << ",a:" << static_cast<int>(color.a) << "]";
    return stream;
}
