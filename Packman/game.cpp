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

void Game::printMenu()
{
	system("cls");
	if (COLORS)
	{
		//"\x1B[31m       \033[0m\t\t"
		cout << "\x1B[95mPlease enter the following option: \033[0m\t\t" << endl;
		cout << "\x1B[92m(1) Start a new game\033[0m\t\t" << endl;
		cout << "\x1B[94m(8) Present instructions and keys\033[0m\t\t" << endl;
		cout << "\x1B[91m(9) EXIT\033[0m\t\t" << endl;
	}
	else
	{
		cout << "Please enter the following option: " << endl;
		cout << "(1) Start a new game" << endl;
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl;
	}
}

void Game::printInstruction()
{
	if (COLORS)
	{
		cout << "\x1B[92m               W- Up                \033[0m\t\t" << endl;
		cout << "\x1B[92m    A- Left             D- Right   \033[0m\t\t" << endl;
		cout << "\x1B[92m              X- Down               \033[0m\t\t" << endl;
		cout << "\x1B[92m              S- Stay               \033[0m\t\t" << endl;
		cout << "\n" << endl;
		cout << "\x1B[92m          ESC- pause game  \033[0m\t\t" << endl;
		cout << "\n" << endl;
		cout << "\x1B[95mMust eat all the breadcramps inside an enclosed maze while avoiding two colored ghosts.  \033[0m\t\t" << endl;
		cout << "\x1B[95mIf you encountered a ghost- ypu will lose a live. Be carfull! You only have 3!  \033[0m\t\t" << endl;
		cout << "\033[3;107;95mWin by eating all of the breadcramps! Good Luck!  \033[0m\t\t" << endl;
		cout << "\n" << endl;
		cout << "\x1B[94mPress (7) to go back to Menu.  \033[0m\t\t" << endl;


	}
	else
	{
		cout << "          W- up                " << endl;
		cout << "A- Left              D- Right  " << endl;
		cout << "         X- Down               " << endl;
		cout << "         S- stay               " << endl;
		cout << "\n" << endl;
		cout << "ESC- pause game  \033[0m\t\t" << endl;

		cout << "Must eat all the breadcramps inside an enclosed maze while avoiding two colored ghosts. " << endl;
		cout << "If you encountered a ghost- ypu will lose a live. Be carfull! You only have 3!  " << endl;
		cout << "Win by eating all of the breadcramps! Good Luck!  " << endl;

		cout << "Press (8) to go back to Menu.";
	}
}

void Game::run()
{
	bool exit = false;
	int input;
	
	printMenu();

	cin >> input;

	while (input != 1 && !exit)
	{
		if (input == 8)
			printInstruction();
		else if (input == 9)
			exit = true;
		else if (input == 7)
			printMenu();
		cin >> input;
		system("cls");
	}

	if(!exit)
		start();
}

void Game::start()
{

	board.printBoard(pacman, ghosts, GHOSTS_COUNT, COLORS);
	bool ghostPace = true;
	bool collision = false;
	char currStep = _getch();
	Location lastLocationGhost;
	Location lastLocationPacman;

	diraction _diraction = caster(currStep);
	lastStep = _diraction;

	while (inProgress)
	{
		if (collision) 
		{
			pacman.initPacmanLocation();
			ghosts[0].initGhostLocation(0);
			ghosts[1].initGhostLocation(1);
			board.printBoard(pacman, ghosts, GHOSTS_COUNT, COLORS);
			currStep = _getch();
			_diraction = caster(currStep);
			lastStep = _diraction;
			collision = false;
		}
		else if (_kbhit()) 
		{
			currStep = _getch();
			_diraction = caster(currStep);
			if (_diraction != ESC && _diraction != ERR && _diraction != STAY) 
			{
				lastStep = _diraction;
			}
			else if (_diraction == STAY) 
			{
				while (!_kbhit() && !collision) {
					board.gotoxy(pacman.getLocation());
					board.printPacman(pacman.getCharacter(), COLORS);
					Sleep(150);
					if (ghostPace == true) {
						for (int i = 0; i < GHOSTS_COUNT; i++)
						{
							ghosts[i].setLastLocation(ghosts[i].getLocation());
							ghosts[i].ghostMoveDecider();
							board.moveGhost(GHOSTS_COUNT, ghosts[i], pacman, COLORS);
						}

					}

					collision = caseCollisionPacman();

					ghostPace = !ghostPace;
				}
				if (!collision) 
				{
					currStep = _getch();
					_diraction = caster(currStep);
					lastStep = _diraction;
				}

			}
			else if (_diraction == ESC) 
			{

				board.gotoxy((80, 23));
				cout << "Game Paused. Press ESC again to continue";
				while (!_kbhit() || _getch() != ESC) {}
				board.gotoxy((80, 23));
				cout << "                                         ";
			}

		}

		if (!collision) 
		{
			pacman.setLastLocation(pacman.getLocation());
			pacman.getLocation().move(lastStep);
			board.movePacman(pacman, lastStep, COLORS);
			collision = caseCollisionPacman();
			if (ghostPace == true) {
				for (int i = 0; i < GHOSTS_COUNT; i++)
				{
					ghosts[i].setLastLocation(ghosts[i].getLocation());
					ghosts[i].ghostMoveDecider();
					board.moveGhost(GHOSTS_COUNT, ghosts[i], pacman, COLORS);
				}


			}
			if (!collision)
			{
				collision = caseCollisionPacman();
			}

			ghostPace = !ghostPace;
			checkGameStatus();

		}
	}



}



bool Game::caseCollisionPacman()
{
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

	if (board.getScore() == board.getBREADCRAMPS_NUM())
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




