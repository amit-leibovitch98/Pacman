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

int Board::getScore()
{
	return score;
}

void Board::setScore(int _score)
{
	score = _score;
}

void Board::setLeftBreadcramps(int _left_breadcramps)
{
	left_breadcramps = _left_breadcramps;
}

int Board::getLeftBreadcramps()
{
	return left_breadcramps;
}

void Board::printBoard(Pacman pacman, Ghost ghosts[], const int ghosts_count)
{
	cout.flush();
	system("cls");

	for (int i = 0; i < BOARD_HIGHT; i++)
	{
		cout << board[i] << endl;
	}
	gotoxy(pacman.getLocation());
	cout << pacman.getCharacter();
	for (int i = 0; i < ghosts_count; i++) {
		gotoxy(ghosts[i].getLocation());
		cout << ghosts[i].getCharacter();
	}

	gotoxy((BOARD_WIDTH, BOARD_HIGHT));
	cout << "Lives: " << pacman.getLives() << " | Score: " << score << endl;
}

void Board::moveGhost(int ghost_count, Ghost ghosts[], Location lastLocation)
{


	for (int i = 0; i < ghost_count; i++)
	{
		gotoxy(lastLocation);
		if (getSquareChar(ghosts[i].getLocation().getX(), ghosts[i].getLocation().getY()) == breadcramp_character) {
			cout << breadcramp_character;
		}
		else if (getSquareChar(ghosts[i].getLocation().getX(), ghosts[i].getLocation().getY()) == wall_caracter) {

			ghosts[i].setLocation(lastLocation);

		}
		else if (getSquareChar(ghosts[i].getLocation().getX(), ghosts[i].getLocation().getY()) == magic_tunnel_character) {
			ghosts[i].setLocation(lastLocation);
		}
		else {
			cout << empty_spot;
		}

		int y = ghosts[i].getLocation().getY();
		int x = ghosts[i].getLocation().getX();

		gotoxy(ghosts[i].getLocation()); //print current location
		cout << ghosts[i].getCharacter();

	}



}

char Board::getSquareChar(int x, int y) {
	return board[x][y];
}

void Board::movePacman(Pacman& pacman, diraction _diraction, Location lastLocation)
{

	gotoxy(lastLocation);


	if (getSquareChar(pacman.getLocation().getX(), pacman.getLocation().getY()) == breadcramp_character)
	{
		score++;
		left_breadcramps--;
		cout << empty_spot;
	}
	else if (getSquareChar(pacman.getLocation().getX(), pacman.getLocation().getY()) == wall_caracter) 
	{

		pacman.setLocation(lastLocation);

	}
	else if (getSquareChar(pacman.getLocation().getX(), pacman.getLocation().getY()) == magic_tunnel_character) 
	{

		if (pacman.getLocation().getX() == 0) {
			//pacman.getLocation().setX(20);
		}
		else {
			//pacman.getLocation().setX(1);
		}
	}

	gotoxy(pacman.getLocation());
	cout << pacman.getCharacter();
	Sleep(200);
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