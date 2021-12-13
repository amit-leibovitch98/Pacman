#include "Creature.h"

void Creature::setCurrLocation(Location _location)
{
	currLocation = _location;
}
Creature::Creature(const Creature& other) :initLocation(other.initLocation) {
	currLocation = other.currLocation;
	lastLocation = other.lastLocation;
	currDiraction = other.currDiraction;
	character = other.character;
}

Creature& Creature::operator=(const Creature& other)
{
	if (this != &other)
	{
		currLocation = other.currLocation;
		lastLocation = other.lastLocation;
		currDiraction = other.currDiraction;
		character = other.character;
	}
	return *this;
}

Location& Creature::getCurrLocation()
{
	return currLocation;
}

Location Creature::getLastLocation()
{
	return lastLocation;
}

void Creature::setLastLocation(Location location)
{
	lastLocation = location;
}

Location Creature::getinitLocation() const
{
	return initLocation;
}

char& Creature::getCharacter()
{
	return character;
}

void Creature::setCurrDiraction(diraction _currDiraction)
{
	currDiraction = _currDiraction;
}

diraction Creature::getCurrDiraction()
{
	return currDiraction;
}

void Creature::initLocations(Location _location)
{

	initLocation = currLocation = lastLocation = _location;

}
