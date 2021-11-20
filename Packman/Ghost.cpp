#include "Ghost.h"

Ghost::Ghost(const Ghost& other) :character('$'), run_over_breadcramp(true), initLocation(other.initLocation)
{
	currLocation = other.currLocation;
	currDiraction = other.currDiraction;
	lastLocation = other.lastLocation;
	run_over_breadcramp = other.run_over_breadcramp;
}

Ghost& Ghost::operator=(const Ghost& other)
{
	if (this != &other)
	{
		currLocation = other.currLocation;
		currDiraction = other.currDiraction;
		run_over_breadcramp = other.run_over_breadcramp;
	}
	return *this;
}

void Ghost::setLocation(Location _location)
{
	currLocation = _location;
}
Location Ghost::getLastLocation() {
	return lastLocation;
}
Location Ghost::getinitLocation() const {
	return initLocation;
}
char Ghost::getCharacter()
{
	return character;
}
void Ghost::setLastLocation(Location location) {
	lastLocation = location;
}

void Ghost::initGhostLocation(int i) {
	if (i == 0) {
		Location location(10, 1);
		setLocation(location);
		setLastLocation(location);
	}
	else {
		Location location(7, 39);
		setLocation(location);
		setLastLocation(location);
	}
}

Location Ghost::getLocation()
{
	return currLocation;
}

bool Ghost::getRunOverBreadcramp()
{
	return run_over_breadcramp;
}

void Ghost::setRunOverBreadcramp(bool _run_over_breadcramp)
{
	run_over_breadcramp = _run_over_breadcramp;
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
		currLocation.moveLeft();
		setCurrDiraction(LEFT);
	}
	else if (randomMove == 2)
	{
		currLocation.moveRight();
		setCurrDiraction(RIGHT);

	}
	else if (randomMove == 3)
	{
		currLocation.moveUp();
		setCurrDiraction(UP);
	}
	else
	{
		currLocation.moveDown();
		setCurrDiraction(DOWN);
	}

}