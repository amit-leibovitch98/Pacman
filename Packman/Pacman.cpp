#include "Pacman.h"

Pacman::Pacman(const Pacman& other) :character('@')
{
	location = other.location;
	lives = other.lives;
}

Pacman& Pacman::operator=(const Pacman& other)
{
	if (this != &other) {
		location = other.location;
		lives = other.lives;
	}
	return *this;
}

void Pacman::initPacmanLocation()
{
	setLocation((40, 11));
}

void Pacman::setLocation(Location _location)
{
	location = _location;
}

Location& Pacman::getLocation()
{
	return location;
}

void Pacman::setLives(int _lives)
{
	lives = _lives;
}

int Pacman::getLives()
{
	return lives;
}

char Pacman::getCharacter()
{
	return '@';
}

void Pacman::liveDedaction()
{
	setLives(getLives() - 1);
}

void Pacman::move(diraction _diraction)
{

	if (_diraction == LEFT)
	{
		location.moveLeft();
	}
	else if (_diraction == RIGHT)
	{
		location.moveRight();

	}
	else if (_diraction == UP)
	{
		location.moveUp();
	}
	else
	{
		location.moveDown();
	}
}

void Pacman::goToStart()
{
	const static Location initLocation(11, 40);
	setLocation(initLocation);
}