#include "stdafx.h"
#include "board.h"
#include "dictionary.h"

using namespace std;

// -------------- Function prototypes -------------- // 

void Option1_createpuzzle();

int main()
{
	//Board b1;

	// ================= INTERFACE ================= //
	cout << "CROSSWORDS PUZZLE CREATOR " << endl;
	cout << "================================================" << endl << endl;
	cout << "INSTRUCTIONS: " << endl;
	cout << "Position ( LCD / CTRL-Z = stop )" << endl;
	cout << "LCD stands for Line Column and Direction" << endl << endl;
	cout << "------------------------------------------------" << endl << endl;

	menu();

	return 0;
}

void menu() // The user enters an option
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
		break;

	case 0:
		break;

	default:
		cout << "Option is invalid" << endl;
		cout << "Please enter a valid option" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
	}
}

void Option1_createpuzzle()
{
	cout << "------------------------------------------------" << endl;
	cout << "CREATE PUZZLE " << endl;
	cout << "------------------------------------------------" << endl;

	cout << "Dictionary file name ? ";
	string filename;
	getline(cin, filename);
	Dictionary d1(filename);

	// CONTINUE .....

}