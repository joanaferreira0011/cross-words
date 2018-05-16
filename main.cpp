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
	cout << "------------------------------------------------" << endl << endl;
	
	cwcreator cwcreator1;
	cwcreator1.menu();
	cwcreator1.usercontinue();

	return 0;
}