#pragma once

#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include <fstream>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using std::cout;

class Board
{
private:
	const int MAX_BOARD_WIDTH = 80;
	const int MAX_BOARD_HIGHT = 22;
	int actual_board_width;
	int actual_board_hight;
	vector<string> board;
	Location ampersand_loc;
	int kindOfGame;
	const char empty_spot = ' ';
	int score;
	int const BREADCRAMPS_NUM = 1064;
	const char breadcramp_character = '.';
	const char wall_caracter = '#';
	const char magic_tunnel_character = '|';
	const char data_start = '&';



public:
	Board(int _kindOfGame) :score(0), board({}),kindOfGame(_kindOfGame) {};
	void initBoard(ifstream& board_file);
	int getScore();
	char getBreadcrampCharacter();
	char getEmptyspot();
	char getWallCharacter();
	char getMagicTunnelCharacter();
	void setScore(int _score);
	int getBREADCRAMPS_NUM();
	Location getAmpersandLocation();
	void setBoardWidth(ifstream& board_file);
	void setBoardHight(ifstream& board_file);
	int getBoardWidth();
	int getBoardHight();
	vector<string>& getBoard() {
		return board;
	}

	//----------------------------------------------------------------------------------------------
	void fileToMatrix(ifstream& board_file, char ghost_character, Pacman& pacman, vector<Ghost>& ghosts);
	void printGhost(Ghost ghost, bool COLORS);
	void printPacman(Pacman pacman, bool COLORS);
	void printFruit(Fruit fruit, bool COLORS);
	void printBoardEndLine(Pacman pacman, bool COLORS);
	void printBoard(Pacman pacman, vector<Ghost>& ghosts, bool COLORS);
	//void clearScreen();
	//----------------------------------------------------------------------------------------------
	void moveGhost(Ghost& ghosts, Pacman pacman, bool COLORS);
	void movePacman(Pacman& pacman, bool COLORS);
	void moveFruit(Fruit& fruit, vector<Ghost> ghosts, Location pacmanLocation, bool COLORS);
	void magicTunnelCase(Pacman& pacman);
	bool outOfRange(int x, int y);
	void gotoxy(Location location);

};
