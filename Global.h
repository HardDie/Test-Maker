#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "TestMaker.h"

#ifdef __linux__
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

void	SaveKeypress();
void	SetNoCanonicalMode();
void	LoadKeypress();

static struct termios stored_settings;
#elif defined( _WIN32 )
#include <conio.h>
#endif

int		WaitPressKey();
void	ClearScreen();

extern uns::ucTestMaker test;

#endif
