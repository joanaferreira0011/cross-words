#ifndef PROG_EXERC_DATE_H
#define PROG_EXERC_DATE_H

#include <string>
#include <vector>
#include <map>


using namespace std;


class Board
{
public:
	Board() {};
<<<<<<< HEAD
	Board(unsigned int lines, unsigned int columns);
	bool addword(string position, string word);
=======
	Board(int lines, int columns);
	/* Creates board*/
	void addword(string position, string word);
	/* Adds word to board and map
	@position for the first letter, must be a 3 char str: 1st char is an uppercase letter representing the line, second char: a lowercase representing the column and last char a 'H' for horizontal or 'V' for vertical
	@word: str to be written in the board
	@returns error message if word doesnt fit
	@does not check if word exists*/
>>>>>>> fabf4792cb5112e902048bdcc5756c2495ef0590
	void remove_word(string position);
	/* Removes word from board and map
	@position for the first letter, must be a 3 char str: 1st char is an uppercase letter representing the line, second char: a lowercase representing the column and last char a 'H' for horizontal or 'V' for vertical
	*/
	void show();
	/* prints board to console*/
	void fill_finished();
	/* fills all positions that have '.' with '#' */
	void addword_nochecking(string position, string word);
<<<<<<< HEAD
	const vector<vector<char>> &matrixboard() const;
=======
	/* Adds word to board and NOT to map, WITHOUT checking if word fits
	@position for the first letter, must be a 3 char str: 1st char is an uppercase letter representing the line, second char: a lowercase representing the column and last char a 'H' for horizontal or 'V' for vertical
	@word: str to be written in the board
	@does not check if word exists*/

	vector<string> get_wildcard(string position);
	/* gets all words that fit in a space starting at @position with wildcards ('?') for instance "A?A??B"
	@position for the first letter, must be a 3 char str: 1st char is an uppercase letter representing the line, second char: a lowercase representing the column and last char a 'H' for horizontal or 'V' for vertical*/
>>>>>>> fabf4792cb5112e902048bdcc5756c2495ef0590

private:
	unsigned int lines;
	unsigned int columns;
	vector<vector<char> > matrix;
	vector<char> name_lines;
	vector<char> name_columns;
	bool check_H(string &word, int &x, int &y);
	bool check_V(string &word, int &y, int &x);
	map<string, string> all_words;
	void transform_to_pos(string position, int &x, int &y, char &orientation);
};

#endif //PROG_EXERC_DATE_H
