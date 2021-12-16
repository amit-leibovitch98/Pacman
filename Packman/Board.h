#pragma once

#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class Board
{
private:
	const int MAX_BOARD_WIDTH = 80;
	const int MAX_BOARD_HIGHT = 22;
	int actual_board_width;
	int actual_board_hight;
	vector<string> board;
	ifstream board_file;
	Location ampersand_loc;


	const char empty_spot = ' ';
	int score;
	int const BREADCRAMPS_NUM = 1064;
	const char breadcramp_character = '.';
	const char wall_caracter = 178;
	const char magic_tunnel_character = 176;
	const char data_start = '&';
	


public:
	Board() :score(0), board({}) {};
	void initBoard();
	int getScore();
	char getBreadcrampCharacter();
	char getEmptyspot();
	char getWallCharacter();
	char getMagicTunnelCharacter();
	void setScore(int _score);
	int getBREADCRAMPS_NUM();
	void openBoardFile(string file_name);
	char& getSquareChar(int x, int y);
	ifstream getFile();
	void setBoardWidth();
	void setBoardHight();
	int getBoardWidth();
	int getBoardHight();

	//----------------------------------------------------------------------------------------------
	void fileToMatrix(char ghost_character, Pacman &pacman, vector<Ghost> &ghosts);
	void printGhost(Ghost ghost, bool COLORS);
	void printPacman(Pacman pacman, bool COLORS);
	void printBoardEndLine(Pacman pacman, bool COLORS);
	void printBoard(Pacman pacman, vector<Ghost> &ghosts, bool COLORS);
	//----------------------------------------------------------------------------------------------
	void moveGhost(Ghost& ghosts, Pacman pacman, bool COLORS);
	void movePacman(Pacman& pacman, diraction _diraction, bool COLORS);
	void moveFruit(Fruit& fruit, vector<Ghost> ghosts, Location pacmanLocation);
	void magicTunnelCase(Pacman& pacman);
	void gotoxy(Location location);

};
