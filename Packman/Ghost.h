#pragma once
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Location.h"

class Ghost
{
private:

	Location location;
	const Location initLoc;
	//Location currLocation;
	//Location lastLocation;
	diraction currDiraction;
	const char character;

public:
	Ghost(Location _location, diraction _currDiraction) :location(_location), currDiraction(_currDiraction), character('$'), initLoc(_location) {};
	Ghost(const Ghost& other);
	Ghost& operator=(const Ghost& other);
	void setLocation(Location _location);
	Location getLocation();
	char getCharacter();
	void setCurrDiraction(diraction _currDiraction);
	diraction getCurrDiraction();
	void ghostMoveDecider();
	void initLocation();

};