#include "Ghost.h"

Ghost::Ghost(const Ghost& other) :character('$')
{
	location = other.location;
	currDiraction = other.currDiraction;
	
}

Ghost& Ghost::operator=(const Ghost& other)
{
	if (this != &other)
	{
		location = other.location;
		currDiraction = other.currDiraction;
		
	}
	return *this;
}

void Ghost::setLocation(Location _location)
{
	location = _location;
}

char Ghost::getCharacter()
{
	return character;
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

void Ghost::ghostMoveDecider()
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

void Ghost::initLocation()
{
	setLocation(initLoc);
}