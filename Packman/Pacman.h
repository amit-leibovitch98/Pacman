#pragma once
#include "Creature.h"

class Pacman: public Creature
{

	int lives;

public:
	Pacman() : Creature('@', { 11,40 }) {};
	Pacman(const Pacman& other);
	Pacman& operator=(const Pacman& other);
	void setLives(int _lives);
	int getLives();
	void liveDedaction();
	void move(diraction _diraction);

};