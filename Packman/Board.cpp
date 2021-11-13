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

	for (int i = 0; i < BOARD_HIGHT ; i++)
	{
		cout << board[i]<<endl;
	}
	gotoxy(pacman.getLocation());
	cout << pacman.getCharacter();
	for (int i = 0; i < ghosts_count; i++)
		gotoxy(ghosts[i].getLocation());
	cout << "Lives: " << pacman.getLives() << " | Score: " << getScore() << endl;
}

void Board::moveGhost(int ghost_count, Ghost ghosts[])
{
	static Location* ghostsLastPos = new Location[2];

	for (int i = 0; i < ghost_count; i++)
	{
		gotoxy(ghostsLastPos[i]);

		if (ghosts[i].getRunOverBreadcramp()) //reprint last location
			cout << getBreadcrampCharacter();
		else
			cout << getEmptyspot();
		
		int y = ghosts[i].getLocation().getY();
		int x = ghosts[i].getLocation().getX();

		ghosts[i].setRunOverBreadcramp(board[x][y] == getBreadcrampCharacter()); //if the ghost is supposed to run over a breadcramp, ghage the falg to true, alse to false
		
		gotoxy(ghosts[i].getLocation()); //print current location
		cout << ghosts[i].getCharacter();
	}

	//make current position last position for the next move
	for (int i = 0; i < ghost_count; i++)
	{
		ghostsLastPos[i] = ghosts[i].getLocation();
	}
	
}

void Board::movePacman(Pacman pacman, diraction _diraction)
{
	static Location last_location = pacman.getLocation();
	
	gotoxy(last_location);
	cout << getEmptyspot();

	gotoxy(pacman.getLocation());
	if (board[pacman.getLocation().getX()][pacman.getLocation().getY()] == getBreadcrampCharacter())
		score++;

	cout << pacman.getCharacter();
}

int Board::countBreadcramps()
{
	int count = 0;
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HIGHT; j++)
		{
			if (board[i][j] == getBreadcrampCharacter())
				count++;
		}
	}
	return count;
}

void Board::gotoxy(Location location)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = location.getX();
	dwCursorPosition.Y = location.getY();
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}