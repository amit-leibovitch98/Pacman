#pragma once
#include <iostream>
#include <stdlib.h>
#include <filesystem>
#include <stdio.h>
#include <time.h> 
#include <conio.h>
#include <windows.h>
#include "Board.h"


using namespace std;
namespace fs = std::filesystem;
class Load
{
protected:
	bool COLORS = true;
	vector<string> screen_files;
	vector<int> pacmanSteps;
	vector<int> ghostSteps;
	vector<int> fruitSteps;
	Pacman pacman;
	vector<Ghost> ghosts;
	Board board;
	Fruit fruit;
	bool inProgress;
	bool res = false;
	bool fruitMode = false;
	int countPaces = 0;

public:
	Load(bool colors,int kindOfGame) : COLORS(colors), pacman(), inProgress(true), fruit(Location::Location(1, 1)), ghosts({}), board(kindOfGame), screen_files({}) {}
	 ~Load();
    bool endswith(string file_name,string suffix);
	void loadFiles();
	void run(int input);
	virtual void start();
	void steps(string file_name);
	int decode(Creature& creature, char ch);
	bool caseCollisionPacman();
	void checkGameStatus();
};




