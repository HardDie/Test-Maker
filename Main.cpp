#include <iostream>
#include "Global.h"
#include "TestMaker.h"
#include "TestFunctions.h"
#include "TestCharTranslate.h"

using namespace std;

int		typeTest();

enum {
	ST_OPENFILE = -2,
	ST_MENU,
	ST_QA,
	ST_AQ,
	ST_MIX,
	ST_TYPEQUESTION,
	ST_TYPEANSWER,
	ST_TYPEMIX,
	ST_END,
	ST_TRY
};

int main( int argc, char **argv ) {
	//=============================
	//		Variables
	//=============================
	int state = ST_OPENFILE;
	int oldState;
	char isDone = false;
	char( *testMas[6] )( void );

	//=============================
	//		Initilization
	//=============================
#ifdef _WIN32
	setlocale( LC_ALL, "Russian" );
#elif defined( __linux__ )
	save_keypress();
#endif
	testMas[0] = test_question_answer;
	testMas[1] = test_answer_question;
	testMas[2] = test_mixing;
	testMas[3] = test_typing_question;
	testMas[4] = test_typing_answer;
	testMas[5] = test_typing_mix;

	if ( argc == 2 ) {
		if ( test.openFile( argv[1] ) ) {
			cout << "Incorrect file name or the file is not available!\n";
			waitPressKey();
			return 1;
		}
		test.readFile();
		state = ST_MENU;
	} else if ( argc == 3 ) {
		if ( test.openFile( argv[1] ) ) {
			cout << "Incorrect file name or the file is not available!\n";
			waitPressKey();
			return 1;
		}
		state = atoi( argv[2] );
		if ( state < 0 || state > 5 ) {
			state = ST_MENU;	// При выборе статуса будет ошибка
		}
		test.readFile();
	}

	//=============================
	//		Test
	//=============================
	while ( !isDone ) {
		/* State test */
		switch ( state ) {
			/* Open new file */
		case ST_OPENFILE:
#ifdef __linux__
			load_keypress();
#endif
			clearScreen();
			cout << "Enter file name: ";
			char filename[100];
			cin >> filename;
			cin.clear();
			while ( cin.get() != '\n' );
			if ( test.openFile( filename ) ) {
				cout << "Incorrect file name or the file is not available!\n";
				waitPressKey();
				break;
			}
			test.clearTest();
			test.readFile();
			state = ST_MENU;
			break;
			/* Main menu */
		case ST_MENU:
			state = typeTest();
			break;
			/* Question -> Answer */
		case ST_QA:
			/* Answer -> Question */
		case ST_AQ:
			/* Mix */
		case ST_MIX:
			/* Typing question */
		case ST_TYPEQUESTION:
			/* Typing answer */
		case ST_TYPEANSWER:
			/* Typing mix */
		case ST_TYPEMIX:
			test.init();
			switch ( testMas[state]() ) {	// В зависимости от state запускаются разные функции теста
			case 'q':
				state = ST_END;
				break;
			case 'm':
				state = ST_MENU;
				break;
			}
			if ( state != ST_END && state != ST_MENU ) {
				oldState = state;
				state = ST_TRY;
			}
			break;
			/* Try again? */
		case ST_TRY:
			clearScreen();
			cout << "Want try again?";
			switch ( waitPressKey() ) {
			case 'n':
			case 'N':
			case 'm':
			case 'M':
				state = ST_MENU;
				break;
			case ' ':
			case 'y':
			case 'Y':
			case 13:	// Enter
				state = oldState;
				break;
			case 'q':
			case 'Q':
				state = ST_END;
				break;
			}
			break;
			/* End game */
		case ST_END:
			isDone = true;
			clearScreen();
			break;
			/* Error */
		default:
			cout << "Wrong argument test type\n";
			state = ST_END;
			break;
		}
	}

#ifdef __linux__
	load_keypress();
#endif
	return 0;
}

/*
====================
typeTest

	Выводит на экран главное меню с выбором типа теста и возвращает результат выбраный пользователем
====================
*/
int	typeTest() {
#ifdef __linux__
	set_keypress_noecho();
#endif
	clearScreen();
	cout << "Choose test type:\n";
	cout << "1. Question -> Answer\n";
	cout << "2. Answer -> Question\n";
	cout << "3. Mixing\n";
	cout << "4. Typing question\n";
	cout << "5. Typing answer\n";
	cout << "6. Typing mixing\n";
	cout << "n. New file\n";
	cout << "Enter: ";
	while ( 1 ) {
		switch ( waitPressKey() ) {
		case '1':
			return ST_QA;
			break;
		case '2':
			return ST_AQ;
			break;
		case '3':
			return ST_MIX;
			break;
		case '4':
			return ST_TYPEQUESTION;
			break;
		case '5':
			return ST_TYPEANSWER;
			break;
		case '6':
			return ST_TYPEMIX;
			break;
		case 'n':
		case 'N':
			return ST_OPENFILE;
			break;
		case 'q':
		case 'Q':
			return ST_END;
			break;
		default:
			continue;
			break;
		}
	}
	return 0;
}
