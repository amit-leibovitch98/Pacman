#include "Pacman.h"

Pacman::Pacman(const Pacman& other) :Creature(other)
{
	lives = other.lives;
}

Pacman& Pacman::operator=(const Pacman& other)
{
	if (this != &other)
	{
		Creature::operator=(other);
		lives = other.lives;
	}
	return *this;
}
void Pacman::initPacmanLocation()
{
	lastLocation = currLocation;
	currLocation = initLocation;
}

void Pacman::setLives(int _lives)
{
	lives = _lives;
}

int Pacman::getLives()
{
	return lives;
}

void Pacman::liveDedaction()
{
	setLives(getLives() - 1);
}

void Pacman::move()
{

	if (currDiraction == LEFT)
	{
		getCurrLocation().moveLeft();
	}
	else if (currDiraction == RIGHT)
	{
		getCurrLocation().moveRight();

	}
	else if (currDiraction == UP)
	{
		getCurrLocation().moveUp();
	}
	else
	{
		getCurrLocation().moveDown();
	}
}