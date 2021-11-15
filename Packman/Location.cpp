#include "Location.h"


Location::Location(const Location& other)
{
	x = other.x;
	y = other.y;
}

Location& Location::operator=(const Location& other)
{
	if (this != &other) {
		x = other.x;
		y = other.y;
	}
	return *this;
}

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

bool Location::isEqual(Location other)
{
	bool ans = false;
	if (x == other.getX()) {
		if (y == other.x) {
			ans = true;
		}
	}
	return ans;
}


void Location::move(diraction _diraction)
{
	if (_diraction == RIGHT)
	{
		moveRight();
	}
	else if (_diraction == LEFT)
	{
		moveLeft();
	}
	else if (_diraction == UP)
	{
		moveUp();
	}
	else if (_diraction == DOWN)
	{
		moveDown();
	}
	else //esc
		pauseGame();
}

void Location::moveDown()
{
	setX(getX() + 1);
}

void Location::moveUp()
{
	setX(getX() - 1);
}

void Location::moveLeft()
{
	setY(getY() - 1);
}

void Location::moveRight()
{
	//if board[getx+1, gety] != wall
	setY(getY() + 1);
	//else
}

void Location::pauseGame()
{

	cout << "Game paused, press ESC again to continue" << endl;
	while (_getch() != 27) {

	}
}

