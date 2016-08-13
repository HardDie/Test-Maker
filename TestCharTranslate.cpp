#include "TestCharTranslate.h"

char* ToLowerConsole( const char* str ) {
	static char res[SIZE];
	for ( int i = 0; i < SIZE; i++ ) {
		if ( str[i] == 0 ) {
			res[i] = 0;
			break;
		}
#ifdef _WIN32
		res[i] = CharTranslateW_Console( str[i] );
#elif defined( __linux__ )
		res[i] = CharTranslateL_Console( str[i] );
#endif
	}
	return res;
}

char* ToLowerFile( const char* str ) {
	static char res[SIZE];
	for ( int i = 0; i < SIZE; i++ ) {
		if ( str[i] == 0 ) {
			res[i] = 0;
			break;
		}
#ifdef _WIN32
		res[i] = CharTranslateW_File( str[i] );
#elif defined( __linux__ )
		res[i] = CharTranslateL_File( str[i] );
#endif
	}
	return res;
}

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

char CharTranslateL_Console( const char symb ) {
	return symb;
}

char CharTranslateL_File( const char symb ) {
	return symb;
}
