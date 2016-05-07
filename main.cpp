#define LINUX

#include <iostream>
#include "TestMaker.h"

using namespace std;

#ifdef LINUX
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

void	save_keypress();
void	set_keypress_echo();
void	set_keypress_noecho();
void	load_keypress();

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
int		test_typing_question();
int		test_typing_answer();
int		test_typing_mix();
char	charTranslate( const char symb );
char*	lowerCase( const char *str );

uns::ucTestMaker test;

enum {
	ST_OPENFILE = -1,
	ST_MENU = 0,
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
		test.readFile();
		state = ST_MENU;
	} else if ( argc == 3 ) {
		if ( test.openFile( argv[1] ) ) {
			cout << "Incorrect file name or the file is not available!\n";
			waitPressKey();
			return 1;
		}
		state = atoi( argv[2] );
		if ( state < 1 || state > 6 ) {
			state = 11;	// При выборе статуса будет ошибка
		}
		test.readFile();
	}

	//=============================
	//		Test
	//=============================
#ifdef LINUX
	save_keypress();
#endif

	while ( !isDone ) {
#ifdef LINUX
		set_keypress_noecho();
#endif
		/* State test */
		switch ( state ) {
			/* Open new file */
		case ST_OPENFILE:
#ifdef LINUX
		set_keypress_echo();
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
			/* Typing question */
		case ST_TYPEQUESTION:
#ifdef LINUX
			set_keypress_echo();
#endif
			test.init();
			switch ( test_typing_question() ) {
			case 'q':
				state = ST_END;
				break;
			case 'm':
				state = ST_MENU;
				break;
			}
			if ( state == ST_TYPEQUESTION ) {
				oldState = state;
				state = ST_TRY;
			}
			break;
			/* Typing answer */
		case ST_TYPEANSWER:
#ifdef LINUX
			set_keypress_echo();
#endif
			test.init();
			switch ( test_typing_answer() ) {
			case 'q':
				state = ST_END;
				break;
			case 'm':
				state = ST_MENU;
				break;
			}
			if ( state == ST_TYPEANSWER ) {
				oldState = state;
				state = ST_TRY;
			}
			break;
			/* Typing mix */
		case ST_TYPEMIX:
#ifdef LINUX
			set_keypress_echo();
#endif
			test.init();
			switch ( test_typing_mix() ) {
			case 'q':
				state = ST_END;
				break;
			case 'm':
				state = ST_MENU;
				break;
			}
			if ( state == ST_TYPEMIX ) {
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
	load_keypress();
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

int	test_typing_question() {
	bool repeat = false;
	while ( repeat || !test.newWord() ) {
		clearScreen();
		cout << test.getCounter() << "/" << test.getLength() << endl;

		cout << test.getAnswer() << "\nEnter: ";
		static char answer[SIZE];
		cin.getline( answer, SIZE );

#ifdef WINDOWS
		for ( int i = 0; i < SIZE; i++ ) {
			if ( answer[i] == 0 ) {
				break;
			}
			answer[i] = charTranslate( answer[i] );
		}

		if ( strcmp( answer, lowerCase( test.getQuestion() ) ) == 0 ) {
#elif defined ( LINUX )
		if ( strcmp( answer, test.getQuestion() ) == 0 ) {
#endif
			cout << "Right!\n";
			repeat = false;
		} else if ( strcmp( answer, " " ) == 0 ) {
			cout << test.getQuestion() << endl;
			cout << "Next\n";
			repeat = false;
		} else {
			cout << "Wrong: " << test.getQuestion() << endl;
			repeat = true;
		}
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

int	test_typing_answer() {
	bool repeat = false;
	while ( repeat || !test.newWord() ) {
		clearScreen();
		cout << test.getCounter() << "/" << test.getLength() << endl;

		cout << test.getQuestion() << "\nEnter: ";
		static char answer[SIZE];
		cin.getline( answer, SIZE );

#ifdef WINDOWS
		for ( int i = 0; i < SIZE; i++ ) {
			if ( answer[i] == 0 ) {
				break;
			}
			answer[i] = charTranslate( answer[i] );
		}

		if ( strcmp( answer, lowerCase( test.getAnswer() ) ) == 0 ) {
#elif defined ( LINUX )
		if ( strcmp( answer, test.getAnswer() ) == 0 ) {
#endif
			cout << "Right!\n";
			repeat = false;
		} else if ( strcmp( answer, " " ) == 0 ) {
			cout << test.getAnswer() << endl;
			cout << "Next\n";
			repeat = false;
		} else {
			cout << "Wrong: " << test.getAnswer() << endl;
			repeat = true;
		}
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

int	test_typing_mix() {
	bool repeat = false;
	while ( repeat || !test.mixNewWord() ) {
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

		cout << "\nEnter: ";
		static char answer[SIZE];
		cin.getline( answer, SIZE );

#ifdef WINDOWS
		for ( int i = 0; i < SIZE; i++ ) {
			if ( answer[i] == 0 ) {
				break;
			}
			answer[i] = charTranslate( answer[i] );
		}
#endif

		switch ( test.getFlag() ) {
		case 1:
		case 4:
#ifdef WINDOWS
			if ( strcmp( answer, lowerCase( test.getQuestion() ) ) == 0 ) {
#elif defined ( LINUX )
			if ( strcmp( answer, test.getQuestion() ) == 0 ) {
#endif
				cout << "Right!\n";
				repeat = false;
			} else if ( strcmp( answer, " " ) == 0 ) {
				cout << test.getQuestion() << endl;
				cout << "Next\n";
				repeat = false;
			} else {
				cout << "Wrong: " << test.getQuestion() << endl;
				repeat = true;
			}
			break;
		case 2:
		case 3:
#ifdef WINDOWS
			if ( strcmp( answer, lowerCase( test.getAnswer() ) ) == 0 ) {
#elif defined ( LINUX )
			if ( strcmp( answer, test.getAnswer() ) == 0 ) {
#endif
				cout << "Right!\n";
				repeat = false;
			} else if ( strcmp( answer, " " ) == 0 ) {
				cout << test.getAnswer() << endl;
				cout << "Next\n";
				repeat = false;
			} else {
				cout << "Wrong: " << test.getAnswer() << endl;
				repeat = true;
			}
			break;
			}

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

char charTranslate( const char symb ) {
	char symb_ = symb;
	// lowcase
	if ( symb_ <= -91 && symb_ >= -96 || symb_ <= -81 && symb_ >= -90 ) {
		return symb_ + 64;
	} else if ( symb_ == -15 ) {
		return -72;
	} else if ( symb_ <= -17 && symb_ >= -32 ) {
		return symb_ + 16;
	}

	// highcase
	if ( symb_ <= -123 && symb_ >= -128 || symb_ <= -97 && symb_ >= -122 ) {
		return symb_ + 96;
	} else if ( symb_ == -16 ) {
		return -72;
	} else if ( symb_ <= -17 && symb_ >= -32 ) {
		return symb_ + 16;
	}
	return tolower( symb_ );
}

char* lowerCase( const char *str ) {
	static char res[SIZE];
	for ( int i = 0; i < SIZE; i++ ) {
		if ( str[i] == 0 ) {
			res[i] = 0;
			break;
		}
		res[i] = tolower( str[i] );
	}
	return res;
}

#ifdef LINUX
void save_keypress() {
	tcgetattr( 0, &stored_settings );
}

void set_keypress_echo() {
	struct termios new_settings;
	new_settings = stored_settings;

	/* Disable canonical mode, and set buffer size to 1 byte */
	new_settings.c_lflag &= ~( ICANON );
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr( 0, TCSANOW, &new_settings );
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