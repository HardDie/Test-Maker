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
		void				ClearTest();
		int					OpenFile( const char filename[] );
		void				ReadFile();
		void				AddQuestion();
		void				Init();
		int					NewWord();
		int					MixNewWord();
		const	char*		GetQuestion();
		const	char*		GetAnswer();
		int					GetCounter() { return counter; }
		int					GetLength() { return data.size(); }
		char				GetFlag() { return data[index].flag; }
							~ucTestMaker();
	};

}

#endif // !_TEST_MAKER_H
