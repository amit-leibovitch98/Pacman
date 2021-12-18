#pragma once
#include "Ghost.h"
#include <vector>
#include <queue>
#include "Board.h"

class Location;
class Board;

//base class
class GhostMoveStrategy {
protected:
	Ghost* ghost;
	Location pacmanLocation;
	Board* board;
public:
	GhostMoveStrategy(Location pacmanLocation, Board* _board) :pacmanLocation(pacmanLocation), board(_board) {};
	virtual ~GhostMoveStrategy() {};
	virtual void moveAlghorithm(Ghost& ghost, int countPaces, int board_width, int board_hight) = 0;
	virtual bool isValidSquare(int x, int y);
	virtual void BFS(Location& s, int i, int j, Ghost& ghost);
	Ghost* getGhost()
	{
		return ghost;
	}
	Location& getPacmanLocation()
	{
		return pacmanLocation;
	}
	Board* getBoard() {
		return board;
	}

};

//for best level

class GhostMoveStrategyA : public GhostMoveStrategy {

public:
	GhostMoveStrategyA(Location pacmanLocation, Board* _board) :GhostMoveStrategy(pacmanLocation, _board) {};
	void moveAlghorithm(Ghost& ghost, int countPaces, int board_width, int board_hight);

};

//for good level
class GhostMoveStrategyB : public GhostMoveStrategy {

public:
	GhostMoveStrategyB(Location pacmanLocation, Board* _board) :GhostMoveStrategy(pacmanLocation, _board) {};
	void moveAlghorithm(Ghost& ghost, int countPaces, int board_width, int board_hight);
};

//for novice level
class GhostMoveStrategyC : public GhostMoveStrategy {

public:
	GhostMoveStrategyC(Location pacmanLocation, Board* _board) :GhostMoveStrategy(pacmanLocation, _board) {};
	void moveAlghorithm(Ghost& ghost, int countPaces, int board_width, int board_hight);
};