#include "TestMaker.h"

namespace uns {
	/*
	* Name: clearTest
	* Description: ������� ����
	*/
	void ucTestMaker::clearTest() {
		for ( int i = 0; i < data.size(); i++ ) {
			delete[] data[i].string;
		}
		data.clear();
		counter = 0;
		index = -1;
	}

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
		file.close();
	}

	/*
	* Name: addQuestion
	* Description: ��������� ����� ������ � ����� �������
	*/
	void ucTestMaker::addQuestion() {
		usData_t tmpData;
		tmpData.string = new char[SIZE];
		char *comentPointer = NULL;
		file.getline( tmpData.string, SIZE );	// ��������� ����� ������
		if ( ( comentPointer = strstr( tmpData.string, "#" ) ) != NULL ) {	// ������� ������������������
			comentPointer[0] = '\0';
		}
		if ( strstr( tmpData.string, " - " ) == NULL ) {	// ��������� �� �������� ������
			delete[] tmpData.string;
			return;
		}
		if ( tmpData.string[strlen( tmpData.string ) - 1] == 13 ) {	// ������ ������ ��������� ������ �� ��� ������ ����� ���������
			tmpData.string[strlen( tmpData.string ) - 1] = '\0';
		}

		data.push_back( tmpData );
	}

	/*
	* Name: init
	* Description: ���������� ��� ����� ����
	*/
	void ucTestMaker::init() {
		srand( ( unsigned int ) time( NULL ) );
		for ( int i = 0; i < data.size(); i++ ) {
			data[i].flag = 0;
		}
		counter = 0;
	}

	/*
	* Name: newWord
	* Description: �������� ����� ����� ��� �������
	*/
	int ucTestMaker::newWord() {
		if ( counter == data.size() ) {
			return 1;
		}
		while ( data[index = rand() % data.size()].flag == 1 );
		data[index].flag = 1;
		counter++;
		return 0;
	}

	/*
	* Name: mixNewWord
	* Description: �������� ����� ����� ��� ������� � ������ ���� ��������
	*/
	int ucTestMaker::mixNewWord() {
		if ( counter == ( 2 * data.size() ) ) {
			return 1;
		}
		while ( data[index = rand() % data.size()].flag == 3 || data[index].flag == 4 );
		if ( data[index].flag == 0 ) {
			data[index].flag = rand() % 2 + 1;
		} else if ( data[index].flag == 1 ) {
			data[index].flag = 3;
		} else if ( data[index].flag == 2 ) {
			data[index].flag = 4;
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
			if ( data[index].string[i] == '-' && data[index].string[i - 1] == ' ' && data[index].string[i + 1] == ' ' ) {
				str[i - 1] = '\0';
				break;
			}
			str[i] = data[index].string[i];
		}
		return str;
	}

	/*
	* Name: getQuestion
	* Description: ���������� �����
	*/
	const char*	ucTestMaker::getAnswer() {
		int i = 0;
		while ( !( data[index].string[i] == '-' && data[index].string[i - 1] == ' ' && data[index].string[i + 1] == ' ' ) ) {
			i++;
		}
		i++;
		for ( int j = 0; j < SIZE; j++ ) {
			if ( data[index].string[++i] == '\0' ) {
				str[j] = '\0';
				break;
			}
			str[j] = data[index].string[i];
		}
		return str;
	}

	ucTestMaker::~ucTestMaker() {
		for ( int i = 0; i < data.size(); i++ ) {
			delete[] data[i].string;
		}
		data.clear();
	}

}