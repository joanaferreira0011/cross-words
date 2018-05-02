#include "stdafx.h"
#include "board.h"
#include "dictionary.h"

int main()
{
	Dictionary d1;
	Board b1=Board("20", "20");
	b1.show();
	b1.addword("CbV", "lol");
	b1.show();
	
	b1.addword("AeH", "lol");
	b1.show();
	return 0;
}