#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include "Pacman.h"
#include "Location.h"
#include <conio.h>
#include <windows.h>
#include "Ghost.h"

using namespace std;

class Game {
	Pacman pacman;//will defined later
	Ghost* ghosts;
	bool inProgress;

public:
	//think about constructors later

	//function
	Game();
	void setInProgress(bool _inProgress);
	bool getInProgress();
	void run();
	void start();
	void printInstruction();
	void exit();
	void pacmanMove();
	void caseCollisionGhosts();
	char step(char ch);
	bool checkGameStatus();
	void caseCollisionPacman();

};