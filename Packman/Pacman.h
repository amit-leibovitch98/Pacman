#pragma once
#include "Creature.h"

class Pacman : public Creature
{

	int lives;

public:
	Pacman() :lives(3), Creature(233, { 11,40 }) {};
	Pacman(const Pacman& other);
	Pacman& operator=(const Pacman& other);
	void setLives(int _lives);
	void initPacmanLocation();
	int getLives();
	void liveDedaction();
	void move(diraction _diraction);

};
