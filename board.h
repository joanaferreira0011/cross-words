#ifndef PROG_EXERC_DATE_H
#define PROG_EXERC_DATE_H

#include <string>
#include <vector>
#include "dictionary.h"

using namespace std;


class Board
{
public:
	Board();
	//
	Board(string lines, string columns);
	//
	Board(string lines, string columns, Dictionary d1);
	bool addword(string position, string word);
	void show();
private:
	unsigned int lines;
	unsigned int columns;
	vector<vector<char> > matrix;
	vector<char> name_lines;
	vector<char> name_columns;
	Dictionary d;
	bool check_H(string word, int x, int y);
	bool check_V(string word, int y, int x);
	vector<string> all_words;
};

#endif //PROG_EXERC_DATE_H
