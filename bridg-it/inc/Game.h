#pragma once
#include <utility>

class Game
{
	bool _firstPlayer;
	int _sizeBoard;
    int* _fields; // 0 - no brick, 2^k - brick with 2^k on it, k=1...16
public:
	Game(int sizeBoard);
	~Game();
	int getResult(); // check if someone won; 0 - game is running, 1 - game over
	int movementToField(int row, int col);
	bool makeMove(int fieldId); // true - movement was available; false - movement was forbidden
	void resetTable(); // reset state of table
	void drawTable(); // drawing table with values of fields
	int getPlayer();
	int pairToId(std::pair<int,int> Pair);
	void aboutGame();
	
};