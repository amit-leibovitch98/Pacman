#pragma once
#include "Location.h"

class Creature
{
private:
	Location currLocation;
	Location lastLocation;
	Location initLocation;
	diraction currDiraction;
	char character;

public:
	Creature() = default;
	Creature(Location _location, diraction currDiraction = RIGHT) :currLocation(_location), lastLocation(_location), initLocation(_location) {};
	Creature(char _character, Location _initLocation, Location _lastLocation, Location _currLocation, diraction _currDiraction = RIGHT) :
		currLocation(_currLocation), lastLocation(_lastLocation), initLocation(_initLocation), currDiraction(_currDiraction), character(_character) {};
	Creature(char _character, Location _Location, diraction _currDiraction = RIGHT) :
		currLocation(_Location), lastLocation(_Location), initLocation(_Location), currDiraction(_currDiraction), character(_character) {};
	Creature(const Creature& other);
	Creature& operator=(const Creature& other);
	void setCurrLocation(Location _location);
	Location& getCurrLocation();
	Location getLastLocation();
	void setLastLocation(Location location);
	Location getinitLocation() const;
	char& getCharacter();
	void setCurrDiraction(diraction _currDiraction);
	diraction getCurrDiraction();
};
