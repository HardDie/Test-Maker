#include "Global.h"

	/* Глобальный обьект класса test, от которого выполняются все команды */
uns::ucTestMaker test;

/*
====================
waitPressKey

	Позволяет остановить консоль и ожидать нажатия клавиши или получить код нажатой клавиши
====================
 */
int waitPressKey() {
#ifdef __linux__
	return getc( stdin );
#elif defined( _WIN32 )
	return _getch();
#endif
}


/*
====================
clearScreen

	Очищает экран
====================
*/
void clearScreen() {
#ifdef __linux__
	system( "clear" );
#elif defined( _WIN32 )
	system( "cls" );
#endif
}

#ifdef __linux__
/*
====================
save_keypress

	Сохраняет стандартные настройки терминала
====================
*/
void save_keypress() {
	tcgetattr( 0, &stored_settings );
}

/*
====================
set_keypress_noecho

	Переводит терминал в не канонический режим и отключает оторажение на экране нажатых клавиш
====================
*/
void set_keypress_noecho() {
	struct termios new_settings;
	new_settings = stored_settings;

	/* Disable canonical mode, and set buffer size to 1 byte */
	new_settings.c_lflag &= ~( ICANON | ECHO );
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr( 0, TCSANOW, &new_settings );
}

/*
====================
load_keypress

	Возвращает стандартные настройки терминала
====================
*/
void load_keypress() {
	tcsetattr( 0, TCSANOW, &stored_settings );
}
#endif
