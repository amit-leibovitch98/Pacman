#pragma once
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Creature.h"

class Fruit : public Creature 
{
	bool meetGhost = false;
	bool meetPacman = false;
public:
	Fruit();
	Fruit(Location& _location);
	void move();
};