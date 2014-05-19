#include "Game.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
Game::Game(int sizeBoard)
{
	_sizeBoard=sizeBoard;
	_fields = new int[(2*sizeBoard+1)*(2*sizeBoard+1)];
	for(int i=0;i<(2*sizeBoard+1)*(2*sizeBoard+1);i++)
	{
		_fields[i] = 0;
	}
	_firstPlayer = true;
}
Game::~Game()
{
	delete[] _fields;
}
int Game::getPlayer()
{
	return _firstPlayer?1:2;
}
int Game::getResult()
{
	for(int player=1;player<3;player++)
	{
		bool existPath = false;
		int numberVertices = _sizeBoard*(_sizeBoard+1);
		
		std::vector<std::map<int,int> > neighbours;
		for(int i=0;i<numberVertices;i++)
		{
			std::map<int,int> mapa;
			neighbours.push_back(mapa);
		}
		for(int i=0;i<_sizeBoard;i++)
		{
			for(int j=0;j<_sizeBoard;j++)
			{
				neighbours[i].insert(std::pair<int,int>(j,j)); neighbours[numberVertices-1-i].insert(std::pair<int,int>(numberVertices-1-j,numberVertices-1-j));//first stage is a full connected component of the network by default 
			}
		}
		for(int i=0; i<(2*_sizeBoard+1)*(2*_sizeBoard+1); i+=2)
		{
			int col, row;
			col = i % (2*_sizeBoard+1);
			row = i/(2*_sizeBoard+1);
			if(col==0 || col == 2*_sizeBoard || row==0 || row== 2*_sizeBoard)
				continue;
			if(_fields[i]==player)
			{
				//push_back to the neighbours list
				if(player==1&&row%2==1)
				{
					neighbours[_sizeBoard*((col-1)/2)+((row-1)/2)][_sizeBoard*((col+1)/2)+((row-1)/2)]=_sizeBoard*((col+1)/2)+((row-1)/2);
					neighbours[_sizeBoard*((col+1)/2)+((row-1)/2)][_sizeBoard*((col-1)/2)+((row-1)/2)]=_sizeBoard*((col-1)/2)+((row-1)/2);
				}
				else if(player==1)
				{
					neighbours[_sizeBoard*((col)/2)+((row-2)/2)][_sizeBoard*((col)/2)+((row)/2)]=_sizeBoard*((col-1)/2)+((row)/2);
					neighbours[_sizeBoard*((col)/2)+((row)/2)][_sizeBoard*((col)/2)+((row-2)/2)]=_sizeBoard*((col)/2)+((row-2)/2);
				}
				else if(col%2==1) // player=2
				{
					neighbours[_sizeBoard*((row-1)/2)+((col-1)/2)][_sizeBoard*((row+1)/2)+((col-1)/2)]=_sizeBoard*((row+1)/2)+((col-1)/2);
					neighbours[_sizeBoard*((row+1)/2)+((col-1)/2)][_sizeBoard*((row-1)/2)+((col-1)/2)]=_sizeBoard*((row-1)/2)+((col-1)/2);
				}
				else
				{
					neighbours[_sizeBoard*((row)/2)+((col)/2)][_sizeBoard*((row)/2)+((col-2)/2)]=_sizeBoard*((row)/2)+((col-2)/2);
					neighbours[_sizeBoard*((row)/2)+((col-2)/2)][_sizeBoard*((row)/2)+((col)/2)]=_sizeBoard*((row)/2)+((col)/2);
				}
			}
		}
		bool change = true;
		int lastCountNeighbours = 0;
		for (std::map<int,int>::iterator it=neighbours[0].begin(); it!=neighbours[0].end(); ++it)
		{
			lastCountNeighbours++;
		}
		while(change==true)
		{
			int countNeighbours = 0;
			change = false;
			for (std::map<int,int>::iterator it=neighbours[0].begin(); it!=neighbours[0].end(); ++it)
			{
				for(std::map<int,int>::iterator it2=neighbours[it->first].begin(); it2!=neighbours[it->first].end(); ++it2)
				{
					neighbours[0][it2->first]=it2->first;
				}
			}
			for (std::map<int,int>::iterator it=neighbours[0].begin(); it!=neighbours[0].end(); ++it)
			{
				countNeighbours++;
			}
			if(countNeighbours != lastCountNeighbours)
			{
				change = true;
				lastCountNeighbours = countNeighbours;
			}
		}
		/* //debug purposes
		for (std::map<int,int>::iterator it=neighbours[0].begin(); it!=neighbours[0].end(); ++it)
			{
				cout << it->first << "\t";
			}
			cout << endl;*/
		if(neighbours[0].find(numberVertices-1)!=neighbours[0].end())
			existPath = true;
		if(existPath)
			return player;
	}
	int holes = _sizeBoard*_sizeBoard+ (_sizeBoard-1)*(_sizeBoard-1);
	int row,col;
	for(int i=0; i<(2*_sizeBoard+1)*(2*_sizeBoard+1); i+=2)
	{
		col = i % (2*_sizeBoard+1);
		row = i/(2*_sizeBoard+1);
		if(col==0 || col == 2*_sizeBoard || row==0 || row== 2*_sizeBoard)
			continue;
		if(_fields[i]!=0) holes--;
	}
	if(holes==0) 
	{
		return 3;
	}
	return 0;
}
int Game::movementToField(int row, int col)
{
	return col+(2*_sizeBoard+1)*row;
}

