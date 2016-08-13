#include "TestFunctions.h"

/*
====================
TestQuestionAnswer

	Проводится по типу отображения, сначала отображается вопрос, а по нажатию клавиши ответ
====================
*/
char TestQuestionAnswer() {
#ifdef __linux__
	SetNoCanonicalMode();
#endif
	while ( !test.NewWord() ) {
		ClearScreen();
		cout << test.GetCounter() << "/" << test.GetLength() << endl;

		cout << test.GetQuestion();
		switch ( WaitPressKey() ) {
		case 'q':
		case 'Q':
			return 'q';
		case 'm':
		case 'M':
			return 'm';
		}

		cout << " - " << test.GetAnswer() << endl;
		cout << "Press any key...";
		switch ( WaitPressKey() ) {
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
TestAnswerQuestion

	Проводится по типу отображения, сначала отображается ответ, а по нажатию клавиши вопрос
====================
*/
char TestAnswerQuestion() {
#ifdef __linux__
	SetNoCanonicalMode();
#endif
	while ( !test.NewWord() ) {
		ClearScreen();
		cout << test.GetCounter() << "/" << test.GetLength() << endl;

		cout << test.GetAnswer();
		switch ( WaitPressKey() ) {
		case 'q':
		case 'Q':
			return 'q';
		case 'm':
		case 'M':
			return 'm';
		}

		cout << " - " << test.GetQuestion() << endl;
		cout << "Press any key...";
		switch ( WaitPressKey() ) {
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
TestMixing

	Проводится по типу отображения, в случайном порядке определяет вывод вопроса - ответа, или ответа - вопроса
====================
*/
char TestMixing() {
#ifdef __linux__
	SetNoCanonicalMode();
#endif
	while ( !test.MixNewWord() ) {
		ClearScreen();
		cout << test.GetCounter() << "/" << test.GetLength() * 2 << endl;

		switch ( test.GetFlag() ) {
		case 1:
		case 4:
			cout << test.GetAnswer();
			break;
		case 2:
		case 3:
			cout << test.GetQuestion();
			break;
		}

		switch ( WaitPressKey() ) {
		case 'q':
		case 'Q':
			return 'q';
		case 'm':
		case 'M':
			return 'm';
		}

		cout << " - ";
		switch ( test.GetFlag() ) {
		case 1:
		case 4:
			cout << test.GetQuestion();
			break;
		case 2:
		case 3:
			cout << test.GetAnswer();
			break;
		}
		cout << endl << "Press any key...";

		switch ( WaitPressKey() ) {
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
TestTypingQuestion

	Проводится по типу набора вопроса при выведеном ответе
====================
*/
char TestTypingQuestion() {
	bool repeat = false;
	while ( repeat || !test.NewWord() ) {
#ifdef __linux__
		LoadKeypress();
#endif
		ClearScreen();
		cout << test.GetCounter() << "/" << test.GetLength() << endl;

		cout << test.GetAnswer() << "\nEnter: ";
		static char answer[SIZE];
		cin.getline( answer, SIZE );

		if ( strcmp( ToLowerConsole( answer ), ToLowerFile( test.GetQuestion() ) ) == 0 ) {
			cout << "Right!\n";
			repeat = false;
		} else if ( strcmp( answer, " " ) == 0 ) {
			cout << test.GetQuestion() << endl;
			cout << "Next\n";
			repeat = false;
		} else {
			cout << "Wrong: " << test.GetQuestion() << endl;
			repeat = true;
		}
#ifdef __linux__
		SetNoCanonicalMode();
#endif
		cout << "Press any key...";
		switch ( WaitPressKey() ) {
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
TestTypingAnswer

	Проводится по типу набора ответа при выведеном вопросе
====================
*/
char TestTypingAnswer() {
	bool repeat = false;
	while ( repeat || !test.NewWord() ) {
#ifdef __linux__
		LoadKeypress();
#endif
		ClearScreen();
		cout << test.GetCounter() << "/" << test.GetLength() << endl;

		cout << test.GetQuestion() << "\nEnter: ";
		static char answer[SIZE];
		cin.getline( answer, SIZE );

		if ( strcmp( ToLowerConsole( answer ), ToLowerFile( test.GetAnswer() ) ) == 0 ) {
			cout << "Right!\n";
			repeat = false;
		} else if ( strcmp( answer, " " ) == 0 ) {
			cout << test.GetAnswer() << endl;
			cout << "Next\n";
			repeat = false;
		} else {
			cout << "Wrong: " << test.GetAnswer() << endl;
			repeat = true;
		}
#ifdef __linux__
		SetNoCanonicalMode();
#endif
		cout << "Press any key...";
		switch ( WaitPressKey() ) {
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
TestTypingMix

	Проводится по типу набора, в случайном порядке определяет что вводить вопрос или ответ
====================
*/
char TestTypingMix() {
	bool repeat = false;
	while ( repeat || !test.MixNewWord() ) {
#ifdef __linux__
		LoadKeypress();
#endif
		ClearScreen();
		cout << test.GetCounter() << "/" << test.GetLength() * 2 << endl;

		switch ( test.GetFlag() ) {
		case 1:
		case 4:
			cout << test.GetAnswer();
			break;
		case 2:
		case 3:
			cout << test.GetQuestion();
			break;
		}

		cout << "\nEnter: ";
		static char answer[SIZE];
		cin.getline( answer, SIZE );

		switch ( test.GetFlag() ) {
		case 1:
		case 4:
			if ( strcmp( ToLowerConsole( answer ), ToLowerFile( test.GetQuestion() ) ) == 0 ) {
				cout << "Right!\n";
				repeat = false;
			} else if ( strcmp( answer, " " ) == 0 ) {
				cout << test.GetQuestion() << endl;
				cout << "Next\n";
				repeat = false;
			} else {
				cout << "Wrong: " << test.GetQuestion() << endl;
				repeat = true;
			}
			break;
		case 2:
		case 3:
			if ( strcmp( ToLowerConsole( answer ), ToLowerFile( test.GetAnswer() ) ) == 0 ) {
				cout << "Right!\n";
				repeat = false;
			} else if ( strcmp( answer, " " ) == 0 ) {
				cout << test.GetAnswer() << endl;
				cout << "Next\n";
				repeat = false;
			} else {
				cout << "Wrong: " << test.GetAnswer() << endl;
				repeat = true;
			}
			break;
		}

#ifdef __linux__
		SetNoCanonicalMode();
#endif
		cout << "Press any key...";
		switch ( WaitPressKey() ) {
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
