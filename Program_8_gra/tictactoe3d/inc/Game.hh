#pragma once

class Game
{
  bool _firstPlayer;
  int _fields[64]; // 0 - no move, 1 - player 1, 2 - player 2
 
public:
  Game();
  int getResult(); // check if someone won; 0 - game is running, 1,2 - one's player victory, 3 - draw
  bool makeMove(int fieldId); // true - movement was available; false - movement was forbidden
  void resetTable(); // reset state of table
  void drawTable(); // drawing table with values of fields
  int getPlayer();

  void undoMove(int fieldId);
  int min_max(int player,int depth);
  int getBestMove(int &bestMove, int depth);
};
