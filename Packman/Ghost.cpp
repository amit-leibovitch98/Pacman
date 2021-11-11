#include "Ghost.h"

void Ghost::setLocation(Location _location)
{
	location = _location;
}

Location Ghost::getLocation()
{
	return location;
}

void Ghost::setCurrDiraction(diraction _currDiraction)
{
	currDiraction = _currDiraction;
}

diraction Ghost::getCurrDiraction()
{
	return currDiraction;
}

void Ghost::ghostMove()
{
	//ganarate random number for the position of the ghost:
	// 1 for left, 2 for right, 3 for up, 4 for down

	srand(time(NULL));
	int randomMove = rand() % 4 + 1;

	if (randomMove == 1)
	{
		location.moveLeft();
		setCurrDiraction(LEFT);
	}
	else if (randomMove == 2)
	{
		location.moveRight();
		setCurrDiraction(RIGHT);

	}
	else if (randomMove == 3)
	{
		location.moveUp();
		setCurrDiraction(UP);
	}
	else
	{
		location.moveDown();
		setCurrDiraction(DOWN);
	}

}