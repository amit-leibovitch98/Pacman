#pragma once

#include "Location.h"

class Pacman
{
	Location currLocation;
	Location lastLocation;
	const Location initLocation;
	const char character; //=@
	int lives;

public:
	Pacman() :currLocation({ 11, 40 }), initLocation({ 11, 40 }), lastLocation({ 11, 40 }), lives(3), character('@') {};
	Pacman(const Pacman& other);
	Pacman& operator=(const Pacman& other);
	void setLocation(Location _location);
	Location getLocation();
	Location getLastLocation();
	void setLastLocation(Location location);
	Location getinitLocation() const;
	void setLives(int _lives);
	int getLives();
	char getCharacter();
	void liveDedaction();
	void initPacmanLocation();
	void move(diraction _diraction);

};