#ifndef _TEST_MAKER_H
#define _TEST_MAKER_H

#include <fstream>
#include <time.h>
#include <string.h>
#include <vector>
using namespace std;

const int SIZE = 1024;

namespace uns {

	struct usData_t {	// ��������� ������ �������
		char *	string;
		char	flag;
	};

	class ucTestMaker {
	private:
		vector< usData_t >	data;	// ������ ������
		int					counter = 0;	// ���������� ��������� �����
		int					index = -1;	// ����� ������� ������
		char				str[SIZE];	// ������������ ������
		std::ifstream 		file;	// ������������ ����
		
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
