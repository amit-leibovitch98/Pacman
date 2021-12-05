#include "Board.h"


char Board::getEmptyspot()
{
	return empty_spot;
}

char Board::getBreadcrampCharacter()
{
	return breadcramp_character;
}

char Board::getMagicTunnelCharacter()
{
	return magic_tunnel_character;
}

char Board::getWallCharacter()
{
	return wall_caracter;
}

int Board::getBREADCRAMPS_NUM()
{
	return BREADCRAMPS_NUM;
}

int Board::getScore()
{
	return score;
}

void Board::setScore(int _score)
{
	score = _score;
}

void Board::printGhost(char ghost_character, bool COLORS)
{
	if (COLORS)
		cout << "\033[3;104;97m" << ghost_character << "\033[0m\t\t";
	else
		cout << ghost_character;
}

void Board::printPacman(char pacman_character, bool COLORS)
{
	if (COLORS)
		cout << "\x1B[93m" << pacman_character << "\033[0m\t\t";
	else
		cout << pacman_character;
}

void Board::printBoardEndLine(Pacman pacman, bool COLORS)
{
	if (COLORS)
		cout << "\x1B[91mLives: " << pacman.getLives() << "\033[0m\t" << "\x1B[92m" << "                                                   Score: " << score << "\033[0m\t" << endl;
	else
		cout << "Lives: " << pacman.getLives() << "                                                   Score: " << score << endl;
}

void Board::printBoard(Pacman pacman, Ghost ghosts[], const int ghosts_count, bool COLORS)
{
	cout.flush();
	system("cls");

	for (int i = 0; i < BOARD_HIGHT; i++)
	{
		cout << board[i] << endl;
	}
	gotoxy(pacman.getinitLocation());
	printPacman(pacman.getCharacter(), COLORS);

	for (int i = 0; i < ghosts_count; i++)
	{
		gotoxy(ghosts[i].getinitLocation());
		printGhost(ghosts[i].getCharacter(), COLORS);
	}

	gotoxy((BOARD_WIDTH, BOARD_HIGHT));
	printBoardEndLine(pacman, COLORS);
}


void Board::moveGhost(int ghost_count, Ghost& ghosts, Pacman pacman, bool COLORS)
{

	gotoxy(ghosts.getLastLocation());
	if (getSquareChar(ghosts.getCurrLocation().getX(), ghosts.getCurrLocation().getY()) == breadcramp_character) {
		cout << breadcramp_character;
	}
	else if (getSquareChar(ghosts.getCurrLocation().getX(), ghosts.getCurrLocation().getY()) == wall_caracter) {

		ghosts.setCurrLocation(ghosts.getLastLocation());

	}
	else if (getSquareChar(ghosts.getCurrLocation().getX(), ghosts.getCurrLocation().getY()) == magic_tunnel_character) {
		ghosts.setCurrLocation(ghosts.getLastLocation());
	}

	else if (getSquareChar(ghosts.getCurrLocation().getX(), ghosts.getCurrLocation().getY()) == empty_spot) {
		cout << empty_spot;
	}

	int y = ghosts.getCurrLocation().getY();
	int x = ghosts.getCurrLocation().getX();

	ghosts.setRunOverBreadcramp(board[x][y] == breadcramp_character); //if the ghost is supposed to run over a breadcramp, ghage the falg to true, alse to false

	gotoxy(ghosts.getCurrLocation()); //print current location
	printGhost(ghosts.getCharacter(), COLORS);
}

char& Board::getSquareChar(int x, int y)
{
	return board[x][y];
}

void Board::movePacman(Pacman& pacman, diraction _diraction, bool COLORS)
{

	gotoxy(pacman.getLastLocation());

	if (getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) == breadcramp_character)
	{
		score++;
		getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) = empty_spot;
		cout << empty_spot;
		gotoxy(pacman.getCurrLocation());
		printPacman(pacman.getCharacter(), COLORS);


	}
	else if (getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) == wall_caracter)
	{

		pacman.setCurrLocation(pacman.getLastLocation());
		gotoxy(pacman.getCurrLocation());
		printPacman(pacman.getCharacter(), COLORS);


	}
	else if (getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) == empty_spot)
	{
		gotoxy(pacman.getCurrLocation());
		printPacman(pacman.getCharacter(), COLORS);

		gotoxy(pacman.getLastLocation());
		cout << empty_spot;
	}
	else if (getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) == magic_tunnel_character)
	{
		gotoxy(pacman.getLastLocation());
		cout << empty_spot;

		magicTunnelCase(pacman);

		gotoxy(pacman.getCurrLocation());
		printPacman(pacman.getCharacter(), COLORS);

	}

	gotoxy((BOARD_WIDTH, BOARD_HIGHT));
	printBoardEndLine(pacman, COLORS);
	Sleep(150);
}

void Board::moveFruit(Fruit& fruit, Ghost ghosts[], int arrSize, Location pacmanLocation) {
	bool specialCases = false;
	gotoxy(fruit.getLastLocation());
	if (pacmanLocation == fruit.getCurrLocation()) {
		specialCases = true;
		cout << empty_spot;
		score = score + (int)fruit.getCharacter();
	}
	else if (getSquareChar(fruit.getCurrLocation().getX(), fruit.getCurrLocation().getY()) == magic_tunnel_character) {
		fruit.move();
	}
	else {
		bool collision = false;
		for (int i = 0; i < arrSize && !collision; i++) {
			if (fruit.getCurrLocation() == ghosts[i].getCurrLocation()) {
				specialCases = true;
				collision = true;
				cout << empty_spot;
				cout << ghosts[i].getCharacter();
			}
		}
	}
	if (!specialCases) {
		gotoxy(fruit.getCurrLocation());
		cout << (int)fruit.getCharacter();
	}


}

void Board::magicTunnelCase(Pacman& pacman)
{
	int x = pacman.getCurrLocation().getX();
	int y = pacman.getCurrLocation().getY();
	int newY;

	if (y == 0)
	{
		newY = BOARD_WIDTH - 4;
	}
	else
	{
		newY = 1;
	}
	Location newLocation(x, newY);
	pacman.setCurrLocation(newLocation);
}

void Board::gotoxy(Location location)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = location.getY();
	dwCursorPosition.Y = location.getX();
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}