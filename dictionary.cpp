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
	// transform(word.begin(), word.end(), word.begin(), [] (unsigned char c) { return toupper(c); } );
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
	unsigned int wordlist = 0;
	unsigned int next = 0;
	

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
		
		wordlist = line.find(':');
		mainwordlist = line.substr(0, wordlist);
		uppercase_letters(mainwordlist);
		synonymslist.insert(pair<string, vector<string>>(mainwordlist, vector<string>()));
		validwordslist.insert(mainwordlist);

		next = wordlist + 2; // next word
		wordlist = line.find(',', next);

		while (wordlist != string::npos)
		{
			words = line.substr(next, wordlist - next);
			

			//  In case of errors in the dictionary
			if (words[0] != '[' && words[0] != '{')
			{
				uppercase_letters(words);
				// Update the list of synonyms
				synonymslist[mainwordlist].push_back(words);
			}

			// If the word contains errors
			// with '{' or '[' is skipped to the next word
			next = wordlist + 2; // next word
			wordlist = line.find(',', next);
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

<<<<<<< HEAD
=======
vector<string> Dictionary::find_matches(vector<string> &possible_words)
{
	vector<string> words;
	for (size_t i = 0; i < possible_words.size(); i++)
	{
		for (const auto& x : synonymslist)
		{
			if (wildcardMatch(possible_words.at(i).c_str(), x.first.c_str()))
				words.push_back(x.first);
		}
	}

	return words;
	
}
>>>>>>> fabf4792cb5112e902048bdcc5756c2495ef0590
/*

// Suggested words to complete the board.
void Dictionary::suggestions(string word)
{
	string lastchar;
	lastchar = word.at(word.length() - 1);
	
	while(!lastchar.empty())
	{
		for (string word : validwordslist)
		{
		if (wildcardMatch(word.c_str(), lastchar.c_str()))
				suggestedwords.push_back(word);
		}
		lastchar.erase(lastchar.length() - 1);  
	}
}

// Shows the words of the vector created, 
// in 'suggestions' that can be placed in the spaces,
// and the list of synonyms of the word
void Dictionary::showsuggestions()
{
	vector<string> mainword;
	

	//for (int i = suggestedwords.cbegin(); i != suggestedwords.cend(); ++i)
	{   

		for (string word : mainword)
		{
			

			for (size_t i = 0; i < suggestedwords.size(); i++)
			{
				cout << suggestedwords.at(i) << ",";
			}
			cout << endl;
		}


	}

}
*/
