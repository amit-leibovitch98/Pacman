#pragma once
#include "Location.h"
class StepPair
{
private:
	diraction dir;
	int steps_num;

public:
	StepPair(diraction _dir, int _steps_num) : dir(_dir), steps_num (_steps_num) {}
	StepPair() : dir(STAY), steps_num(0) {}
	diraction getDiraction() { return dir; }
	int getStepsNum() { return steps_num; }
};

