#ifndef _TEST_MAKER_H
#define _TEST_MAKER_H

#include <fstream>
#include <time.h>
#include <string.h>
using namespace std;

const int SIZE = 1024;

namespace uns {

	class ucTestMaker {
	private:
		char **			mas = NULL;	// ������ �����
		char *			flags = NULL;	// ������ ����� ������������� �����
		int				length = 0;	// ���������� �����
		int				counter = 0;	// ���������� ��������� �����
		int				index = -1;	// ����� ������� ������
		char			str[SIZE];	// ������������ ������
		std::ifstream 	file;	// ������������ ����

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
		int					getLength() { return length; }
		char				getFlag() { return flags[index]; }
							~ucTestMaker();
	};

}

#endif // !_TEST_MAKER_H
