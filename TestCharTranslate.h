#ifndef _TEST_CHAR_TRANSLATE_H_
#define _TEST_CHAR_TRANSLATE_H_

#include "TestMaker.h"

char*	ToLowerConsole( const char* str );
char*	ToLowerFile( const char* str );
char	CharTranslateW_Console( const char symb );
char	CharTranslateW_File( const char symb );
char	CharTranslateL_Console( const char symb );
char	CharTranslateL_File( const char symb );

#endif
