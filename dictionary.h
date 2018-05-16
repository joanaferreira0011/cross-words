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
	void suggestions(string word);
	void showsuggestions();
	vector<string> find_matches(vector<string> &possible_words);

private:
	map<string, vector<string>> synonymslist;
	set<string> validwordslist;
	vector<string> suggestedwords;
};

#endif //CROSS_WORDS_DICTIONARY_H
