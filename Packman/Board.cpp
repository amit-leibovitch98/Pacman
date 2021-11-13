#include "Board.h"

Board::Board(int _score = 0) :score(0) {}

char Board::getEmptyspot()
{
	return empty_spot;
}

int Board::getScore()
{
	return score;
}

char** Board::getBoard()
{
	return board;
}

void Board::setScore(int _score)
{
	score = _score;
}

void Board::initBoard()
{

}
void Board::printBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HIGHT; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
}

void Board::moveGhost(Ghost ghost, Location lastPos, Location newPos)
{

}

void Board::movePacman(Pacman pacman, Location lastPos, Location newPos)
{
	board[lastPos.getX()][newPos.getY()] = ' ';
	board[lastPos.getX()][newPos.getY()] = pacman.getCharacter();
}