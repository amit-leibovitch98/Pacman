#pragma once
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Creature.h"

class Ghost : public Creature
{
private:
	bool run_over_breadcramp;

public:
	Ghost(Location _location, bool _run_over_breadcramp = false) :
		Creature('$', _location), run_over_breadcramp(_run_over_breadcramp) {};
	Ghost(const Ghost& other);
	Ghost& operator=(const Ghost& other);
	void initGhostLocation(int i);
	void ghostMoveDecider();
	bool getRunOverBreadcramp();
	void setRunOverBreadcramp(bool _run_over_breadcramp);
};
