#include "stdafx.h"
#include "board.h"
#include "dictionary.h"
#include "cwcreator.h"
#include <algorithm>
#include <fstream>
#include <sstream>

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
		create_puzzle();
		break;

	case 2:
		resume_puzzle();
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

void cwcreator::create_puzzle()
{
	cout << "------------------------------------------------" << endl;
	cout << "CREATE PUZZLE " << endl;
	cout << "------------------------------------------------" << endl;

	cout << "Dictionary file name ? ";

	cin >> dictionaryname;

	dictionary = Dictionary (dictionaryname);

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
	
    board = Board (line, column);
	board.show();

	update_board(board, dictionary);

}

void cwcreator::update_board(Board boardname, Dictionary dictionaryname)
{
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
				boardname.remove_word(position); // Remove Word
			else if (word == "?")
			{
				vector<string> thewords = boardname.get_wildcard(position);
				dictionaryname.print_matches(thewords);
			}
			else if (dictionaryname.validword(word)) // Is valid?
			{
				if (boardname.is_word_in_board(word))
					std::cout << "That word is already on the board \n";
				else
					boardname.addword(position, word); // Add Word
			}
			else cout << "The word is not in the dictionary or you entered an invalid position" << endl;
			boardname.show();
			cout << endl;
		}
		else
		{

			valid = false;

			string option;

			//question_is_over();
			
			while (option != "no" && option != "yes") {
				cin.clear();
				cout << "You want to save the board? (yes / no) ";
				cin >> option;
				if (option == "yes")
					save_board(boardname);
				else if (option == "no")
					exit(1);
				else if (option != "no")
					cerr << "Insert a valid option." << endl;
			}
		}

	} while (valid);

}

void cwcreator::resume_puzzle()
{
	cout << "------------------------------------------------" << endl;
	cout << "RESUME PUZZLE " << endl;
	cout << "------------------------------------------------" << endl;
	
	ifstream boardfile;

	string boardfilename, dictionaryfilename, line;
	int lines = 1;
	int columns = 0;

	cout << "Enter the board file name you want to change: ";
	cin >> boardfilename;

	//opening file
	boardfile.open(boardfilename);

	
	while (!boardfile.is_open())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "File " << "board" << " not found !\n";
		cout << "Enter the board file name you want to change: ";
		cin >> boardfilename;
		boardfile.open(boardfilename);
	}

	getline(boardfile,dictionaryfilename);
	Dictionary dictionary1(dictionaryfilename);

	getline(boardfile, line); // Skip empty line

	// Count the columns

	getline(boardfile, line) && line != "";
	
	string strings = " ";
	for (size_t i = 0; i < line.size(); i++)
	{
		strings[0] = line[i];
		if (strings != " ")
			columns++;
	}

	// Count the lines

	while (getline(boardfile, line) && line != "")
		lines++;

	Board board1(lines, columns);
	while (getline(boardfile, line))
	{
		if (line != "")
			board1.addword(line.substr(0, line.find(' ')), line.substr(line.find(' ') + 1, line.size() - 1));
	}
	
	boardfile.close();
	board1.show();
	
	// ---- The same as the create puzzle function --- //
	cout << "Dictionary file name ? ";

	cin >> dictionaryname;

	dictionary1 = Dictionary(dictionaryname);	

	update_board(board1, dictionary1);
}

// Ask the user if you have finished 
// and fill in the blanks
// save the board in a text file
void cwcreator::question_is_over(Board boardname)
{
	string option;
	
	do
	{
		cout << "Finished the board (yes / no)?";
		cin >> option;

		if (option == "yes")
		{
			boardname.fill_finished();
			//bool valid = 
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
void cwcreator::save_board(Board boardname)
{
	string option;
	ofstream outputstream;
	static unsigned int boardnumber = 0;
	boardnumber++;

	stringstream filenameboard;
	filenameboard << setw(3) << setfill('0') << boardnumber;
	string filename = "b" + filenameboard.str() + ".txt";

	cout << "Save file to " << filename << endl;

	//Prints the dictionary name on the first line
	//Save to board file on the third line
	//Prints a list of words that have been placed on the board with their position
	boardname.printboard(filename,dictionaryname);

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
