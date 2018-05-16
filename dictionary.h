#ifndef CROSS_WORDS_DICTIONARY_H
#define CROSS_WORDS_DICTIONARY_H

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <iomanip>

using namespace std;

class Dictionary 
{
public:

	Dictionary();
	/* Standard function */
	Dictionary(string filename);
	/* load the dictionary */
	void loadfile(string filename);
	/* Open the dictionary and put the words in a map */
	bool validword(string word);
	/* Checks if the word is valid, and puts the words on a set */
	vector<string> find_matches(vector<string> &possible_words);
	/* */

private:
	map<string, vector<string>> synonymslist;
	set<string> validwordslist;
	vector<string> suggestedwords;
};

#endif //CROSS_WORDS_DICTIONARY_H
