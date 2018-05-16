#include "stdafx.h"
#include "board.h"
#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib> 
#include <windows.h> 
#include "dictionary.h"
#include <sstream>
#include <algorithm>  

using namespace std;	

#define LIGHTRED 12
#define LIGHTGRAY 7 
#define BLACK 0
#define WHITE 15

// COLOR
void setcolor(unsigned int color) 
{ HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);   
SetConsoleTextAttribute(hcon, color); }

void setcolor(unsigned int color, unsigned int background_color) 
{ HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);   
if (background_color == BLACK)     
SetConsoleTextAttribute(hCon, color);   
else     SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED); }

bool Board::check_H(string &word, int &x, int &y)
{
	size_t acum=0;
	if ((matrix[y - 1][x] == '.' || matrix[y - 1][x] == '#') && (matrix[y + word.length()][x] == '.' || matrix[y + word.length()][x] == '#'))
	{
		while (acum < word.length())
		{
			if ((matrix[y+acum][x] == '.') || (matrix[y+acum][x] == word.at(acum)))
			{
				acum++;
			}

			else
				return false;
		}


		if (acum == (word.length() + 1))
			return true;
	}
	else
		return false;
}

bool Board::check_V(string &word, int &y, int &x)
{
	size_t acum = 0;
	if ((matrix[x - 1][y] == '.' || matrix[x - 1][y] == '#') && (matrix[x + word.length()][y] == '.' || matrix[x + word.length()][y] == '#'))
	{
		while (acum < word.length())
		{
			if ((matrix[x][y+acum] == '.') || (matrix[x][y+acum] == word.at(acum)))
			{
				acum++;
			}

			else
				return false;
		}


		if (acum == (word.length() + 1))
			return true;
	}
	else
		return false;
}

Board::Board(unsigned int l, unsigned int c)
{
	
	lines = l;
	columns = c;

	//MATRIX BOARD
	matrix.resize(lines);

	for (size_t i = 0; i < matrix.size(); i++)
		matrix[i].resize(columns);

	for (size_t i = 0; i < matrix.size(); i++)
		fill(matrix[i].begin(), matrix[i].end(), '.');


	//NAME LINES
	name_lines.resize(lines);


	for (size_t i = 0; i < name_lines.size(); i++)
	{
		char letter = (char)('a' + i);
		name_lines[i] = letter;
	}

	// NAME COLUMNS
	name_columns.resize(columns);


	for (size_t i = 0; i < name_columns.size(); i++)
	{
		char letter = (char)('A' + i);
		name_columns[i] = letter;
	}

}

void Board::show()
{
	
	cout << ' ';
	// PRINT name of lines
	
	setcolor(LIGHTRED);
	for (size_t i = 0; i < lines; i++)
	{
		cout << ' ' << name_lines[i];
	}

	cout << endl;

	for (size_t i = 0; i < columns; i++)
	{
		setcolor(LIGHTRED, BLACK);
		cout << name_columns[i] << ' ';

		setcolor(BLACK, LIGHTGRAY);
		for (size_t a = 0; a < lines; a++)
			cout << matrix[a][i] << ' ';
		cout << endl;
	}
	setcolor(WHITE, BLACK);
	cout << endl;
	
}

void Board::transform_to_pos(string position, int &x, int &y, char &orientation)
{
	x = position[0] - 'A';
	y = position[1] - 'a';
	orientation = position[2];
}

void Board::addword(string position, string word)
{
	//check if valid input
	if (position.length() == 3 && isupper(position[0]) && !(isupper(position[1])) && (toupper(position[2]) == 'V' || toupper(position[2]) == 'H'))
	{
		//initializing variables position
		int x = 0;
		int y = 0;
		char orientation = 'a';

		//get true value for variables position 
		transform_to_pos(position, x, y, orientation);

		transform(word.begin(), word.end(), word.begin(), toupper); //transform to uppercase


			switch (orientation) {
			case 'H':
			{
				//check if empty
				if (check_H(word, x, y))
				{
					matrix[y-1][x] = '#';
					matrix[y + word.length()][x] = '#';
					size_t i = 0;
					while (i < word.length())
					{
						matrix[y+i][x] = word.at(i);
						
						i++;
					}

					//add to map
					all_words.insert(pair<string, string>(position, word));
					break;

					
				}
				else
				{
					std::cout << "Cannot fit " << word<< " in position " << position << endl<<endl;
					break;

					
				}


			}

			case 'V':
			{
				if (check_V(word, x, y))
				{
					matrix[y][x-1] = '#';
					matrix[y][x + word.length()] = '#';
					size_t i = 0;
					while (i < word.length())
					{
						matrix[y][x+i] = word.at(i);
				
						i++;
					}

					//add to map
					all_words.insert(pair<string, string>(position, word));
					break;

					
				}
				else
				{
					std::cout << "Cannot fit " << word << " in position " << position << endl << endl;
					break;
				}
			
			}
			}
	}
	else
		cout << "Invalid input\n";
}

