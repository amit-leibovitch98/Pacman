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

void Board::printBoard(Pacman pacman)
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HIGHT; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << "Lives: " << pacman.getLives() << " | Score: " << getScore() << endl;
}

void Board::moveGhost(int ghost_count, Ghost ghosts[])
{
	static Location* ghostsLastPos = new Location[2];

	for (int i = 0; i < ghost_count; i++)
	{
		int x = ghostsLastPos[i].getX();
		int y = ghostsLastPos[i].getY();

		Game::gotoxy(x, y);

		if (ghosts[i].getRunOverBreadcramp()) //reprint last location
			cout << getBreadcrampCharacter();
		else
			cout << getEmptyspot();
		
		x = ghosts[i].getLocation().getX();
		y = ghosts[i].getLocation().getY();

		ghosts[i].setRunOverBreadcramp(board[x][y] == getBreadcrampCharacter()); //if the ghost is supposed to run over a breadcramp, ghage the falg to true, alse to false
		
		Game::gotoxy(x, y); //print current location
		cout << ghosts[i].getCharacter();
	}

	//make current position last position for the next move
	for (int i = 0; i < ghost_count; i++)
	{
		ghostsLastPos[i] = ghosts[i].getLocation();
	}
	
}

//void Board::movePacman(Pacman pacman, Location lastPos, Location newPos)
//{
//	board[lastPos.getX()][newPos.getY()] = ' ';
//	board[lastPos.getX()][newPos.getY()] = pacman.getCharacter();
//}

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