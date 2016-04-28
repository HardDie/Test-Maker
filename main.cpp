#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include "TestMaker.h"

using namespace std;

int		waitPressKey();
void	clearScreen();
void	print( const char *msg );
void	print( const int msg );
int		typeTest();
int		test_question_answer();
int		test_answer_question();
int		test_mixing();
void	set_keypress();
void	reset_keypress();

uns::ucTestMaker test;
static struct termios stored_settings;

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
			print( "Incorrect file name or the file is not available!\n" );
			waitPressKey();
			return 1;
		}
	} else if ( argc == 3 ) {
		if ( test.openFile( argv[1] ) ) {
			print( "Incorrect file name or the file is not available!\n" );
			waitPressKey();
			return 1;
		}
		state = atoi( argv[2] );
	} else {
		clearScreen();
		print( "Enter file name: " );
		char filename[100];
		cin >> filename;
		while ( getc( stdin ) != '\n' );
		if ( test.openFile( filename ) ) {
			print( "Incorrect file name or the file is not available!\n" );
			waitPressKey();
			return 1;
		}
	}
	test.readFile();

	//=============================
	//		Test
	//=============================
	set_keypress();
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
				case 1:
					isDone = true;
					continue;
					break;
				case 2:
					state = ST_MENU;
					continue;
			}
			break;
		case ST_AQ:
			test.init();
			switch ( test_answer_question() ) {
				case 1:
					isDone = true;
					continue;
					break;
				case 2:
					state = ST_MENU;
					continue;
			}
			break;
		case ST_MIX:
			test.init();
			switch ( test_mixing() ) {
			case 1:
				isDone = true;
				continue;
				break;
			case 2:
				state = ST_MENU;
				continue;
			}
			break;
		default:
			print( "Wrong argument test type\n" );
			isDone = true;
			continue;
		}
		/* Try again? */
		clearScreen();
		print( "Want try again?" );
		char tmp = getc( stdin );
		if ( tmp != ' ' && tmp != 'y' && tmp != 'Y' ) {
			isDone = true;
		}
	}

	reset_keypress();
	return 0;
}

int waitPressKey() {
	char tmp = getc( stdin );
	if ( tmp == 'q' || tmp == 'Q' ) {
		return 1;
	} else if ( tmp == 'm' || tmp == 'M' ) {
		return 2;
	}
	return 0;
}

void clearScreen() {
	system( "clear" );
}

void print( const char *msg ) {
	cout << msg;
}

void print( const int msg ) {
	cout << msg;
}

int	typeTest() {
	clearScreen();
	print( "Choose test type:\n" );
	print( "1. Question -> Answer\n" );
	print( "2. Answer -> Question\n" );
	print( "3. Mixing\n" );
	print( "Enter: " );
	while ( 1 ) {
		switch( getc( stdin ) ) {
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
	int temp;

	while ( !test.newWord() ) {
		clearScreen();
		print( test.getCounter() );
		print( "/" );
		print( test.getLength() );
		print( "\n" );

		print( test.getQuestion() );
		if ( temp = waitPressKey() ) {
			return temp;
		}

		print( " - " );
		print( test.getAnswer() );
		print( "\n" );
		print( "Press any key..." );
		if ( temp = waitPressKey() ) {
			return temp;
		}
	}
	return 0;
}

int test_answer_question() {
	int temp;

	while ( !test.newWord() ) {
		clearScreen();
		print( test.getCounter() );
		print( "/" );
		print( test.getLength() );
		print( "\n" );

		print( test.getAnswer() );
		if ( temp = waitPressKey() ) {
			return temp;
		}

		print( " - " );
		print( test.getQuestion() );
		print( "\n" );
		print( "Press any key..." );
		if ( temp = waitPressKey() ) {
			return temp;
		}
	}
	return 0;
}

int test_mixing() {
	int temp;

	while ( !test.mixNewWord() ) {
		clearScreen();
		print( test.getCounter() );
		print( "/" );
		print( test.getLength() * 2 );
		print( "\n" );

		switch ( test.getFlag() ) {
		case 1:
		case 4:
			print( test.getAnswer() );
			break;
		case 2:
		case 3:
			print( test.getQuestion() );
			break;
		}
		if ( temp = waitPressKey() ) {
			return temp;
		}

		print( " - " );
		switch ( test.getFlag() ) {
		case 1:
		case 4:
			print( test.getQuestion() );
			break;
		case 2:
		case 3:
			print( test.getAnswer() );
			break;
		}
		print( "\n" );
		print( "Press any key..." );
		if ( temp = waitPressKey() ) {
			return temp;
		}
	}
	return 0;
}

void set_keypress() {
	struct termios new_settings;

	tcgetattr(0,&stored_settings);

	new_settings = stored_settings;

	/* Disable canonical mode, and set buffer size to 1 byte */
	new_settings.c_lflag &= ~(ICANON|ECHO);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&new_settings);
}

void reset_keypress() {
	tcsetattr(0,TCSANOW,&stored_settings);
}