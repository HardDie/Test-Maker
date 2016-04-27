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
void	set_keypress();
void	reset_keypress();

uns::ucTestMaker test;
static struct termios stored_settings;

int main( int argc, char **argv ) {
	//=============================
	//		Variables
	//=============================
	int result;
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
		result = typeTest();
		while ( getc( stdin ) != '\n' );
	} else if ( argc == 3 ) {
		if ( test.openFile( argv[1] ) ) {
			print( "Incorrect file name or the file is not available!\n" );
			waitPressKey();
			return 1;
		}
		result = atoi( argv[2] );
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
		result = typeTest();
		while ( getc( stdin ) != '\n' );
	}
	test.readFile();

	//=============================
	//		Test
	//=============================
	set_keypress();
	while ( !isDone ) {
		/* Test type 1 or 2 */
		switch ( result ) {
		case 1:
			test.init();
			if ( test_question_answer() ) {
				reset_keypress();
				return 0;
			}
			break;
		case 2:
			test.init();
			if ( test_answer_question() ) {
				reset_keypress();
				return 0;
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
	print( "Enter: " );
	int res = -1;
	while ( !( cin >> res ) || res < 1 || res > 2 ) {
		cin.clear();
		while ( cin.get() != '\n' );
		print( "Wrong, try again: " );
	}
	return res;
}

int test_question_answer() {
	while ( !test.newWord() ) {
		clearScreen();
		print( test.getCounter() );
		print( "/" );
		print( test.getLength() );
		print( "\n" );

		print( test.getQuestion() );
		if ( waitPressKey() ) {
			return 1;
		}

		print( " - " );
		print( test.getAnswer() );
		print( "\n" );
		print( "Press any key..." );
		if ( waitPressKey() ) {
			return 1;
		}
	}
	return 0;
}

int test_answer_question() {
	while ( !test.newWord() ) {
		clearScreen();
		print( test.getCounter() );
		print( "/" );
		print( test.getLength() );
		print( "\n" );

		print( test.getAnswer() );
		if ( waitPressKey() ) {
			return 1;
		}

		print( " - " );
		print( test.getQuestion() );
		print( "\n" );
		print( "Press any key..." );
		if ( waitPressKey() ) {
			return 1;
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