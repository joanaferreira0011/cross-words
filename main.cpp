#include "board.h"
#include "cwcreator.h"
#include "dictionary.h"

int main()
{
	// ================= INTERFACE ================= //
	cout << "CROSSWORDS PUZZLE CREATOR " << endl;
	cout << "================================================" << endl << endl;
	cout << "INSTRUCTIONS: " << endl;
	cout << "Position ( LCD / CTRL-Z = stop )" << endl;
	cout << "LCD stands for Line Column and Direction" << endl << endl;
	cout << "The character '-' removes the word in the position indicated by the user " << endl;
	cout << "The character '?' is given a list of suggested words to the user to insert on the board " << endl;
	cout << "------------------------------------------------" << endl << endl;
	
	cwcreator cwcreator1;
	cwcreator1.menu();
	cwcreator1.usercontinue();

	return 0;
}