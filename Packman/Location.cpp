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
bool Location::operator==(const Location& other)const {
	if (x != other.x) {
		return false;
	}
	else if (y != other.y) {
		return false;
	}
	return true;
}
bool Location::operator!=(const Location& other)const {
	return !(*this == other);
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
