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
	Dictionary(string filename);
	void loadfile(string filename);
	bool validword(string word);
	void suggestions(string coordinates, string line);
	void showsuggestions();

private:
	map<string, vector<string>> synonymslist;
	set<string> validwordslist;
	map<string, vector<string>> suggestedwords;
};

#endif //CROSS_WORDS_DICTIONARY_H
