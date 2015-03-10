#include "Game.h"
#include "Interface.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int main(int argc, char* argv[])
{
	srand(time(NULL));
	int sizeBoard = 6;
	Interface i(sizeBoard);
	i.startNewGame(0, 1); // rozpoczyna grê z 1 graczem komputerowym (gracz typu random) oraz z 1 ludzkim graczem
	return 0;
	
}