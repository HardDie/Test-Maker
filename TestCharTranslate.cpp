#include "TestCharTranslate.h"

/*
====================
ToLowerConsoleW

	Принимает строку полученую из консоли от пользователя, посимвольно переводит ее в нижний регистр, возвращает результирующую строку
====================
*/
char* ToLowerConsoleW( const char* str ) {
	static char res[SIZE];
	for ( int i = 0; i < SIZE; i++ ) {
		if ( str[i] == 0 ) {
			res[i] = 0;
			break;
		}
		res[i] = CharTranslateW_Console( str[i] );
	}
	return res;
}

/*
====================
ToLowerFileW

	Принимает строку считаную из файла теста, посимвольно переводит ее в нижний регистр, возвращает результирующую строку
====================
*/
char* ToLowerFileW( const char* str ) {
	static char res[SIZE];
	for ( int i = 0; i < SIZE; i++ ) {
		if ( str[i] == 0 ) {
			res[i] = 0;
			break;
		}
		res[i] = CharTranslateW_File( str[i] );
	}
	return res;
}

/*
====================
CharTranslateW_Console

	Переводит символ, считаный из консоли пользователя, в нижний регистр
====================
*/
char CharTranslateW_Console( const char symb ) {
	// Если на вход поступила английская буква нижнего региста, то просто возвращаем ее
	if ( symb >= 97 && symb <= 122 ) {
		return symb;
	}

	// Перевод английского символа, верхнего регистра в нижний
	if ( symb >= 65 && symb <= 90 ) {
		return symb + 32;
	}

	// Перевод введенной русской буквы нижнего регистра
	if ( symb >= -96 && symb <= -91 || symb >= -90 && symb <= -81 ) {	// а-е ж-п
		return symb + 64;
	} else if ( symb == -15 ) {		// ё
		return -72;
	} else if ( symb >= -32 && symb <= -17 ) {	// р-я
		return symb + 16;
	}

	// Перевод введенной русской буквы верхнего регистра
	if ( symb >= -128 && symb <= -123 || symb >= -122 && symb <= -97 ) {	// А-Е Ж-Я
		return symb + 96;
	} else if ( symb == -16 ) {	// Ё
		return -72;
	}

	return symb;
}

/*
====================
CharTranslateW_File

	Переводит символ, считаный из файла теста, в нижний регистр
====================
*/
char CharTranslateW_File( const char symb ) {

	// Если на вход поступила русская буква нижнего регистра, то просто возвращаем ее
	if ( symb >= -32 && symb <= -1 || symb == -72 ) {
		return symb;
	}

	// Если на вход поступила английская буква нижнего региста, то просто возвращаем ее
	if ( symb >= 97 && symb <= 122 ) {
		return symb;
	}

	// Перевод английского символа, верхнего регистра в нижний
	if ( symb >= 65 && symb <= 90 ) {
		return symb + 32;
	}

	// Перевод русской буквы верхнего регистра в нижний
	if ( symb >= -64 && symb <= -33 ) {
		return symb + 32;
	} else if ( symb == -88 ) {	// Буква Ё
		return -72;
	}

	return symb;
}

/*
====================
ToLowerL

	Принимает строку, посимвольно переводит ее в нижний регистр, возвращает результирующую строку
====================
*/
char* ToLowerL( const char* str ) {
	static char res[SIZE];
	for ( int i = 0; i < SIZE; i++ ) {
		if ( str[i] == 0 ) {
			res[i] = 0;
			break;
		}
		if ( str[i] == -47 || str[i] == -48 ) {
			char* endChar = CharTranslateL_Ru( &str[i] );
			if ( endChar != NULL ) {
				res[i] = endChar[0];
				res[i + 1] = endChar[1];
				free( endChar );
			} else {
				res[i] = str[i];
				res[i + 1] = str[i + 1];
			}
			i++;
		} else {
			res[i] = CharTranslateL_En( str[i] );
		}
	}
	return res;
}

/*
====================
CharTranslateL_En

	Переводит английский символ в нижний регистр
====================
*/
char CharTranslateL_En( const char symb ) {
	// Если на вход поступила буква нижнего региста, то просто возвращаем ее
	if ( symb >= 97 && symb <= 122 ) {
		return symb;
	}

	// Перевод символа, верхнего регистра в нижний
	if ( symb >= 65 && symb <= 90 ) {
		return symb + 32;
	}

	return symb;
}

/*
====================
CharTranslateL_Ru

	Переводит русский символ в нижний регистр
====================
*/
char* CharTranslateL_Ru( const char *symb ) {
	// Если на вход поступила буква нижнего региста, то возвращаем NULL
	if ( symb[0] == -48 && symb[1] >= -80 && symb[1] <= -65 ) {	// а-е ж-п
		return NULL;
	} else if ( symb[0] == -47 && symb[1] == -111 ) {	//ё
		return NULL;
	} else if ( symb[0] == -47 && symb[1] >= -128 && symb[1] <= -113 ) {	//р-я
		return NULL;
	}

	// Перевод символа, верхнего регистра в нижний
	if ( symb[0] == -48 && symb[1] >= -112 && symb[1] <= -97 ) {	// А-Е Ж-П
		char *retSymb = ( char* )malloc( 2 );
		retSymb[0] = -48;
		retSymb[1] = symb[1] + 32;
		return retSymb;
	} else if ( symb[0] == -48 && symb[1] == -127 ) {	//Ё
		char *retSymb = ( char* )malloc( 2 );
		retSymb[0] = -47;
		retSymb[1] = -111;
		return retSymb;
	} else if ( symb[0] == -48 && symb[1] >= -96 && symb[1] <= -81 ) {	//Р-Я
		char *retSymb = ( char* )malloc( 2 );
		retSymb[0] = -47;
		retSymb[1] = symb[1] - 32;
		return retSymb;
	}

	return NULL;
}
