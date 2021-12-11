#pragma once
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Creature.h"

class Fruit :public Creature {
	bool meetGhost = false;
	bool meetPacman = false;
public:
	Fruit(Location _location, int _character = 0);
	void setMeetGhost(bool ans);
	void setMeetPacman(bool ans);
	bool getMeetGhost();
	bool getMeetPacman();
	void move();
};