//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ConIO.h
//
// Namespace   : osal
//
// Class       : -
//
// Description :
//  Linux terminal I/O for getch
//
//------------------------------------------------------------------------------

#pragma once

#if defined(PLATFORM_LINUX)

int _getch(void);

/* Read 1 character with echo */
int _getche(void);

#endif
