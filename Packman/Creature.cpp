#include "Creature.h"

void Creature::setCurrLocation(Location _location)
{
	currLocation = _location;
}

Creature& Creature::operator=(const Creature& other)
{
	if (this != &other)
	{
		currLocation = other.currLocation;
		currDiraction = other.currDiraction;
	}
	return *this;
}

Location Creature::getCurrLocation()
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

char Creature::getCharacter()
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