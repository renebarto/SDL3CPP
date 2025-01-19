//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : Console.cpp
//
// Namespace   : osal
//
// Class       : Console
//
// Description :
//
//------------------------------------------------------------------------------

#include "osal/utilities/Console.h"

#include <map>
#include <string>
#include "osal/utilities/Environment.h"

namespace osal {

static std::ostream* DetermineStream(FileDescriptor handle)
{
    switch (handle)
    {
    case STDOUT_FILENO:
        return &std::cout;
    case STDERR_FILENO:
        return &std::cerr;
    case STDIN_FILENO:
    default:
        std::cerr << "Invalid handle specified, please specify only stdout or stderr handle" << std::endl;
    }
    return nullptr;
}

static FileDescriptor DetermineHandle(std::ostream* stream)
{
    if (stream == &std::cout)
        return GetFileDescriptor(stdout);
    else if (stream == &std::cerr)
        return GetFileDescriptor(stderr);
    return InvalidHandle;
}

#if defined(PLATFORM_LINUX)
static std::map<ConsoleColor, const char*> s_colorLookup {
    { ConsoleColor::Black, "0" },
    { ConsoleColor::Red, "1" },
    { ConsoleColor::Green, "2" },
    { ConsoleColor::Yellow, "3" },
    { ConsoleColor::Blue, "4" },
    { ConsoleColor::Magenta, "5" },
    { ConsoleColor::Cyan, "6" },
    { ConsoleColor::White, "7" },
};

static const char* GetAnsiColorCode(ConsoleColor color)
{
    if (s_colorLookup.find(color & ConsoleColor::ColorMask) != s_colorLookup.end())
        return s_colorLookup[color & ConsoleColor::ColorMask];
    return "";
}
#else
#if _MSC_VER > 1900 // Versions after VS 2015
#pragma warning(disable: 5039)
#endif
#include <windows.h>
#if _MSC_VER > 1900 // Versions after VS 2015
#pragma warning(default: 5039)
#endif
#include <processenv.h>

static std::map<ConsoleColor, int> s_colorLookup {
    { ConsoleColor::Black, 0 },
    { ConsoleColor::Red, FOREGROUND_RED },
    { ConsoleColor::Green, FOREGROUND_GREEN },
    { ConsoleColor::Yellow, FOREGROUND_RED | FOREGROUND_GREEN },
    { ConsoleColor::Blue, FOREGROUND_BLUE },
    { ConsoleColor::Magenta, FOREGROUND_RED | FOREGROUND_BLUE },
    { ConsoleColor::Cyan, FOREGROUND_RED | FOREGROUND_GREEN },
    { ConsoleColor::White, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE },
};

static uint16_t GetColorCode(ConsoleColor color)
{
    if (s_colorLookup.find(color & ConsoleColor::ColorMask) != s_colorLookup.end())
        return static_cast<uint16_t>(s_colorLookup[color & ConsoleColor::ColorMask]);
    return 0;
}
#endif

Console::Console(int handle)
    : m_handle(handle)
    , m_stream(DetermineStream(m_handle))
    , m_forceUseColor()
    , m_currentForegroundColor(ConsoleColor::Default)
    , m_currentBackgroundColor(ConsoleColor::Default)
{
}

Console::Console(FILE* file)
    : m_handle(GetFileDescriptor(file))
    , m_stream(DetermineStream(m_handle))
    , m_forceUseColor()
    , m_currentForegroundColor(ConsoleColor::Default)
    , m_currentBackgroundColor(ConsoleColor::Default)
{
}

Console::Console(std::ostream& stream)
    : m_handle(DetermineHandle(&stream))
    , m_stream(&stream)
    , m_forceUseColor()
    , m_currentForegroundColor(ConsoleColor::Default)
    , m_currentBackgroundColor(ConsoleColor::Default)
{
}

void Console::SetTerminalColor(ConsoleColor foregroundColor, ConsoleColor backgroundColor)
{
    if (!ShouldUseColor())
        return;
    m_stream->flush();
#if defined(PLATFORM_WINDOWS)
    if (m_handle != -1)
    {
        uint16_t colorAttributes = GetColorCode(ConsoleColor::White);
        if (foregroundColor != ConsoleColor::Default)
        {
            colorAttributes = static_cast<uint16_t>((colorAttributes & ~static_cast<uint16_t>(ConsoleColor::ColorMask)) | GetColorCode(foregroundColor));
            if ((foregroundColor & ConsoleColor::Intensity) == ConsoleColor::Intensity)
                colorAttributes |= FOREGROUND_INTENSITY;
        }
        if (backgroundColor != ConsoleColor::Default)
        {
            colorAttributes = static_cast<uint16_t>((colorAttributes & ~(static_cast<uint16_t>(ConsoleColor::ColorMask)) << 4) | (GetColorCode(backgroundColor) << 4));
            if ((backgroundColor & ConsoleColor::Intensity) == ConsoleColor::Intensity)
                colorAttributes |= BACKGROUND_INTENSITY;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorAttributes);
    }
 
#else
    std::string command = "\033[0";
    if (foregroundColor != ConsoleColor::Default)
    {
        if ((foregroundColor & ConsoleColor::Intensity) == ConsoleColor::Intensity)
            command += ";9";
        else
            command += ";3";
        command += GetAnsiColorCode(foregroundColor);
        if ((foregroundColor & ConsoleColor::Bold) == ConsoleColor::Bold)
        {
            command += ";1";
        }
    }
    if (backgroundColor != ConsoleColor::Default)
    {
        if ((backgroundColor & ConsoleColor::Intensity) == ConsoleColor::Intensity)
            command += ";10";
        else
            command += ";4";
        command += GetAnsiColorCode(backgroundColor);
        if ((backgroundColor & ConsoleColor::Bold) == ConsoleColor::Bold)
        {
            command += ";1";
        }
    }
    command += "m";
    if (m_stream)
        *m_stream << command;
#endif
    m_currentForegroundColor = foregroundColor;
    m_currentBackgroundColor = backgroundColor;
}

bool Console::IsTTY() const
{
    return ::IsTTY(m_handle);
}

bool Console::ShouldUseColor() const
{
    if (ForceUseColor())
        return true;
    if (m_handle == InvalidHandle)
        return false;
    if (!IsTTY())
        return false;
#if defined(PLATFORM_WINDOWS)
    return true;
#else
    const char* termSetting = Environment::Get("TERM");
    if (!termSetting)
        return false;
    std::string term = termSetting;
    const bool terminalSupportsColor = (term == "xterm") || (term == "xterm-color")
        || (term == "xterm-256color") || (term == "screen") || (term == "screen-256color")
        || (term == "linux") || (term == "cygwin");
    return terminalSupportsColor;
#endif
}

bool Console::ForceUseColor() const
{
    return m_forceUseColor;
}

void Console::ForceUseColor(bool value)
{
    m_forceUseColor = value;
}

} // namespace osal

osal::SetConsoleForegroundColor fgcolor(osal::ConsoleColor color)
{
    return {color};
}

osal::SetConsoleBackgroundColor bgcolor(osal::ConsoleColor color)
{
    return {color};
}
