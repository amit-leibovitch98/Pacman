#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

enum diraction {RIGHT = 'a', LEFT = 'd', UP = 'w', DOWN = 'x', ESC = 27, STAY = 's' };

class Location
{
	int x;
	int y;

public:

	Location(int _x = 0, int _y = 0) : x(_x), y(_y) {};
	Location(const Location& other);
	Location& operator=(const Location& other);
	void setX(int _x);
	void setY(int _y);
	int getX();
	int getY();
	void move(char diraction);
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	bool isEqual(Location other);
	void pauseGame();
};