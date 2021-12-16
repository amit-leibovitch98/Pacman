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
void Pacman::initPacmanLocation() {
	getCurrLocation() = Location::Location(11, 40);
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

void Pacman::move(diraction _diraction)
{

	if (_diraction == LEFT)
	{
		getCurrLocation().moveLeft();
	}
	else if (_diraction == RIGHT)
	{
		getCurrLocation().moveRight();
	}
	else if (_diraction == UP)
	{
		getCurrLocation().moveUp();
	}
	else
	{
		getCurrLocation().moveDown();
	}
}