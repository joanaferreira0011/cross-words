#include "dictionary.h" // Using the dictionary class
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <set>
#include "string.h"

using namespace std;

// This function compares text strings, one of which can 
// have wildcards ("*").
/*bool Dictionary::GeneralTextCompare(
	char * pTameText,
	// A string without wildcards
	char * pWildText,
	// A (potentially) corresponding string with wildcards
	bool bCaseSensitive = false,
	// By default, match on "X" vs "x"
	char cAltTerminator = '\0'
	// For function names, for example, you can stop at the first "("
)
{
	bool bMatch = true;
	char * pAfterLastWild = NULL;
	// Location after last "*", if we've encountered one
	char t, w;
	// Walk the text strings one character at a time.
	while (1)
	{
		t = *pTameText;
		w = *pWildText;
		// How do you match a unique text string?
		if (!t || t == cAltTerminator)
		{
			// Easy: unique up on it!
			if (!w || w == cAltTerminator)
			{
				break;                 // "x" matches "x"
			}
			else if (w == '*')
			{
				pWildText++;
				continue;              // "x*" matches "x" or "xy"
			}
			bMatch = false;
			break;                     // "x" doesn't match "xy"
		}
		else
		{
			if (!bCaseSensitive)
			{
				// Lowercase the characters to be compared.
				if (t >= 'A' && t <= 'Z')
				{
					t += ('a' - 'A');
				}

				if (w >= 'A' && w <= 'Z')
				{
					w += ('a' - 'A');
				}
			}
			// How do you match a tame text string?
			if (t != w)
			{
				// The tame way: unique up on it!
				if (w == '*')
				{
					pAfterLastWild = ++pWildText;
					continue;              // "*y" matches "xy"
				}
				else if (pAfterLastWild)
				{
					pWildText = pAfterLastWild;
					w = *pWildText;

					if (!w || w == cAltTerminator)
					{
						break;             // "*" matches "x"
					}
					else if (t == w)
					{
						pWildText++;
					}
					pTameText++;
					continue;     // "*sip*" matches "mississippi"
				}
				else
				{
					bMatch = false;
					break;           // "x" doesn't match "y"
				}
			}
		}
		pTameText++;
		pWildText++;
	}
	return bMatch;
}*/
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
}

Dictionary::Dictionary(string filename)
{
	loadfile(filename);
}

//  Open the dictionary and put the words in a map
void Dictionary::loadfile(const string &filename)
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

vector<string> Dictionary::find_matches(vector<string> possible_words)
{
	vector<string> words;

	for (size_t i = 0; i < possible_words.size(); i++)
	{
		string wild = possible_words.at(i);
		for (const auto& x : synonymslist)
		{
			string notwild = x.first;
			if (wildcardMatch(notwild.c_str(), wild.c_str()))
			/*if(GeneralTextCompare(
				x.first.c_str(),
				// A string without wildcards
				possible_words.at(i).c_str()
				// A (potentially) corresponding string with wildcards

			))*/
				words.push_back(x.first);
		}
	}

	return words;
	
}

void Dictionary::print_matches(vector<string> possible_words)
{
	vector<string> words = find_matches(possible_words);

	if (words.size() == 0)
		std::cout << "Sorry, no matching words for that position" << endl << endl;
	else
	{
		random_shuffle(possible_words.begin(), words.end());
		std::cout << "Possible words you could use: " << words.at(0) << ", " << words.at(1) << endl << endl;
	}
}