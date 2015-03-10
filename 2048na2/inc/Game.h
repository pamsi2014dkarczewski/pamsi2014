#pragma once


class Game
{
	bool _firstPlayer;
    int _fields[16]; // 0 - no brick, 2^k - brick with 2^k on it, k=1...16
	int _score;
public:
	Game();
	int getResult(int &score); // check if someone won; 0 - game is running, 1 - game over
	bool makeMove(int fieldId, int nr = 2); // true - movement was available; false - movement was forbidden
	void resetTable(); // reset state of table
	void drawTable(); // drawing table with values of fields
	int getPlayer();
	
};