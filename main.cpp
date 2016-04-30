#define LINUX

#include <iostream>
#include "TestMaker.h"

using namespace std;

#ifdef LINUX
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

void	set_keypress();
void	reset_keypress();

static struct termios stored_settings;
#elif defined( WINDOWS )
#include <conio.h>
#endif

int		waitPressKey();
void	clearScreen();
int		typeTest();
int		test_question_answer();
int		test_answer_question();
int		test_mixing();

uns::ucTestMaker test;

enum {
	ST_MENU = 0,
	ST_QA,
	ST_AQ,
	ST_MIX,
	ST_END,
	ST_TRY
};

int main( int argc, char **argv ) {
	//=============================
	//		Variables
	//=============================
	int state = ST_MENU;
	int oldState;
	char isDone = false;

	//=============================
	//		Initilization
	//=============================
	setlocale( LC_ALL, "Russian" );


	if ( argc == 2 ) {
		if ( test.openFile( argv[1] ) ) {
			cout << "Incorrect file name or the file is not available!\n";
			waitPressKey();
			return 1;
		}
	} else if ( argc == 3 ) {
		if ( test.openFile( argv[1] ) ) {
			cout << "Incorrect file name or the file is not available!\n";
			waitPressKey();
			return 1;
		}
		state = atoi( argv[2] );
		if ( state < 1 || state > 3 ) {
			state = 11;	// При выборе статуса будет ошибка
		}
	} else {
		clearScreen();
		cout << "Enter file name: ";
		char filename[100];
		cin >> filename;
		//while ( waitPressKey() != '\n' );
		if ( test.openFile( filename ) ) {
			cout << "Incorrect file name or the file is not available!\n";
			waitPressKey();
			return 1;
		}
	}
	test.readFile();

	//=============================
	//		Test
	//=============================
#ifdef LINUX
	set_keypress();
#endif

	while ( !isDone ) {
		/* State test */
		switch ( state ) {
			/* Main menu */
		case ST_MENU:
			state = typeTest();
			break;
			/* Question -> Answer */
		case ST_QA:
			test.init();
			switch ( test_question_answer() ) {
			case 'q':
				state = ST_END;
				break;
			case 'm':
				state = ST_MENU;
				break;
			}
			if ( state == ST_QA ) {
				oldState = state;
				state = ST_TRY;
			}
			break;
			/* Answer -> Question */
		case ST_AQ:
			test.init();
			switch ( test_answer_question() ) {
			case 'q':
				state = ST_END;
				break;
			case 'm':
				state = ST_MENU;
				break;
			}
			if ( state == ST_AQ ) {
				oldState = state;
				state = ST_TRY;
			}
			break;
			/* Mix */
		case ST_MIX:
			test.init();
			switch ( test_mixing() ) {
			case 'q':
				state = ST_END;
				break;
			case 'm':
				state = ST_MENU;
				break;
			}
			if ( state == ST_MIX ) {
				oldState = state;
				state = ST_TRY;
			}
			break;
		/* Try again? */
		case ST_TRY:
			clearScreen();
			cout << "Want try again?";
			switch ( waitPressKey() ) {
			case 'm':
			case 'M':
				state = ST_MENU;
				break;
			case ' ':
			case 'y':
			case 'Y':
				state = oldState;
				break;
			case 'q':
			case 'Q':
			case 'n':
			case 'N':
				state = ST_END;
				break;
			}
			break;
		/* End game */
		case ST_END:
			isDone = true;
			cout << endl;
			break;
		/* Error */
		default:
			cout << "Wrong argument test type\n";
			state = ST_END;
			break;
		}		
	}

#ifdef LINUX
	reset_keypress();
#endif
	return 0;
}

int waitPressKey() {
#ifdef LINUX
	return getc( stdin );
#elif defined( WINDOWS )
	return _getch();
#endif
}

void clearScreen() {
#ifdef LINUX
	system( "clear" );
#elif defined( WINDOWS )
	system( "cls" );
#endif
}

int	typeTest() {
	clearScreen();
	cout << "Choose test type:\n";
	cout << "1. Question -> Answer\n";
	cout << "2. Answer -> Question\n";
	cout << "3. Mixing\n";
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

int test_question_answer() {
	while ( !test.newWord() ) {
		clearScreen();
		cout << test.getCounter() << "/" << test.getLength() << endl;

		cout << test.getQuestion();
		switch ( waitPressKey() ) {
		case 'q':
		case 'Q':
			return 'q';
		case 'm':
		case 'M':
			return 'm';
		}

		cout << " - " << test.getAnswer() << endl;
		cout << "Press any key...";
		switch ( waitPressKey() ) {
		case 'q':
		case 'Q':
			return 'q';
		case 'm':
		case 'M':
			return 'm';
		}
	}
	return 0;
}

int test_answer_question() {
	while ( !test.newWord() ) {
		clearScreen();
		cout << test.getCounter() << "/" << test.getLength() << endl;

		cout << test.getAnswer();
		switch ( waitPressKey() ) {
		case 'q':
		case 'Q':
			return 'q';
		case 'm':
		case 'M':
			return 'm';
		}

		cout << " - " << test.getQuestion() << endl;
		cout << "Press any key...";
		switch ( waitPressKey() ) {
		case 'q':
		case 'Q':
			return 'q';
		case 'm':
		case 'M':
			return 'm';
		}
	}
	return 0;
}

int test_mixing() {
	while ( !test.mixNewWord() ) {
		clearScreen();
		cout << test.getCounter() << "/" << test.getLength() * 2 << endl;

		switch ( test.getFlag() ) {
		case 1:
		case 4:
			cout << test.getAnswer();
			break;
		case 2:
		case 3:
			cout << test.getQuestion();
			break;
		}

		switch ( waitPressKey() ) {
		case 'q':
		case 'Q':
			return 'q';
		case 'm':
		case 'M':
			return 'm';
		}

		cout << " - ";
		switch ( test.getFlag() ) {
		case 1:
		case 4:
			cout << test.getQuestion();
			break;
		case 2:
		case 3:
			cout << test.getAnswer();
			break;
		}
		cout << endl << "Press any key...";

		switch ( waitPressKey() ) {
		case 'q':
		case 'Q':
			return 'q';
		case 'm':
		case 'M':
			return 'm';
		}
	}
	return 0;
}

#ifdef LINUX
void set_keypress() {
	struct termios new_settings;

	tcgetattr( 0, &stored_settings );

	new_settings = stored_settings;

	/* Disable canonical mode, and set buffer size to 1 byte */
	new_settings.c_lflag &= ~( ICANON | ECHO );
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr( 0, TCSANOW, &new_settings );
}

void reset_keypress() {
	tcsetattr( 0, TCSANOW, &stored_settings );
}
#endif