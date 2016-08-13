#include "TestFunctions.h"

/*
====================
test_question_answer

	Проводится по типу отображения, сначала отображается вопрос, а по нажатию клавиши ответ
====================
*/
char test_question_answer() {
#ifdef __linux__
	set_keypress_noecho();
#endif
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

/*
====================
test_answer_question

	Проводится по типу отображения, сначала отображается ответ, а по нажатию клавиши вопрос
====================
*/
char test_answer_question() {
#ifdef __linux__
	set_keypress_noecho();
#endif
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

/*
====================
test_mixing

	Проводится по типу отображения, в случайном порядке определяет вывод вопроса - ответа, или ответа - вопроса
====================
*/
char test_mixing() {
#ifdef __linux__
	set_keypress_noecho();
#endif
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

/*
====================
test_typing_question

	Проводится по типу набора вопроса при выведеном ответе
====================
*/
char test_typing_question() {
	bool repeat = false;
	while ( repeat || !test.newWord() ) {
#ifdef __linux__
		load_keypress();
#endif
		clearScreen();
		cout << test.getCounter() << "/" << test.getLength() << endl;

		cout << test.getAnswer() << "\nEnter: ";
		static char answer[SIZE];
		cin.getline( answer, SIZE );

		if ( strcmp( ToLowerConsole( answer ), ToLowerFile( test.getQuestion() ) ) == 0 ) {
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
#ifdef __linux__
		set_keypress_noecho();
#endif
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

/*
====================
test_typing_answer

	Проводится по типу набора ответа при выведеном вопросе
====================
*/
char test_typing_answer() {
	bool repeat = false;
	while ( repeat || !test.newWord() ) {
#ifdef __linux__
		load_keypress();
#endif
		clearScreen();
		cout << test.getCounter() << "/" << test.getLength() << endl;

		cout << test.getQuestion() << "\nEnter: ";
		static char answer[SIZE];
		cin.getline( answer, SIZE );

		if ( strcmp( ToLowerConsole( answer ), ToLowerFile( test.getAnswer() ) ) == 0 ) {
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
#ifdef __linux__
		set_keypress_noecho();
#endif
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

/*
====================
test_typing_mix

	Проводится по типу набора, в случайном порядке определяет что вводить вопрос или ответ
====================
*/
char test_typing_mix() {
	bool repeat = false;
	while ( repeat || !test.mixNewWord() ) {
#ifdef __linux__
		load_keypress();
#endif
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

		switch ( test.getFlag() ) {
		case 1:
		case 4:
			if ( strcmp( ToLowerConsole( answer ), ToLowerFile( test.getQuestion() ) ) == 0 ) {
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
			if ( strcmp( ToLowerConsole( answer ), ToLowerFile( test.getAnswer() ) ) == 0 ) {
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

#ifdef __linux__
		set_keypress_noecho();
#endif
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
