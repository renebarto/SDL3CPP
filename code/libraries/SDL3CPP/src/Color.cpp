#include "SDL3CPP/Color.h"

std::ostream &operator<<(std::ostream &stream, const SDL3CPP::Color &color)
{
    stream << "[r:" << static_cast<int>(color.r) << ",g:" << static_cast<int>(color.g)
           << ",b:" << static_cast<int>(color.b) << ",a:" << static_cast<int>(color.a) << "]";
    return stream;
}
