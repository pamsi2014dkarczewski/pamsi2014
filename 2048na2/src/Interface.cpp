#include "Interface.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>
Interface::Interface()
{
}
void Interface::CPUmove(int lvl)
{
	if(lvl==0)
		return;
	else if(lvl==1)
	{
		while(!_game.makeMove(rand()%16));
	}
	else if(lvl==2)
	{
		while(!_game.makeMove(rand()%16,2+2*(rand()%2)));
	}
	else 
	{
		//miejsce na implementacje Twojego algorytmu
		//przykladowy wybor ruchu:
		//int bestMove;
		//_game.getBestMoveValue(bestMove);
		//_game.makeMove(bestMove);
	}
}
void Interface::startNewGame(int firstCPU, int secondCPU)
{
	_game.resetTable();
	_firstCPU = firstCPU;
	_secondCPU = secondCPU;
	int score=0;
	while(_game.getResult(score) == 0)
	{
		printGameTable();
		std::cout << _game.getPlayer() << " player's turn";
		if((_game.getPlayer()==1) && (_firstCPU > 0))
		{
			CPUmove(_firstCPU);
		}
		else if((_game.getPlayer()==2) && (_secondCPU >0 ))
		{
			CPUmove(_secondCPU);
		}
		else // ruch gracza typu HUMAN
		{
			if(_game.getPlayer()==2)
			{	//zwykle 2048
				while(true)
				{
					std::cout << std::endl;
					unsigned char direction;
					std::cout << "choose direction [l/r/u/d] (left/right/up/down): " << std::endl;
					std::cin >> direction;
					int level1;
					switch(direction)
					{
					case 'l': level1 = 0;
						break;
					case 'd': level1 = 1;
						break;
					case 'r': level1 = 2;
						break;
					case 'u': level1 = 3;
						break;
					default: level1 = 0;
					}
					if(!_game.makeMove(level1))
					{
						std::cout << "An impossible move! " << std::endl;
					}
					else
					{
						break;
					}
				}
			}
			else
			if(_game.getPlayer()==1)
			{
				while(true)
				{
					// wstawienie 2/4 w wybrane pole
					std::cout << std::endl;
					unsigned char row, column, number;
					std::cout << "choose level [2/4]: " << std::endl;
					std::cin >> number;
					std::cout << "choose row [q-r]: " << std::endl;
					std::cin >> row;
					std::cout << "choose column [a-f]: " << std::endl;
					std::cin >> column;
					int level1, level2;
					switch(row)
					{
					case 'q': level1 = 0;
						break;
					case 'w': level1 = 1;
						break;
					case 'e': level1 = 2;
						break;
					case 'r': level1 = 3;
						break;
					default: level1 = 0;
					}
					switch(column)
					{
					case 'a': level2 = 0;
						break;
					case 's': level2 = 1;
						break;
					case 'd': level2 = 2;
						break;
					case 'f': level2 = 3;
						break;
					default: level2 = 0;
					}
					int nr = 2;
					if(number=='4') nr=4;
					if(!_game.makeMove(level1*4+level2,nr))
					{
						std::cout << "An impossible move! " << std::endl;
					}
					else
					{
						break;
					}
				}
			}
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
	_game.drawTable();
	std::cout << std::endl;	
	std::cout << "game status: ";
	int score = 0;
	switch(_game.getResult(score))
	{
	case 0: std::cout << "Game is running";
		break;
	case 1: std::cout << "Game over! Score\t" << score;
	}		
	std::cout << std::endl;	
}