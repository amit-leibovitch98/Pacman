#pragma once
#include "Ghost.h"
#include <queue>
#include "Board.h"


class Ghost;
class Location;
class Board;

//base class
class GhostMoveStrategy {
	Ghost* ghost;
	Location pacmanLocation;
	Board* board;
public:
	GhostMoveStrategy(Ghost* _ghost, Location pacmanLocation, Board* _board) :ghost(_ghost), pacmanLocation(pacmanLocation), board(_board) {
		ghost[0] = _ghost[0];
		ghost[1] = _ghost[1];
	};
	virtual ~GhostMoveStrategy() {};
	virtual void moveAlghorithm(Ghost& ghost) = 0;
	Ghost* getGhost() {
		return ghost;
	}
	Location& getPacmanLocation() {
		return pacmanLocation;
	}
	Board* getBoard() {
		return board;
	}

};

//for best level
class GhostMoveStrategyA : public GhostMoveStrategy {


public:
	GhostMoveStrategyA(Ghost* ghost, Location pacmanLocation, Board* _board) :GhostMoveStrategy(ghost, pacmanLocation, _board) {};
	void moveAlghorithm(Ghost& ghost);
	bool BFS(Location& s, int i, int j, Ghost& ghost);
};

//for good level
class GhostMoveStrategyB : public GhostMoveStrategy {

public:
	GhostMoveStrategyB(Ghost* ghost, Location pacmanLocation, Board* _board) :GhostMoveStrategy(ghost, pacmanLocation, _board) {};
	void moveAlghorithm(Ghost& ghost);
};

//for novice level
class GhostMoveStrategyC : public GhostMoveStrategy {

public:
	GhostMoveStrategyC(Ghost* ghost, Location pacmanLocation, Board* _board) :GhostMoveStrategy(ghost, pacmanLocation, _board) {};
	void moveAlghorithm(Ghost& ghost);
};