#include "Game.h"

Game::Game()
{
	Pacman _pacman(40, 11);
	pacman = _pacman;
	Ghost ghost1, ghost2;
	ghosts = new Ghost[2];
	ghosts[0] = ghost1;
	ghosts[1] = ghost2;
	inProgress = true;
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

void Game::start() {
	board.print();//later
	cout << "Press any move to start" << endl;

	//the condition for continuing the game
	while (inProgress)
	{
		pacmanMove();
	}

}

void Game::pacmanMove() 
{
	bool ghostPace = true;
	char currStep = step(getch());
	while (getInProgress() && ( !_kbhit() || !currStep))
	{
		if (currStep == ESC)
		{
			cout << "Game Paused. Press ESC again to continue" << endl;
			currStep = step(getch()); // expected esc again
		}
		if (ghostPace)
		{
			ghosts[0].ghostMove();
			ghosts[1].ghostMove();
			caseCollisionGhosts();
			//printboard
		}
		
		currStep = step(getch());
		ghostPace = !ghostPace;
		checkGameStatus();
	}
}

bool Game::checkGameStatus()
{

	if (pacman.getLive() == 0)
	{
		cout << "You Win :)" << endl;
		setInProgress(false);
	}
	else if (board.getNumberOfBread() == 0)
	{
		cout << "You Lose :(" << endl;
		setInProgress(false);
	}
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
	if (ghosts[0].getLocation() == ghosts[1].getLocation())
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
	if (pacman.getLocation() == ghosts[0].getLocation() || pacman.getLocation() == ghosts[1].getLocation())
	{
		pacman.liveDedaction();
		pacman.initPacmanLocation();
	}

	//case wall
}


