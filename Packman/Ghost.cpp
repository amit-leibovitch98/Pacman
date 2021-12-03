#include "Ghost.h"

Ghost::Ghost(const Ghost& other) : Creature(other)
{
	run_over_breadcramp = other.run_over_breadcramp;
}

Ghost& Ghost::operator=(const Ghost& other)
{
	if (this != &other)
	{
		Creature::operator=(other);
		run_over_breadcramp = other.run_over_breadcramp;
	}
	return *this;
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

bool Ghost::getRunOverBreadcramp()
{
	return run_over_breadcramp;
}

void Ghost::setRunOverBreadcramp(bool _run_over_breadcramp)
{
	run_over_breadcramp = _run_over_breadcramp;
}