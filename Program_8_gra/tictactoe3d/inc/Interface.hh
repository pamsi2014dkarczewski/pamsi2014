#pragma once
#include "Game.hh"
#include <list>

class Interface
{
  Game _game;
  int _firstCPU; // 0 means Human Player
  int _secondCPU; // 0 means Human Player
public:	
  Interface();
  void startNewGame(int firstCPU, int secondCPU);
  void printGameTable();
  void CPUmove(int lvl);
};
