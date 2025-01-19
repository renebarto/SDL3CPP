//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Console.h
//
// Namespace   : osal
//
// Class       : Console
//
// Description :
//  ANSI console class
//
//------------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <mutex>

#include "osal/utilities/FileHandling.h"

namespace osal
{

    class Secret;

} // namespace osal

// Ensures that there is at least one operator<< in the global namespace.
// See Message& operator<<(...) below for why.
void operator <<(const osal::Secret&, int);

namespace osal {

enum class ConsoleColor : int {
    Default = -1,
    Black = 0,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    ColorMask = 0x07,
    Intensity = 0x08,
    Bold = 0x10,
};

std::ostream& operator << (std::ostream& stream, ConsoleColor value);

struct SetConsoleForegroundColor
{
public:
    ConsoleColor color;
};

struct SetConsoleBackgroundColor
{
public:
    ConsoleColor color;
};

class Console
{
protected:
    // The type of basic IO manipulators (endl, ends, and flush) for narrow
    // streams.
    typedef std::ostream& (* BasicIoManip)(std::ostream &);

public:
    Console(int handle = GetFileDescriptor(stdout));
    explicit Console(FILE* file);
    explicit Console(std::ostream& stream);

    std::ostream* GetStream() { return m_stream; }

    void SetForegroundColor(ConsoleColor foregroundColor)
    {
        SetTerminalColor(foregroundColor, m_currentBackgroundColor);
    }
    void SetBackgroundColor(ConsoleColor backgroundColor)
    {
        SetTerminalColor(m_currentForegroundColor, backgroundColor);
    }
    void SetTerminalColor(ConsoleColor foregroundColor = ConsoleColor::Default,
                          ConsoleColor backgroundColor = ConsoleColor::Default);
    void ResetTerminalColor()
    {
        SetTerminalColor();
    }
    bool IsTTY() const;
    bool ShouldUseColor() const;
    bool ForceUseColor() const;
    void ForceUseColor(bool value);

    // Streams a non-pointer value to this object.
    template <typename T>
    Console& operator << (const T& val)
    {
        Lock lock(m_mutex);
        using ::operator <<;
        if (m_stream != nullptr)
            *m_stream << val;
        return *this;
    }

    Console& operator << (BasicIoManip val)
    {
        Lock lock(m_mutex);
        if (m_stream != nullptr)
            *m_stream << val;
        return *this;
    }

    Console& operator << (SetConsoleForegroundColor color)
    {
        Lock lock(m_mutex);
        SetForegroundColor(color.color);
        return *this;
    }
    Console& operator << (SetConsoleBackgroundColor color)
    {
        Lock lock(m_mutex);
        SetBackgroundColor(color.color);
        return *this;
    }

private:
    using Mutex = std::recursive_mutex;
    using Lock = std::lock_guard<Mutex>;

    FileDescriptor m_handle;
    std::ostream* m_stream;
    Mutex m_mutex;
    bool m_forceUseColor;
    ConsoleColor m_currentForegroundColor;
    ConsoleColor m_currentBackgroundColor;
};

inline ConsoleColor operator &(ConsoleColor lhs, ConsoleColor rhs)
{
    return static_cast<ConsoleColor>(static_cast<int>(lhs) & static_cast<int>(rhs));
}
inline ConsoleColor operator |(ConsoleColor lhs, ConsoleColor rhs)
{
    return static_cast<ConsoleColor>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

} // namespace osal

osal::SetConsoleForegroundColor fgcolor(osal::ConsoleColor color);
osal::SetConsoleBackgroundColor bgcolor(osal::ConsoleColor color);

