#pragma once
 
#include "Load.h"


class Silent :public Load 
{
public:
	Silent() : Load(3) {};
	void start();
	bool compareFiles(string file_name_1, string file_name_2);
	void bigRun(int input);
};