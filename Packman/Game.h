#pragma once

#include <iostream>
#include <stdlib.h>
#include <filesystem>
#include <stdio.h>
#include <time.h> 
#include <conio.h>
#include <windows.h>
#include "Board.h"
#include "GhostMoveStrategy.h"

using namespace std;
namespace fs = std::filesystem;

class GhostMoveStrategy;

class Game
{

protected:
	bool COLORS = true;
	Pacman pacman;
	vector<Ghost> ghosts;
	Board board;
	Fruit fruit;
	bool inProgress;
	bool res = false;
	bool fruitMode = false;
	int countPaces = 1;
	GhostMoveStrategy* strategy;

public:
	Game(bool colors) : COLORS(colors), pacman(), inProgress(true), fruit(Location::Location(1, 1)), strategy(nullptr), ghosts({}), board(1) {}
	~Game() { delete strategy; };

	bool endswith(string file_name);
	vector<string> loadFiles();
	void choseBoard(vector<string> screen_files);
	Pacman getPacman();
	void setPacman(Pacman _pacman);
	int getGhostCount();
	void setInProgress(bool _inProgress);
	bool getInProgress();
	Location& randomLocation();
	void run(string file_name, int input);
	void start();
	void restart();
	void printInstruction();
	int printMenu();
	void printLevels(bool COLORS);
	void caseCollisionGhosts();
	bool caseCollisionPacman();
	diraction caster(char ch);
	void checkGameStatus();
};