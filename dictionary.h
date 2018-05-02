#ifndef CROSS_WORDS_DICTIONARY_H
#define CROSS_WORDS_DICTIONARY_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Dictionary 
{
public:

	Dictionary();
	Dictionary(string filename);
	void loadfile(string filename);
	bool validword(string word);

private:
	map<string, vector<string>> synonymslist;
	vector <string> validwordslist;
};

#endif //CROSS_WORDS_DICTIONARY_H
