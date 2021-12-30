#pragma once
#include "Location.h"

class Creature
{
protected:
	Location currLocation;
	Location lastLocation;
	Location initLocation;
	diraction currDiraction;
	char character;
	int howManySteps = 0;

public:
	Creature() = default;
	Creature(Location _location, diraction _currDiraction = RIGHT) : currDiraction(_currDiraction) { initLocations(_location); }
	Creature(char _character, Location _initLocation, Location _lastLocation, Location _currLocation, diraction _currDiraction = RIGHT) :
		currDiraction(_currDiraction), character(_character) {}
	Creature(char _character, Location _location, diraction _currDiraction = RIGHT) :
		currDiraction(_currDiraction), character(_character) {
		initLocations(_location);
	}
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
	void initLocations(Location _location);
	int getHowManySteps() {
		return howManySteps;
	}
	void setHowManySteps(int many) {
		howManySteps = many;
	}
	virtual void move()=0;
};