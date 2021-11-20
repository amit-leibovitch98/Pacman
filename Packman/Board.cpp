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

void Board::printBoard(Pacman pacman, Ghost ghosts[], const int ghosts_count)
{
	cout.flush();
	system("cls");

	for (int i = 0; i < BOARD_HIGHT; i++)
	{
		cout << board[i] << endl;
	}
	gotoxy(pacman.getinitLocation());
	cout << pacman.getCharacter();
	for (int i = 0; i < ghosts_count; i++) {
		gotoxy(ghosts[i].getinitLocation());
		cout << ghosts[i].getCharacter();
	}

	gotoxy((BOARD_WIDTH, BOARD_HIGHT));
	cout << "Lives: " << pacman.getLives() << " | Score: " << score << endl;
}


void Board::moveGhost(int ghost_count, Ghost& ghosts, Pacman pacman)
{

	gotoxy(ghosts.getLastLocation());
	if (getSquareChar(ghosts.getLocation().getX(), ghosts.getLocation().getY()) == breadcramp_character) {
		cout << breadcramp_character;
	}
	else if (getSquareChar(ghosts.getLocation().getX(), ghosts.getLocation().getY()) == wall_caracter) {

		ghosts.setLocation(ghosts.getLastLocation());

	}
	else if (getSquareChar(ghosts.getLocation().getX(), ghosts.getLocation().getY()) == magic_tunnel_character) {
		ghosts.setLocation(ghosts.getLastLocation());
	}

	else if (getSquareChar(ghosts.getLocation().getX(), ghosts.getLocation().getY()) == empty_spot) {
		cout << empty_spot;
	}

	int y = ghosts.getLocation().getY();
	int x = ghosts.getLocation().getX();

	ghosts.setRunOverBreadcramp(board[x][y] == breadcramp_character); //if the ghost is supposed to run over a breadcramp, ghage the falg to true, alse to false

	gotoxy(ghosts.getLocation()); //print current location
	cout << ghosts.getCharacter();


}

char& Board::getSquareChar(int x, int y) {
	return board[x][y];
}

void Board::movePacman(Pacman& pacman, diraction _diraction)
{

	gotoxy(pacman.getLastLocation());


	if (getSquareChar(pacman.getLocation().getX(), pacman.getLocation().getY()) == breadcramp_character) {
		score++;
		getSquareChar(pacman.getLocation().getX(), pacman.getLocation().getY()) = empty_spot;
		cout << empty_spot;
		gotoxy(pacman.getLocation());
		cout << pacman.getCharacter();

	}
	else if (getSquareChar(pacman.getLocation().getX(), pacman.getLocation().getY()) == wall_caracter) {

		pacman.setLocation(pacman.getLastLocation());
		gotoxy(pacman.getLocation());
		cout << pacman.getCharacter();

	}
	else if (getSquareChar(pacman.getLocation().getX(), pacman.getLocation().getY()) == empty_spot) {
		gotoxy(pacman.getLocation());
		cout << pacman.getCharacter();
		gotoxy(pacman.getLastLocation());
		cout << empty_spot;
	}
	else if (getSquareChar(pacman.getLocation().getX(), pacman.getLocation().getY()) == magic_tunnel_character) {

		if (pacman.getLocation().getX() == 0) {
			//pacman.getLocation().setX(20);
		}
		else {
			//pacman.getLocation().setX(1);
		}
	}



	gotoxy((BOARD_WIDTH, BOARD_HIGHT));
	cout << "Lives: " << pacman.getLives() << " | Score: " << score << endl;
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