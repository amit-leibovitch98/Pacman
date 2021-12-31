#include "Game.h"

bool Game::endswith(string file_name)
{
	string suffix = "screen";
	return file_name.size() >= suffix.size() && 0 == file_name.compare(file_name.size() - suffix.size(), suffix.size(), suffix);

}

vector<string> Game::loadFiles()
{
	string prefix = "/.";
	vector<string> screen_files;

	for (const auto& file : fs::directory_iterator("."))
		if (endswith(file.path().string()))
			screen_files.push_back(file.path().string());


	if (screen_files.size() < 3)
		cout << "There are not enough board files on diractory (less then 3)" << endl;
	else
	{
		for (auto i = screen_files.begin(); i != screen_files.end(); i++)
		{
			string file_name = i->substr(prefix.length());
		}
	}

	return screen_files;
}

int Game::getGhostCount()
{
	return ghosts.size();
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

int Game::printMenu()
{
	system("cls");
	int input;
	if (COLORS)
	{
		//"\x1B[31m       \033[0m\t\t"
		cout << "\x1B[95mPlease enter the following option: \033[0m\t\t" << endl;
		cout << "\x1B[92m(1) Start a new game\033[0m\t\t" << endl;
		cout << "\x1B[93m(2) Run only one board\033[0m\t\t" << endl;
		cout << "\x1B[96m(8) Present instructions and keys\033[0m\t\t" << endl;
		cout << "\x1B[91m(9) EXIT\033[0m\t\t" << endl;
	}
	else
	{
		cout << "Please enter the following option: " << endl;
		cout << "(1) Start a new game" << endl;
		cout << "(2) Run only one board" << endl;
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl;

	}
	cin >> input;
	return input;
}

void Game::printInstruction()
{
	system("cls");

	if (COLORS)
	{
		cout << "\n" << endl;
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
		cout << "\n" << endl;
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

void Game::printLevels(bool COLORS)
{
	system("cls");

	if (COLORS)
	{
		cout << "\x1B[95mPlease enter the following level: \033[0m\t\t" << endl;
		cout << "\x1B[92m(a) BEST\033[0m\t\t" << endl;
		cout << "\x1B[94m(b) BEST\033[0m\t\t" << endl;
		cout << "\x1B[91m(c) NOVICE\033[0m\t\t" << endl;
	}
	else
	{
		cout << "Please enter the following level: " << endl;
		cout << "(a) BEST" << endl;
		cout << "(b) GOOD" << endl;
		cout << "(c) NOVICE" << endl;
	}

}
void Game::choseBoard(vector<string> screen_file) {
	system("cls");
	char input;
	cout << "Please chose the following board: " << endl;
	cout << "(a) pacman_a" << endl;
	cout << "(b) pacman_b" << endl;
	cout << "(c) pacman_c" << endl;
	cin >> input;
	if (input == 'a') {
		run(screen_file[0], 2);
	}
	else if (input == 'b') {
		run(screen_file[1], 2);
	}
	else if (input == 'c') {
		run(screen_file[2], 2);
	}

}

void Game::run(string file_name, int input)
{
	bool exit_game = false;

	ifstream board_file;
	board_file.open(file_name);

	if (!board_file)
	{
		cout << "Error with infile" << endl;
		exit(-1);
	}

	board.fileToMatrix(board_file, '$', pacman, ghosts);

	board_file.close();

	while (input != 1 && input != 2 && !exit_game)
	{
		if (input == 8)
			printInstruction();
		else if (input == 9)
			exit_game = true;
		else if (input == 7)
			printMenu();
		cin >> input;
	}
	

	if (!exit_game)
	{
		if (!res) {
			char level;
			printLevels(COLORS);
			cin >> level;
			//CREATE HERE THE STRATEGY OF MOVING GHOSTS and pass it as parameter to game
			Location pacmanLoc = pacman.getCurrLocation();
			if (level == 'a') {

				strategy = new GhostMoveStrategyA(pacmanLoc, &board);
			}
			else if (level == 'b') {
				strategy = new GhostMoveStrategyB(pacmanLoc, &board);
			}
			else {
				strategy = new GhostMoveStrategyC(pacmanLoc, &board);
			}
		}
		
		board.printBoard(pacman, ghosts, COLORS);
		start();
	}

}

void Game::start()
{
	int till_fruit_appear = 0;
	int fruit_pace = 0;
	bool ghostPace = true;
	bool collision = false;

	char currStep = _getch();
	//
	ofstream file1;
	file1.open("file1.txt");
	int curr_diraction_step_count = 0;
	file1 << "p " << currStep << " ";
	//

	Location lastLocationGhost;
	Location lastLocationPacman;
	diraction _diraction = caster(currStep);
	pacman.setCurrDiraction(_diraction);


	while (inProgress)
	{

		if (collision)
		{
			//if the pacman meet ghost
			pacman.initLocations(pacman.getinitLocation());
			for (int i = 0; i < ghosts.size(); i++) {
				ghosts[i].initLocations(ghosts[i].getinitLocation());
			}
			board.printBoard(pacman, ghosts, COLORS);
			currStep = _getch();
			_diraction = caster(currStep);
			collision = false;
		}
		else if (_kbhit())
		{
			currStep = _getch();
			_diraction = caster(currStep);
			pacman.setCurrDiraction(_diraction);
			//
			file1 << curr_diraction_step_count << endl;
			curr_diraction_step_count = 0;
			file1 << "p " << currStep << " ";
			//
			if (_diraction != ESC && _diraction != ERR && _diraction != STAY)
			{
				pacman.setCurrDiraction(_diraction);
			}
			else if (_diraction == STAY)
			{
				while (!_kbhit() && !collision)
				{
					board.gotoxy(pacman.getCurrLocation());
					board.printPacman(pacman, COLORS);
					Sleep(150);
					if (ghostPace == true)
					{
						for (int i = 0; i < ghosts.size(); i++)
						{
							strategy->getPacmanLocation() = pacman.getCurrLocation();
							ghosts[i].setLastLocation(ghosts[i].getCurrLocation());
							strategy->moveAlghorithm(ghosts[i], countPaces);
							board.moveGhost(ghosts[i], pacman, COLORS);
						}
					}
					collision = caseCollisionPacman();
					ghostPace = !ghostPace;
				}
				if (!collision)
				{
					currStep = _getch();
					_diraction = caster(currStep);
					pacman.setCurrDiraction(_diraction);

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
			//
			curr_diraction_step_count++;
			//
			

			//the game continue regullary
			pacman.setLastLocation(pacman.getCurrLocation());
			pacman.move();
			board.movePacman(pacman, COLORS);
			collision = caseCollisionPacman();
			if (ghostPace == true)
			{
				for (int i = 0; i < ghosts.size(); i++)
				{
					strategy->getPacmanLocation() = pacman.getCurrLocation();
					ghosts[i].setLastLocation(ghosts[i].getCurrLocation());
					strategy->moveAlghorithm(ghosts[i], countPaces);
					board.moveGhost(ghosts[i], pacman, COLORS);
				}
				fruit_pace++;
			}
			if (!collision)
			{
				collision = caseCollisionPacman();
			}
			if (till_fruit_appear == 20)
			{
				//the case that fruit appears on the board
				fruitMode = true;
				randomLocation();
				board.moveFruit(fruit, ghosts, pacman.getCurrLocation(), COLORS);
			}
			if (fruitMode && ghostPace)
			{
				fruit.setLastLocation(fruit.getCurrLocation());
				fruit.move();
				board.moveFruit(fruit, ghosts, pacman.getCurrLocation(), COLORS);
				Sleep(200);
			}
			if (till_fruit_appear > 20 && fruit_pace % 5 == 0)
			{
				//the case that fruit disapperas
				fruitMode = false;
				board.gotoxy(fruit.getCurrLocation());
				cout << board.getBoard()[fruit.getCurrLocation().getX()][fruit.getCurrLocation().getY()];
				fruit_pace = 0;
				till_fruit_appear = 0;
			}
			if (fruit.getMeetGhost() || fruit.getMeetPacman())
				fruitMode = false;

			ghostPace = !ghostPace;
			checkGameStatus();
		}

		if (countPaces == 25)
			countPaces = 0;
		countPaces++;

		till_fruit_appear++;
	}

	file1 << countPaces <<endl;
	file1.close();
}



Location& Game::randomLocation()
{

	int randomX = rand() % (board.getBoardHight() - 5) + 1;
	int randomY = rand() % (board.getBoardWidth() - 5) + 1;

	while (board.outOfRange(randomX, randomY) || (board.getBoard()[randomX][randomY] == '#' || board.getBoard()[randomX][randomY] == '|')) 
	{
		randomX = rand() % (board.getBoardHight() - 5) + 1;
		randomY = rand() % (board.getBoardWidth() - 5) + 1;
	}

	Location fruitLoc(randomX, randomY);
	fruit.setCurrLocation(fruitLoc);
	int randomDigit = rand() % 5 + 53;
	fruit.getCharacter() = randomDigit;
	return fruitLoc;

}

bool Game::caseCollisionPacman()
{
	bool ans = false;
	for (int i = 0; i < ghosts.size() && !ans; i++) {
		if (pacman.getCurrLocation() == (ghosts[i].getCurrLocation())) {
			ans = true;
			pacman.liveDedaction();
		}
	}

	return ans;
}

void Game::checkGameStatus()
{
	if (board.getBREADCRAMPS_NUM() == 0)
	{
		cout.flush();
		system("cls");
		cout << "You Win :)" << endl;
		inProgress = false;
		cout << "To continue press any key" << endl;
		_getch();
		system("cls");
	}
	else if (pacman.getLives() == 0)
	{
		cout.flush();
		system("cls");
		cout << "You Lose :(" << endl;
		cout << "To continue press any key" << endl;
		inProgress = false;
		_getch();
		system("cls");
	}
	
}
void Game::restart() {
	inProgress =true;
	res = true;
	board.setScore(0);
	pacman.setLives(3);
	while (!ghosts.empty()) {
		ghosts.pop_back();
	}
	while (!board.getBoard().empty()) {
		board.getBoard().pop_back();
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
	if (ghosts[0].getCurrLocation() == (ghosts[1].getCurrLocation()))
	{
		if (ghosts[0].getCurrDiraction() == RIGHT)
		{
			ghosts[0].getCurrLocation().moveRight();
		}
		else if (ghosts[0].getCurrDiraction() == LEFT)
		{
			ghosts[0].getCurrLocation().moveLeft();
		}
		else if (ghosts[0].getCurrDiraction() == UP)
		{
			ghosts[0].getCurrLocation().moveUp();
		}
		else if (ghosts[0].getCurrDiraction() == DOWN)
		{
			ghosts[0].getCurrLocation().moveDown();
		}
	}

}