void Board::remove_word(string position)
{
	if (position.length() == 3 && isupper(position[0]) && !(isupper(position[1])) && (all_words.find(position) != all_words.end()))
	{
		all_words.erase(position);
		int y = position[0] - 'A';  //y and x is diferent from the ones in addword
		int x = position[1] - 'a';
		char orientation = position[2];
		switch (orientation)
		{
		case 'H':
		{
			size_t i = 0;
			matrix[x - 1][y] = '.';
			do
			{
				matrix[x + i][y] = '.';
				i++;
			} while (matrix[x + i][y] != '#' && matrix[x + i][y] != (columns - 2));

			matrix[x + i][y] = '.';
			break;

		}
		case 'V':
		{
			size_t i = 0;
			matrix[x][y - 1] = '.';
			do
			{
				matrix[x][y + i] = '.';
				i++;


			} while (matrix[x][y + i] != '#' && matrix[x][y + i] != lines - 2);
			matrix[x][y + i] = '.';
			break;

		}
	
	}
	
	for (const auto& x : all_words)
	{
		addword_nochecking(x.first, x.second);
	}

	}
	else
		cout << "Not a valid input\n";



}

void Board::fill_finished()
{
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t a = 0; a < matrix.at(i).size(); a++)
		{
			if (matrix.at(i).at(a) == '.')
				matrix.at(i).at(a) = '#';
		}
	}
}

void Board::addword_nochecking(string position, string word)
{

	//initializing variables position
	int x = 0;
	int y = 0;
	char orientation = 'a';

	//get true value for variables position 
	transform_to_pos(position, x, y, orientation);

	//write the word
	switch (orientation) {
	case 'H':
	{
		matrix[y - 1][x] = '#';
		matrix[y + word.length()][x] = '#';
		size_t i = 0;
		while (i < word.length())
		{
			matrix[y + i][x] = word.at(i);

			i++;
		}
	}

	case 'V':
	{

		matrix[y][x - 1] = '#';
		matrix[y][x + word.length()] = '#';
		size_t i = 0;
		while (i < word.length())
		{
			matrix[y][x + i] = word.at(i);

			i++;
		}
	}
	}
}

const vector<vector<char>> &Board::matrixboard() const
{
	return matrix;
}

vector<string> Board::get_wildcard(string position)
{
	//check if valid input
	if (position.length() == 3 && isupper(position[0]) && !(isupper(position[1])) && (toupper(position[2]) == 'V' || toupper(position[2]) == 'H'))
	{
		//initializing variables position
		int x = 0;
		int y = 0;
		char orientation = 'a';

		//get true value for variables position 
		transform_to_pos(position, y, x, orientation);

		vector<string> words; //all possible words
		string possible_word;
		switch (orientation)
		{
		case 'V':
		{
			if (matrix[x][y] != '.')
				possible_word += matrix[x][y];


			for (size_t i = 1; matrix[x][y + i] != '#' && (y + i) < lines - 1; i++) //scan all possibilitis like 'w?', 'w??', ...
			{
				//for (size_t a=0; a<= i; a++)
				if (matrix[x][y + i] == '.')
					possible_word += '?';
				else
					possible_word += matrix[x][y + i];

				words.push_back(possible_word);
			}


			break;
		}

		case 'H':
		{
			if (matrix[x][y] != '.')
				possible_word += matrix[x][y];


			for (size_t i = 1; matrix[x+i][y] != '#' && (x + i) < columns - 1; i++) //scan all possibilitis like 'w?', 'w??', ...
			{
				//for (size_t a=0; a<= i; a++)
				if (matrix[x+i][y] == '.')
					possible_word += '?';
				else
					possible_word += matrix[x+i][y];

				words.push_back(possible_word);
			}


			break;
		}
		}

		return words;
	}
	else
		cout << "Invalid position \n \n";

}
