#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include "Pacman.h"
#include <conio.h>
#include <windows.h>
#include "Board.h"
#include "Ghost.h"

using namespace std;

class Game
{
	Pacman pacman;
	static const int GHOSTS_COUNT = 2;
	Ghost ghosts[GHOSTS_COUNT];
	Board board;
	bool inProgress;
	int left_breadcramps;

public:

	Game() : pacman(), ghosts{ {(0,10),UP},{(39,7),DOWN} }, board(), inProgress(true), left_breadcramps(1048) {};
	Pacman getPacman();
	int getGhostCount();
	void setInProgress(bool _inProgress);
	bool getInProgress();
	void setLeftBreadcramps(int _left_breadcramps);
	int getLeftBreadcramps();
	void run();
	void start();
	void printInstruction();
	void exit();
	void move();
	void caseCollisionGhosts();
	char step(char ch);
	bool checkGameStatus();
	void caseCollisionPacman();
	static void gotoxy(int x, int y);
};