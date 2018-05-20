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
	void create_puzzle();
	/* creates the puzzle by loading the dictionary and empty board */
	void uppercase_letterscw(string &word);
	/* Will make the entire string in uppercase
	@It has as parameter a string that is a word that will become the capital letter */
	void update_board(Board boardname, Dictionary dictionaryname);
	/* Update the board, and the user creates, adding words, removing words ... 
	@has as parameters the name of the board to be updated and the dictionary that will be used to update the board */
	void resume_puzzle();
	/* This function allows the user to continue an unfinished puzzle, asking the user which board to finish */
	void question_is_over(Board Boardname);
	/* 
	@It has as parameter the board, receives the name of the board; */
	void save_board(Board Boardname);
	/* Save the puzzle in a text file with the name of the dictionary the board and the list of words with that position
	@It has as parameter the board, receives the name of the board */
	
	Board board;
	Board board1;
	Dictionary dictionary;
	string dictionaryname;
};

#endif // !CROSS_WORDS_CWCREATOR_H

