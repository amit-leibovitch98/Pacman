#pragma once
#include "Ghost.h"
#include <vector>
#include <queue>
#include "Board.h"

class Ghost;
class Location;
class Board;

//base class
class GhostMoveStrategy
{
protected:
	vector<Ghost> ghosts;
	Location pacmanLocation;
	Board* board;
public:
	GhostMoveStrategy(vector<Ghost> _ghosts, Location pacmanLocation, Board* _board) :ghosts(_ghosts), pacmanLocation(pacmanLocation), board(_board)
	{
		for (int i = 0; i < _ghosts.size(); i++)
			_ghosts.push_back(ghosts[i]);

	};

	virtual ~GhostMoveStrategy() {};
	virtual void moveAlghorithm(Ghost& ghost, int countPaces) = 0;
	virtual bool isValidSquare(int x, int y);
	virtual void BFS(Location& s, int i, int j, Ghost& ghost);


	Location& getPacmanLocation()
	{
		return pacmanLocation;
	}

};

//for best level
class GhostMoveStrategyA : public GhostMoveStrategy
{

public:
	GhostMoveStrategyA(Location pacmanLocation, Board* _board) :GhostMoveStrategy(ghosts, pacmanLocation, _board) {};
	void moveAlghorithm(Ghost& ghost, int countPaces);

};

//for good level
class GhostMoveStrategyB : public GhostMoveStrategy
{

public:
	GhostMoveStrategyB(Location pacmanLocation, Board* _board) :GhostMoveStrategy(ghosts, pacmanLocation, _board) {};
	void moveAlghorithm(Ghost& ghost, int countPaces);
};

//for novice level
class GhostMoveStrategyC : public GhostMoveStrategy
{

public:
	GhostMoveStrategyC(Location pacmanLocation, Board* _board) :GhostMoveStrategy(ghosts, pacmanLocation, _board) {};
	void moveAlghorithm(Ghost& ghost, int countPaces);
};