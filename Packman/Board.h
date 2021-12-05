#pragma once

#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"


class Board
{
private:
	static const int BOARD_WIDTH = 80;
	static const int BOARD_HIGHT = 22;
	char board[BOARD_HIGHT][BOARD_WIDTH] = {
	"##############################################################################",
	"########........................................................##############",
	"###............######.......................................................##",
	"###.........................................###########....##.....############",
	"#...........#######################..........###################.............#",
	"#.....####..########...................................#............###......#",
	"|...###.............###....###.......#####....#######..##...####..#..........|",
	"#.#.######..###...#######.....####.....##.....#######.......##......####.....#",
	"#.#........##..................#######.##....#######........####..#......#...#",
	"#.######.....###.............##........#...#####.###.####....######..........#",
	"#.........###...######.....#####....... ..................................##.#",
	"#..###.####.....#################............................##.###....###...#",
	"#............................................................................#",
	"##..##.###.........#######..........###...........####.###...........#########",
	"##.###.####.....#################..........######............##.###....#######",
	"#............................................................................#",
	"#################....................................................#########",
	"|.........###...######.....#####.............................................|",
	"#.................#######.....####.....##.....#######.......##......####.....#",
	"#...........##..................#######.......#######........####..#......#..#",
	"#########............................................................#########",
	"##############################################################################"
	};


	const char empty_spot = ' ';
	int score;
	int const BREADCRAMPS_NUM = 1064;
	const char breadcramp_character = '.';
	const char wall_caracter = '#';
	const char magic_tunnel_character = '|';


public:
	Board() :score(0) {};
	int getScore();
	char getBreadcrampCharacter();
	char getEmptyspot();
	char getWallCharacter();
	char getMagicTunnelCharacter();
	void setScore(int _score);
	int getBREADCRAMPS_NUM();
	char& getSquareChar(int x, int y);
	void printGhost(char ghost_character, bool COLORS);
	void printPacman(char pacman_character, bool COLORS);
	void printBoardEndLine(Pacman pacman, bool COLORS);
	void printBoard(Pacman pacman, Ghost ghosts[], const int ghosts_count, bool COLORS);
	void moveGhost(int ghost_count, Ghost& ghosts, Pacman pacman, bool COLORS);
	void movePacman(Pacman& pacman, diraction _diraction, bool COLORS);
	void moveFruit(Fruit& fruit, Ghost ghost[], int arrSize, Location pacmanLocation);
	void magicTunnelCase(Pacman& pacman);
	void gotoxy(Location location);

};
