#include "Global.h"

uns::ucTestMaker test;

int waitPressKey() {
#ifdef __linux__
	return getc( stdin );
#elif defined( _WIN32 )
	return _getch();
#endif
}

void clearScreen() {
#ifdef __linux__
	system( "clear" );
#elif defined( _WIN32 )
	system( "cls" );
#endif
}

#ifdef __linux__
void save_keypress() {
	tcgetattr( 0, &stored_settings );
}

void set_keypress_noecho() {
	struct termios new_settings;
	new_settings = stored_settings;

	/* Disable canonical mode, and set buffer size to 1 byte */
	new_settings.c_lflag &= ~( ICANON | ECHO );
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr( 0, TCSANOW, &new_settings );
}

void load_keypress() {
	tcsetattr( 0, TCSANOW, &stored_settings );
}
#endif
