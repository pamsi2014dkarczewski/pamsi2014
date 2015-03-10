#include "Interface.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>
Interface::Interface(int sizeBoard)
{
	_game = new Game(sizeBoard);
	_sizeBoard = sizeBoard;
}
Interface::~Interface()
{
	delete _game;
}
void Interface::CPUmove(int lvl)
{
	if(lvl==0)
		return;
	else if(lvl==1)
	{
		while(!_game->makeMove(rand()%((2*_sizeBoard+1)*(2*_sizeBoard+1))));
	}
	else 
	{
		//miejsce na implementacje Twojego algorytmu
		//przykladowy wybor ruchu:
		//int bestMove;
		//_game->getBestMoveValue(bestMove);
		//_game->makeMove(bestMove);
	}
}
void Interface::startNewGame(int firstCPU, int secondCPU)
{
	_game->resetTable();
	_game->aboutGame();
	_firstCPU = firstCPU;
	_secondCPU = secondCPU;
	while(_game->getResult() == 0)
	{
		printGameTable();
		std::cout << _game->getPlayer() << " player's turn";
		if((_game->getPlayer()==1) && (_firstCPU > 0))
		{
			CPUmove(_firstCPU);
		}
		else if((_game->getPlayer()==2) && (_secondCPU >0 ))
		{
			CPUmove(_secondCPU);
		}
		else // ruch gracza typu HUMAN
		{
			char letter[27]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			std::cout << std::endl << "choose a point coordinates:\n";
			std::string row;
			unsigned char col;
			std::cout << "[1-" << 2*_sizeBoard+1 << "]: ";
			std:: cin >> row;
			std::cout << "[A-" << letter[2*_sizeBoard] << "]: ";
			std:: cin >> col;
			int x = atoi(row.c_str())-1;
			if(x<0) x=0;
			if(x>2*_sizeBoard+1) x=0;
			if(col < 'A') col = 'A';
			if(col > 'z') col = 'A';
			if(col > 'Z') col = col-32;
			int y = col-'A';
			if(y<0) y=0;
			if(y>2*_sizeBoard+1) y=0;
			_game->makeMove(_game->movementToField(x,y));
		}
	}
	printGameTable();
	std::cout << "Play again? [y/n]" << std::endl;
	char n;
	std::cin >> n;
	if(n=='y') startNewGame(_firstCPU, _secondCPU);
	else std::cout << "Byebye! " << std::endl;
}
void Interface::printGameTable()
{
	_game->drawTable();
	std::cout << std::endl;	
	std::cout << "game status: ";
	switch(_game->getResult())
	{
	case 0: std::cout << "Game is running";
		break;
	case 1: std::cout << "1st Player won";
		break;
	case 2: std::cout << "2nd Player won";
		break;
	case 3: std::cout << "Draw!";
		break;
	default: std::cout << "Unknown status game";
	}		
	std::cout << std::endl;	
}