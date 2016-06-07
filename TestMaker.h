#ifndef _TEST_MAKER_H
#define _TEST_MAKER_H

#include <fstream>
#include <time.h>
#include <string.h>
#include <vector>
using namespace std;

const int SIZE = 1024;

namespace uns {

	struct usData_t {	// Структура одного объекта
		char *	string;
		char	flag;
	};

	class ucTestMaker {
	private:
		vector< usData_t >	data;	// Вектор данных
		int					counter = 0;	// Количество выведеных строк
		int					index = -1;	// Номер текущей строки
		char				str[SIZE];	// Возвращаемая строка
		std::ifstream 		file;	// Подключаемый файл
		
	public:
		void				clearTest();
		int					openFile( const char filename[] );
		void				readFile();
		void				addQuestion();
		void				init();
		int					newWord();
		int					mixNewWord();
		const	char*		getQuestion();
		const	char*		getAnswer();
		int					getCounter() { return counter; }
		int					getLength() { return data.size(); }
		char				getFlag() { return data[index].flag; }
							~ucTestMaker();
	};

}

#endif // !_TEST_MAKER_H
