#pragma once

#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include <fstream>
#include <vector>
#include <iostream>

class Board
{
private:
	const  int BOARD_WIDTH = 80;
	const  int BOARD_HIGHT = 22;
	vector<vector<char>> board;
	ifstream* board_file;
	int data_start_line;

	const char empty_spot = ' ';
	int score;
	int const BREADCRAMPS_NUM = 1064;
	const char breadcramp_character = '.';
	const char wall_caracter = 178;
	const char magic_tunnel_character = 176; //177
	const char data_start = '&';


public:
	Board() :score(0), board({}) {};
	int getScore();
	char getBreadcrampCharacter();
	char getEmptyspot();
	char getWallCharacter();
	char getMagicTunnelCharacter();
	void setScore(int _score);
	int getBREADCRAMPS_NUM();
	char& getSquareChar(int x, int y);
	void setFile(ifstream* _board_file);
	//----------------------------------------------------------------------------------------------
	void fileToMatrix();
	void printGhost(char ghost_character, bool COLORS);
	void printPacman(char pacman_character, bool COLORS);
	void printBoardEndLine(Pacman pacman, bool COLORS);
	void printBoard(Pacman pacman, Ghost ghosts[], const int ghosts_count, bool COLORS);
	//----------------------------------------------------------------------------------------------
	void moveGhost(int ghost_count, Ghost& ghosts, Pacman pacman, bool COLORS);
	void movePacman(Pacman& pacman, diraction _diraction, bool COLORS);
	void moveFruit(Fruit& fruit, Ghost ghost[], int arrSize, Location pacmanLocation);
	void magicTunnelCase(Pacman& pacman);
	void gotoxy(Location location);

};
