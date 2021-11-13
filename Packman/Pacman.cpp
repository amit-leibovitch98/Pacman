#include "Pacman.h"

//test


Pacman::Pacman(Location _location, int _lives = 3, char _character = '@') :location(_location), lives(_lives), character(_character) {}

void Pacman::initPacmanLocation()
{
	setLocation((40, 11));
}

void Pacman::setLocation(Location _location)
{
	location = _location;
}

Location Pacman::getLocation()
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