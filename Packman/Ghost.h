#pragma once
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Location.h"

class Ghost
{
private:

	Location location;
	diraction currDiraction;
	bool run_over_breadcramp;
	const char character;

public:
	Ghost(Location _location, diraction _currDiraction, bool _run_over_breadcramp = true) :location(_location), currDiraction(_currDiraction), character('$'), run_over_breadcramp(_run_over_breadcramp) {};
	Ghost (const Ghost& other);
	Ghost& operator=(const Ghost& other);
	void setLocation(Location _location);
	Location getLocation();	
	char getCharacter();
	bool getRunOverBreadcramp();
	void setRunOverBreadcramp(bool _run_over_breadcramp);
	void setCurrDiraction(diraction _currDiraction);
	diraction getCurrDiraction();
	void ghostMoveDecider();

};