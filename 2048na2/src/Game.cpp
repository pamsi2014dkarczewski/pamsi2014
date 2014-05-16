#include "Game.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
Game::Game()
{
	for(int i=0;i<64;i++)
	{
		_fields[i] = 0;
	}
	_firstPlayer = true;
	_score = 0;
}
int Game::getPlayer()
{
	return _firstPlayer?1:2;
}
int Game::getResult(int &score)
{
	score = _score;
	int holes = 16;
	for(int i=0; i<16; i++)
	{
		if(_fields[i]!=0) holes--;
	}
	if(holes==0) 
	{
		if(getPlayer()==1)
			return 1;
		else
		{
			bool possibilityToMove = false;
			for(int i=0;i<4;i++)
			{
				for(int j=0;j<3;j++)
				{
					if(_fields[4*i+j]==_fields[4*i+j+1])
						possibilityToMove = true;
					if(_fields[i+4*j]==_fields[i+4*(j+1)])
						possibilityToMove = true;
				}
			}
			if(!possibilityToMove)
				return 1;
		}
	}
	return 0;
}
bool Game::makeMove(int fieldId, int nr)
{
	if(getPlayer()==2)
	{
		int move = fieldId%4;
		// 0 - left
		// 1 - down
		// 2 - right
		// 3 - up
		bool possibilityToMove = false;
		for(int i=0;i<4;i++)
		{
			int last=-1;
			int count=0;
			int lastVal=0;
			for(int j=0;j<4;j++)
			{
				switch(move)
				{
					case 0:
					{
						if(_fields[4*i+j]!=0)
						{
							if(lastVal==_fields[4*i+j])
							{
								possibilityToMove = true;
							}
							lastVal = _fields[4*i+j];
							last=j;
							count++;
						}
					}
					break;
					case 1:
					{
						if(_fields[i+12-4*j]!=0)
						{
							if(lastVal==_fields[i+12-4*j])
							{
								possibilityToMove = true;
							}
							lastVal = _fields[i+12-4*j];
							last=j;
							count++;
						}
					}
					break;
					case 2:
					{
						if(_fields[4*i+3-j]!=0)
						{
							if(lastVal==_fields[4*i+3-j])
							{
								possibilityToMove = true;
							}
							lastVal = _fields[4*i+3-j];
							last=j;
							count++;
						}
					}
					break;
					case 3:
					{
						if(_fields[i+4*j]!=0)
						{
							if(lastVal==_fields[i+4*j])
							{
								possibilityToMove = true;
							}
							lastVal = _fields[i+4*j];
							last=j;
							count++;
						}
					}
					break;
					
					
				}
			}
			if(count<=last && count > 0)
				possibilityToMove = true;
		}
		if(possibilityToMove)
		{
			switch(move)
				{
					case 0:
					{
						for(int i=0;i<4;i++)
						{
							int pos = 0;
							int last = 0;
							for(int j=0;j<4;j++)
							{
								if(_fields[4*i+j]!=0)
								{
									bool thesame=false;
									int value = _fields[4*i+j];
									if(value==last)
									{
										value = value*2;
										_score+=value;
										thesame = true;
									}
									if(thesame) pos--;
									_fields[4*i+pos]=value;
									if(j!=pos) _fields[4*i+j]=0;
									last=value;
									pos++;
								}
							}
						}
					}
					break;
					
					case 1:
					{
						for(int i=0;i<4;i++)
						{
							int pos = 3;
							
							int last = 0;
							for(int j=3;j>=0;j--)
							{
								if(_fields[i+4*j]!=0)
								{
									bool thesame=false;
									int value = _fields[i+4*j];
									if(value==last)
									{
										value = value*2;
										_score+=value;
										thesame = true;
									}
									if(thesame) pos++;
									_fields[i+4*pos]=value;
									if(j!=pos) _fields[i+4*j]=0;
									last=value;
									pos--;
								}
							}
						}
					}
					break;
					case 2:
					{
						for(int i=0;i<4;i++)
						{
							int pos = 3;
							int last = 0;
							for(int j=3;j>=0;j--)
							{
								if(_fields[4*i+j]!=0)
								{
									bool thesame=false;
									int value = _fields[4*i+j];
									if(value==last)
									{
										value = value*2;
										_score+=value;
										thesame = true;
									}
									if(thesame) pos++;
									_fields[4*i+pos]=value;
									if(j!=pos) _fields[4*i+j]=0;
									last=value;
									pos--;
								}
							}
						}
					}
					break;
					case 3:
					{
						for(int i=0;i<4;i++)
						{
							int pos = 0;
							int last = 0;
							for(int j=0;j<4;j++)
							{
								if(_fields[i+4*j]!=0)
								{
									bool thesame=false;
									int value = _fields[i+4*j];
									if(value==last)
									{
										value = value*2;
										_score+=value;
										thesame = true;
									}
									if(thesame) pos--;
									_fields[i+4*pos]=value;
									if(j!=pos) _fields[i+4*j]=0;
									last=value;
									pos++;
								}
							}
						}
					}
					break;
					
				}
		}
		else
		{
			return false;
		}
	}
	else
	{
		int move = fieldId;
		int number = nr;
		if(_fields[move]!=0)
			return false;
		else _fields[move]=number;
	}
	_firstPlayer = !_firstPlayer;
	return true;
}
void Game::resetTable()
{
	for(int i=0;i<64;i++)
	{
		_fields[i] = 0;
	}
	_firstPlayer = true;
}
void Game::drawTable()
{
	std::cout << "Actual score:\t"<<_score << std::endl;
	std::cout << "\ta \ts \td \tf" << std::endl;
	for(int j=0; j<4; j++)
	{
		switch(j)
		{
		case 0: std::cout << "q\t";
			break;
		case 1: std::cout << "w\t";
			break;
		case 2: std::cout << "e\t";
			break;
		case 3: std::cout << "r\t";
			break;
		}
		for(int k=0; k<4; k++)
		{

			std::cout << _fields[j*4+k] << "\t";
		}
		std::cout << "\n";
	}
}