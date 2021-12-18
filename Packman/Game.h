#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <Windows.h>
#include <conio.h>
#include <vector>
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
	Game(bool colors) : COLORS(colors), pacman(), inProgress(true), fruit(Location::Location(1, 1)), strategy(nullptr), ghosts({}), board({}) {}
	~Game() { delete strategy; };
	Pacman getPacman();
	void setPacman(Pacman _pacman);
	int getGhostCount();
	void setInProgress(bool _inProgress);
	bool getInProgress();
	void randomFruitLocation();
	void run(string file_name);
	void start();
	void printInstruction();
	void printMenu();
	void caseCollisionGhosts();
	bool caseCollisionPacman();
	diraction caster(char ch);
	void checkGameStatus();
};