#include "stdafx.h"
#include "board.h"
#include "dictionary.h"
#include <vector>

int main()
{
	Dictionary d1;
	Board b2;
	Board b1=Board(10, 10);
	b1.show();

	b1.addword("AaH", "lsdihf");
	b1.show();
	b1.addword("DdH", "lsdihf");
	b1.show();
	/*b1.addword("AaH", "yup");
	b1.show();*/



	vector<string> v = b1.get_wildcard("CbH");
	for (size_t i = 0; i < v.size(); i++)
		cout << v.at(i)<< endl;
	b1.show();
	/*b1.remove_word("CcV");
	b1.show();*/
	/*b1.fill_finished();*/
	b1.show();
	b1.show_emptyboard();
	system("pause");
	return 0;
}
