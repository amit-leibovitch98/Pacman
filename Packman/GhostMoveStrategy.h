#pragma once
#include "Ghost.h"
#include <queue>
#include "Board.h"


class Ghost;
class Location;
class Board;

//base class
class GhostMoveStrategy 
{
	vector<Ghost> ghosts;
	Location pacmanLocation;
	Board* board;
public:
	GhostMoveStrategy(vector<Ghost> _ghosts, Location pacmanLocation, Board* _board) :ghosts(_ghosts), pacmanLocation(pacmanLocation), board(_board) 
	{
		for (int i = 0; i < _ghosts.size(); i++)
			ghosts[i] = _ghosts[i];
	};
	virtual ~GhostMoveStrategy() {};
	virtual void moveAlghorithm(Ghost& ghost) = 0;

	vector<Ghost> getGhost() 
	{
		return ghosts;
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
class GhostMoveStrategyA : public GhostMoveStrategy 
{


public:
	GhostMoveStrategyA(vector<Ghost> ghosts, Location pacmanLocation, Board* _board) :GhostMoveStrategy(ghosts, pacmanLocation, _board) {};
	void moveAlghorithm(Ghost& ghost);
	bool BFS(Location& s, int i, int j, Ghost& ghost);
};

//for good level
class GhostMoveStrategyB : public GhostMoveStrategy 
{

public:
	GhostMoveStrategyB(vector<Ghost> ghosts, Location pacmanLocation, Board* _board) :GhostMoveStrategy(ghosts, pacmanLocation, _board) {};
	void moveAlghorithm(Ghost& ghosts);
};

//for novice level
class GhostMoveStrategyC : public GhostMoveStrategy 
{

public:
	GhostMoveStrategyC(vector<Ghost> ghosts, Location pacmanLocation, Board* _board) :GhostMoveStrategy(ghosts, pacmanLocation, _board) {};
	void moveAlghorithm(Ghost& ghost);
};