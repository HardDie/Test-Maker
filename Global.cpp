#include "Global.h"

	/* Глобальный обьект класса test, от которого выполняются все команды */
uns::ucTestMaker test;

/*
====================
WaitPressKey

	Позволяет остановить консоль и ожидать нажатия клавиши или получить код нажатой клавиши
====================
 */
int WaitPressKey() {
#ifdef __linux__
	return getc( stdin );
#elif defined( _WIN32 )
	return _getch();
#endif
}


/*
====================
ClearScreen

	Очищает экран
====================
*/
void ClearScreen() {
#ifdef __linux__
	system( "clear" );
#elif defined( _WIN32 )
	system( "cls" );
#endif
}

#ifdef __linux__
/*
====================
SaveKeypress

	Сохраняет стандартные настройки терминала
====================
*/
void SaveKeypress() {
	tcgetattr( 0, &stored_settings );
}

/*
====================
SetNoCanonicalMode

	Переводит терминал в не канонический режим и отключает оторажение на экране нажатых клавиш
====================
*/
void SetNoCanonicalMode() {
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
LoadKeypress

	Возвращает стандартные настройки терминала
====================
*/
void LoadKeypress() {
	tcsetattr( 0, TCSANOW, &stored_settings );
}
#endif
