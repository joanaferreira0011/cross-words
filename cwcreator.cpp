#include "stdafx.h"
#include "board.h"
#include "dictionary.h"
#include "cwcreator.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

// Will make the entire string in uppercase 
void cwcreator::uppercase_letterscw(string &word)
{
	transform(word.begin(), word.end(), word.begin(), toupper);
}

void cwcreator::menu() // The user enters an option
{
	unsigned int option;
	cout << "OPTIONS: " << endl;
	cout << "1 - Create puzzle" << endl;
	cout << "2 - Resume puzzle" << endl;
	cout << "0 - Exit" << endl << endl;

	cout << "Option ? ";
	cin >> option;

	switch (option)
	{

	case 1:
		Option1_createpuzzle();
		break;

	case 2:
		cout << "falta cenas" << endl;
		break;

	case 0:
		cout << " End of program " << endl;
		exit(1);

	default:
		cout << "Option is invalid" << endl;
		cout << "Please enter a valid option" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		menu();
	}
}

void cwcreator::Option1_createpuzzle()
{
	cout << "------------------------------------------------" << endl;
	cout << "CREATE PUZZLE " << endl;
	cout << "------------------------------------------------" << endl;

	cout << "Dictionary file name ? ";

	cin >> dictionaryname;

	dictionary1 = Dictionary(dictionaryname);

	// Choose the size of the board
	unsigned int line, column;

	cout << "Board size (lines columns) ? ";
	cin >> line >> column;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Enter valid numbers!" << endl;
		cin >> line >> column;
	}


	board1 = Board(line, column);
	board1.show();

	string position, word;
	bool valid = true;

	do
	{

		cout << "Position (LCD / CTRL-Z = stop) ?  ";
		cin >> position;

		if (!cin.eof()) // If not you enter ctrl + z
		{

			cout << "Word ( - = remove / ? = help ) .. ? ";
			cin >> word;

			uppercase_letterscw(word);

			if (word == "-")
				board1.remove_word(position); // Remove Word
			else if (word == "?")
			{
				

				cout << "INCOMPLETO" << endl;
			}
			else if (dictionary1.validword(word)) // Is valid?
				board1.addword(position, word); // Add Word
			else cout << "The word is not in the dictionary or you entered an invalid position" << endl;
			board1.show();
			cout << endl;
		}
		else
		{

			valid = false;

			string option;

			while (option != "no" && option != "yes") {
				cin.clear();
				cout << "You want to save the board? (yes / no) ";
				cin >> option;
				if (option == "yes")
					save_board();
				else if (option == "no")
					exit(1);
				else if (option != "no")
					cerr << "Insert a valid option." << endl;
			}
		}

	} while (valid);
}

void cwcreator::resume_puzzle() // INCOMPLETO
{
	ifstream boardfile;
	ifstream dictionaryfile;

	string boardfilename;

	cout << "Enter the board file you want to change";
	cin >> boardfilename;

	//opening file
	boardfile.open(boardfilename);

	// Open the file; exit program if the file couldn't be opened
	if (!boardfile.is_open())
	{
		cerr << "File " << "board" << " not found !\n";
		exit(1);
	}

	//getline(boardfile, dictionaryfile);

}

// Ask the user if you have finished 
// and fill in the blanks
// save the board in a text file
void cwcreator::question_is_over()
{
	string option;
	Board board;
	do
	{
		cout << "Finished the board (yes / no)?";
		cin >> option;

		if (option == "yes")
		{
			board.fill_finished();
			//  função faz a verificação final
		//	if (true) {
		//	save_board();
		//}
			break;
		}
		else if (option != "no")
			cout << "Invalid option" << endl;

	} while (option != "yes" && option != "no");

}

// Save the board in a text file
void cwcreator::save_board()
{
	string option;
	ofstream outputstream;
	static unsigned int boardnumber = 0;
	boardnumber++;

	ostringstream filenameboard;
	filenameboard << 'b' << setw(3) << setfill('0') << boardnumber << ".txt";
	string filename = filenameboard.str();

	cout << "Save file to " << filename << endl;

	//Prints the dictionary name on the first line
	//Save to board file on the third line
	//Prints a list of words that have been placed on the board with their position
	board1.printboard(filename,dictionaryname);

	//Back to menu?
	usercontinue();
}

// Ask the user if they want to continue
void cwcreator::usercontinue()
{
	char option;
	cin.clear();

	cout << "Do you want to continue? Enter 'Y'es or 'N'o ";
	cin >> option;

	while (cin.fail() || option != 'Y' && option != 'y' && option != 'N' && option != 'n')
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid option " << endl;
		cout << "Do you want to continue? Enter 'Y'es or 'N'o ";
		cin >> option;
	}

	while (option == 'Y' || option == 'y')
	{
		menu();
		cout << "Do you want to continue playing? 'Y'es or 'N'o? ";
		cin >> option;

		while (cin.fail() || option != 'Y' && option != 'y' && option != 'N' && option != 'n')
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid option " << endl;
			cout << "Do you want to continue? Enter 'Y'es or 'N'o ";
			cin >> option;
		}
	}
}
