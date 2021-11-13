#include "Game.h"

int Game::getGhostCount()
{
	return GHOSTS_COUNT;
}

Pacman Game::getPacman()
{
	return pacman;
}

void Game::setInProgress(bool _inProgress)
{
	inProgress = _inProgress;
}

bool Game::getInProgress()
{
	return inProgress;
}

void Game:: setLeftBreadcramps(int _left_breadcramps)
{
	left_breadcramps = _left_breadcramps;
}

int Game::getLeftBreadcramps()
{
	return left_breadcramps;
}

void Game::run() 
{
	char ch;
	cout << "Please enter the following option: " << endl;
	cout << "(1) Start a new game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;

	cin >> ch;

	if (ch == 1) {
		start();
	}
	else if (ch == 8) {
		printInstruction();
	}

}

void Game::start() 
{
	board.printBoard(getPacman());
	cout << "Press any move to start" << endl;

	//the condition for continuing the game
	while (inProgress)
	{
		move();
	}

}
void Game::move() 
{
	bool ghostPace = true;
	char currStep = step(_getch());
	while (getInProgress() && (!_kbhit() || !currStep))
	{
		if (currStep == ESC)
		{
			cout << "Game Paused. Press ESC again to continue" << endl;
			currStep = step(_getch()); // expected esc again
		}
		if (ghostPace)
		{
			ghosts[0].ghostMoveDecider();
			ghosts[1].ghostMoveDecider();
			caseCollisionGhosts();
			//printboard
		}

		currStep = step(_getch());
		ghostPace = !ghostPace;
		checkGameStatus();
	}
}

bool Game::checkGameStatus()
{

	if (pacman.getLives() == 0)
	{
		cout << "You Win :)" << endl;
		inProgress = false;
	}
	else if (board.countBreadcramps() == 0)
	{
		cout << "You Lose :(" << endl;
		inProgress = false;

	}
	return inProgress;
}

char Game::step(char ch)
{
	char ans = 0;
	if (ch == 'a' || ch == 'A') //left
	{
		ans = 'a';
	}
	else if (ch == 'd' || ch == 'D') //right
	{
		ans = 'd';
	}
	else if (ch == 'w' || ch == 'W') //up
	{
		ans = 'w';
	}
	else if (ch == 'x' || ch == 'X') //down
	{
		ans = 'x';
	}
	else if (ch == 's' || ch == 'S') //stay
	{
		ans = 's';
	}
	else if (ch == 27) //ESC
	{
		ans = 27;
	}
	return ans;
}

void Game::caseCollisionGhosts()
{
	if (ghosts[0].getLocation().isEqual(ghosts[1].getLocation()))
	{
		if (ghosts[0].getCurrDiraction() == RIGHT)
		{
			ghosts[0].getLocation().moveRight();
		}
		else if (ghosts[0].getCurrDiraction() == LEFT)
		{
			ghosts[0].getLocation().moveLeft();
		}
		else if (ghosts[0].getCurrDiraction() == UP)
		{
			ghosts[0].getLocation().moveUp();
		}
		else if (ghosts[0].getCurrDiraction() == DOWN)
		{
			ghosts[0].getLocation().moveDown();
		}
	}
}

void Game::caseCollisionPacman()
{
	//case ghost
	if (pacman.getLocation().isEqual(ghosts[0].getLocation()) || pacman.getLocation().isEqual(ghosts[1].getLocation()))
	{
		pacman.liveDedaction();
		pacman.initPacmanLocation();
	}

	//case wall
}

void Game:: gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}