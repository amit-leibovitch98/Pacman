#include "Location.h"

Location::Location(int _x=0, int _y=0) : x(_x), y(_y) {}

void Location::setX(int _x)
{
	x = _x;
}

void Location::setY(int _y)
{
	y = _y;
}

int Location::getX()
{
	return x;
}

int Location::getY()
{
	return y;
}

void Location::move(char diraction)
{
	if (diraction == RIGHT)
	{
		moveRight();
	}
	else if (diraction == LEFT)
	{
		moveLeft();
	}
	else if (diraction == UP)
	{
		moveUp();
	}
	else if (diraction == DOWN)
	{
		moveDown();
	}
	else //esc
		pauseGame();
}

void Location::moveRight()
{
	setY(getY() + 1);
}

void Location::moveLeft()
{
	setY(getY() - 1);
}

void Location::moveUp()
{
	setX(getX() - 1);
}

void Location::moveDown()
{
	//if board[getx+1, gety] != wall
	setX(getX() + 1);
	//else
}

