#pragma once

#include "Location.h"

class Pacman
{
	Location location;
	const char character; //=@
	int lives;

public:
	Pacman() :location((40, 11)), lives(3), character('@') {};
	Pacman(const Pacman& other);
	Pacman& operator=(const Pacman& other);
	void setLocation(Location _location);
	Location getLocation();
	void setLives(int _lives);
	int getLives();
	char getCharacter();
	void liveDedaction();
	void initPacmanLocation();

};
