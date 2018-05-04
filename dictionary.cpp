#include "dictionary.h" // Using the dictionary class
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <set>


using namespace std;

//  ------------- Additional Functions ------------- //

// Will make the entire string in uppercase 
void uppercase_letters(string &word)
{
	transform(word.begin(), word.end(), word.begin(), toupper);
}

//////////////////////////////////////////////////////////////////////////
// WildcardMatch
// str - Input string to match
// strWild - Match mask that may contain wildcards like .
//
// A . sign matches any character, except an empty string.
// Characters are compared caseless.
//
// ADAPTED FROM:
// https://www.codeproject.com/Articles/188256/A-Simple-Wildcard-Matching-Function
bool wildcardMatch(const char *str, const char *strWild)
{
	// We have a special case where string is empty ("") and the mask is "*".
	// We need to handle this too. So we can't test on !*str here.
	// The loop breaks when the match string is exhausted.
	while (*strWild)
	{
		// Single wildcard character
		if (*strWild == '.')
		{
			// Matches any character except empty string
			if (!*str)
				return false;
			// OK next
			++str;
			++strWild;
		}
		else
		{
			// Standard compare of 2 chars. Note that *str might be 0 here,
			// but then we never get a match on *strWild
			// that has always a value while inside this loop.
			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}
	// Have a match? Only if both are at the end...
	return !*str && !*strWild;
}

 // ------------- Dictionary Class Functions ------------- //

Dictionary::Dictionary()
{
	// Structure
	map<string, vector<string>> synonymslist;
	set<string> validwordslist;
	map<string, vector<string>> suggestedwords;
}

Dictionary::Dictionary(string filename)
{
	loadfile(filename);
}

//  Open the dictionary and put the words in a map
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
		// Once you find ":", save the words from a list of synonyms
		
		wordlist = line.find(":");
		mainwordlist = line.substr(0, wordlist);
		uppercase_letters(mainwordlist);
		synonymslist.insert(pair<string, vector<string>>(mainwordlist, vector<string>()));
		validwordslist.insert(mainwordlist);

		next = wordlist + 2; // next word
		wordlist = line.find_first_of(",", next);

		while (wordlist != string::npos)
		{
			words = line.substr(next, wordlist - next);
			uppercase_letters(words);

			//  In case of errors in the dictionary
			if (words[0] != '[' && words[0] != '{' && words[1] != '[')
			{

				// Update the list of synonyms
				synonymslist[mainwordlist].push_back(words);

				next = wordlist + 2; // next word
				wordlist = line.find(",", next);
			}
			else {
				// If the word contains errors
				// with '{' or '[' is skipped to the next word
				next = wordlist + 2;
				wordlist = line.find(",", next);
			}
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

// Checks if the word is valid
// Puts the words on a set
bool Dictionary::validword(string word)
{
	bool isvalid;

	// Search a sorted list through binary search 
	// ** More Efficient **

	// sort(validwordslist.begin(), validwordslist.end());  //If a vector
	isvalid = binary_search(validwordslist.begin(), validwordslist.end(), word);
	
	if (isvalid)
		return true;
	else
		return false;

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

/*
--------------------- DON'T WORK ---------------------------

// Suggested words to complete the board.
// Using the set of ordered valid words, check which one can be
// inserted in the space left over, then remove the last element.
// If you find matching words, they are stored in a map with 
// a string of the first letter of the word, and in a vector 
// of strings that are the valid words for given coordinates.
void Dictionary::suggestions(string coordinates, string line)
{
	while (!line.empty())
	{
		string word;

		for (string word : validwordslist)
		{

			if (wildcardMatch(word.c_str(), line.c_str()))
			{
				suggestedwords.insert(pair<string, vector<string>>(coordinates, vector<string>()));
				suggestedwords[coordinates].push_back(word);
			}
		}
		line.erase(line.length() - 1);  
	}
}

// Shows the words of the map created, 
// in 'suggestions' that can be placed in the spaces,
// and the list of synonyms of the word
void Dictionary::showsuggestions()
{
	vector<string> mainword;
	vector<string> synonyms;

	for (auto it = suggestedwords.cbegin(); it != suggestedwords.cend(); ++it)
	{   
		// show coordinates
		cout << "Coordinates: " << (*it).first << "-> Words: " << endl; 
		
		mainword = (*it).second;

		for (string word : mainword)
		{
			cout << "                              " << word << " - ";
			synonyms = (*synonymslist.find(word)).second;

			for (size_t i = 0; i < synonyms.size(); i++)
			{
				cout << synonyms.at(i) << ",";
			}
			cout << endl;
		}


	}

}
*/