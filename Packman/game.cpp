#include "Game.h"

int Game::getGhostCount()
{
	return GHOSTS_COUNT;
}

Pacman Game::getPacman()
{
	return pacman;
}

void Game::setPacman(Pacman _pacman)
{
	pacman = _pacman;
}

void Game::setInProgress(bool _inProgress)
{
	inProgress = _inProgress;
}

bool Game::getInProgress()
{
	return inProgress;
}



void Game::run()
{
	int input;
	cout << "Please enter the following option: " << endl;
	cout << "(1) Start a new game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;

	cin >> input;

	if (input == 1)
	{
		start();
	}
	else if (input == 8)
	{
		//printInstruction();
	}

}

void Game::start()
{

	board.printBoard(pacman, ghosts, GHOSTS_COUNT);
	bool ghostPace = true;
	char currStep = _getch();
	Location lastLocationGhost;
	Location lastLocationPacman;

	diraction _diraction = caster(currStep);

	while (inProgress)
	{
		if (_kbhit()) {
			currStep = _getch();
			_diraction = caster(currStep);
		}
		if (_diraction != ESC || _diraction != ERR) {
			lastLocationPacman = pacman.getLocation();
			pacman.getLocation().move(_diraction);
			board.movePacman(pacman, _diraction, lastLocationPacman);
			//caseCollisionPacman();
			if (ghostPace == true) {
				for (int i = 0; i < GHOSTS_COUNT; i++)
				{
					lastLocationGhost = ghosts[i].getLocation();
					ghosts[i].ghostMoveDecider();
					board.moveGhost(GHOSTS_COUNT, ghosts, lastLocationGhost);
				}

				caseCollisionGhosts();
			}
			caseCollisionPacman();
			ghostPace = !ghostPace;
			if (board.getLeftBreadcramps() == 0)
				gameWon();

		}
		else
		{
			//cout << "Game Paused. Press ESC again to continue" << endl;
			//currStep = caster(_getch()); // expected esc again
		}
	}

}



void Game::checkGameStatus()
{

	if (board.getLeftBreadcramps() == 0)
	{
		cout << "You Win :)" << endl;
		inProgress = false;
	}
	else if (pacman.getLives() == 0)
	{
		cout << "You Lose :(" << endl;
		inProgress = false;

	}

}

diraction Game::caster(char ch)
{
	diraction ans = ERR;

	if (ch == 'a' || ch == 'A') //left
	{
		ans = LEFT;
	}
	else if (ch == 'd' || ch == 'D') //right
	{
		ans = RIGHT;
	}
	else if (ch == 'w' || ch == 'W') //up
	{
		ans = UP;
	}
	else if (ch == 'x' || ch == 'X') //down
	{
		ans = DOWN;
	}
	else if (ch == 's' || ch == 'S') //stay
	{
		ans = STAY;
	}
	else if (ch == 27) //ESC
	{
		ans = ESC;
	}

	return ans;
}

void Game::caseCollisionGhosts()
{
	Location lastLocationGhost;
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
	bool lost = false;
	for (int i = 0; i < GHOSTS_COUNT && !lost; i++)
	{
		if (pacman.getLocation().isEqual(ghosts[i].getLocation()))
		{
			pacman.liveDedaction();
			pacman.initPacmanLocation();
			for (int i = 0; i < GHOSTS_COUNT; i++)
			{
				ghosts[i].initLocation();
			}
			lost = true;
		}
	}
	if (pacman.getLives() == 0)
		gameLost();
}

void Game::gameLost()
{
	cout << "You Lose!  :(" << endl;
	 inProgress = !inProgress;
}

void Game::gameWon()
{
	cout << "You Won!  :)" << endl;
	inProgress = !inProgress;
}

