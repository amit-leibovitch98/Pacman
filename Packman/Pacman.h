#pragma once

#include "Location.h"

class Pacman
{
	Location location;
	const char character; //=@
	int lives;

public:
	Pacman(Location _location, int _lives = 3, char _character = '@');
	void setLocation(Location _location);
	Location getLocation();
	void setLives(int _lives);
	int getLives();
	char getCharacter();
	void liveDedaction();
	void initPacmanLocation();

};
