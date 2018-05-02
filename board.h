#ifndef PROG_EXERC_DATE_H
#define PROG_EXERC_DATE_H

#include <string>
#include <vector>

using namespace std;


class Board
{
public:
	Board(string lines, string columns);
	void addword(stringstream position);
	void show();
private:
	unsigned int lines;
	unsigned int columns;
	vector<vector<char> > matrix;
	vector<char> name_lines;
	vector<char> name_columns;
};

#endif //PROG_EXERC_DATE_H
