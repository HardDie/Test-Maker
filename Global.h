#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "TestMaker.h"

#ifdef __linux__
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

void	save_keypress();
void	set_keypress_noecho();
void	load_keypress();

int		waitPressKey();
void	clearScreen();

static struct termios stored_settings;
#elif defined( _WIN32 )
#include <conio.h>
#endif

extern uns::ucTestMaker test;

#endif
