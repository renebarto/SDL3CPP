//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ConIO.h
//
// Namespace   : osal
//
// Class       : Console
//
// Description :
//  ANSI console class
//
//------------------------------------------------------------------------------

#if defined(PLATFORM_LINUX)

#include "osal/utilities/ConIO.h"

#include <termios.h>
#include <stdio.h>

namespace TerminalIO {

static struct termios old, current;

void InitTermios(bool echo)
{
    tcgetattr(fileno(stdin), &old); /* grab old terminal i/o settings */
    current = old; /* make new settings same as old settings */
    current.c_lflag &= ~ICANON; /* disable buffered i/o */
    current.c_cc[VTIME] = 0;
    current.c_cc[VMIN] = 0;
    if (echo)
    {
        current.c_lflag |= ECHO; /* set echo mode */
    }
    else
    {
        current.c_lflag &= ~ECHO; /* set no echo mode */
    }
    tcsetattr(fileno(stdin), TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void ResetTermios(void)
{
    tcsetattr(fileno(stdin), TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
int GetCh(bool echo = false)
{    
    InitTermios(echo);
    int ch = fgetc(stdin);
    ResetTermios();
    return ch;
}

} // namespace TerminalIO

int _getch(void)
{
    return TerminalIO::GetCh(true);
}

/* Read 1 character with echo */
int _getche(void)
{
    return TerminalIO::GetCh(true);
}

#endif
