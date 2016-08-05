#include "TestMaker.h"

namespace uns {
	/*
	* Name: clearTest
	* Description: Очищает тест
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
	* Description: Открывает файл
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
	* Description: Считывает все строки из файла
	*/
	void ucTestMaker::readFile() {
		while ( !file.eof() ) {
			addQuestion();
		}
		file.close();
	}

	/*
	* Name: addQuestion
	* Description: Считывает новую строку в конец массива
	*/
	void ucTestMaker::addQuestion() {
		usData_t tmpData;
		tmpData.string = new char[SIZE];
		char *comentPointer = NULL;
		file.getline( tmpData.string, SIZE );	// Считываем новую строку
		if ( ( comentPointer = strstr( tmpData.string, "#" ) ) != NULL ) {	// Убираем закомментированное
			comentPointer[0] = '\0';
		}
		if ( strstr( tmpData.string, " - " ) == NULL ) {	// Проверяем на верность строки
			delete[] tmpData.string;
			return;
		}
		if ( tmpData.string[strlen( tmpData.string ) - 1] == 13 ) {	// Ставим символ окончания строки во все строки кроме последней
			tmpData.string[strlen( tmpData.string ) - 1] = '\0';
		}

		data.push_back( tmpData );
	}

	/*
	* Name: init
	* Description: Сбрасывает все флаги слов
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
	* Description: Выбирает новое слово для вопроса
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
	* Description: Выбирает новое слово для вопроса с учетом двух вопросов
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
	* Description: Возвращает вопрос
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
	* Description: Возвращает ответ
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