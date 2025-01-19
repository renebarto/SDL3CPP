#pragma once

#include <optional>
#include <ostream>

namespace SDL3CPP {

template <typename T>
using Optional = std::optional<T>;

constexpr std::nullopt_t NullOpt = std::nullopt;

} // namespace SDL3CPP

template <typename T>
std::ostream &operator<<(std::ostream &stream, const SDL3CPP::Optional<T> &optional)
{
    if (optional.has_value())
    {
        return stream << optional.value();
    }
    else
    {
        return stream << "null";
    }
}

