#pragma once
 
#include "Load.h"

class Silent :public Load 
{
public:
	Silent() : Load(3) {}
	Silent(int pacman_lives) : Load (3, pacman_lives) {}
	void sStart();
	bool compareFiles(string file_name_1, string file_name_2);
	void sRun(int input);
};