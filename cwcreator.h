#ifndef CROSS_WORDS_CWCREATOR_H
#define CROSS_WORDS_CWCREATOR_H

#include <iostream>
#include "dictionary.h"
#include "board.h"

using namespace std;

class cwcreator

{
public:
   
	void menu();
	/* Displays a menu with options */
	void usercontinue();
	/* Ask the user if they want to continue */

private:
	void Option1_createpuzzle();
	/* creates the puzzle by loading the dictionary and empty board */
	void uppercase_letterscw(string &word);
	/* Will make the entire string in uppercase */
	void resume_puzzle();
	void question_is_over();
	void save_board();
	/* Save the puzzle in a text file with the name of
	the dictionary the board and the list of words with that position */
	Board board1;
	Dictionary dictionary1;
	string dictionaryname;
};

#endif // !CROSS_WORDS_CWCREATOR_H

