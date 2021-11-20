#include "Pacman.h"

Pacman::Pacman(const Pacman& other) :character('@'), initLocation({ 11,40 })
{
	currLocation = other.currLocation;
	lastLocation = other.lastLocation;
	lives = other.lives;
}

Pacman& Pacman::operator=(const Pacman& other)
{
	if (this != &other) {
		currLocation = other.currLocation;
		lastLocation = other.lastLocation;
		lives = other.lives;
	}
	return *this;
}

void Pacman::initPacmanLocation()
{
	Location location(11, 40);
	setLocation(location);
	setLastLocation(location);

}

void Pacman::setLocation(Location _location)
{
	currLocation = _location;
}
Location Pacman::getLastLocation() {
	return lastLocation;
}
Location Pacman::getinitLocation() const {
	return initLocation;
}
void Pacman::setLastLocation(Location location) {
	lastLocation = location;
}

Location& Pacman::getLocation()
{
	return currLocation;
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
		currLocation.moveLeft();
	}
	else if (_diraction == RIGHT)
	{
		currLocation.moveRight();

	}
	else if (_diraction == UP)
	{
		currLocation.moveUp();
	}
	else
	{
		currLocation.moveDown();
	}
}