int Game::pairToId(std::pair<int, int> Pair)
{
	return std::get<1>(Pair)+(2*_sizeBoard+1)*std::get<0>(Pair);
}

bool Game::makeMove(int fieldId)
{
	int row,col;
	col = (fieldId) % (2*_sizeBoard+1);
	row = fieldId/(2*_sizeBoard+1);
	//std::cout << "r/c/d: " << row << "\t" << col << "\t" << direction << "\n"; //just for debug purposes
	if(col==0 || col == 2*_sizeBoard || row==0 || row== 2*_sizeBoard)
		return false;
	if((col+row)%2==1)
		return false;
	std::pair<int,int> pos1, pos2, pos3;
	pos1=std::make_pair(row, col);
	int player = getPlayer();
	switch(player)
	{
		case 1: //up-down player
		{
			if((row%2)==0)
			{
				pos2=std::make_pair(row-1, col);
				pos3=std::make_pair(row+1, col);
			}
			else
			{
				pos2=std::make_pair(row, col-1);
				pos3=std::make_pair(row, col+1);
			}
		}
		break;
		case 2: //left-right player
		{
			if((row%2)==1)
			{
				pos2=std::make_pair(row-1, col);
				pos3=std::make_pair(row+1, col);
			}
			else
			{
				pos2=std::make_pair(row, col-1);
				pos3=std::make_pair(row, col+1);
			}
		}
	}
	
	int id1 = pairToId(pos1);
	int id2 = pairToId(pos2);
	int id3 = pairToId(pos3);	
	{
		if(_fields[id1]!=0)
			return false;
		if(_fields[id2]==3-player)
			return false;
		if(_fields[id3]==3-player)
			return false;
	}
	//return false;
	_fields[pairToId(pos1)]=player;
	_fields[pairToId(pos2)]=player;
	_fields[pairToId(pos3)]=player;
	
	_firstPlayer = !_firstPlayer;
	return true;
}
void Game::resetTable()
{
	for(int i=0;i<(2*_sizeBoard+1)*(2*_sizeBoard+1);i++)
	{
		_fields[i] = 0;
	}
	_firstPlayer = true;
}
void Game::drawTable()
{
	char letter[27]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::cout << "\n\t";
	for(int j=0; j<2*_sizeBoard+1; j++)
	{
		std::cout << letter[j];
	}
	std::cout << std::endl;
	
	for(int j=0; j<2*_sizeBoard+1; j++)
	{
		std::cout << j+1 << "\t";
		for(int k=0; k<2*_sizeBoard+1; k++)
		{
			int value = _fields[j*(2*_sizeBoard+1)+k];
			if((j+k)%2==1)
			{ // dot
				if(value!=0)
					std::cout << value;
				else if((j%2)==0)
					std::cout << '*';
				else
					std::cout << 'o';
			}
			else
			{ // line
				if(value!=0)
				{
					std::cout << value;
				}
				else
				{
					std::cout << " ";
				}
			}
			
		}
		std::cout << "\n";
	}
}
void Game::aboutGame()
{
	std::cout << "about game: one move = one line\n";
	std::cout << "1st player need to connect left-right (o dots)\n";
	std::cout << "before 2nd player will connect up-down (* dots)\n";
	std::cout << "valid moves: only between * * or o o\n";
}