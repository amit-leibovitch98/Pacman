#pragma once
#include "Location.h"
#include "Game.h"

class Ghost
{
private:

	Location location;
	diraction currDiraction;

public:

	void setLocation(Location _location);
	Location getLocation();
	void setCurrDiraction(diraction _currDiraction);
	diraction getCurrDiraction();
	void ghostMove();

};