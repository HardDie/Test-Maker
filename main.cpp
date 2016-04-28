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
	ST_MIX
};

int main( int argc, char **argv ) {
	//=============================
	//		Variables
	//=============================
	int state = ST_MENU;
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
		case ST_MENU:
			state = typeTest();
			continue;
			break;
		case ST_QA:
			test.init();
			switch ( test_question_answer() ) {
			case 'q':
				isDone = true;
				continue;
				break;
			case 'm':
				state = ST_MENU;
				continue;
			}
			break;
		case ST_AQ:
			test.init();
			switch ( test_answer_question() ) {
			case 'q':
				isDone = true;
				continue;
				break;
			case 'm':
				state = ST_MENU;
				continue;
			}
			break;
		case ST_MIX:
			test.init();
			switch ( test_mixing() ) {
			case 'q':
				isDone = true;
				continue;
				break;
			case 'm':
				state = ST_MENU;
				continue;
			}
			break;
		default:
			cout << "Wrong argument test type\n";
			isDone = true;
			continue;
		}
		/* Try again? */
		clearScreen();
		cout << "Want try again?";
		char tmp = waitPressKey();
		if ( tmp != ' ' && tmp != 'y' && tmp != 'Y' ) {
			isDone = true;
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