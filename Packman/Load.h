#pragma once
#include <iostream>
#include <stdlib.h>
#include <filesystem>
#include <stdio.h>
#include <time.h> 
#include <conio.h>
#include <windows.h>
#include "Board.h"
#include "StepPair.h"

using namespace std;
namespace fs = std::filesystem;
class Load
{
protected:
	bool COLORS = true;
	vector<string> screen_files;
	vector<StepPair> pacmanSteps;
	vector<StepPair> ghostSteps;
	vector<int> fruitSteps;
	Pacman pacman;
	vector<Ghost> ghosts;
	Board board;
	Fruit fruit;
	bool inProgress;
	bool res = false;
	bool fruitMode = false;
	int countPaces = 0;
	vector<int> deaths = { 0,0,0 };
	int steps_counter;

public:
	Load(bool colors, int kindOfGame) : COLORS(colors), pacman(), inProgress(true), fruit(Location::Location(1, 1)), ghosts({}), board(kindOfGame), screen_files({}) {}
	bool endswith(string file_name, string suffix);
	vector<string>& getScreenFiles() { return screen_files; }
	void restart();
	Pacman getPacman();
	void loadFiles();
	void run(int input);
	virtual void start();
	void steps(string file_name);
	int decode(Creature& creature, diraction dir = STAY);
	bool caseCollisionPacman();
	void checkGameStatus();
	diraction caster(char ch);
	Location& randomLocation();
	string createFileName(int screen);
	void createResultFile(int screen);
	bool compareFiles(string file_name_1, string file_name_2);
};




