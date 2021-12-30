#pragma once
 
#include "Load.h"


class Silent :public Load {
public:
	Silent(bool color) : Load(color,3) {};
	void start();
};