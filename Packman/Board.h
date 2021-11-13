#pragma once

#include"Game.h"


class Board
{
private:
	static const int BOARD_WIDTH = 40;
	static const int BOARD_HIGHT = 22;
	char board[BOARD_WIDTH][BOARD_HIGHT];
	char empty_spot;
	int score;

public:
	Board(int _score = 0);
	int getScore();
	char getEmptyspot();
	void setScore(int _score);
	char** getBoard();
	void initBoard();
	void printBoard();
	void moveGhost(Ghost ghost, Location lastPos, Location newPos);
	void movePacman(Pacman pacman, Location lastPos, Location newPos);
};
