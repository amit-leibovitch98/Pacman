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

void Game::setLeftBreadcramps(int _left_breadcramps)
{
	left_breadcramps = _left_breadcramps;
}

int Game::getLeftBreadcramps()
{
	return left_breadcramps;
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
	bool collision = false;
	char currStep = _getch();
	Location lastLocationGhost;
	Location lastLocationPacman;

	diraction _diraction = caster(currStep);
	lastStep = _diraction;

	while (inProgress)
	{
		if (collision) {
			pacman.initPacmanLocation();
			ghosts[0].initGhostLocation(0);
			ghosts[1].initGhostLocation(1);
			board.printBoard(pacman, ghosts, GHOSTS_COUNT);
			currStep = _getch();
			_diraction = caster(currStep);
			lastStep = _diraction;
			collision = false;
		}
		else if (_kbhit()) {
			currStep = _getch();
			_diraction = caster(currStep);
			if (_diraction != ESC && _diraction != ERR && _diraction != STAY) {
				lastStep = _diraction;
			}
			else if (_diraction == STAY) {
				while (!_kbhit() && !collision) {
					board.gotoxy(pacman.getLocation());
					cout << pacman.getCharacter();
					Sleep(200);
					if (ghostPace == true) {
						for (int i = 0; i < GHOSTS_COUNT; i++)
						{
							ghosts[i].setLastLocation(ghosts[i].getLocation());
							ghosts[i].ghostMoveDecider();
							board.moveGhost(GHOSTS_COUNT, ghosts[i], pacman);
						}

					}

					collision = caseCollisionPacman();


					ghostPace = !ghostPace;
				}
				if (!collision) {
					currStep = _getch();
					_diraction = caster(currStep);
					lastStep = _diraction;
				}

			}
			else if (_diraction == ESC) {

				board.gotoxy((80, 23));
				cout << "Game Paused. Press ESC again to continue";
				while (!_kbhit() || _getch() != ESC) {}
				board.gotoxy((80, 23));
				cout << "                                         ";
			}

		}

		if (!collision) {
			pacman.setLastLocation(pacman.getLocation());
			pacman.getLocation().move(lastStep);
			board.movePacman(pacman, lastStep);
			collision = caseCollisionPacman();
			if (ghostPace == true) {
				for (int i = 0; i < GHOSTS_COUNT; i++)
				{
					ghosts[i].setLastLocation(ghosts[i].getLocation());
					ghosts[i].ghostMoveDecider();
					board.moveGhost(GHOSTS_COUNT, ghosts[i], pacman);
				}


			}
			if (!collision) {
				collision = caseCollisionPacman();
			}

			ghostPace = !ghostPace;
			checkGameStatus();

		}
	}



}



bool Game::caseCollisionPacman() {
	bool ans = false;
	if (pacman.getLocation().isEqual(ghosts[0].getLocation()) ||
		pacman.getLocation().isEqual(ghosts[1].getLocation())) {
		ans = true;
		pacman.liveDedaction();
	}
	return ans;
}

void Game::checkGameStatus()
{

	if (getLeftBreadcramps() == 0)
	{
		cout.flush();
		system("cls");
		cout << "You Win :)" << endl;
		inProgress = false;
	}
	else if (pacman.getLives() == 0)
	{
		cout.flush();
		system("cls");
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




