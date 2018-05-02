#include "dictionary.h" // Using the dictionary class
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

// Will make the entire string in uppercase 
void uppercase_letters(string &word)
{
	transform(word.begin(), word.end(), word.begin(), toupper);
}

Dictionary::Dictionary()
{
	// Structure
	synonymslist[""] = { "" };
	validwordslist = { "" };
}

Dictionary::Dictionary(string filename)
{
	loadfile(filename);
}

// -------------- Input File ------------------ //
void Dictionary::loadfile(string filename)
{
	ifstream dictionary;
	string words;
	string line;
	string mainwordlist;
	int wordlist = 0;
	int	next = 0;

	dictionary.open(filename);

	// Open the file; exit program if the file couldn't be opened
	if (!dictionary.is_open())
	{
		cerr << "File " << "dictionary" << " not found !\n";
		exit(1);
	}

	while (getline(dictionary, line))
	{
		uppercase_letters(words);

		// Once you find ":", save the words from a list of synonyms
		wordlist = line.find(":");
		mainwordlist = line.substr(0, wordlist);

		synonymslist.insert(pair<string, vector<string>>(mainwordlist, vector<string>()));
		validwordslist.push_back(words);

		next = wordlist + 2; // next word
		wordlist = line.find_first_of(",", next);

		while (wordlist != string::npos)
		{
			words = line.substr(next, wordlist - next);
			uppercase_letters(words);
			// Update the list of synonyms
			synonymslist[mainwordlist].push_back(words);

			next = wordlist + 2; // next word
			wordlist = line.find_first_of(",", next);
		}

		// Check for more synonyms
		if (line[line.length() - 1] != ',')
		{
			words = line.substr(next, line.length() - next);
			uppercase_letters(words);
			// Update the list of synonyms
			synonymslist[mainwordlist].push_back(words);
		}
	}
}

bool Dictionary::validword(string word)
{
	bool isvalid;

	// Search a sorted list through binary search 
	// ** More Efficient **

	sort(validwordslist.begin(), validwordslist.end());
	isvalid = binary_search(validwordslist.begin(), validwordslist.end(), word);
	
	return isvalid;
	
	/* // ----   Not so efficient ----
	bool isvalid = false;
	
	for (unsigned int i = 0; i < validwordslist.size(); i++)
	{
		if (word == validwordslist.at(i))
		{
			isvalid = true;
			break;
		}
	}
	return isvalid; 
	*/
}
