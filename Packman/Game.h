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
	bool COLORS = true;
	Pacman pacman;
	static const int GHOSTS_COUNT = 2;
	Ghost ghosts[GHOSTS_COUNT];
	Board board;
	bool inProgress;
	diraction lastStep;

public:

	Game(bool colors) : COLORS(colors), pacman(), ghosts{ {{10,1},UP},{{7,39},DOWN} }, board(), inProgress(true), left_breadcramps(1048) {};
	Pacman getPacman();
	void setPacman(Pacman _pacman);
	int getGhostCount();
	void setInProgress(bool _inProgress);
	bool getInProgress();
	
	void run();
	void start();
	void printInstruction();
	void printMenu();
	void move();
	void caseCollisionGhosts();
	bool caseCollisionPacman();
	diraction caster(char ch);
	void checkGameStatus();
	//void caseCollisionPacman();
};