#pragma once
#include "Ghost.h"

class Ghost;
class Location;

//base class
class GhostMoveStrategy 
{
	Ghost* ghost;
	Location* pacmanLocation;
public:
	GhostMoveStrategy(Ghost* ghost, Location* pacmanLocation) :ghost(ghost), pacmanLocation(pacmanLocation) {};
	virtual ~GhostMoveStrategy() {};
	virtual void moveAlghorithm() = 0;
};

//for best level
class GhostMoveStrategyA : public GhostMoveStrategy
{
	Ghost* ghost;
	Location* pacmanLocation;
public:
	GhostMoveStrategyA(Ghost* ghost, Location* pacmanLocation) :GhostMoveStrategy(ghost, pacmanLocation) {};
	void moveAlghorithm();
};

//for good level
class GhostMoveStrategyB : public GhostMoveStrategy 
{
	Ghost* ghost;
	Location* pacmanLocation;
public:
	GhostMoveStrategyB(Ghost* ghost, Location* pacmanLocation) :GhostMoveStrategy(ghost, pacmanLocation) {};
	void moveAlghorithm();
};

//for novice level
class GhostMoveStrategyC : public GhostMoveStrategy 
{
	Ghost* ghost;
	Location* pacmanLocation;
public:
	GhostMoveStrategyC(Ghost* ghost, Location* pacmanLocation) :GhostMoveStrategy(ghost, pacmanLocation) {};
	void moveAlghorithm();
};