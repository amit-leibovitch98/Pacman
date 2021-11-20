#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <conio.h>
#include <windows.h>
#include "Board.h"


using namespace std;

class Game
{
	Pacman pacman;
	static const int GHOSTS_COUNT = 2;
	Ghost ghosts[GHOSTS_COUNT];
	Board board;
	bool inProgress;
	diraction lastStep;

public:

	Game() : pacman(), ghosts{ {{2,3},UP},{{12,69},DOWN} }, board(), inProgress(true) {};
	Pacman getPacman();
	void setPacman(Pacman _pacman);
	int getGhostCount();
	void setInProgress(bool _inProgress);
	bool getInProgress();
	
	void run();
	void start();
	//void printInstruction();
	//void exit();
	void move();
	void caseCollisionGhosts();
	bool caseCollisionPacman();
	diraction caster(char ch);
	void checkGameStatus();
	//void caseCollisionPacman();
};