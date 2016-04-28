#include "TestMaker.h"

namespace uns {
	/*
	* Name: openFile
	* Description: ��������� ����
	*/
	int ucTestMaker::openFile( const char filename[] ) {
		file.open( filename );
		if ( !file.is_open() ) {
			return -1;
		}
		return 0;
	}

	/*
	* Name: readFile
	* Description: ��������� ��� ������ �� �����
	*/
	void ucTestMaker::readFile() {
		while ( !file.eof() ) {
			addQuestion();
		}
	}

	/*
	* Name: addQuestion
	* Description: ��������� ����� ������ � ����� �������
	*/
	void ucTestMaker::addQuestion() {
		char **tmp;	// ������� ��������� ���������
		tmp = new char*[length + 1];	// �������� � ���� ������ ������ �� 1 ��� ������
		tmp[length] = new char[SIZE];	// �������� ������ ��� ��������� �������
		for ( int i = 0; i < length; i++ ) {	// �������� ����� ��������� ��������
			tmp[i] = mas[i];
		}
		if ( mas != NULL ) {
			delete[] mas;	// ������� ������ ������
		}
		file.getline( tmp[length], SIZE );	// ��������� ����� ������
		if ( tmp[length][strlen(tmp[length]) - 1] == 13 ) {	// ������ ������ ��������� ������ �� ��� ������ ����� ���������
			tmp[length][strlen(tmp[length]) - 1] = '\0';
		}
		length++;
		mas = tmp;
	}

	/*
	* Name: init
	* Description: ���������� ��� ����� ����
	*/
	void ucTestMaker::init() {
		srand( ( unsigned int ) time( NULL ) );
		if ( flags == NULL ) {
			flags = new char[length];
		}
		for ( int i = 0; i < length; i++ ) {
			flags[i] = 0;
		}
		counter = 0;
	}

	/*
	* Name: newWord
	* Description: �������� ����� ����� ��� �������
	*/
	int ucTestMaker::newWord() {
		if ( counter == length ) {
			return 1;
		}
		while ( flags[index = rand() % length] == 1 );
		flags[index] = 1;
		counter++;
		return 0;
	}

	int ucTestMaker::mixNewWord() {
		if ( counter == ( 2 * length ) ) {
			return 1;
		}
		while ( flags[index = rand() % length] == 3 || flags[index = rand() % length] == 4 );
		if ( flags[index] == 0 ) {
			flags[index] = rand() % 2 + 1;
		} else if ( flags[index] == 1 ) {
			flags[index] = 3;
		} else if ( flags[index] == 2 ) {
			flags[index] = 4;
		}
		counter++;
		return 0;
	}

	/*
	* Name: getQuestion
	* Description: ���������� ������
	*/
	const char*	ucTestMaker::getQuestion() {
		for ( int i = 0; i < SIZE; i++ ) {
			if ( mas[index][i] == '-' && mas[index][i - 1] == ' ' && mas[index][i + 1] == ' ' ) {
				str[i - 1] = '\0';
				break;
			}
			str[i] = mas[index][i];
		}
		return str;
	}

	/*
	* Name: getQuestion
	* Description: ���������� �����
	*/
	const char*	ucTestMaker::getAnswer() {
		int i = 0;
		while ( !( mas[index][i] == '-' && mas[index][i - 1] == ' ' && mas[index][i + 1] == ' ' ) ) {
			i++;
		}
		i++;
		for ( int j = 0; j < SIZE; j++ ) {
			if ( mas[index][++i] == '\0' ) {
				str[j] = '\0';
				break;
			}
			str[j] = mas[index][i];
		}
		return str;
	}

	ucTestMaker::~ucTestMaker() {
		if ( length != 0 ) {
			for ( int i = 0; i < length; i++ ) {
				delete[] mas[i];
			}
			delete[] mas;
			delete[] flags;
		}
	}

}