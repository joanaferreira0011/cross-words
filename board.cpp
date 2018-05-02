#include "stdafx.h"
#include "board.h"
#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib> 
#include <windows.h> 

using namespace std;

#define LIGHTRED 12
#define LIGHTGRAY 7 
#define BLACK 0

// COLOR
void setcolor(unsigned int color) 
{ HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);   
SetConsoleTextAttribute(hcon, color); }

void setcolor(unsigned int color, unsigned int background_color) 
{ HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);   
if (background_color == BLACK)     
SetConsoleTextAttribute(hCon, color);   
else     SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED); }


Board::Board(string l, string c)
{
	lines = stoi(l, nullptr, 10);
	columns = stoi(c, nullptr, 10);

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
		char letter = 'a' + i;
		name_lines[i] = letter;
	}

	// NAME COLUMNS
	name_columns.resize(columns);


	for (size_t i = 0; i < name_columns.size(); i++)
	{
		char letter = 'A' + i;
		name_columns[i] = letter;
	}

}

Board::Board(string l, string c)
{
	
	lines = stoi(l, nullptr, 10);
	columns = stoi(c, nullptr, 10);

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
		char letter = 'a' + i;
		name_lines[i] = letter;
	}

	// NAME COLUMNS
	name_columns.resize(columns);


	for (size_t i = 0; i < name_columns.size(); i++)
	{
		char letter = 'A' + i;
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
	cout << endl;
}

bool Board::addword(string position, string word)
{
	//check if valid input
	if (position.length() == 3 && isupper(position[0]) && !(isupper(position[1])) && (toupper(position[2]) == 'V' || toupper(position[2]) == 'H'))
	{
		int x = position[0] - 'A';
		int y = position[1] - 'a';
		char orientation = position[2];
		transform(word.begin(), word.end(), word.begin(), toupper); //transform to uppercase


		//if (d.validword(word))
		if (true)
		{
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

					all_words.push_back(word); //add word to vector
					return true;
				}
				else
				{
					cout << "Can not fit that word\n";
					return false;
				}


			}

			case 'V':
			{
				if (check_V(word, y, x))
				{
					matrix[y][x-1] = '#';
					matrix[y][x + word.length()] = '#';
					size_t i = 0;
					while (i < word.length())
					{
						matrix[y][x+i] = word.at(i);
				
						i++;
					}

					all_words.push_back(word); //add word to vector
					return true;
				}
				else
				{
					cout << "Cannot fit that word\n";
					return false;
				}
			}
			}
		}
		else
		{
			cout << "Word not found in the dictionary";
			return false;
		}
	}
	else
	{
		cout << "Invalid input\n";
		return false;
	}

}