#ifndef _TEST_CHAR_TRANSLATE_H_
#define _TEST_CHAR_TRANSLATE_H_

#include "TestMaker.h"

#ifdef _WIN32
#define ToLowerConsole ToLowerConsoleW
#define ToLowerFile ToLowerFileW
#elif defined( __linux__ )
#define ToLowerConsole ToLowerL
#define ToLowerFile ToLowerL
#endif

char*	ToLowerConsoleW( const char* str );
char*	ToLowerFileW( const char* str );
char	CharTranslateW_Console( const char symb );
char	CharTranslateW_File( const char symb );

char*	ToLowerL( const char* str );
char	CharTranslateL_En( const char symb );
char*	CharTranslateL_Ru( const char *symb );

#endif
