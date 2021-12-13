#pragma once

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <time.h> 
#include <conio.h>
#include <vector>
#include <windows.h>
#include "Board.h"
#include "GhostMoveStrategy.h"




using namespace std;

class GhostMoveStrategy;

class Game
{
	bool COLORS = true;
	Pacman pacman;
	vector<Ghost> ghosts;
	Board board;
	Fruit fruit;
	bool inProgress;
	bool fruitMode = false;
	diraction lastStep;
	int countPaces = 1;
	GhostMoveStrategy* strategy;

public:
	Game(bool colors) : COLORS(colors), pacman(), inProgress(true), fruit(Location::Location(1, 1)), strategy(nullptr) { ghosts.empty(); };
	~Game() { delete strategy; };
	Pacman getPacman();
	void setPacman(Pacman _pacman);
	int getGhostCount();
	void setInProgress(bool _inProgress);
	bool getInProgress();
	Location& randomLocation();
	void run(string file_name);
	void start();
	void printInstruction();
	void printMenu();
	void caseCollisionGhosts();
	bool caseCollisionPacman();
	diraction caster(char ch);
	void checkGameStatus();
	void closeFile();

};