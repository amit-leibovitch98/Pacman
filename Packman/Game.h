#pragma once

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <time.h> 
#include <conio.h>
#include <windows.h>
#include "Board.h"
#include "GhostMoveStrategy.h"




using namespace std;

class GhostMoveStrategy;

class Game
{
	bool COLORS = true;
	Pacman pacman;
	static const int GHOSTS_COUNT = 2;
	Ghost ghosts[GHOSTS_COUNT];
	Board board;
	Fruit fruit;
	bool inProgress;
	bool fruitMode = false;
	diraction lastStep;
	int countPaces = 1;
	GhostMoveStrategy* strategy;

public:
	Game(bool colors) : COLORS(colors), pacman(), ghosts{ {Location::Location(10,1)} , {Location::Location(7,39)} }, board(), inProgress(true), fruit(Location::Location(1, 1)), strategy(nullptr){};
	~Game()
	{
		delete strategy;
	};
	Pacman getPacman();
	void setPacman(Pacman _pacman);
	int getGhostCount();
	void setInProgress(bool _inProgress);
	bool getInProgress();
	Location& randomLocation();
	void run();
	void start();
	void printInstruction();
	void printMenu();
	void caseCollisionGhosts();
	bool caseCollisionPacman();
	diraction caster(char ch);
	void checkGameStatus();
	void openFile(string file_name);

};